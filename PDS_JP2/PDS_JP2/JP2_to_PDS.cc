/*	JP2_to_PDS

HiROC CVS ID: JP2_to_PDS.cc,v 1.21 2013/01/29 19:06:32 guym Exp

Copyright (C) 2007 Arizona Board of Regents on behalf of the
Planetary Image Research Laboratory, Lunar and Planetary Laboratory at
the University of Arizona.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License, version 2, as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include	"Dimensions.hh"
using UA::HiRISE::Size_2D;
//using UA::HiRISE::Rectangle;

#include	"PDS_Converters.hh"
using UA::HiRISE::converter_for;
using UA::HiRISE::PDS_Converter;
using UA::HiRISE::Image_Data_Block;

#include	"JP2_Decoder.hh"
using UA::HiRISE::JP2_Decoder;

#include	"Files.hh"
#include	"endian.hh"
using namespace PIRL;

#include	<iostream>
#include	<iomanip>
#include	<cstdlib>
#include	<fstream>
#include	<sstream>
#include	<cctype>
#include	<string>
#include	<cstring>
#include	<vector>
#include	<utility>
#include	<stdexcept>
using namespace std;

/*==============================================================================
	Parameters
*/
//!	The default filename extension for the JPEG2000 JP2 file.
const char * const
	JP2_EXTENSION				= ".JP2";

//!	The default filename extension for the PDS/JP2 label file.
const char * const
	LABEL_EXTENSION				= ".LBL";

//!	The default filename extension for the PDS file.
const char * const
	PDS_IMAGE_EXTENSION			= ".IMG";

/**	The default data order if it can't be determined from the source.

	Positive is MSB; negative is LSB.
*/
const int
	DEFAULT_DATA_ORDER			= 1;


//!	Exit status values.
const int
	SUCCESS						= 0,

	//	Command line syntax.
	BAD_SYNTAX					= 1,

	//	Software / data problem.
	INVALID_ARGUMENT			= 11,
	PDS_LABEL_ERROR				= 12,
	NO_IMAGE_DATA				= 13,
	LABEL_INCONSISTENCY			= 14,
	LOGIC_ERROR					= 19,

	//	IO.
	NO_INPUT_FILE				= 20,
	EXISTING_OUTPUT_FILE		= 21,
	IO_FAILURE					= 29,

	//	PVL.
	PVL_ERROR					= 30,

	//	JP2 Decoder.
	DECODER_ERROR				= JP2_Decoder::DECODER_EXCEPTION,

	//	Unknown?
	UNKNOWN_ERROR				= -1;

/*==============================================================================
	Constants
*/
#ifndef MODULE_VERSION
#define _VERSION_ " "
#else
#define _VERSION_ " v" MODULE_VERSION " "
#endif
//!	Application identification name with source code version and date.
const char
	*ID =
		"JP2_to_PDS"
		_VERSION_
		"(1.21 2013/01/29 19:06:32)";

//!	The label parameter to have its value set to the ID.
const char
	*SOFTWARE_NAME_PARAMETER	= "SOFTWARE_NAME";

//!	The runtime command name.
char
	*Program_Name;

#ifndef FILESYSTEM_PATHNAME_DELIMITER
#define FILESYSTEM_PATHNAME_DELIMITER		'/'
#endif
//!	Host filesystem pathname delimiter.
const char
	PATHNAME_DELIMITER			= FILESYSTEM_PATHNAME_DELIMITER;

//!	Listing format widths.
const int
	LABEL_WIDTH							= 24,
	VALUE_WIDTH							= 9;

