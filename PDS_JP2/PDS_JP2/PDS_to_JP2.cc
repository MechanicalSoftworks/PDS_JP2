/*	PDS_to_JP2

HiROC CVS ID: PDS_to_JP2.cc,v 1.55 2013/03/14 21:00:57 guym Exp

Copyright (C) 2006-2007 Arizona Board of Regents on behalf of the
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

#ifdef	INCLUDE_OSSP_UUID
//	This include must be first to avoid uuid_t conflict on OS X.
#include	"uuid++.hh"
#endif

#include	"PDS_Converters.hh"
using UA::HiRISE::converter_for;
using UA::HiRISE::PDS_Converter;
using UA::HiRISE::PDS_Data;
using UA::HiRISE::Image_Data_Block;
using UA::HiRISE::indent;

#include "PVL.hh"
using idaeim::PVL::Assignment;
using idaeim::PVL::String;

#ifdef	INCLUDE_GDAL
#include	"PDS_Projection_Data.hh"
using UA::HiRISE::PDS_Projection_Data;
#endif

#include	"JP2_Encoder.hh"
using UA::HiRISE::JP2_Encoder;
using UA::HiRISE::JP2_Box;
using UA::HiRISE::power_of_2;

#include	"Dimensions.hh"
using UA::HiRISE::Size_2D;

#include	"Files.hh"
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
	Local Functions: Declarations
*/
int
recommended_resolution_levels
	(
	int		width,
	int		height
	);

unsigned char*
UUID
	(
	const char*	signature
	);

/*==============================================================================
	Parameters
*/
//!	The filename extension for the output PDS label file.
const char * const
	LABEL_EXTENSION				= ".LBL";

//!	The filename extension for the output JPEG2000 JP2 file.
const char * const
	JP2_EXTENSION				= ".JP2";

//! The default tile size.
const int
	DEFAULT_TILE_SIZE			= 0;

//!	The minimum image dimension at lowest resolution.
const int
	MIN_RESOLUTION_SIZE			= 64;

/** The default progression order, optimized for very large images.

	Precinct (area), Component (band), Resolution, Layer (quality).
*/
const char * const
	DEFAULT_PROGRESSION_ORDER	= "PCRL";

/**	The default data signedness if it can't be determined from the input.

	Positive is signed; negative is unsigned.
*/
const int
	DEFAULT_SIGNED_DATA			= -1;

/**	The default data order if it can't be determined from the input.

	Positive is MSB; negative is LSB.
*/
const int
	DEFAULT_DATA_ORDER			= 1;

//!	The default precinct size.
const int
	DEFAULT_PRECINCT_SIZE		= 256;

//!	The default code block size.
const int
	DEFAULT_CODE_BLOCK_SIZE		= 64;

#if defined (INCLUDE_OSSP_UUID)
#if defined (PRODUCER_SIGNATURE)
//!	Default data provider identification signature.
const char
	*DEFAULT_PRODUCER_SIGNATURE	= PRODUCER_SIGNATURE;
//!	Default data provider identification UUID.
unsigned char
	*DEFAULT_PRODUCER_UUID		= UUID (DEFAULT_PRODUCER_SIGNATURE);
#else	//	! defined (PRODUCER_SIGNATURE)
const char
	*DEFAULT_PRODUCER_SIGNATURE	= NULL;
#ifndef PRODUCER_UUID
#define PRODUCER_UUID
#endif
unsigned char
	DEFAULT_PRODUCER_UUID[]		= {PRODUCER_UUID};
#endif
#else	//	! defined (INCLUDE_OSSP_UUID)
const char
	*DEFAULT_PRODUCER_SIGNATURE	= NULL;
#ifndef PRODUCER_UUID
#define PRODUCER_UUID
#endif
//!	Default data provider identification UUID.
unsigned char
	DEFAULT_PRODUCER_UUID[]		= {PRODUCER_UUID};
#endif


//!	Exit status values.
const int
	SUCCESS						= 0,

	//	Command line syntax.
	BAD_SYNTAX					= 1,

	//	Software / data problem.
	INVALID_ARGUMENT			= 11,
	PDS_LABEL_ERROR				= 12,
	NO_IMAGE_DATA				= 13,
	LOGIC_ERROR					= 19,

	//	IO.
	NO_INPUT_FILE				= 20,
	EXISTING_OUTPUT_FILE		= 21,
	IO_FAILURE					= 29,

	//	PVL.
	PVL_ERROR					= 30,

	//	JP2 Encoder.
	ENCODER_ERROR				= JP2_Encoder::ENCODER_EXCEPTION,

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
		"PDS_to_JP2"
		_VERSION_
		"(1.55 2013/03/14 21:00:57)";

//!	The label parameter to have its value set to the ID.
const char
	*SOFTWARE_NAME_PARAMETER			= "SOFTWARE_NAME";

//!	The maximum number of resolution levels allowed.
const int
	MAX_RESOLUTION_LEVELS				= 32;

//!	The maximum number of quality layers allowed.
const int
	MAX_QUALITY_LAYERS					= 16384;
//!	Default lossy encoding quality layers.
const int
	DEFAULT_LOSSY_QUALITY_LAYERS		= 20;

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

#if defined (DEBUG)
/*******************************************************************************
	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			-1
#define DEBUG_ENCODE		(1 << 2)
#define	DEBUG_EXCEPTIONS	(1 << 3)
#define DEBUG_HELPERS		(1 << 4)
#include	<iostream>
using std::clog;
#endif  // DEBUG

/*==============================================================================
	Usage
*/
//!	The runtime command name.
char
	*Program_Name;

