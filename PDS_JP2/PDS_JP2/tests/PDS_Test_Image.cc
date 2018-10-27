/*	PDS_Test_Image

CVS ID: PDS_Test_Image.cc,v 1.9 2011/07/16 02:59:29 castalia Exp

Copyright (C) 2006 Arizona Board of Regents on behalf of the
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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "PVL.hh"
using namespace idaeim::PVL;

/*==============================================================================
	Constants
*/
const char* const
	ID =
		"PDS_Test_Image (1.9 2011/07/16 02:59:29)";

const int
	LABEL_SIZE			= 3000;

const char* const
	FILENAME_EXTENSION	= ".IMG";

enum
	{
	LINEAR_DATA,
	GRADIENT_DATA,
	RANDOM_DATA
	};
const char*
	DATA_PATTERN_NAMES[] =
	{
	"linear",
	"gradient",
	"random"
	};
const int
	DEFAULT_DATA_PATTERN = LINEAR_DATA;

enum
	{
	SUCCESS				= 0,
	SYNTAX_ERROR		= 1,
	IO_FAILURE			= 2,
	PVL_ERROR			= 3,
	UNKNOWN_ERROR		= 4
	};

/*==============================================================================
	Local Functions: Declarations
*/
string
default_filename
	(
	int		data_pattern,
	long	image_components,
	long	image_width,
	long	image_height,
	long	pixel_bytes,
	long	pixel_bits,
	string&	data_order,
	string&	signedness
	);

/*==============================================================================
	Usage
*/
void
usage
	(
	int		exit_status = SUCCESS
	)
{
cout
	<< endl
	<< "Usage: PDS_Test_Image <options>"
	<< "  Writes a skeleton PDS image file for testing." << endl
	<< "  The PDS label conforms to PDS standards, but only includes image data." << endl
	<< "  Multiple byte pixel values will be MSB ordered." << endl
	<< "Options -" << endl
	<< "  -Output_filename <filename>" << endl
	<< "    Specify the file to which the PDS image should be written." << endl
	<< "	Default: \"linear|random-"
		<< "<components>x<width>x<height>x<pixel_bytes>.<pixel_bits>"
		<< "_<signedness>_<data_order>"
		<< FILENAME_EXTENSION << "\"" << endl
	<< "  -Linear | Gradient | Random" << endl
	<< endl
	<< "    Linear ramp pixel data starts with zero for the first pixel of" << endl
	<< "    each band and increments by one until the maximum value possible" << endl
	<< "    for the number of bytes per pixel; this pattern then repeats." << endl
	<< endl
	<< "    Gradient pixel data starts with zero for the upper left pixel of" << endl
	<< "    each band, then two for the next pixels to the right and below," << endl
	<< "    then three for the next diagonal of pixels, etc.; this pattern" << endl
	<< "    continues to the maximum possible pixel value and then repeats." << endl
	<< endl
	<< "    Random pixel data sets all pixels to a random value." << endl
	<< endl
	<< "    Default: " << DATA_PATTERN_NAMES[DEFAULT_DATA_PATTERN] << endl
	<< endl
	<< "  -Components <components>" << endl
	<< "    Image components (bands)." << endl
	<< "    Default: 1; Maximum: 3" << endl
	<< "  -Width <width>" << endl
	<< "    Image pixels per line." << endl	  
	<< "  -Height <height>" << endl
	<< "    Image lines." << endl
	<< "  -Bytes_per_pixel <bytes>" << endl
	<< "    Image pixel bytes for each component." << endl
	<< "    Default: 1; Maximum: 4" << endl
	<< "  -Precision <bits>" << endl
	<< "    Pixel datum precision in bits." << endl
	<< "    Default: Bytes per pixel times 8." << endl
	<< "  -[Un]Signed" << endl
	<< "    Pixel datum signedness." << endl
	<< "    Default: UnSigned" << endl
	<< "  -LSB | MSB" << endl
	<< "    Pixel datum byte order." << endl
	<< "    Default: MSB" << endl
	<< "  -Interval <interval>" << endl
	<< "    Print the number of pixels written every <interval> pixels." << endl
	<< "    Any non-positive argument to this option turns reporting off." << endl
	<< "    Default: No pixel output reporting." << endl;

exit (exit_status);
}