/*==============================================================================
	Usage
*/
/** JP2_to_PDS command line syntax and usage.

	<h3>Command line syntax:
	</h3>

	<b>JP2_to_PDS</b> [<i>Options</i>] [-Input | -Jp2] &lt;<i>pathname</i>&gt;

	<h3>Command line options:
	</h3>

	<h4><b>-I</b>nput | <b>-J</b>p2 &lt;<i>pathname</i>&gt;
	</h4>
	The pathname of the input JP2 file.

	Default: The PDS label file pathname with a #JP2_EXTENSION.

	<h4><b>-LA</b>bel &lt;<i>pathname</i>&gt;
	</h4>
	The pathname of the input PDS label file.

	Default: The JP2 source PDS label URL if present or the input JP2
	pathname with a #LABEL_EXTENSION.

	<h4><b>-O</b>utput | <b>-P</b>ds &lt;<i>pathname</i>&gt;
	</h4>
	The pathname of the output PDS file.

	Default: The input JP2 file pathname with a #PDS_IMAGE_EXTENSION.

	<h4><b>-N</b>o_output
	</h4>
	No ouput file will be written. The input files will be examined and
	prepared for conversion with all the reports listed. This is a
	convenient way to see the source file structure and check that the
	expected output will be produced without having to process the
	files.

	Default: Output is produced.

	<h4><b>-F</b>orce
	</h4>
    If the output file already exists, it will be overwritten.

    Default: Do not overwrite an existing file.

	<h4><b>-A</b>rea &lt;<i>origin_x</i>&gt;<b>,</b>&lt;<i>origin_y</i>&gt;<b>,</b>&lt;<i>extent_x</i>&gt;<b>,</b>&lt;<i>extent_y</i>&gt;
	</h4>
	An area of the image to be selected for decompression. The area
	is specified relative to the image at full resolution, before any
	resolution level selection size reduction is applied.  If the
	area selected extends beyond the width (x) or height (y) of the
	image size the area is clipped to corresponding limit. If the
	origin of the area falls outside the image boundaries no output
	will be generated; an empty image will not be produced.

	Default: The entire image.

	<h4><b>-R</b>esolution &lt;<i>level</i>&gt;
	</h4>
	The JPEG2000 codestream may provide access to the image at
	multiple resolution levels. The image is always available at full
	resolution; level 1. The next level is half resolution, then half
	of that, etc.; i.e. the effective image size at resolution level
	L is the full resolution size divided by 2**(L-1). If the
	selected resolution level is greater than the number of
	resolution levels available in the JP2 source codestream the
	image will be rendered at the smallest size.

	Default: Full resolution level 1.

	<h4><b>-L</b>sb | <b>-M</b>sb
	</h4>
	Normally the image data values are treated as MSB or LSB ordered
	based on information from the source PDS label file: If the
	<code>SAMPLE_TYPE</code> parameter is present and its value contains
	the "MSB" string, the image data is treated as MSB ordered; if the
	value contains the "LSB" string the data is treated as LSB ordered.
	This option determines the effective byte order of multi-byte image
	data values regardless of the PDS label parameter value.

	Default: Pixel data of unknown data order is MSB.

	<h4><b>-H</b>elp
	</h4>
		Prints this usage description.

	@param	exit_status	This method always result in program exit. If the
		exit status value is not specified the #BAD_SYNTAX value will be used.
	@param	list_descriptions	If true, long option descriptions will be
		listed; otherwise only the brief option syntax is listed.
	@see	main(int, char**)
*/
void
usage
	(
	int		exit_status = BAD_SYNTAX,
	bool	list_descriptions = false
	)
{
cout
	<< "Usage: " << Program_Name << " [options] [-Input | -Jp2] <pathname>" << endl;
if (list_descriptions)
	cout
	<< endl
	<< "Converts a JP2 file with a detached PDS label file to a PDS file" << endl
	<< "with a label attached to uncompressed image data." << endl
	<< endl;

cout
	<< "Options -" << endl;

cout
	<< "  -Input | -Jp2 <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    The pathname of the input JP2 file." << endl
	<< endl
	<< "    Default: The input PDS label file pathname with a "
		<< JP2_EXTENSION << " extension." << endl
	<< endl;

cout
	<< "  -LAbel <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    The pathname of the input PDS/JP2 label file." << endl
	<< endl
	<< "    Default: The JP2 source PDS label URL if present" << endl
	<< "             or the input JP2 pathname with a "
		<< LABEL_EXTENSION << " extension." << endl
	<< endl;

cout
	<< "  -Output | -Pds <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    The pathname of the output PDS file." << endl
	<< endl
	<< "    Default: The JP2 pathname with a "
		<< PDS_IMAGE_EXTENSION << " extension." << endl
	<< endl;

cout
	<< "  -No_output" << endl;
if (list_descriptions)
	cout
	<< "    No ouput file will be written. The input files will be examined" << endl
	<< "    and prepared for conversion with all the reports listed. This is" << endl
	<< "    a convenient way to see the source file structure and check that" << endl
	<< "    the expected output will be produced without having to process" << endl
	<< "    the files." << endl
	<< endl
	<< "    Default: Output is produced." << endl
	<< endl;

cout
	<< "  -Force" << endl;
if (list_descriptions)
	cout
	<< "    If the output file already exists, it will be overwritten." << endl
	<< endl
	<< "    Default: Do not overwrite an existing file." << endl
	<< endl;

cout << "  -Area <origin_x>,<origin_y>,<extent_x>,<extent_y>" << endl;
if (list_descriptions)
	cout
	<< "    An area of the image to be selected for decompression. The area" << endl
	<< "    is specified relative to the image at full resolution, before any" << endl
	<< "    resolution level selection size reduction is applied.  If the" << endl
	<< "    area selected extends beyond the width (x) or height (y) of the" << endl
	<< "    image size the area is clipped to corresponding limit. If the" << endl
	<< "    origin of the area falls outside the image boundaries no output" << endl
	<< "    will be generated; an empty image will not be produced." << endl
	<< endl
	<< "    Default: The entire image." << endl
	<< endl;

cout << "  -Resolution <level>" << endl;
if (list_descriptions)
	cout
	<< "    The JPEG2000 codestream may provide access to the image at multiple" << endl
	<< "    resolution levels. The image is always available at full resolution;" << endl
	<< "    level 1. The next level is half resolution, then half of that, etc.;" << endl
	<< "    i.e. the effective image size at resolution level L is the full" << endl
	<< "    resolution size divided by 2**(L-1). If the selected resolution level" << endl
	<< "    is greater than the number of resolution levels available in the JP2" << endl
	<< "    source codestream the image will be rendered at the smallest size." << endl
	<< endl
	<< "    Default: Full resolution level 1." << endl
	<< endl;

cout
	<< "  -Lsb | -Msb" << endl;
if (list_descriptions)
	cout
	<< "    Normally the image data values are treated as MSB or LSB ordered" << endl
	<< "    based on information from the source PDS/JP2 label file: If the" << endl
	<< "    SAMPLE_TYPE parameter is present and its value contains the" << endl
	<< "    \"MSB\" string, the image data is treated as MSB ordered; if the" << endl
	<< "    value contains the \"LSB\" string the data is treated as LSB ordered." << endl
	<< "    This option determines the effective byte order of the image data" << endl
	<< "    values regardless of the PDS label parameter value." << endl
	<< endl
	<< "    Default: Pixel data of unknown data order is "
		<< (DEFAULT_DATA_ORDER ? "MSB" : "LSB") << '.' << endl
	<< endl;

cout
	<< "  -Help" << endl;
if (list_descriptions)
	cout
	<< "    Prints this usage description." << endl
	<< endl;

exit (exit_status); 
}