/** PDS_to_JP2 command line syntax and usage.

	<h3>Command line syntax:
	</h3>

	<b>PDS_to_JP2</b> [<i>options</i>]
		[<b>-I</b>nput] &lt;<i>pathname</i>&gt;

	<h3>Command line options:
	</h3>

	<h4><b>-I</b>nput &lt;<i>pathname</i>&gt;
	</h4>
	Input PDS image file pathname.

	<h4><b>-O</b>utput &lt;<i>pathname</i>&gt;
	</h4>
	If the pathname does not refer to a directory then it is the output
	JP2 file pathname. Otherwise the directory pathname and input
	filename are used with the #JP2_EXTENSION replacing any existing
	extension or being appended. The output PDS label pathname is always
	the JP2 pathname with the #LABEL_EXTENSION replacing any existing
	extension or being appended. The pathnames may be absolute or
	relative (to the current working directory).

	Default: The directory where the input file is located.

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
    If the output files already exist, they will be overwritten.

    Default: Do not overwrite existing files.

	<h4><b>-P</b>rogression_<b>O</b>rder &lt;<i>order</i>&gt;
	</h4>
	The order in which the JPEG2000 codestream is written. A JPEG2000
	codestream has Position (image area), Component (image band),
	Resolution and Layer (quality) dimensions. The codestream progression
	order is specified as the first letters of each dimension in the
	order in which they are to be written; the first dimension specified
	varies the most slowly while the last dimension specified varies the
	most quickly.

	Default: PCRL

	<h4><b>-T</b>ile_size &lt;<i>width</i>&gt;[<b>,</b>&lt;<i>height</i>&gt;]
	</h4>
	The JPEG2000 image data is organized into tiles. The size of these
	tiles is specified in width,height pixels. If only the first tile
	size dimension is sepecified the tile will be square. The tile
	dimensions will be limited to the image dimensions. A tile size of 0
	means that the corresponding dimension of the image is to be used.
	Thus if a single 0 is specified the tile size will be the same as the
	image which is conceptually an untiled JP2 file.

	Default: 0

	<h4><b>-R</b>esolution &lt;<i>levels</i>&gt;
	</h4>
	The JPEG2000 codestream provides access to the image at multiple
	resolution levels. The image is always available at full resolution.
	The next level is half resolution, then half of that, etc. No more
	than 31 resolutions are allowed. If not specified, the number of
	resolution levels will be chosen such that the minimum dimension of
	the image at lowest resolution is not less than 64 pixels, unless the
	minimum dimension at full resolution is less than twice this size in
	which case only the first full resolution will be provided.

	Default: Depends on the minimum image dimension.

	<h4><b>-Q</b>uality &lt;<i>layers</i>&gt;
	</h4>
	The JPEG2000 codestream may contain multiple quality layers when
	progressive quality rendering is desired. A minimum of one quality
	layer is required, and this is generally sufficient when lossless
	encoding is used to preserve scientific data accuracy. For lossy
	(irreversible) encoding multiple quality layers (typically 20)
	may be appropriate. A maximum of 16384 quality layers is allowed.

	Default: 1 for lossless encoding (-Bit_rate of zero);
	         20 for lossy encoding (non-zero -Bit_rate)

	<h4><b>-B</b>it_rate &lt;<i>rate</i>&gt;
	</h4>
	The JPEG2000 codestream may be generated using lossless encoding
	- in which the encoded image values can be decoded to their original
	values - or using lossy encoding - which can produce a more highly
	compressed codestream but can not be decoded to the exact original
	values. Specifying a non-zero bit-rate selects lossy encoding. The
	bit-rate is a floating point value expressed in terms of the ratio
	between the total number of compressed bits (including headers) and
	the area of the image; this is most easly thought of as the number
	of bits per pixel used in the compressed encoding. For example, an
	8-bit per pixel image might be encoded with a bit-rate of 2.5 to
	achieve a highly compressed codestream that still retains excellent
	image rendering quality. The bit-rate is logarithmically distributed
	over all of the quality levels.

	Default: 0.0 (lossless encoding)

	<h4><b>-P</b>recinct_<b>S</b>izes &lt;<i>width</i>&gt;[<b>,</b>&lt;<i>height</i>&gt;][;...]
	</h4>
	The JPEG2000 image data is precinct structured. The size of these
	precincts is specified in width,height pixels. If only the first
	precinct size dimension is sepecified the precinct will be square.
	The precinct dimensions must be powers of 2. Precinct sizes may be
	specfied for each resolution level (the first resolution level is
	full resolution). If fewer precinct sizes have been specified than
	the number of resolution levels, the last precinct size specified
	will be used for all remaining resolution levels.

	Default: 256

	<h4><b>-C</b>ode_block_size &lt;<i>width</i>&gt;[<b>,</b>&lt;<i>height</i>&gt;]
	</h4>
	The basic structural unit of JPEG2000 image data is a code block.
	This unit contains the image information for a small area of the
	image, which will not be greater than 64 by 64 pixels. If only one
	code block dimension is specified the code block size will be square.

	Default: 64

	<h4><b>-</b>[<b>U</b>n]<b>S</b>igned
	</h4>
	Normally the image data values are treated as signed or unsigned
	based on information from the input file PDS label: If the
	<code>SAMPLE_TYPE</code> parameter is present and its value contains
	the "UNSIGNED" string, the image data is treated as unsigned; if the
	value contains the "SIGNED" string the data is treated as signed. This
	option determines the effective signedness of the image data values
	regardless of the PDS label parameter value.

	Default: Pixel data of unknown signedness is unsigned.

	<h4><b>-L</b>sb | <b>-M</b>sb
	</h4>
	Normally the image data values are treated as MSB or LSB ordered
	based on information from the input file PDS label: If the
	<code>SAMPLE_TYPE</code> parameter is present and its value contains
	the "MSB" string, the image data is treated as MSB ordered; if the
	value contains the "LSB" string the data is treated as LSB ordered.
	This option determines the effective byte order of multi-byte image
	data values regardless of the PDS label parameter value.

	Default: Pixel data of unknown data order is MSB.

	<h4><b>-ID</b> &lt;<i>values</i>&gt;
	</h4>
	The data producer ID is stored in a UUID box of the JP2 file
	alongside the URL box that contains the relative file URL for the PDS
	label file. These boxes are encapsulated inside a UUID Info box. A
	Universally Unique IDentifier (UUID; see
	http://www.webdav.org/specs/draft-leach-uuids-guids-01.txt) is 16,
	comma separated (no spaces) 8-bit values that are intended to
	uniquely identify the data producer. Software for producing UUIDs is
	available on line (e.g. http://www.ossp.org/pkg/lib/uuid/). If a
	single 0, or the word "none", is specified a null (all zeros) UUID
	will be used.

	If the OSSP UUID library support is available
	(<code>OSSP_UUID</code> was defined at compile time) the ID may
	alternatively be specified as a signature string; this is usually a
	URL such as "http://hirise.lpl.arizona.edu/". In this case the UUID
	values will be determined from the signature string.

	Default: The default UUID is sepecified at compile time by the
		<code>PRODUCER_SIGNATURE</code> or <code>PRODUCER_UUID</code>
		value.

	<h4><b>-G</b>eotiff
	</h4>
	Add a GeoTIFF UUID box to the JP2 file if the necessary image
	projection parameters are available in the input file PDS label.
	The GeoTIFF UUID signature is -

	<code><pre>
    0xb1, 0x4b, 0xf8, 0xbd, 0x08, 0x3d, 0x4b, 0x43,
    0xa5, 0xae, 0x8c, 0xd7, 0xd5, 0xa6, 0xce, 0x03
	</pre></code>

	Default: No GeoTIFF box
	
	<b>Note</b>: This feature is optionally included at compile-time and
	requires a GDAL library compiled with OGR support.

	<h4><b>-GML</b>
	</h4>
	Add GML boxes to the JP2 file if the necessary image projection
	parameters are available in the input file PDS label. The GML boxes
	are contained in an Association ("asoc") super-box with an initial
	Label ("lbl ") box with the text "gml.data", followed by an
	Association with a "gml.root-instance" label and an XML box with the
	"gml:FeatureCollection" specifications, and then an Association with
	a "CRSDictionary.gml" label and an XML box with the "gml:Dictionary"
	specifications.

	<b>Warning</b>: This is an experimental feature. It has not been
	shown to produce correct results. It will have no affect on any other
	operation of the program nor on any other content of the JP2 file
	that is produced.

	Default: No GML box
	
	<b>Note</b>: This feature, optionally included at compile time (if
	<CODE>GDAL</CODE> was defined),  requires the use of a GDAL library
	compiled with OGR support.

	<h4><b>-H</b>elp
	</h4>
	Prints this usage description.

	@param	exit_status	This method always results in program exit. If the
		exit status value is not specified the #BAD_SYNTAX value will be
		used.
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
	<< "Usage: " << Program_Name << " [options] [-Input] <pathname>" << endl;
if (list_descriptions)
	cout
	<< endl
	<< "Converts a PDS image file with an attached label to a detached PDS" << endl
	<< "label file and JP2 image file. The input image data will be written" << endl
	<< "as a losslessly compressed JPEG2000 codestream." << endl
	<< endl;

cout
	<< "Options -" << endl;
if (list_descriptions)
	cout << endl;

cout
	<< "  -Input <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    Input PDS image file pathname." << endl << endl;

cout
	<< "  -Output <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    If the pathname does not refer to a directory then it is the output" << endl
	<< "    JP2 file pathname. Otherwise the directory pathname and input" << endl
	<< "    filename are used with the \"JP2\" extension replacing any existing" << endl
	<< "    extension or being appended. The output PDS label pathname is always" << endl
	<< "    the JP2 pathname with the \"LBL\" extension replacing any existing" << endl
	<< "    extension or being appended. The pathnames may be absolute or" << endl
	<< "    relative (to the current working directory)." << endl
	<< endl
	<< "    Default: The directory where the input file is located." << endl << endl;

cout
	<< "  -No_output" << endl;
if (list_descriptions)
	cout
	<< "    No ouput file will be written. The input file will be examined" << endl
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
	<< "    If the output files already exist, they will be overwritten." << endl
	<< endl
	<< "    Default: Do not overwrite existing files." << endl << endl;
	  
cout
	<< "  -Progression_Order <order>" << endl;
if (list_descriptions)
	cout
	<< "    The order in which the JPEG2000 codestream is written. A JPEG2000" << endl
	<< "    codestream has Resolution, Precinct (image area), Component" << endl
	<< "    (image band) and Layer (quality) dimensions. The codestream" << endl
	<< "    progression order is specified as the first letters of each" << endl
	<< "    dimension in the order in which they are to be written;" << endl
	<< "    the first dimension specified varies the most slowly while" <<endl
	<< "    the last dimension specified varies the most quickly." << endl
	<< endl
	<< "    Default: " << DEFAULT_PROGRESSION_ORDER << endl << endl;
	  
cout
	<< "  -Tile_size <width>[,<height>]" << endl;
if (list_descriptions)
	cout
	<< "    The JPEG2000 image data is organized into tiles. The size of" << endl
	<< "    these tiles is specified in width,height pixels. If only the" << endl
	<< "    first tile size dimension is sepecified the tile will be square." << endl
	<< "    The tile dimensions will be limited to the image dimensions." << endl
	<< "    A tile size of 0 means that the corresponding dimension of the" << endl
	<< "    image is to be used. Thus if a single 0 is specified the tile" << endl
	<< "    size will be the same as the image which is conceptually an" << endl
	<< "    untiled JP2 file." << endl
	<< endl
	<< "    Default:." << DEFAULT_TILE_SIZE << endl << endl;
	  
cout
	<< "  -Resolution <levels>" << endl;
if (list_descriptions)
	cout
	<< "    The JPEG2000 codestream provides access to the image at multiple" << endl
	<< "    resolution levels. The image is always available at full" << endl
	<< "    resolution. The next level is half resolution, then half of that," << endl
	<< "    etc. No more than " << MAX_RESOLUTION_LEVELS 
		<< " resolutions are allowed. If not specified, or zero," << endl
	<< "    the number of resolution levels will be chosen such that the" << endl
	<< "    minimum dimension of the image at the lowest resolution is not less" << endl
	<< "    than " << MIN_RESOLUTION_SIZE
		<< " pixels, unless the minimum dimension at full resolution" << endl
	<< "    is less than twice this size in which case only full resolution" << endl
	<< "    will be provided." << endl
	<< endl
	<< "    Default: Depends on the minimum image dimension." << endl << endl;

cout
	<< "  -Quality <layers>" << endl;
if (list_descriptions)
	cout
	<< "    The JPEG2000 codestream may contain multiple quality layers when" << endl
	<< "    progressive quality rendering is desired. A minimum of one quality" << endl
	<< "    layer is required, and this is generally sufficient when lossless" << endl
	<< "    encoding is used to preserve scientific data accuracy. For lossy" << endl
	<< "    (irreversible) encoding multiple quality layers (typically 20)" << endl
	<< "    may be appropriate. A maximum of 16384 quality layers is allowed." << endl
	<< endl
	<< "    Default: 1 for lossless encoding (-Bit_rate of zero);" << endl
	<< "             20 for lossy encoding (non-zero -Bit_rate)" << endl << endl;

cout
	<< "  -Bit_rate <rate>" << endl;
if (list_descriptions)
	cout
	<< "    The JPEG2000 codestream may be generated using lossless encoding" << endl
	<< "    - in which the encoded image values can be decoded to their original" << endl
	<< "    values - or using lossy encoding - which can produce a more highly" << endl
	<< "    compressed codestream but can not be decoded to the exact original" << endl
	<< "    values. Specifying a non-zero bit-rate selects lossy encoding. The" << endl
	<< "    bit-rate is a floating point value expressed in terms of the ratio" << endl
	<< "    between the total number of compressed bits (including headers) and" << endl
	<< "    the area of the image; this is most easly thought of as the number" << endl
	<< "    of bits per pixel used in the compressed encoding. For example, an" << endl
	<< "    8-bit per pixel image might be encoded with a bit-rate of 2.5 to" << endl
	<< "    achieve a highly compressed codestream that still retains excellent" << endl
	<< "    image rendering quality. The bit-rate is logarithmically distributed" << endl
	<< "    over all of the quality levels." << endl
	<< endl
	<< "    Default: 0.0 (lossless encoding)" << endl << endl;

cout
	<< "  -Precinct_Sizes <width>[,<height>][:...]" << endl;
if (list_descriptions)
	cout
	<< "    The JPEG2000 image data is precinct structured. The size of these" << endl
	<< "    precincts is specified in width,height pixels. If only the first" << endl
	<< "    precinct size dimension is sepecified the precinct will be" << endl
	<< "    square. The precinct dimensions must be powers of 2. Precinct" << endl
	<< "    sizes may be specfied for each resolution level (the first" << endl
	<< "    resolution level is full resolution). If fewer precinct sizes" << endl
	<< "    have been specified than the number of resolution levels, the" << endl
	<< "    last precinct size specified will be used for all remaining" << endl
	<< "    resolution levels." << endl
	<< endl
	<< "    Default: " << DEFAULT_PRECINCT_SIZE << endl << endl;

cout
	<< "  -Code_block_size <width>[,<height>]" << endl;
if (list_descriptions)
	cout
	<< "    The basic structural unit of JPEG2000 image data is a code block." << endl
	<< "    This unit contains the image information for a small area of the" << endl
	<< "    image, which will not be greater than 64 by 64 pixels. If only one" << endl
	<< "    code block dimension is specified the code block size will be square." << endl
	<< endl
	<< "    Default: " << DEFAULT_CODE_BLOCK_SIZE << endl << endl;

cout
	<< "  -[Un]Signed" << endl;
if (list_descriptions)
	cout
	<< "    Normally the image data values are treated as signed or unsigned" << endl
	<< "    based on information from the input file PDS label: If the" << endl
	<< "    SAMPLE_TYPE parameter is present and its value contains the" << endl
	<< "    \"UNSIGNED\" string, the image data is treated as unsigned; if the" << endl
	<< "    value contains the \"SIGNED\" string the data is treated as signed." << endl
	<< "    This option determines the effective signedness of the image data" << endl
	<< "    values regardless of the PDS label parameter value." << endl
	<< endl
	<< "    Default: Pixel data of unknown signedness is "
		<< ((DEFAULT_SIGNED_DATA > 0) ? "" : "un") << "signed." << endl << endl;

cout
	<< "  -Lsb | -Msb" << endl;
if (list_descriptions)
	cout
	<< "    Normally the image data values are treated as MSB or LSB ordered" << endl
	<< "    based on information from the input file PDS label: If the" << endl
	<< "    SAMPLE_TYPE parameter is present and its value contains the" << endl
	<< "    \"MSB\" string, the image data is treated as MSB ordered; if the" << endl
	<< "    value contains the \"LSB\" string the data is treated as LSB ordered." << endl
	<< "    This option determines the effective signedness of the image data" << endl
	<< "    values regardless of the PDS label parameter value." << endl
	<< endl
	<< "    Default: Pixel data of unknown data order is "
		<< ((DEFAULT_DATA_ORDER > 0) ? "MSB" : "LSB") << '.' << endl << endl;

cout
	<< "  -ID <values>" << endl;
if (list_descriptions)
	{
	cout
	<< "    The data producer ID is stored in a UUID box of the JP2 file" << endl
	<< "    alongside the URL box that contains the relative file URL for the" << endl
	<< "    PDS label file. These boxes are encapsulated inside a UUID Info box." << endl
	<< "    A Universally Unique IDentifier (UUID; see" << endl
	<< "    http://www.webdav.org/specs/draft-leach-uuids-guids-01.txt) is" << endl
	<< "    16, comma separated (no spaces) 8-bit values that are intended to" << endl
	<< "    uniquely identify the data producer. Software for producing UUIDs" << endl
	<< "    is available on line (e.g. http://www.ossp.org/pkg/lib/uuid/). If a" << endl
	<< "    single 0, or the word \"none\", is specified a null (all zeros) UUID" << endl
	<< "    will be used." << endl
	<< endl;
#ifdef INCLUDE_OSSP_UUID
	cout
	<< "    The ID may alternatively be specified as a signature string; this is" << endl
	<< "    usually a URL such as \"http://hirise.lpl.arizona.edu/\". In this case" << endl
	<< "    the UUID values will be determined from the signature string." << endl
	<< endl;
#endif
	if (! DEFAULT_PRODUCER_UUID ||
		! sizeof (DEFAULT_PRODUCER_UUID))
		cout
		<< "    Default: Null (all zeros) UUID" << endl;
	else
		{
		cout
		<< "    Default: ";
		if (DEFAULT_PRODUCER_SIGNATURE)
			cout
			<< "Version 3 URL namespace UUID for \""
				<< DEFAULT_PRODUCER_SIGNATURE << "\" -" << endl
			<< "    ";
		cout << hex << setfill ('0');
		for (unsigned int
				index = 0;
				index < JP2_Box::UUID_SIZE;
				index++)
			{
			if (index)
				cout << ", ";
			cout << "0x" << setw (2) << ((int)DEFAULT_PRODUCER_UUID[index] & 0xFF);
			}
		cout << setfill (' ') << dec << endl;
		}
	cout << endl;
	}

#ifdef INCLUDE_GDAL
cout
	<< "  -Geotiff" << endl;
if (list_descriptions)
	{
	cout
	<< "    Add a GeoTIFF UUID box to the JP2 file if the necessary image" << endl
	<< "    projection parameters are available in the input file PDS label." << endl
	<< "    The GeoTIFF UUID signature is -" << endl
	<< "    " << hex << setfill ('0');
	for (unsigned int
			index = 0;
			index < JP2_Box::UUID_SIZE;
			index++)
		{
		if (index)
			cout << ", ";
		cout << "0x" << setw (2)
			<< ((int)PDS_Projection_Data::GEO_TIFF_UUID[index] & 0xFF);
		}
	cout
	<< setfill (' ') << dec << endl
	<< endl
	<< "    Default: No GeoTIFF box" << endl << endl;
	}

cout
	<< "  -GML" << endl;
if (list_descriptions)
	{
	cout
	<< "    Add GML boxes to the JP2 file if the necessary image" << endl
	<< "    projection parameters are available in the input file PDS label." << endl
	<< "    The GML boxes are contained in an Association (\"asoc\") super-box" << endl
	<< "    with an initial Label (\"lbl \") box with the text \"gml.data\"," << endl
	<< "    followed by an Association with a \"gml.root-instance\" label and" << endl
	<< "    an XML box with the \"gml:FeatureCollection\" specifications, and" << endl
	<< "    then an Association with a \"CRSDictionary.gml\" label and an XML" << endl
	<< "    box with the \"gml:Dictionary\" specifications." << endl
	<< endl
	<< "    Warning: This is an experimental feature. It has not been shown" << endl
	<< "    to produce correct results. It will have no affect on any other" << endl
	<< "    operation of the program nor on any other content of the JP2 file" << endl
	<< "    that is produced." << endl
	<< endl
	<< "    Default: No GML box" << endl << endl;
	}

cout
	<< "  -No_Version_Change" << endl;
if (list_descriptions)
	{
	cout
	<< "    For HiRISE data products ONLY: When the -Geotiff or -GML options" << endl
	<< "    are specified and the PDS label contains DATA_SET_ID and/or" << endl
	<< "    DATA_SET_NAME parameters with values that have a minor version" << endl
	<< "    number of 0 - a version number is a dot ('.') delimited pair of" << endl
	<< "    integer values where the first is the major version number and" << endl
	<< "    the second is the minor version number - the minor version number" << endl
	<< "    is reset to 1 in these parameters of the output PDS label. This" << endl
	<< "    option suppresses changing the version number." << endl
	<< endl
	<< "    Default: Change the version number if applicable" << endl << endl;
	}
#endif

cout
	<< "  -Help" << endl;
if (list_descriptions)
	cout
	<< "    Prints this usage description." << endl << endl;

exit (exit_status); 
}

/*==============================================================================
	Main
*/
/**	PDS_to_JP2 application.

	Converts a PDS image file having a label attached to uncompressed
	image data to a detached PDS label file and a JP2 image data file.

	<h3>Files:
	</h3>

	In input PDS file is required. The output PDS label file pathname
	always follows the JP2 file pathname but with the #LABEL_EXTENSION
	replacing the JP2 filename extension, or appended to it if it does
	not have an extension. If the -Output pathname is specified and does
	not refer to a directory, then that is the JP2 file pathname. If it
	does refer to a directory, then the input filename is used with the
	directory pathname but with the #JP2_EXTENSION replacing the input
	filename extension, or appended to it if it does not have an
	extension. If no -Output pathname is specified then the input
	pathname is used but with the #JP2_EXTENSION. Pathnames may be
	absolute or relative (to the current working directory). If files at
	either the output PDS label or JP2  pathnames exist and the -Force
	option has not been specified the program will exit with an
	#EXISTING_OUTPUT_FILE status; a warning will be provided in this case
	if the -Force option has been specified.

	A report listing the input and output files, the image data
	specifications and the JP2 configuration will be written to stdout
	before the input file is processed to generate the output files.

	<h4>PDS label -
	</h4>

	A {@link UA::HiRISE::PDS_Converter PDS_Converter} object
	instantiated on the input file is used to convert the input file PDS
	label to the new detatched label file. The selection of the
	appropriate PDS label converter is done by each registered PDS label
	converter examining the file's label and deciding if it is suitable
	for handling the conversion; the first one to indicate that it is
	appropriate for the input file is used. Product specific converters
	are queried first until finally the
	{@link UA::HiRISE::Generic_PDS_Converter Generic_PDS_Converter} is tried.

	If the label converter is unable to locate a group of parameters in the
	label that describes the <code>IMAGE</code> data block the program will
	exit with a #PDS_LABEL_ERROR status. If the
	{@link UA::HiRISE::Image_Data_Block Image_Data_Block}
	does not report a non-zero size, as determined from the
	<code>BANDS</code>, <code>LINES</code>, <code>LINE_SAMPLES</code> and
	<code>SAMPLE_BITS</code> parameters (the corresponding values default to
	zero if the parameter is not present, except <code>BANDS</code> which
	defaults to one), the program will exit with a
	#NO_IMAGE_DATA status. If <code>LINE_PREFIX_BYTES</code> or
	<code>LINE_SUFFIX_BYTES</code> are specified, they will be skipped
	during input image encoding. The image description parameters are used
	to set the JP2 encoder configuration. The <code>SAMPLE_BITS</code>
	parameter determines the number of bits per pixel unless a
	<code>SAMPLE_BIT_MASK</code> parameter is provided. The JP2 encoder is
	capable of processing from 1 to 16 bits per pixel. Source image pixel data
	is expected to be contained in whole bytes; thus an image with 10 bits
	per pixel will use 2 bytes of storage per pixel and the extra bits will
	be ignored by the JP2_Encoder.

	Product specific {@link UA::HiRISE::converter_for(const std::string&)
	PDS label converters} may apply any label changes
	deemed appropriate in addition to, or instead of, using the {@link
	UA::HiRISE::Generic_PDS_Converter Generic_PDS_Converter}. The
	generic label converter ensures that a {@link
	UA::HiRISE::PDS_Converter::PDS_JP2_image_parameters(const std::string&)
	standard compliant PDS/JP2 label} is generated. <b>N.B.</b>: the
	generic label converter will remove all data block descriptions from
	the label except the <code>IMAGE</code> description which is moved to
	its appropriate location in the new label.

	Note: Before the PDS label converter is requested to write the new label
	file the <code>SOFTWARE_NAME</code> parameter in the label, if it
	exists, is updated with the application identification.

	<h4>JP2 -
	</h4>

	A {@link UA::HiRISE::JP2_Encoder JP2_Encoder} object is used to generate the JP2 file containing the
	compressed image data from the input file. The JP2 file conforms to the
	<a href="http://www.jpeg.org/jpeg2000/">JPEG2000</a>
	Part 1 standard (ISO/IEC 15444-1:2004). The input image data will be
	written as a losslessly compressed JPEG2000 codestream contained in the
	JP2 file. The input image data must be organized as column major band
	sequential pixels. If <code>LINE_PREFIX_BYTES</code> and/or
	<code>LINE_SUFFIX_BYTES</code> parameters are present in the PDS label
	the corresponding bytes in the input file will be skipped.
	The encoder is given the input file pathname and the starting
	location of the image data in the input file and image data description
	provided by the PDS_Converter. The encoder is configured with
	additional codestream structural information - tile, precinct and code
	block sizes, progression order and resolution levels - provided by
	command line options or default values. <b>N.B.</b>: The default values
	have been chosen to produce a JPEG2000 codestream that should be
	optimally structured for most JP2 file readers. However, the choice of
	precinct sizes and, in particular, tiling may have a significant effect
	for some readers. The encoder will include both tile and packet location
	markers in the JPEG2000 codestream to assist rendering software in
	accessing the image data from large files as quickly as possible.
	Nevertheless, some rendering software will not recognize these markers;
	and some software may be overwhelmed by large images that are not tiled.

	In addition to the JPEG2000 codestream the JP2 file contains
	metadata "boxes" that describe the image data. A UUID List box will
	always be included that contains a UUID box with the producer
	signature specifed by the -ID option or the default value alongside
	a URL box which names the detatched PDS label file. If the -Geotiff
	and/or -GML command line options have been specified a
	PDS_Projection_Data object will be instantiated on the PDS_Converter
	object. This will use the <code>IMAGE_MAP_PROJECTION</code>
	parameters of the PDS label to construct a spatial reference
	description from which GeoTIFF and/or GML formatted data content is
	produced and then encapsulated in appropriate JP2 boxes that are
	passed to the encoder for inclusion in the JP2 file.

	Note: Generating the JPEG2000 codestream can be a very resource intensive
	process. In particular, unless incremental codestream flushing was
	enabled when the software was compiled (which is generally not
	recommened due to the codestream structural complications this creates)
	the entire codestream is held in memory until it is complete before
	being written to the JP2 file.

	<h3>Exit status values:
	</h3>

	<dl>
	<dt>#SUCCESS</dt>
	<dd>The application completed successfully.</dd>
	<dt>#BAD_SYNTAX</dt>
	<dd>There was a syntax problem in the command line. A description of
		the problem followed by a brief command line syntax summary will
		be written to stdout.</dd>
	<dt>#INVALID_ARGUMENT</dt>
	<dd>An invalid software function argument exception was encountered.
		A description of the error will be written to stdout. This error
		may indicate a bug in the software so the complete error
		description should be reported to the application software
		development contact.</dd>
	<dt>#PDS_LABEL_ERROR</dt>
	<dd>There was a problem with the PDS label. A description of the
		problem will be written to stdout. This problem is typically the
		result of specifying an input file for processing that is not a
		valid PDS image file.</dd>
	<dt>#NO_IMAGE_DATA</dt>
	<dd>The PDS label indicates that the file does not contain any image
		data. Check the label for a complete set of valid IMAGE
		parameters.</dd>
	<dt>#LOGIC_ERROR</dt>
	<dd>A logic error was detected in the software. A description of the
		error will be written to stdout. This error may indicate a bug
		in the software so the complete error description should be
		reported to the application software development contact.</dd>
	<dt>#NO_INPUT_FILE</dt>
	<dd>No input file was specified on the command line or the file
		could not be accessed from the filesystem. Check that the input
		file exists at the specified pathname and its permissions allow
		read access to the user.
	<dt>#EXISTING_OUTPUT_FILE</dt>
	<dd>A label or JP2 file at the intended output pathname already
		exists. Use the -Force option if existing files are to be
		overwritten.</dd>
	<dt>#IO_FAILURE</dt>
	<dd>A filesystem I/O failure has occurred. A likely cause of the
		failure is insufficient user permissions to write the output
		file or running out of space on the storage volume.</dd>
	<dt>#PVL_ERROR</dt>
	<dd>An exception occurred while managing the Parameter Value
		Language of a PDS label. A description of the error will be
		written to stdout. This may be due to an invalid PDS label that
		can not be parsed. If the input file label is valid then the
		complete error description should be reported to the application
		software development contact.</dd>
	<dt>#ENCODER_ERROR</dt>
	<dd>An exception occurred while encoding the input image data into
		the JPEG2000 codestream. This may be due to the exhaustion of
		system resources, such as available memory or storage
		capacity.</dd>
	<dt>#UNKNOWN_ERROR</dt>
	<dd>An unanticipated exception occurred. This error may indicate a
		bug in the software so the complete error description should be
		reported to the application software development contact.</dd>
	</dl>

	@param	argument_count	The number of command line arguments.
	@param	arguments	The array of command line arguments.
	@see	#usage(int, bool)

	@author		Bradford Castalia, Andrew Davidson and Ben Pearson; UA/HiROC
	@version	1.55
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

/*------------------------------------------------------------------------------
   Default initialization
*/
Size_2D
	tile_size (DEFAULT_TILE_SIZE, DEFAULT_TILE_SIZE),
	code_block_size (0, 0);