/*==============================================================================
	Main
*/
int
main
	(
	int		argument_count,
	char**	arguments
	)
{
cout << ID << endl;

int
	data_pattern     = DEFAULT_DATA_PATTERN;
long
	image_components = 1,
	image_width      = 0,
	image_height     = 0,
	pixel_bytes      = 1,
	pixel_bits       = 0,
	report_interval  = 0;
bool
	signed_data      = false,
	MSB_data         = true;
std::string
	filename;
char
	*character;
unsigned long
	pixel_mask = 0;

//	Argument processing:

if (argument_count == 1)
	usage ();

for (int
		count = 1;
		count < argument_count;
		count++)
	{
	if (arguments[count][0]== '-')
		{
		switch (toupper(arguments[count][1]))
			{
			case 'G':	//	Gradient data.
				data_pattern = GRADIENT_DATA;
				break;
			case 'R':	//	Random data.
				data_pattern = RANDOM_DATA;
				break;
			case 'L':
				if (strchr (arguments[count], 'S') ||
					strchr (arguments[count], 's'))
					//	LSB data.
					MSB_data = false;
				else
					//	Linear ramp data.
					data_pattern = LINEAR_DATA;
				break;
			case 'C':	//	Components per image.
				if (++count == argument_count ||
					*arguments[count] == '-')
					{
					Missing_Value:
					cout << "Missing value for option "
							<< arguments[--count] << endl;
					usage (SYNTAX_ERROR);
					}
				image_components = strtol (arguments[count], &character, 0);
				if (*character)
					{
					Not_a_Number:
					cout << "Invalid command line argument: "
							<< arguments[count - 1] << endl
						 << "Number expected; found \""
							<< arguments[count] << '"' << endl;
					usage (SYNTAX_ERROR);
					}
				break;
			case 'H':	//	Height of image.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				image_height = strtol (arguments[count], &character, 0);
				if (*character)
					goto Not_a_Number;
				break;
			case 'W':	//	Width of image.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				image_width = strtol (arguments[count], &character, 0);
				if (*character)
					goto Not_a_Number;
				break;
			case 'B':	//	Bytes per pixel.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				pixel_bytes = strtol (arguments[count], &character, 0);
				if (*character)
					goto Not_a_Number;
				break;
			case 'P':	//	Pixel precision bits.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				pixel_bits = strtol (arguments[count], &character, 0);
				if (*character)
					goto Not_a_Number;
				break;
			case 'S':	//	Signed data.
				signed_data = true;
				break;
			case 'U':	//	Unsigned data.
				signed_data = false;
				break;
			case 'M':	//	MSB data.
				MSB_data = true;
				break;
			case 'I':	//	Interval for progress report.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				report_interval = strtol (arguments[count], &character, 0);
				if (*character)
					goto Not_a_Number;
				break;
			case 'O':	//	Output filename.
				if (++count == argument_count ||
					*arguments[count] == '-')
					goto Missing_Value;
				filename = arguments[count];
				break;
			default:
				cout << "Unrecognized option: " << arguments[count] <<endl;
				usage (SYNTAX_ERROR);
			}
		}
	}

if (image_components <= 0 ||
	image_components > 3)
	{
	if (image_components)
		cout << "Invalid image components value: " << image_components << endl;
	else
		cout << "Missing image image_components value." << endl;
	usage (SYNTAX_ERROR);
	}
if (image_width <= 0)
	{
	if (image_width)
		cout << "Invalid image width value: " << image_width << endl;
	else
		cout << "Missing image width value." << endl;
	usage (SYNTAX_ERROR);
	}
if (image_height <= 0)
	{
	if (image_height)
		cout << "Invalid image height value: " << image_height << endl;
	else
		cout << "Missing image height value." << endl;
	usage (SYNTAX_ERROR);
	}
if (pixel_bytes != 1 &&
	pixel_bytes != 2 &&
	pixel_bytes != 4)
	{
	cout << "Invalid image pixel bytes value: " << pixel_bytes << endl;
	usage (SYNTAX_ERROR);
	}
if (! pixel_bits)
	pixel_bits = pixel_bytes << 3;
else if (pixel_bits > (pixel_bytes << 3))
	{
	cout << "Invalid pixel precision bits value: " << pixel_bits << endl
		 << "     Number of pixel storage bytes: " << pixel_bytes << endl;
	usage (SYNTAX_ERROR);
	}

string
	data_order (MSB_data ? "MSB" : "LSB"),
	signedness (signed_data ? "" : "UN");
signedness += "SIGNED";

/*==============================================================================
	Generate the image file:
*/
if (filename.empty ())
	filename = default_filename
		(
		data_pattern,
		image_components,
		image_width, image_height,
		pixel_bytes, pixel_bits,
		data_order, signedness);
cout << "     Output file: " << filename << endl;
ofstream
	output (filename.c_str(), ios::binary);
if (! output)
	{
	cerr << "Couldn't open output file.";
	exit (IO_FAILURE);
	}

cout << "      Image data: " << DATA_PATTERN_NAMES[data_pattern] << endl
	 << "Image components: " << image_components << endl
	 << "     Image width: " << image_width << endl
	 << "    Image height: " << image_height << endl
	 << "     Pixel bytes: " << pixel_bytes << endl
	 << "      Pixel bits: " << pixel_bits << endl
	 << "     Signed data: " << signedness << endl
	 << "      Data order: " << data_order << endl
	 << endl;

//------------------------------------------------------------------------------
//	PDS label

try
{
Aggregate
	label (Parser::CONTAINER_NAME);
label.add (Assignment ("PDS_VERSION_ID")
	= String ("PDS3")
		.type (Value::IDENTIFIER));
label.add (Assignment ("RECORD_TYPE")
	= String ("UNDEFINED")
		.type (Value::IDENTIFIER));
label.add (Assignment ("LABEL_RECORDS")
	= Integer (LABEL_SIZE, Value::UNSIGNED, 10)
		.units ("BYTES"));
label.add (Assignment ("^IMAGE")
	= Integer (LABEL_SIZE + 1, Value::UNSIGNED, 10)
		.units ("BYTES"));
Aggregate
	image_group ("IMAGE");
image_group.add (Assignment ("BANDS")
	= Integer (image_components));
image_group.add (Assignment ("LINES")
	= Integer (image_height));
image_group.add (Assignment ("LINE_SAMPLES")
	= Integer (image_width));
image_group.add (Assignment ("SAMPLE_BITS")
	= Integer (pixel_bytes << 3));

//	Convert pixel bits to a bit mask;
while (pixel_bits--)
	pixel_mask = (pixel_mask << 1) | 1;
image_group.add (Assignment ("SAMPLE_BIT_MASK")
	= Integer (pixel_mask, 2));
image_group.add (Assignment ("SAMPLE_TYPE")
	= String (data_order + '_' + signedness + '_' + "INTEGER"));
label.add (image_group);

idaeim::PVL::Lister lister;
lister
	.strict						(true)			
	.begin_aggregates			(false)
	.uppercase_aggregates		(true)
	.name_end_aggregates		(true)
	.assign_align				(true)
	.array_indenting			(false)
	.use_statement_delimiter	(false)
	.single_line_comments		(true);
output << lister << label << flush;
int
	label_size = lister.total ();
while (label_size++ < LABEL_SIZE)
	output << ' ';
output.flush ();
if (! output)
	{
	cerr << "Couldn't write the complete PDS label." << endl;
	exit (IO_FAILURE);
	}

}
catch (idaeim::Exception except)
	{
	cerr << "Problem with PDS label PVL:" << endl
		 << except.message () << endl;
	exit (PVL_ERROR);
	}
//------------------------------------------------------------------------------
//	Image data

unsigned long long
	component_pixels =
		(unsigned long long)image_height *
		 (unsigned long long)image_width,
	pixels_written;

int
	field_width = 0;
for (pixels_written = image_components * component_pixels;
	 pixels_written;
	 pixels_written /= 10)
	 ++field_width;
cout << "Writing "
		<< setw (field_width) << (image_components * component_pixels)
		<< " pixels." << endl;

if (data_pattern == RANDOM_DATA)
	srandom ((unsigned long)time (0));
unsigned long
	datum = 0;

for (int
		component = 0;
		component < image_components;
		component++)
	{
	//	Components.
	for (unsigned long long
			pixel = 0;
			pixel < component_pixels;
		  ++pixel)
		{
		//	Pixels.
		switch (data_pattern)
			{
			case LINEAR_DATA:
				datum = (unsigned long)pixel;
				break;
			case GRADIENT_DATA:
				if (! (pixel % image_width))
					datum = (unsigned long)(pixel / image_width);
				else
					++datum;
				break;
			case RANDOM_DATA:
				datum = (unsigned long)random ();
			}
		datum &= pixel_mask;
		if (MSB_data)
			{
			for (int
					byte = pixel_bytes;
					byte--;)
				{
				//	Pixel bytes in MSB order.
				int
					bits = byte << 3;
				char
					pixel_value = ((0xFF << bits) & datum) >> bits;
    			output.put (pixel_value);
				if (! output)
					{
					cerr << "Couldn't write pixel "
							<< pixels_written << " byte " << byte << '.' << endl;
					exit (IO_FAILURE);
					}
				}
			}
		else
			{
			for (int
					byte = 0;
					byte < pixel_bytes;
					byte++)
				{
				//	Pixel bytes in LSB order.
				int
					bits = byte << 3;
				char
					pixel_value = ((0xFF << bits) & datum) >> bits;
    			output.put (pixel_value);
				if (! output)
					{
					cerr << "Couldn't write pixel "
							<< pixels_written << " byte " << byte << '.' << endl;
					exit (IO_FAILURE);
					}
				}
			}
		pixels_written++;
		if (report_interval &&
			! (pixels_written % report_interval))
			cout << "Written " << setw (field_width) << pixels_written << "\r"
				 << flush;
		}
	}
cout << "Written " << setw (field_width) << pixels_written << endl;
output.flush ();

exit (SUCCESS);
}

/*==============================================================================
	Local Functions: Definitions
*/
string
default_filename
	(
	int		data_pattern,
	long	image_components,
	long	image_width,
	long	image_height,
	long	pixel_bytes,
	long	pixel_bits,
	string&	data_order,
	string&	signedness
	)
{
ostringstream
	filename;
filename << DATA_PATTERN_NAMES[data_pattern] << '-'
		 << image_components << 'x'
		 << image_width << 'x'
		 << image_height << 'x'
		 << pixel_bytes << '.' << pixel_bits
		 << '_' << data_order << '_' << signedness
		 << FILENAME_EXTENSION;
return filename.str ();
}