#if defined (DEBUG)
/*******************************************************************************
	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL		-1
#define DEBUG_HELPERS	(1 << 4)
#include	<iostream>
using std::clog;
#endif  // DEBUG

/*==============================================================================
	Main
*/
/**	JP2_to_PDS application.

	Converts a JP2 image data file with a detached PDS label file to a PDS
	image file having a label attached to uncompressed image data.

	<h3>Files:
	</h3>

	An input JP2 file and associated PDS label file are required. If
	only a -Label pathname is provided it is used to determine the JP2
	file pathname by replacing the extension, if any, with the
	#JP2_EXTENSION. If the -Label pathname is not specified it is
	determined from the JP2 PDS label URL. If no URL is found the label
	file pathname is determined by replacing the JP2 file pathname
	extension, if any, with the #LABEL_EXTENSION. If no -Output pathname
	for the PDS file is specified it is determined by replacing the JP2
	pathname extension, if any, with the #PDS_IMAGE_EXTENSION. If a file
	at the output pathname exists and the -Force option has not been
	specified the program will exit (with #EXISTING_OUTPUT_FILE status);
	a warning will be provided in this case if the -Force option has
	been specified.

	A report listing the input and output files, the image data
	specifications, the JP2 data producer signature if present, the
	selected image area and rendering resolution and resultant output
	image size will be written to stdout before the input files are
	processed to generate the output file.

	<h4>JP2  -
	</h4>

	A {@link UA::HiRISE::JP2_Decoder JP2_Decoder} object is instantiated
	and opened on the input JP2 file. The JPEG2000 codestream is checked
	by the decoder to be sure it meets the requirment that all image
	data components (bands) are have the same size, pixel bits and data
	signedness; if they are not the same the program will exit with a
	#LOGIC_ERROR status. The decoder is configured with the rendering
	-Resolution level and image -Area selection. This will result in the
	resolution level being limited to the maximum number of resolution
	levels present in the JP2 source, and the selected image area
	clipped to the image extent. If the selected image area is entirely
	outside the image boundaries the program will exit with a
	#LOGIC_ERROR status.

	<h4>PDS label -
	</h4>
	A {@link UA::HiRISE::PDS_Converter PDS_Converter} object
	instantiated on the PDS label file is used to convert the input file
	PDS label to the new attached label. The selection of the
	appropriate PDS label converter is done by each registered PDS label
	converter examining the file's contents and deciding if it is
	suitable for handling the conversion; the first one to indicate that
	it is appropriate for the input file is used. Product specific
	converters are queried first until finally the {@link
	UA::HiRISE::Generic_PDS_Converter Generic_PDS_Converter} is tried.

	If the label converter is unable to locate a group of parameters in
	the label that describes the <code>IMAGE</code> data block the
	program will exit with a #PDS_LABEL_ERROR status. The JP2 decoder is
	then configured to reorder multi-byte pixels if it is found from the
	user specified order, the label converter or the default that the
	source image data order is not the same as the host system native
	data order. If the number of image bands and pixel bits obtained
	from the label converter does not match the values obtained from the
	JP2 decoder the program will exit with a #LABEL_INCONSISTENCY
	status. Inconsitency of image size will be reported with a warning,
	but the output PDS label will have the correct values set, which are
	set appropriately if an image region or less than full resolution
	rendering is selected in any case. A warning is also provided if the
	image data signedness from the PDS label does not match that from
	the JP2 file, but this has no effect on the output PDS label.

	Before the output file is generated a check is made that the host
	filesystem is capable of storing a file of the size to be produced.
	If it appears that it can not handle very large files the program
	will exit with an #IO_FAILURE status.

	Note: Before the PDS label converter is requested to write the new
	label file the <code>SOFTWARE_NAME</code> parameter in the label, if
	it exists, is updated with the application identification.

	The PDS label converter is informed of the selected image area and
	resolution and requested to write the converted label to the output
	file. Then the JP2 decoder is requested to appended the rendered
	image pixel data to this file.

	<h3>Exit status values:
	</h3>

	<dl>
	<dt>#SUCCESS</dt>
	<dd>The application completed successfully.</dd>
	<dt>#BAD_SYNTAX</dt>
	<dd>There was a syntax problem in the command line. A description of the
		problem followed by a brief command line syntax summary will be written
		to stdout.</dd>
	<dt>#INVALID_ARGUMENT</dt>
	<dd>An invalid software function argument exception was encountered. A
		description of the error will be written to stdout. This error may
		indicate a bug in the software so the complete error description
		should be reported to the application software development
		contact.</dd>
	<dt>#PDS_LABEL_ERROR</dt>
	<dd>There was a problem with the PDS label. A description of the problem
		will be written to stdout. This problem is typically the result of
		specifying an input file for processing that is not, or is not
		associated with, a valid PDS label file.</dd>
	<dt>#NO_IMAGE_DATA</dt>
	<dd>The PDS label indicates that the file does not contain any image
		data; in this case check the label for a complete set of valid IMAGE
		parameters. Or an -Area was specified that is empty or is outside the
		image boundaries; in this case the error message will describe the
		problem.</dd>
	<dt>#LABEL_INCONSISTENCY</dt>
	<dd>The image data characterization from the PDS label does not
		match the image data characterization from the JP2 file. Check
		that the correct files are being used together.
	<dt>#LOGIC_ERROR</dt>
	<dd>A logic error was detected in the software. A description of the
		error will be written to stdout. This error may indicate that
		the JP2 decoder detected a problem with the file format, which
		will be reported to stdout. If, however, a software but is
		suspected the complete error description should be reported to
		the application software development contact.</dd>
	<dt>#NO_INPUT_FILE</dt>
	<dd>No input file was specified on the command line or the PDL label or
		JP2 file could not be accessed from the filesystem. Check that the
		input files exists at the specified pathname and that their
		permissions allow read access to the user.
	<dt>#EXISTING_OUTPUT_FILE</dt>
	<dd>A PDS image file at the intended output pathname already exists. Use
		the -Force option an existing file is to be overwritten.</dd>
	<dt>#IO_FAILURE</dt>
	<dd>A filesystem I/O failure has occurred. A likely cause of the failure
		is insufficient user permissions to write the output file or running
		out of space on the storage volume. This exit status will also occur
		if the program detects that the host system is not capable of
		storing a file of the expected size, including the PDS label and
		decompressed image data.
		</dd>
	<dt>#PVL_ERROR</dt>
	<dd>An exception occurred while managing the Parameter Value Language of
		a PDS label. A description of the error will be written to stdout.
		This may be due to an invalid PDS label that can not be parsed. If
		the input file label is valid then the complete error description
		should be reported to the application software development
		contact.</dd>
	<dt>#DECODER_ERROR</dt>
	<dd>An exception occurred while decoding the JPEG2000 codestream to the
		output image data. This may be due to the exhaustion of system
		resources, such as available memory or storage capacity.</dd>
	<dt>#UNKNOWN_ERROR</dt>
	<dd>An unanticipated exception occurred. This error may indicate a bug
		in the software so the complete error description should be reported
		to the application software development contact.</dd>
	</dl>


	@param	argument_count	The number of command line arguments.
	@param	arguments	The array of command line arguments.
	@see	#usage(int, bool)

	@author		Bradford Castalia, UA/HiROC
	@version	1.21
*/
int
main
	(
	int		argument_count,
	char	**arguments
	)
{
//	Application identification.
cout << ID << endl;
Program_Name = *arguments;

string
	PDS_pathname,
	PDS_label_pathname,
	JP2_pathname,
	values;
int
	//	offset x,y and size x,y.
	image_area[]	 = {0, 0, 0, 0},
	resolution_level = 1;

//	Tri-state flag: false (-), true (+), default (0).
int
	MSB_data		 = 0;
bool
	no_output		 = false,
	force_overwrite  = false;
long
	value;
char
	*character;
int
	index;

/*------------------------------------------------------------------------------
   Command line arguments
*/
if (argument_count == 1)
    usage ();

for (int
		count = 1;
		count < argument_count;
		count++)
	{
	if (arguments[count][0]== '-')
		{
		switch (toupper (arguments[count][1]))
			{
			case 'R':	//	Resolution.
				if (++count == argument_count || 
					arguments[count][0] == '-')
					{
					cout << "Missing resolution level." << endl
						 << endl;
					usage ();
					}
				value = strtol (arguments[count], &character, 0);
				if (*character ||
					value <= 0)
					{
					cout << "Positive value expected, but "
							<< arguments[count] << " found." << endl;
					usage ();
					}
				resolution_level = value;
				break;

			case 'A':	//	Area.
				if (++count == argument_count)
					{
					cout << "Missing image area values." << endl
						 << endl;
					usage ();
					}
				values = arguments[count];
				index = 0;
				for (char*
						token = strtok (arguments[count], ",xX");
						token;
						token = strtok (NULL, ",xX"))
					{
					if (index == 4)
						goto Invalid_Region_Values;
					value = strtol (token, &character, 0);
					if (*character)
						goto Invalid_Region_Values;
					if (index > 1 &&
						value < 0)
						{
						cout << "Image area sizes must be positive, but "
								<< value << " found in "
								<< values << '.' << endl;
						usage ();
						}
					image_area[index++] = (int)value;
					}
				if (index < 4)
					{
					Invalid_Region_Values:
					cout << "Four image area values expected, but "
							<< values << " found." << endl;
					usage ();
					}
				if (! image_area[2] ||
					! image_area[3])
					{
					cout << "!!! " << arguments[--count] << " " << values
							<< " selects an empty image area." << endl;
					exit (NO_IMAGE_DATA);
					}
				break;

			case 'O':	//	Output pathname.
			case 'P':	//	PDS pathname.
				if (++count == argument_count || 
					arguments[count][0] == '-')
					{
					cout << "Missing PDS output file pathname." << endl
						 << endl;
					usage ();
					}
				if (! PDS_pathname.empty ())
					{
					cout << "Only one output file, please." << endl
						 << "   First filename: " << PDS_pathname << endl
						 << "  Second filename: " << arguments[count] << endl
						 << endl;
					usage ();
					}
				PDS_pathname = arguments[count];
				break;

			case 'I':	//	Input pathname.
			case 'J':	//	JP2 pathname.
				if (++count == argument_count || 
					arguments[count][0] == '-')
					{
					cout << "Missing JP2 input file pathname." << endl
						 << endl;
					usage ();
					}
				JP2_Pathname_Argument:
				if (! JP2_pathname.empty ())
					{
					cout << "Only one JP2 input file, please." << endl
						 << "   First filename: " << JP2_pathname << endl
						 << "  Second filename: " << arguments[count] << endl
						 << endl;
					usage ();
					}
				  JP2_pathname = arguments[count];
				break;

			case 'L':
				if (strchr (arguments[count], 'A') ||
					strchr (arguments[count], 'a'))
					{
					//	Label pathname.
					if (++count == argument_count || 
						arguments[count][0] == '-')
						{
						cout << "Missing PDS label input file pathname." << endl
							 << endl;
						usage ();
						}
					if (! PDS_label_pathname.empty ())
						{
						cout << "Only one PDS label input file, please." << endl
							 << "   First filename: " << PDS_label_pathname << endl
							 << "  Second filename: " << arguments[count] << endl
							 << endl;
						usage ();
						}
					  PDS_label_pathname = arguments[count];
					 }
				else
					//	LSB data.
					MSB_data = -1;
				break;

			case 'M':	//	MSB data.
				MSB_data = 1;
				break;

			case 'N':	//	No output.
				no_output = true;
				break;

			case 'F':	//	Force output.
				force_overwrite = true;
				break;

			case 'H':	//	Help.
				usage (SUCCESS, true);
				break;

			default:
				cout << "Unrecognized argument: "  << arguments[count] << endl
					 << endl;
				usage ();
			}
		}
	else
		goto JP2_Pathname_Argument;
	 }

if (JP2_pathname.empty () &&
	PDS_label_pathname.empty ())
	{
	cout << "Missing JP2 input file pathname." << endl
		 << endl;
	usage (NO_INPUT_FILE);
    }


//	Host system.
cout
	<< endl
	<< setw (LABEL_WIDTH) << "Processing host: "
		<< hostname () << endl;


JP2_Decoder
	JP2_decoder;
string
	error_report;
int
	exit_status = SUCCESS;
try
{
/*------------------------------------------------------------------------------
	PDS/JP2 input
*/
cout
	<< endl
	<< "PDS/JP2 input -" << endl;

//	JP2 image file.
if (JP2_pathname.empty ())
	JP2_pathname = file_basename (PDS_label_pathname) + JP2_EXTENSION;
JP2_pathname = file_pathname (JP2_pathname);
cout
	<< setw (LABEL_WIDTH) << "JP2 file pathname: "
		<< JP2_pathname << endl;
if (! file_is_readable (JP2_pathname))
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
		<< "Unable to access the JP2 file." << endl;
	exit (NO_INPUT_FILE);
	}
if (file_is_directory (JP2_pathname))
	{
    cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "The pathname is for a directory." << endl;
	exit (NO_INPUT_FILE);
	}


//	Configure the JP2 Decoder.
JP2_decoder
	.source           (JP2_pathname)
	.resolution_level (resolution_level)
	.image_region     (image_area[0],
	                   image_area[1],
					   image_area[2],
					   image_area[3]);

//	Open the JP2 Decoder.
JP2_decoder.open ();

//	Check for a PDS label URL.
string
	label_URL (JP2_decoder.URL ());
if (! label_URL.empty () &&
	  label_URL.find ("file://") == 0)
	//	Remove the protocol prefix.
	label_URL = label_URL.substr (7);


//	PDS/JP2 label file.
if (PDS_label_pathname.empty ())
	{
	if (! label_URL.empty ())
		PDS_label_pathname = file_pathname
			(file_directory (JP2_pathname), label_URL);
	else
		PDS_label_pathname = file_basename (JP2_pathname) + LABEL_EXTENSION;
	}
PDS_label_pathname = file_pathname (PDS_label_pathname);
cout
	<< setw (LABEL_WIDTH) << "Label file pathname: "
		<< PDS_label_pathname << endl;
if (! file_is_readable (PDS_label_pathname))
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "Unable to access the label file." << endl;
	exit (NO_INPUT_FILE);
	}