int
	resolution_levels	= 0,
	quality_layers		= 0,
	index				= 0;
double
	bit_rate			= 0;
string
	option,
	argument,
	source_pathname,
   source_directory,
	destination,
	progression_order (DEFAULT_PROGRESSION_ORDER),
	text;

vector<Size_2D>
	precinct_sizes;

//	Tri-state flags: false (-), true (+), default (0).
int
	signed_data			= 0,
	MSB_data			= 0;
char
	*producer_signature	= NULL;
unsigned char
	*producer_ID		= NULL;
bool
	no_output			= false,
	force_overwrite		= false;
#ifdef INCLUDE_GDAL
bool
	add_GeoTIFF_box		= false,
	add_GML_box			= false,
	no_version_change	= false;
#endif
char
	*character,
	*number_string;

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
		option = arguments[count];
		switch (toupper (arguments[count][1]))
			{
			case 'O':	//	Output directory.
				if (++count == argument_count || 
					arguments[count][0] == '-')
					{
					Missing_Value:
					cout << "Missing " << option << " value." << endl
						 << endl;
					usage ();
					}
				if (! destination.empty ())
					{
					cout << "Only one " << option
							<< " output directory, please." << endl
						 << "   First directory: "
						 	<< destination << endl
						 << "  Second directory: "
						 	<< arguments[count] << endl
						 << endl;
					usage ();
					}
				destination = arguments[count];
				break;

			case 'I':	//	Input pathname.
				if (toupper (arguments[count][2]) != 'D')
					{
					if (++count == argument_count || 
						arguments[count][0] == '-')
						goto Missing_Value;
					goto Input_Pathname;
					}

				//	Producer ID.
				if (++count == argument_count || 
					arguments[count][0] == '-')
					goto Missing_Value;
				if (producer_ID)
					{
					cout << "Only one " << option
							<< " producer ID, please." << endl
						 << endl;
					usage ();
					}
				producer_ID = new unsigned char[JP2_Encoder::UUID_SIZE];
				argument = arguments[count];
				for (index = 0,
						number_string = strtok (arguments[count], ",");
						number_string;
					 index++,
						number_string = strtok (NULL, ","))
					{
					if (index == JP2_Encoder::UUID_SIZE)
						{
						cout << "Too many " << option
								<< " producer ID values: " << argument << endl
							 << "Exactly " << JP2_Encoder::UUID_SIZE
							 	<< " are required." << endl
							 << endl;
						usage ();
						}
					producer_ID[index] =
						(char)(strtol (number_string, &character, 0) & 0xFF);
					if (*character)
						{
						#ifdef INCLUDE_OSSP_UUID
						if (! index)
							{
							if (strlen (number_string) == 4 &&
								toupper (number_string[0]) == 'N' &&
								toupper (number_string[1]) == 'O' &&
								toupper (number_string[2]) == 'N' &&
								toupper (number_string[3]) == 'E')
								goto No_Signature;

							producer_signature = number_string;
							delete [] producer_ID;
							producer_ID = UUID (producer_signature);
							break;
							}
						#endif

						Not_a_Number:
						cout << "Invalid " << option << " argument: "
								<< argument << endl
							 << "Number expected; found \""
								<< number_string << '"' << endl
							 << endl;
						usage ();
						}
					}
				if (producer_signature)
					break;
				if (index < JP2_Encoder::UUID_SIZE)
					{
					if (index != 1 ||
						producer_ID[0] != 0)
						{
						cout << "Too few " << option
								<< " producer ID values: " << argument << endl
							 << "Exactly " << JP2_Encoder::UUID_SIZE
								<< " are required;"
								<< " or a single '0' or \"none\" for a null ID." << endl
							 << endl;
						usage ();
						}
					else
						{
						//	No UUID signature is to be used.
						No_Signature:
						for (index = 0;
							 index < JP2_Encoder::UUID_SIZE;
							 index++)
							producer_ID[index] = 0;
						}
					}
				break;

			case 'P':
				if (strchr (arguments[count], 'o') ||
					strchr (arguments[count], 'O'))
					{
					//	Progression Order.
					if (++count == argument_count || 
						arguments[count][0] == '-')
						goto Missing_Value;
					for (index = 0;
						 arguments[count][index];
						 index++)
						{
						if (index == 4)
							{
							cout << "Too many " << option
									<< " progression order indicators: "
									<< arguments[count] << endl
								 << "Exactly 4 are required." << endl
								 << endl;
							usage ();
							}
						char
							character = toupper (arguments[count][index]);
						if (character == 'R' ||
							character == 'P' ||
							character == 'C' ||
							character == 'L')
							{
							if (progression_order.find (character)
									== string::npos)
								progression_order += character;
							else
								{
								cout << "Duplicate " << option
										<< " progression order indicator '"
										<< arguments[count][index] << "' in "
										<< arguments[count] << endl
									 << endl;
								usage ();
								}
							}
						else
							{
							cout << "Invalid " << option
									<< " progression order indicator '"
									<< arguments[count][index] << "' in "
									<< arguments[count] << endl
								 << endl;
							usage ();
							}
						}
					if (progression_order.size () != 4)
						{
						cout << "Insufficient " << option
								<< " progression order indicators: "
								<< arguments[count] << endl
							 << "Exactly 4 are required." << endl
							 << endl;
						usage ();
						}
					}
				else
					{
					//	Precinct Sizes.
					if (++count == argument_count ||
						*arguments[count] == '-')
						goto Missing_Value;
					argument = arguments[count];
					Size_2D
						size;
					for (number_string = strtok (arguments[count], ":");
						 number_string;
						 number_string = strtok (NULL, ":"))
						{
						text = number_string;
						size.Width =
							(unsigned int)strtol
								(number_string, &character, 0);
						if (*character)
							{
							if (*character != ',')
								goto Not_a_Number;
							number_string = ++character;
							size.Height =
								(unsigned int)strtol
									(number_string, &character, 0);
							if (*character)
								goto Not_a_Number;
							}
						else
							size.Height = size.Width;

						if (! size.Width ||
							! power_of_2 (size.Width) ||
							! size.Height ||
							! power_of_2 (size.Height))
							{
							cout << "Invalid " << option << " precinct size \""
									<< text << "\" in " << argument << endl
								 << "Precinct sizes must be non-zero powers of 2."
								 	<< endl
								 << endl;
							usage ();
							}
						precinct_sizes.push_back (size);
						}
					}
				break;

			case 'T':	//	Tile size.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				argument = number_string = arguments[count];
				tile_size.Width = strtol (arguments[count], &character, 0);
				if (*character)
					{
					if (*character != ',')
						goto Not_a_Number;
					number_string = ++character;
					tile_size.Height = strtol (number_string, &character, 0);
					if (*character)
						goto Not_a_Number;
					}
				else
					tile_size.Height = tile_size.Width;
				break;

			case 'C':	//	Code block size.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				argument = number_string = arguments[count];
				code_block_size.Width
					= strtol (number_string, &character, 0);
				if (*character)
					{
					if (*character != ',')
						goto Not_a_Number;
					number_string = ++character;
					code_block_size.Height
						= strtol (number_string, &character, 0);
					if (*character)
						goto Not_a_Number;
					}
				else
					code_block_size.Height = code_block_size.Width;
				if (! code_block_size.Width ||
					! code_block_size.Height ||
					code_block_size.Width > 64 ||
					code_block_size.Height > 64)
					{
					cout << "Invalid " << option << " code block size: "
							<< argument << endl
						 << "Code block sizes must be > 0 and <= 64." << endl
						 << endl;
					usage ();
					}
				break;

			case 'R':	//	Resolution levels.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				argument = number_string = arguments[count];
				resolution_levels = strtol (number_string, &character, 0);
				if (*character)
					goto Not_a_Number;
				if (resolution_levels < 0 ||
					resolution_levels > MAX_RESOLUTION_LEVELS)
					{
					cout << "Invalid " << option
							<< " resolution levels: "
							<< resolution_levels << endl
						 << "The number of resolution levels must be > 0 and <= "
						 	<< MAX_RESOLUTION_LEVELS << "." << endl
						 << endl;
					usage ();
					}
				break;

			case 'Q':	//	Quality layers.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				argument = number_string = arguments[count];
				quality_layers = strtol (number_string, &character, 0);
				if (*character)
					goto Not_a_Number;
				if (quality_layers < 1 ||
					quality_layers > MAX_QUALITY_LAYERS)
					{
					cout << "Invalid " << option
							<< " quality layers: "
							<< quality_layers << endl
						 << "The number of quality layers must be > 0 and <= "
						 	<< MAX_QUALITY_LAYERS << "." << endl
						 << endl;
					usage ();
					}
				break;

			case 'B':	//	Bit-rate.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				argument = number_string = arguments[count];
				bit_rate = strtod (number_string, &character);
				if (*character)
					goto Not_a_Number;
				if (bit_rate < 0.0)
					bit_rate = 0.0;
				break;

			case 'S':	//	Signed data.
				signed_data = 1;
				break;
			case 'U':	//	Unsigned data.
				signed_data = -1;
				break;

			case 'L':	//	LSB data.
				MSB_data = -1;
				break;
			case 'M':	//	MSB data.
				MSB_data = 1;
				break;

			case 'N':
				if ((strchr (arguments[count], 'V') ||
					 strchr (arguments[count], 'v')) &&
					(strchr (arguments[count], 'C') ||
					 strchr (arguments[count], 'c')))
					//	No Version Change.
					no_version_change = true;
				else
					//	No output.
					no_output = true;
				break;

			case 'F':	//	Force output.
				force_overwrite = true;
				break;

			#ifdef INCLUDE_GDAL
			case 'G':
				if ((strchr (arguments[count], 'M') ||
					 strchr (arguments[count], 'm')) &&
					(strchr (arguments[count], 'L') ||
					 strchr (arguments[count], 'l')))
					//	GML box.
					add_GML_box = true;
				else
					//	Geo_TIFF box.
					add_GeoTIFF_box = true;
				break;
			#endif

			case 'H':	//	Help.
				usage (SUCCESS, true);
				break;

			default:
				cout << "Unrecognized option: "  << option << endl
					 << endl;
				usage ();
			}
		}
	else
		{
		Input_Pathname:
		if (! source_pathname.empty ())
			{
			cout << "Only one input file, please." << endl
				 << "   First pathname: " << source_pathname << endl
				 << "  Second pathname: " << arguments[count] << endl
				 << endl;
			usage ();
			}
		  source_pathname = arguments[count];
		  }
	 }
if (source_pathname.empty ())
	{
	cout << "Missing source file." << endl
		 << endl;
	usage (NO_INPUT_FILE);
    }


//	Host system.
cout
	<< endl
	<< setw (LABEL_WIDTH) << "Processing host: "
		<< setw (VALUE_WIDTH) << hostname () << endl;


JP2_Encoder
	JP2_encoder;
string
	error_report;
int
	exit_status = SUCCESS;
try
{
/*------------------------------------------------------------------------------
   PDS input
*/
cout
	<< endl
	<< "PDS input -" << endl;

// relative to absolute
source_pathname = file_pathname (source_pathname);

// get directory for resolving detached files
source_directory = file_directory(source_pathname);

cout
	<< setw (LABEL_WIDTH) << "PDS file pathname: "
		<< source_pathname <<endl;
if (! file_is_readable (source_pathname))
	{
    cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "Can't access the PDS file." << endl;
	exit (NO_INPUT_FILE);
	}
if (file_is_directory (source_pathname))
	{
    cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "The pathname is for a directory." << endl;
	exit (NO_INPUT_FILE);
	}


//	PDS label.
PDS_Converter
	*label_converter = NULL;
const char
	*message = NULL;
try {label_converter = converter_for (source_pathname);}
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

//	Source image description:

Image_Data_Block
	*image_metadata = label_converter->image_data ();
if (! image_metadata)
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "No " << label_converter->IMAGE_DATA_BLOCK_NAME
			<< " was found in the PDS label." << endl;
	exit (PDS_LABEL_ERROR);
	}