if (! label_URL.empty () &&
	file_name (label_URL) != file_name (PDS_label_pathname))
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "The JP2 PDS label URL has a different filename -" << endl
		<< setw (LABEL_WIDTH) << "" << label_URL << endl;

//	Label.
PDS_Converter
	*label_converter = NULL;
const char
	*message = NULL;
try {label_converter = converter_for (PDS_label_pathname);}
catch (exception& except) {message = except.what ();}
catch (...) {message = "Unknown exception.";}
if (! label_converter)
	{
	cout << "!!! No converter could be found for the PDS label." << endl;
	if (message)
		cout << message << endl;
	exit (PDS_LABEL_ERROR);
	}
cout
	<< setw (LABEL_WIDTH) << "PDS label converter: "
		<< label_converter->product_names () << endl;

Image_Data_Block
	*image_metadata = label_converter->image_data ();
if (! image_metadata)
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "No " << label_converter->IMAGE_DATA_BLOCK_NAME
			<< " was found in the source PDS label." << endl;
	exit (PDS_LABEL_ERROR);
	}

if (MSB_data &&
	image_metadata->MSB_data () &&
	image_metadata->MSB_data () != MSB_data &&
	image_metadata->pixel_bytes () > 1)
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "Image label "
			<< ((image_metadata->MSB_data () > 0) ? 'M' : 'L')
			<< "SB data order overridden." << endl;