if (! image_metadata->size ())
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "The image source does not contain any image data." << endl;
	if (! no_output)
		exit (NO_IMAGE_DATA);
	}
if (! image_metadata->pixel_bytes ())
	{
	cout
		<< setw (LABEL_WIDTH) << "!!! "
			<< "No " << Image_Data_Block::PIXEL_BYTES_PARAMETER_NAME
			<< " was found in the PDS label." << endl;
	if (! no_output)
		exit (PDS_LABEL_ERROR);
	}

if (signed_data &&
	image_metadata->signed_data () &&
	image_metadata->signed_data () != signed_data)
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "Image label data signedness overridden." << endl;
if (! signed_data &&
	! (signed_data = image_metadata->signed_data ()))
	{
	signed_data = DEFAULT_SIGNED_DATA;
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "Image data signedness unknown," << endl
		<< setw (LABEL_WIDTH) << ""
			<< "so it is assumed by default to be "
		 	<< ((signed_data < 0) ? "un" : "") << "signed." << endl;
	}
if (signed_data < 0)
	signed_data = 0;

if (MSB_data &&
	image_metadata->MSB_data () &&
	image_metadata->MSB_data () != MSB_data &&
	image_metadata->pixel_bytes () > 1)
	cout
		<< setw (LABEL_WIDTH) << "*** "
			<< "Image label data order overridden." << endl;
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

cout << endl
	<< setw (LABEL_WIDTH) << "PDS image -" << endl
	<< setw (LABEL_WIDTH) << "Bytes per pixel: "
		<< setw (VALUE_WIDTH) << image_metadata->pixel_bytes () << endl
	<< setw (LABEL_WIDTH) << "Bits per pixel: "
		<< setw (VALUE_WIDTH) << image_metadata->pixel_bits () << endl
	<< setw (LABEL_WIDTH) << "Pixels per line: "
		<< setw (VALUE_WIDTH) << image_metadata->image_width () << endl
	<< setw (LABEL_WIDTH) << "Lines per band: "
		<< setw (VALUE_WIDTH) << image_metadata->image_height () << endl
	<< setw (LABEL_WIDTH) << "Bands per image: "
		<< setw (VALUE_WIDTH) << image_metadata->image_bands () << endl
	<< setw (LABEL_WIDTH) << "Signed data: "
		<< setw (VALUE_WIDTH) << (signed_data ? "true" : "false") << endl
	<< setw (LABEL_WIDTH) << "Data order: "
		<< setw (VALUE_WIDTH) << (MSB_data ? "MSB" : "LSB") << endl;

if (image_metadata->line_prefix_bytes ())
	cout
	<< setw (LABEL_WIDTH) << "Line prefix: "
		<< setw (VALUE_WIDTH) << image_metadata->line_prefix_bytes ()
			<< " byte"
			<< ((image_metadata->line_prefix_bytes () == 1) ? "" : "s") << endl;