if (! MSB_data &&
	! (MSB_data = image_metadata->MSB_data ()))
	{
	MSB_data = DEFAULT_DATA_ORDER;
	if (image_metadata->pixel_bytes () > 1)
		cout
			<< setw (LABEL_WIDTH) << "*** "
				<< "Image data order unknown," << endl
			<< setw (LABEL_WIDTH) << ""
				<< "so it is assumed by default to be "
		 		<< ((MSB_data > 0) ? 'M' : 'L') << "SB ordered." << endl;
	}
if (MSB_data < 0)
	//	Convert to false condition.
	MSB_data = 0;
bool
	swap_bytes = high_endian_host () ? (! MSB_data) : MSB_data;

//	Inform the JP2 Decoder of the byte ordering.
JP2_decoder.swap_pixel_bytes (swap_bytes);


//	Check the PDS metadata against the JP2 metadata.

if (image_metadata->image_bands () != JP2_decoder.image_bands ())
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "The number of image bands from the PDS/JP2 label ("
			<< image_metadata->image_bands () << ')' << endl
		<< setw (LABEL_WIDTH) << ""
			<< "does not match the number of bands from the JP2 source ("
		 	<< JP2_decoder.image_bands () << ')' << endl;
	if (! no_output)
		exit (LABEL_INCONSISTENCY);
	}