if (image_metadata->line_suffix_bytes ())
	cout
	<< setw (LABEL_WIDTH) << "Line suffix: "
		<< setw (VALUE_WIDTH) << image_metadata->line_suffix_bytes ()
			<< " byte"
			<< ((image_metadata->line_suffix_bytes () == 1) ? "" : "s") << endl;

/*------------------------------------------------------------------------------
   JP2 output
*/
//	Determine the destination pathnames.
string
	JP2_pathname,
	PDS_label_pathname;

if (destination.empty ())
	{
	//	Use the source pathname.
	destination = file_basename (file_pathname (source_pathname));
	JP2_pathname = destination + JP2_EXTENSION;
	PDS_label_pathname = destination + LABEL_EXTENSION;
	}
else
	{
	if (file_is_directory (destination))
		{
		//	Use the destination directory plus the source filename.
		destination = file_pathname (destination,
			file_basename (file_name (source_pathname)));
		JP2_pathname = destination + JP2_EXTENSION;
		PDS_label_pathname = destination + LABEL_EXTENSION;
		}
	else
		{
		//	Use the destination file pathname.
		JP2_pathname = file_pathname (destination);
		PDS_label_pathname = file_basename (JP2_pathname) + LABEL_EXTENSION;
		}
	}

cout
	<< endl
	<< "PDS/JP2 output -" << endl
	<< setw (LABEL_WIDTH) << "Label file pathname: "
		<< PDS_label_pathname << endl;
if (file_exists (PDS_label_pathname))
	{
	if (force_overwrite)
		cout
			<< setw (LABEL_WIDTH) << "*** "
			<< "An existing label file will be overwritten." << endl;
	else
		{
		cout
			<< setw (LABEL_WIDTH) << "!!! "
			<< "An existing label file will not be overwritten." << endl;
		if (! no_output)
			exit (EXISTING_OUTPUT_FILE);
		}
	}

cout
	<< setw (LABEL_WIDTH) << "JP2 file pathname: "
		<< JP2_pathname << endl;
if (file_exists (JP2_pathname))
	{
	if (force_overwrite)
		cout
			<< setw (LABEL_WIDTH) << "*** "
			<< "An existing JP2 file will be overwritten." << endl;
	else
		{
		cout
			<< setw (LABEL_WIDTH) << "!!! "
			<< "An existing JP2 file will not be overwritten." << endl;
		if (! no_output)
			exit (EXISTING_OUTPUT_FILE);
		}
	}

//	JP2 codestream specifications.

if (tile_size.Width == 0 ||
	tile_size.Width > image_metadata->image_width ())
	tile_size.Width = image_metadata->image_width ();
if (tile_size.Height == 0 ||
	tile_size.Height > image_metadata->image_height ())
	tile_size.Height = image_metadata->image_height ();

if (! resolution_levels)
	resolution_levels = recommended_resolution_levels
		(image_metadata->image_width (), image_metadata->image_height ());

cout
	<< endl
	<< setw (LABEL_WIDTH) << "JP2 image -" << endl
	<< setw (LABEL_WIDTH) << "Tile size: "
		<< setw (VALUE_WIDTH - 1)
		<< tile_size.Width << "w, "
		<< tile_size.Height << "h" << endl
	<< setw (LABEL_WIDTH) << "Resolution levels: "
		<< setw (VALUE_WIDTH) << resolution_levels << endl;

if (bit_rate > 0.0)
	{
	if (! quality_layers)
		quality_layers = DEFAULT_LOSSY_QUALITY_LAYERS;
	cout << setw (LABEL_WIDTH) << "Lossy bit rate: "
			<< setw (VALUE_WIDTH) << bit_rate << endl;
	}
else
	cout << setw (LABEL_WIDTH) << "Lossless encoding. " << endl;

if (! quality_layers)
	quality_layers = 1;
cout << setw (LABEL_WIDTH) << "Quality layers: "
		<< setw (VALUE_WIDTH) << quality_layers << endl;

if (! precinct_sizes.size ())
	precinct_sizes.push_back
		(Size_2D (DEFAULT_PRECINCT_SIZE, DEFAULT_PRECINCT_SIZE));

cout << setw (LABEL_WIDTH) << "Precinct sizes: " << "0 - "
		<< setw (VALUE_WIDTH - 5)
		<< precinct_sizes[0].Width << "w, "
		<< precinct_sizes[0].Height << "h" << endl;
int
	count = precinct_sizes.size ();
for (index = 1;
	 index < resolution_levels &&
	 index < count;
	 index++)
	cout << setw (LABEL_WIDTH + 1) << index << " - "
		<< setw (VALUE_WIDTH - 5)
		<< precinct_sizes[index].Width << "w, "
		<< precinct_sizes[index].Height << "h" << endl;
if (index < resolution_levels)
	for (--count;
		 index < resolution_levels;
		 index++)
		cout << setw (LABEL_WIDTH + 1) << index << " - "
			<< setw (VALUE_WIDTH - 5)
			<< precinct_sizes[count].Width << "w, "
			<< precinct_sizes[count].Height << "h" << endl;

if (! code_block_size.Width)
	code_block_size.Width =
	code_block_size.Height = DEFAULT_CODE_BLOCK_SIZE;
cout
	<< setw (LABEL_WIDTH) << "Code block size: "
	<< setw (VALUE_WIDTH - 1)
	<< code_block_size.Width << "w, "
	<< code_block_size.Height << "h" << endl;

cout
	<< setw (LABEL_WIDTH) << "Progression Order: ";
for (index = 0;
	 index < (int)progression_order.length ();
	 index++)
    {
    if (index)
		cout << "-";
	switch (progression_order[index])
		{
		case 'R': cout << "Resolution";	break;
		case 'P': cout << "Precinct";	break;
		case 'C': cout << "Component";	break;
		case 'L': cout << "Level";		break;
		}
    }
cout << endl;

cout << setw (LABEL_WIDTH) << "Producer ID: ";
if (! producer_ID &&
	DEFAULT_PRODUCER_UUID &&
	sizeof (DEFAULT_PRODUCER_UUID))
	{
	producer_ID = new unsigned char[JP2_Encoder::UUID_SIZE];
	for (index = 0;
		 index < JP2_Encoder::UUID_SIZE;
		 index++)
		producer_ID[index] = DEFAULT_PRODUCER_UUID[index];
	if (DEFAULT_PRODUCER_SIGNATURE)
		producer_signature = const_cast<char*>(DEFAULT_PRODUCER_SIGNATURE);
	}
if (producer_ID)
	{
	for (index = 0;
		 index < JP2_Encoder::UUID_SIZE;
		 index++)
		if (producer_ID[index])
			//	Non-null producer_ID.
			break;
	if (index == JP2_Encoder::UUID_SIZE)
		producer_ID = NULL;
	}