if (image_metadata->pixel_bits () != JP2_decoder.pixel_bits ())
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "The image data precision from the PDS/JP2 label ("
			<< image_metadata->pixel_bits () << ')' << endl
		<< setw (LABEL_WIDTH) << ""
			<< "does not match the precision from the JP2 source ("
		 	<< JP2_decoder.pixel_bits () << ')' << endl;
	if (! no_output)
		exit (LABEL_INCONSISTENCY);
	}
if (image_metadata->signed_data () &&
	((image_metadata->signed_data () > 0) ? true : false)
		!= JP2_decoder.signed_data ())
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "The image data signedness from the PDS/JP2 label ("
			<< boolalpha << (image_metadata->signed_data () > 0) << ')' << endl
		<< setw (LABEL_WIDTH) << ""
			<< "does not match the signedness from the JP2 source ("
		 	<< JP2_decoder.signed_data () << ')' << endl;

unsigned int
	image_width  = image_metadata->image_width (),
	image_height = image_metadata->image_height ();
if (image_width  != JP2_decoder.image_width () ||
	image_height != JP2_decoder.image_height ())
	{
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "The image size from the PDS/JP2 label ("
			<< image_width << ','
			<< image_height << ')' << endl
		<< setw (LABEL_WIDTH) << ""
			<< "does not match the size from the JP2 source ("
		 	<< JP2_decoder.image_width () << ','
			<< JP2_decoder.image_height () << ')' << endl
		<< setw (LABEL_WIDTH) << ""
			<< "so the JP2 source image size will be used." << endl;
	image_width  = JP2_decoder.image_width ();
	image_height = JP2_decoder.image_height ();
	}
if (! image_width ||
	! image_height)
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "The image is empty." << endl;
	if (! no_output)
		exit (NO_IMAGE_DATA);
	}

cout << endl
	<< setw (LABEL_WIDTH) << "JP2 image -" << endl
	<< setw (LABEL_WIDTH) << "Bytes per pixel: "
		<< setw (VALUE_WIDTH) << JP2_decoder.pixel_bytes () << endl
	<< setw (LABEL_WIDTH) << "Bits per pixel: "
		<< setw (VALUE_WIDTH) << JP2_decoder.pixel_bits () << endl
	<< setw (LABEL_WIDTH) << "Pixels per line: "
		<< setw (VALUE_WIDTH) << image_width << endl
	<< setw (LABEL_WIDTH) << "Lines per band: "
		<< setw (VALUE_WIDTH) << image_height << endl
	<< setw (LABEL_WIDTH) << "Bands per image: "
		<< setw (VALUE_WIDTH) << JP2_decoder.image_bands () << endl
	<< setw (LABEL_WIDTH) << "Signed data: "
		<< setw (VALUE_WIDTH) << boolalpha << JP2_decoder.signed_data () << endl
	<< setw (LABEL_WIDTH) << "Resolution levels: "
		<< setw (VALUE_WIDTH) << JP2_decoder.resolution_levels () << endl;
unsigned char
	*producer_ID = JP2_decoder.producer_UUID ();
if (producer_ID)
	{
	cout << setw (LABEL_WIDTH) << "Producer ID: " << hex << setfill ('0');
	for (index = 0;
		 index < UUID_SIZE;
		 index++)
		{
		if (index)
			cout << ", ";
		cout << "0x" << setw (2) << ((int)producer_ID[index] & 0xFF);
		}
	cout << setfill (' ') << dec << endl;
	}

/*------------------------------------------------------------------------------
   PDS output
*/
if (PDS_pathname.empty ())
	PDS_pathname = file_basename (JP2_pathname) + PDS_IMAGE_EXTENSION;
PDS_pathname = file_pathname (PDS_pathname);
cout
	<< endl
	<< "PDS output -" << endl
	<< setw (LABEL_WIDTH) << "PDS file pathname: "
		<< PDS_pathname <<endl;
if (file_exists (PDS_pathname))
	{
	if (force_overwrite)
		cout
			<< setw (LABEL_WIDTH) << "*** "
				<< "An existing PDS file will be overwritten." << endl;
	else
		{
		cout
			<< setw (LABEL_WIDTH) << "!!! "
				<< "An existing PDS file will not be overwritten." << endl;
		if (! no_output)
			exit (EXISTING_OUTPUT_FILE);
		}
	}