if (producer_ID)
	{
	cout << hex << setfill ('0');
	for (index = 0;
		 index < JP2_Encoder::UUID_SIZE;
		 index++)
		{
		if (index)
			cout << ", ";
		cout << "0x" << setw (2) << ((int)producer_ID[index] & 0xFF);
		}
	cout << setfill (' ') << dec << endl;

	if (producer_signature)
		cout << setw (LABEL_WIDTH) << "Producer signature: "
				<< producer_signature << endl;
	}
else
	cout << "None" << endl;

PDS_Data
	*conversion_parameters = NULL;
#ifdef INCLUDE_GDAL
//	Attempt to assemble projection data for GeoTIFF and GML JP2 boxes.
JP2_Box
	*Geo_TIFF_box = NULL,
	*GML_box = NULL;
if (add_GeoTIFF_box ||
	add_GML_box)
	{
	try
		{
		PDS_Projection_Data
			*PDS_projection_data = new PDS_Projection_Data (*label_converter);
		if (add_GeoTIFF_box)
			{
			Geo_TIFF_box = PDS_projection_data->JP2_GeoTIFF ();
			if (! conversion_parameters)
				conversion_parameters = new PDS_Data ();
			conversion_parameters->add
				(Assignment (PDS_Converter::GeoTIFF_PARAMETER_NAME)
					= String ("TRUE"));
			}
		if (add_GML_box)
			{
			GML_box = PDS_projection_data->JP2_GML
				(image_metadata->image_width (),
				 image_metadata->image_height ());
				conversion_parameters = new PDS_Data ();
			conversion_parameters->add
				(Assignment (PDS_Converter::GML_PARAMETER_NAME)
					= String ("TRUE"));
			}
		}
	catch (idaeim::Exception& except)
		{error_report = except.what ();}
	catch (exception& except)
		{error_report = except.what ();}
	if (add_GeoTIFF_box)
		cout << setw (LABEL_WIDTH) << "GeoTIFF JP2 box: "
				<< (Geo_TIFF_box ? "Provided" : "Not available") << endl;
	if (add_GML_box)
		cout << setw (LABEL_WIDTH) << "GML JP2 box: "
				<< (GML_box ? "Provided" : "Not available") << endl;
	if (! error_report.empty ())
		{
		cout << setw (LABEL_WIDTH) << "No GeoTIFF/GML: "
				<< "The reason it is not available -" << endl
			 << indent (error_report, LABEL_WIDTH) << endl;
		error_report.erase ();
		}
	}

if (no_version_change)
	{
	if (! conversion_parameters)
		conversion_parameters = new PDS_Data ();
	conversion_parameters->add
		(Assignment (PDS_Converter::NO_VERSION_CHANGE_PARAMETER_NAME)
			= String ("TRUE"));
	}
#endif

cout << endl;

//..............................................................................

//	Try to reset the SOFTWARE_NAME_PARAMETER.
label_converter->parameter_value (SOFTWARE_NAME_PARAMETER, ID);

if (! no_output)
	//	Write the converted PDS label file.
	label_converter->write_PDS_JP2_label (PDS_label_pathname, JP2_pathname,
		NULL, conversion_parameters);

//	Configure the JP2 encoder.
#if ((DEBUG) & DEBUG_ENCODE)
clog << "Configuring the JP2_Encoder" << endl;
#endif

std::string source_filename = image_metadata->source_filename();
if (source_filename.empty()) source_filename = source_pathname;
else if (! file_exists(source_filename)) // need to resolve
{
#if ((DEBUG) & DEBUG_ENCODE)
   clog << "Attempting to resolve the path to " << source_filename << " using directory " << source_directory << endl;
#endif

   image_metadata->source_filename(source_filename = file_pathname(source_directory, file_name(source_filename)));

#if ((DEBUG) & DEBUG_ENCODE)
   clog << "Checking path resolution for " << source_filename << endl;
#endif

   if (! file_exists(source_filename))
   {
      throw invalid_argument("Could not resolve detached data from " + source_pathname);
   }

   if (PDS_label_pathname == source_filename)
   {
      throw invalid_argument("input and output are the same");
   }
}

JP2_encoder

	//	PDS specifications.
	.source					(source_filename)
	.image_data_location	(image_metadata->location ())
	.image_bands			(image_metadata->image_bands ())
	.image_size				(Size_2D
							(image_metadata->image_width (),
							 image_metadata->image_height ()))
	.pixel_bytes			(image_metadata->pixel_bytes ())
	.pixel_bits				(image_metadata->pixel_bits ())
	.signed_data			(signed_data)
	.MSB_data				(MSB_data)
	.line_prefix_bytes		(image_metadata->line_prefix_bytes ())
	.line_suffix_bytes		(image_metadata->line_suffix_bytes ())

	//	JP2 specifications.
	.destination			(JP2_pathname)
	.PDS_label_pathname		(PDS_label_pathname)
	.comment				(ID)
	.producer_UUID			(producer_ID)
	.tile_size				(tile_size)
	.resolution_levels		(resolution_levels)
	.quality_layers			(quality_layers)
	.bit_rate				(bit_rate)
	.precinct_sizes			(precinct_sizes)
	.code_block_size		(code_block_size)
	.progression_order		(progression_order)
	#ifdef INCLUDE_GDAL
	.add_box				(Geo_TIFF_box)
	.add_box				(GML_box)
	#endif
	;

if (! no_output)
	{
	//	Write the JP2 image data file.
	/*	!!! Bug:

		On OS X Darwin platforms the number of bytes written is always
		returned as 0. Other platforms report the correct value.
	*/
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "Starting the JP2_Encoder" << endl;
	#endif
	JP2_encoder.encode ();
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "JP2_Encoder done" << endl;
	#endif
	}
}
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
	if (except == JP2_Encoder::ENCODER_EXCEPTION)
		{
		error_report += string ("JP2 Encoder error: ")
			+ JP2_encoder.encoder_error ()->Message;
		exit_status = ENCODER_ERROR;
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
	{
	#if ((DEBUG) & DEBUG_EXCEPTIONS)
	clog << "PDS_to_JP2 exit status: " << exit_status << endl;
	#endif
	cout << "!!! " << error_report << endl;
	}
exit (exit_status);
}

/*==============================================================================
	Local Functions: Definitions
*/
/**	Determines the recommended number of resolution levels.

	The minimum of the image width and height is used to determine
	the number of resolution levels. While the minimum dimension
	value is larger than the #MIN_RESOLUTION_SIZE the dimension
	value is halved and the number of resolution levels is increased
	from its intial value of zero. When the dimension value falls
	below the minimum the the final resolution values is returned,
	or one if the initial minimum dimension was less than the
	#MIN_RESOLUTION_SIZE.

	@param	width	The image width.
	@param	height	The image height.
	@return	The recommended number of resolution levels for the image.
*/
int
recommended_resolution_levels
	(
	int		width,
	int		height
	)
{
#if ((DEBUG) & DEBUG_HELPERS)
clog << ">>> recommended_resolution_levels: " << width << ',' << height << endl;
#endif
int
	levels = 1,
	min_size = (width > height) ? height : width;
#if ((DEBUG) & DEBUG_HELPERS)
clog << "    min_size = " << min_size << endl;
#endif
while (min_size > MIN_RESOLUTION_SIZE &&
		levels < MAX_RESOLUTION_LEVELS)
	{
	++levels;
	min_size >>= 1;		
	#if ((DEBUG) & DEBUG_HELPERS)
	clog
		<< "    levels = "<< levels << endl
		<< "    min_size = "<< min_size << endl;
	#endif
	}
#if ((DEBUG) & DEBUG_HELPERS)
clog << "<<< recommended_resolution_levels: " << levels << endl;
#endif
return levels;
}

/**	Provides a UUID for a signature string.

	A version 3 URL namespace UUID is generated from the signature string.

	@param	signature	The signature string.
	@return	A pointer to the 16 UUID bytes. If a NULL signature was
		specified, NULL is returned. <b>N.B.</b>: If INCLUDE_OSSP_UUID
		was not defined at compile time to provide support for the OSSP
		uuid library that generates the UUID values then NULL is always
		returned.
*/
unsigned char*
UUID
	(
	const char*	signature
	)
{
#ifdef	INCLUDE_OSSP_UUID
if (! signature)
	return NULL;
uuid
	UUID,
	UUID_ns;
UUID_ns.load ("ns:URL");
UUID.make (UUID_MAKE_V3, &UUID_ns, signature);
return (unsigned char*)UUID.binary ();
#else
return NULL;
#endif
}