JP2_decoder.destination (PDS_pathname);

UA::HiRISE::Rectangle
	region (JP2_decoder.image_region ());
if (image_area[2])
	{
	//	Image area selected.
	if (! region.area ())
		{
		cout
			<< setw (LABEL_WIDTH) << "!!! "
				<< "The selected image area is outside of the image -" << endl
			<< setw (LABEL_WIDTH) << "Selected image area: "
			 	<< image_area[0] << "x, "
				<< image_area[1] << "y, "
				<< image_area[2] << "w, "
				<< image_area[3] << "h" << endl
			<< setw (LABEL_WIDTH) << "Source image size: "
			 	<< image_width << "w, "
				<< image_height << "h" << endl;
		if (! no_output)
			exit (NO_IMAGE_DATA);
		}
	if (image_area[0] != region.X ||
		image_area[1] != region.Y ||
		image_area[2] != (int)region.Width ||
		image_area[3] != (int)region.Height)
		cout
			<< setw (LABEL_WIDTH) << "*** Note: "
				<< "The selected image area has been adjusted." << endl;
	}

ostringstream
	ratio;
ratio << "1:" << (1 << (JP2_decoder.resolution_level () - 1));
image_width  = JP2_decoder.rendered_width ();
image_height = JP2_decoder.rendered_height ();
cout
	<< endl
	<< setw (LABEL_WIDTH) << "PDS image -" << endl
	<< setw (LABEL_WIDTH) << "Resolution: "
		<< setw (VALUE_WIDTH) << ratio.str () << endl
	<< setw (LABEL_WIDTH) << "Source image area: "
		<< setw (VALUE_WIDTH - 1)
		<< region.X << "x, " << region.Y << "y" << endl
	<< setw (LABEL_WIDTH) << ""
		<< setw (VALUE_WIDTH - 1)
		<< region.Width << "w, " << region.Height << "h" << endl
	<< setw (LABEL_WIDTH) << "Output image size: "
		<< setw (VALUE_WIDTH - 1)
		<< image_width << "w, " << image_height << "h" << endl;


if (sizeof (std::streamoff) < sizeof (unsigned long long))
	{
	//	Confirm that the size of the output file can be handled by this system.
	unsigned long long
		output_size =
			(unsigned long long)label_converter->label_size ()
			+ ((unsigned long long)image_width * image_height
				* JP2_decoder.image_bands ()
				* JP2_decoder.pixel_bytes ()),
		file_size = (std::streamoff)output_size;
	if (file_size != output_size)
		{
		cout
			<< endl
			<< setw (LABEL_WIDTH) << "!!! "
				<< "The host system is unable to write the expected "
					<< output_size << " byte output file size." << endl;
		exit (IO_FAILURE);
		}
	}
cout << endl;

//..............................................................................

if (! no_output)
	{
	//	Try to reset the SOFTWARE_NAME_PARAMETER.
	label_converter->parameter_value (SOFTWARE_NAME_PARAMETER, ID);

	//	Write the converted PDS label file.
	region.Width = image_width;
	region.Height = image_height;
	label_converter->write_PDS_label
		(PDS_pathname, &region, JP2_decoder.resolution_level ());

	//	Decode the JP2 source.
	JP2_decoder.decode ();
	}
}
//------------------------------------------------------------------------------
catch (invalid_argument& except)
	{
	error_report += string ("Invalid argument: ") + except.what ();
	exit_status = INVALID_ARGUMENT;
	}
catch (logic_error& except)
	{
	error_report += string ("Logic error: ") + except.what ();
	exit_status = LOGIC_ERROR;
	}
catch (std::ios::failure& except)
	{
	error_report += string ("I/O failure: ") + except.what ();
	exit_status = IO_FAILURE;
	}
catch (idaeim::Exception& except)
	{
	error_report += string ("idaeim Exception: ") + except.what ();
	exit_status = PVL_ERROR;
	}
catch (exception& except)
	{
	error_report += string ("Exception: ") + except.what ();
	exit_status = UNKNOWN_ERROR;
	}
catch (int except)
	{
	if (except == JP2_Decoder::DECODER_EXCEPTION)
		{
		error_report += string ("JP2 Decoder error: ")
			+ JP2_decoder.decoder_error ()->Message;
		exit_status = DECODER_ERROR;
		}
	else
		{
		ostringstream
			message;
		message << "Unknown exception: " << except;
		error_report += message.str ();
		exit_status = UNKNOWN_ERROR;
		}
	}
catch (...)
	{
	error_report += string ("Unknown exception!");
	exit_status = UNKNOWN_ERROR;
	}

if (exit_status != SUCCESS)
	cout << "!!! " << error_report << endl;
exit (exit_status);
}

