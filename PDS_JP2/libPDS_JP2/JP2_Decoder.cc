/*	JP2_Decoder

HiROC CVS ID: JP2_Decoder.cc,v 1.21 2013/09/24 17:59:38 guym Exp

Copyright (C) 2007  Arizona Board of Regents on behalf of the
Planetary Image Research Laboratory, Lunar and Planetary Laboratory at
the University of Arizona.

This library is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License, version 2.1,
as published by the Free Software Foundation.

This library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.

*******************************************************************************/

#include	"JP2_Decoder.hh"

#include	"Files.hh"
#include	"endian.hh"
using namespace PIRL;

//	Kakadu
#include	"jp2.h"
#include	"kdu_stripe_decompressor.h"

#include	<iostream>
using std::ios;
using std::streamoff;
using std::streamsize;
#include	<fstream>
using std::fstream;
#include	<string>
using std::string;
#include	<sstream>
using std::ostringstream;
#include	<iomanip>
using std::endl;
#include	<stdexcept>
using std::logic_error;
using std::invalid_argument;
using std::out_of_range;
using std::runtime_error;

#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			-1
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_ACCESSORS		(1 << 1)
#define DEBUG_MANIPULATORS	(1 << 2)
#define DEBUG_HELPERS		(1 << 3)
#define DEBUG_DECODE		(1 << 4)
#define DEBUG_WRITE_STRIPE	(1 << 5)
#define	DEBUG_ONE_LINE		(1 << 6)

using std::clog;
using std::setw;
using std::boolalpha;
using std::hex;
using std::dec;
using std::setfill;
#endif	//	DEBUG


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	JP2_Decoder
*/
/*==============================================================================
	Constants
*/
const char* const
	JP2_Decoder::ID =
		"UA::HiRISE::JP2_Decoder (1.21 2013/09/24 17:59:38)";

const char* const
	JP2_Decoder::UUID_INFO_BOX_NAME			= "uinf";
const char* const
	JP2_Decoder::UUID_BOX_NAME				= "ulst";
const char* const
	JP2_Decoder::URL_BOX_NAME				= "url ";

const int
	JP2_Decoder::MIN_STRIPE_HEIGHT			= 256,
	JP2_Decoder::MAX_STRIPE_HEIGHT			= 8192;

const int
	JP2_Decoder::DECODER_EXCEPTION			= 67;

/*==============================================================================
	Constructors
*/
JP2_Decoder::JP2_Decoder ()
	:	
	//	Input JP2:
		JP2_Pathname (),
		Image_Bands (0),
		Image_Size (0, 0),
		Pixel_Bytes (0),
		Pixel_Bits (0),
		Signed_Data (false),
		Resolution_Levels (0),
		UUID_Info_UUID (NULL),
		UUID_Info_URL (),

	//	Output rendered image:
		Image_Destination (),
		Rendered_Size (0, 0),
		Image_Region (0, 0),
		Resolution_Level (1),
		Swap_Pixel_Bytes (false),
		Bytes_Written (0),

	//	Kakadu JP2 decoder classes:
		JP2_Stream (NULL),
		JP2_Source (NULL),
		JPEG2000_Codestream (NULL),
		Decoder_Error (new JP2_Decoder_Error)
{
#if (DEBUG & DEBUG_CONSTRUCTORS)
clog << ">-< JP2_Decoder" << endl;
#endif
//	Register the Kakadu error handler.
kdu_customize_errors (Decoder_Error);
}

/*==============================================================================
	Local functions
*/
#ifndef DOXYGEN_PROCESSING
namespace
{
/**	A subclass of the Kakadu kdu_dims class.

	Provides type converters with the Point_2D, Size_2D and Rectangle
	Dimensions classes.
*/
struct KDU_dims
:	public kdu_dims
{
KDU_dims () {}

KDU_dims
	(
	const Point_2D&	position
	)
{
pos.x = position.X;
pos.y = position.Y;
}


KDU_dims
	(
	const Size_2D&	size_2D
	)
{
size.x = size_2D.Width;
size.y = size_2D.Height;
}


KDU_dims
	(
	const Rectangle&	rectangle
	)
{
pos.x = rectangle.X;
pos.y = rectangle.Y;
size.x = rectangle.Width;
size.y = rectangle.Height;
}

KDU_dims&
operator=
	(
	const Rectangle&	rectangle
	)
{
pos.x = rectangle.X;
pos.y = rectangle.Y;
size.x = rectangle.Width;
size.y = rectangle.Height;
return *this;
}

operator Size_2D () const
{return Size_2D (size.x, size.y);}


operator Rectangle () const
{return Rectangle (pos.x, pos.y, size.x, size.y);}

};	//	End of KDU_dims class.

std::ostream& operator<< (std::ostream& stream, const KDU_dims& dimensions)
{
stream << dimensions.pos.x << "x, "  << dimensions.pos.y << "y, "
	   << dimensions.size.x << "w, " << dimensions.size.y << "h";
return stream;
}

std::ostream& operator<< (std::ostream& stream, const kdu_dims& dimensions)
{
stream << dimensions.pos.x << "x, "  << dimensions.pos.y << "y, "
	   << dimensions.size.x << "w, " << dimensions.size.y << "h";
return stream;
}


kdu_uint32
box_type
	(
	const char*	box_name
	)
{
kdu_uint32
	code = (kdu_uint32)box_name[0];
for (int
		index = 1;
		index < 4;
		index++)
	{
	code <<= 8;
	code += (kdu_uint32)box_name[index];
	}
return code;
}


string
box_name
	(
	kdu_uint32	box_type
	)
{
string
	name;
for (int
		shift = 24,
		mask = 0x7F000000;
		shift >= 0;
		shift -= 8,
		mask >>= 8)
	name += (char)((box_type & mask) >> shift);
return name;
}

}	//	local namespace.
#endif	//	DOXYGEN_PROCESSING

/*==============================================================================
	Accessors
*/
//------------------------------------------------------------------------------
//	Input

JP2_Decoder&
JP2_Decoder::source
	(
	const std::string&	filename
	)
{
if (JP2_Source &&
	JP2_Pathname != filename)
	close ();
JP2_Pathname = filename;
return *this;
}

//------------------------------------------------------------------------------
//	Output

Size_2D
JP2_Decoder::rendered_size () const
{return Rendered_Size;}

unsigned int
JP2_Decoder::rendered_width () const
{return Rendered_Size.Width;}


unsigned int
JP2_Decoder::rendered_height () const
{return Rendered_Size.Height;}


JP2_Decoder&
JP2_Decoder::image_region
	(
	int		x,
	int		y,
	int		width,
	int		height
	)
{
if (width  <= 0 ||
	height <= 0)
	{
	//	Empty image extent.
	Image_Region.X  =
	Image_Region.Y  =
	Image_Region.Width =
	Image_Region.Height = 0;
	}
else
	{
	Image_Region.X  = x;
	Image_Region.Y  = y;
	Image_Region.Width  = width;
	Image_Region.Height = height;
	}
//	Set the effective image region.
set_resolution_and_region (Resolution_Level, Image_Region);
return *this;
}


JP2_Decoder&
JP2_Decoder::image_region
	(
	const Rectangle&	region
	)
{return image_region (region.X, region.Y, region.Width, region.Height);}


JP2_Decoder&
JP2_Decoder::resolution_level
	(
	unsigned int	level
	)
{
if (! (Resolution_Level = level))
	   Resolution_Level = 1;
//	Set the effective resolution and image region.
set_resolution_and_region (Resolution_Level, Image_Region);
return *this;
}

/*==============================================================================
	Decoder
*/
unsigned long long
JP2_Decoder::decode ()
{
//	Open the JP2 file.
open ();

/*
	Pull all the image data from the source through the JPEG2000
	decoder and write it to the destination file.
*/
write_image_data ();

//	Close the JP2 file.
close ();

return Bytes_Written;
}


void
JP2_Decoder::open ()
{
#if ((DEBUG) & DEBUG_DECODE)
clog << ">>> JP2_Decoder::open" << endl;
#endif
if (is_open ())
	{
	#if ((DEBUG) & DEBUG_DECODE)
	clog << "    Already open." << endl
		 << "<<< JP2_Decoder::open" << endl;
	#endif
	return;
	}
if (JP2_Pathname.empty ())
	{
	ostringstream
		message;
	message << ID << endl
			<< "No JP2 source specified to open." << endl;
	throw logic_error (message.str ());
	}

//	Open the JP2 file stream.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Opening a jp2_family_src stream on \""
		<< JP2_Pathname << '"' << endl;
#endif
JP2_Stream = new jp2_family_src ();
JP2_Stream->open (JP2_Pathname.c_str ());

//	Confirm that the file has the JP2 Signature and File Type boxes.
string
	missing_box_name;
jp2_input_box
	box;
if (! box.open (JP2_Stream) ||
	  box.get_box_type () != jp2_signature_4cc)
	{
	missing_box_name = "JP2 Signature";

	Invalid_Source:
	JP2_Stream->close ();
	delete JP2_Stream;
	JP2_Stream = NULL;
	ostringstream
		message;
	message << ID << endl
			<< "Unable to open the decoder." << endl
			<< "The source file \"" << JP2_Pathname << '"' << endl
			<< "does not have valid JP2 format content.";
	if (! missing_box_name.empty ())
		message << endl
				<< "Missing " << missing_box_name << " box.";
	throw invalid_argument (message.str ());
	}
#if ((DEBUG) & DEBUG_DECODE)
clog << "    JP2 " << box_name (box.get_box_type ())
		<< " box type " << hex << box.get_box_type () << dec
		<< ", position " << box.get_pos ()
		<< ", header length " << box.get_box_header_length ()
		<< ", remaining " << box.get_remaining_bytes () << endl;
#endif
box.close ();
if (! box.open_next () ||
	  box.get_box_type () != jp2_file_type_4cc)
	{
	missing_box_name = "File Type";
	goto Invalid_Source;
	}
#if ((DEBUG) & DEBUG_DECODE)
clog << "    JP2 " << box_name (box.get_box_type ())
		<< " box type " << hex << box.get_box_type () << dec
		<< ", position " << box.get_pos ()
		<< ", header length " << box.get_box_header_length ()
		<< ", remaining " << box.get_remaining_bytes () << endl;
#endif
box.close ();

//	Search for UUID Info.
while (box.open_next ())
	{
	#if ((DEBUG) & DEBUG_DECODE)
	clog << "    JP2 " << box_name (box.get_box_type ())
			<< " box type " << hex << box.get_box_type () << dec
			<< ", position " << box.get_pos ()
			<< ", header length " << box.get_box_header_length ()
			<< ", remaining " << box.get_remaining_bytes () << endl;
	#endif
	if (box.get_box_type () == box_type (UUID_INFO_BOX_NAME))
		{
		jp2_input_box
			UUID_info_box;
		if (UUID_info_box.open (&box))
			{
			#if ((DEBUG) & DEBUG_DECODE)
			clog << "    --> Sub-boxes -" <<endl;
			#endif
			do
				{
				#if ((DEBUG) & DEBUG_DECODE)
				clog << "    JP2 " << box_name (UUID_info_box.get_box_type ())
						<< " box type " << hex << UUID_info_box.get_box_type () << dec
						<< ", position " << UUID_info_box.get_pos ()
						<< ", header length " << UUID_info_box.get_box_header_length ()
						<< ", remaining " << UUID_info_box.get_remaining_bytes () << endl;
				#endif
				if (UUID_info_box.get_box_type () == box_type (UUID_BOX_NAME) &&
					! UUID_Info_UUID &&
					UUID_info_box.get_remaining_bytes () >= (2 + UUID_SIZE))
					{
					UUID_Info_UUID = new unsigned char[UUID_SIZE];
					UUID_info_box.read (UUID_Info_UUID, 2);	//	UUID count.
					UUID_info_box.read (UUID_Info_UUID, UUID_SIZE);
					#if ((DEBUG) & DEBUG_DECODE)
					clog << "    UUID: " << hex;
					for (int
							index = 0;
							index < UUID_SIZE;
							index++)
						clog << (index ? ", " : "") << "0x" << setw (2)
								<< (unsigned int)UUID_Info_UUID[index];
					clog << dec << endl;
					#endif
					}
				else
				if (UUID_info_box.get_box_type () == box_type (URL_BOX_NAME) &&
					UUID_Info_URL.empty () &&
					UUID_info_box.get_remaining_bytes () > 4)
					{
					unsigned char
						character[4];
					UUID_info_box.read (character, 4);	//	Version and Flags.
					UUID_info_box.read (character, 1);
					while (*character)
						{
						UUID_Info_URL += *character;
						if (UUID_info_box.get_remaining_bytes ())
							UUID_info_box.read (character, 1);
						else
							break;
						}
					#if ((DEBUG) & DEBUG_DECODE)
					clog << "    URL: " << UUID_Info_URL << endl;
					#endif
					}
				UUID_info_box.close ();
				}
				while (UUID_info_box.open_next ());
			#if ((DEBUG) & DEBUG_DECODE)
			clog << "    <-- Sub-boxes" <<endl;
			#endif
			}
		}
	box.close ();
	}

//	Open the JP2 source.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Opening a jp2_source on the stream" << endl;
#endif
JP2_Source = new jp2_source ();
if (! JP2_Source->open (JP2_Stream))
	{
	delete JP2_Source;
	JP2_Source = NULL;
	goto Invalid_Source;
	}
//	Initialize the JP2 header boxes up to the first codestream box.
JP2_Source->read_header ();

//	Open the JP2000 codestream.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Opening a kdu_codestream on the JP2 source" << endl;
#endif
JPEG2000_Codestream = new kdu_codestream ();
JPEG2000_Codestream->create (JP2_Source);

//	Get the image data characterization:

//	Number of components.
Image_Bands = JPEG2000_Codestream->get_num_components (true);
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Image_Bands = " << Image_Bands << endl;
#endif

//	Image size.
KDU_dims
	image_size;
JPEG2000_Codestream->get_dims (0, image_size, true);
Image_Size = image_size;
#if ((DEBUG) & DEBUG_DECODE)
clog << "     Image_Size = "
		<< Image_Size.Width << 'x' << Image_Size.Height << endl;
#endif

//	Pixel data structure.
Pixel_Bits = JPEG2000_Codestream->get_bit_depth (0, true);
Pixel_Bytes = (Pixel_Bits >> 3) + ((Pixel_Bits % 8) ? 1 : 0);
#if ((DEBUG) & DEBUG_DECODE)
clog << "     Pixel_Bits = " << Pixel_Bits << endl
	 << "    Pixel_Bytes = " << Pixel_Bytes << endl;
#endif
if (Pixel_Bytes == 3)
	Pixel_Bytes++;
Signed_Data = JPEG2000_Codestream->get_signed (0, true);
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Signed_Data = " << boolalpha << Signed_Data << endl;
#endif

//	Check all bands for consistency.
KDU_dims
	dimensions;
unsigned int
	pixel_bits;
bool
	signed_data;
for (unsigned int band = 1;
		 band < Image_Bands;
	   ++band)
	{
	JPEG2000_Codestream->get_dims (band, dimensions, true);
	pixel_bits = JPEG2000_Codestream->get_bit_depth (band, true);
	signed_data = JPEG2000_Codestream->get_signed (band, true);
	#if ((DEBUG) & DEBUG_DECODE)
	clog << "    Band " << band << ": "
			<< dimensions.size.x << ", "
			<< dimensions.size.y << "  "
			<< pixel_bits << "-bit "
			<< (signed_data ? "" : "un") << "signed" << endl;
	#endif
	if (dimensions.size.x != (int)Image_Size.Width ||
		dimensions.size.y != (int)Image_Size.Height ||
		pixel_bits  != Pixel_Bits ||
		signed_data != Signed_Data)
		{
		ostringstream
			message;
		message << ID << endl
				<< "The source file \"" << JP2_Pathname << '"' << endl
				<< "does not have matching image bands:" << endl
				<< "  band 0 - "
					<< Image_Size.Width << ',' << Image_Size.Height
					<< " " << Pixel_Bits << "-bit "
					<< (Signed_Data ? "" : "un") << "signed pixels" << endl
				<< "  band " << band << " - "
					<< dimensions.size.x << ',' << dimensions.size.y
					<< " " << pixel_bits << "-bit "
					<< (signed_data ? "" : "un") << "signed pixels";
		throw out_of_range (message.str ());
		}
	}

//	Total available resolution levels.
Resolution_Levels = JPEG2000_Codestream->get_min_dwt_levels () + 1;
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Resolution_Levels = " << Resolution_Levels << endl;
#endif

//	Set the effective resolution and image region.
set_resolution_and_region (Resolution_Level, Image_Region);
#if ((DEBUG) & DEBUG_DECODE)
clog << "<<< JP2_Decoder::open" << endl;
#endif
}


void
JP2_Decoder::set_resolution_and_region
	(
	unsigned int		level,
	const Rectangle&	region
	)
{
#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
clog << ">>> JP2_Decoder::set_resolution_and_region: region "
		<< region.X << "x, "     << region.Y << "y, "
		<< region.Width << "w, " << region.Height << "h"
		<< "; resolution " << level << endl;
#endif
if (! is_open ())
	{
	#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
	clog << "    Not open." << endl;
	#endif
	return;
	}
//	Limit the rendered resolution level.
if (level < 1)
	level = 1;
else
if (level > Resolution_Levels)
	level = Resolution_Levels;
//	Apply the selected resolution.
Resolution_Level = level;
#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
clog << "    Resolution_Level = " << Resolution_Level << endl;
#endif
JPEG2000_Codestream->apply_input_restrictions
	(0, 0, level - 1, 0, NULL, KDU_WANT_OUTPUT_COMPONENTS);

KDU_dims
	image_size (Image_Size),
	*region_rectangle = NULL;
if (region.area ())
	{
	//	Set the region of interest.
	region_rectangle = new KDU_dims (region);
	int
		divisor = level - 1;
	if (divisor)
		{
		//	Image size at reduced resolution.
		JPEG2000_Codestream->get_dims (0, image_size, true);

		//	Region at reduced resolution.
		region_rectangle->pos.x  >>= divisor;
		region_rectangle->pos.y  >>= divisor;
		region_rectangle->size.x >>= divisor;
		region_rectangle->size.y >>= divisor;
		}
	#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
	clog << "                  image size = " << image_size << endl
		 << "    resolution adjust region = " << *region_rectangle << endl;
	#endif
	image_size &= *region_rectangle;	//	Intersection of region with image.
	#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
	clog << "              clipped region = " << image_size << endl;
	#endif
	if (! image_size)
		{
		ostringstream
			message;
		message << ID << endl
				<< "No image data to write." << endl
				<< "The selected region - "
					<< region.X << "x, "
					<< region.Y << "y, "
					<< region.Width << "w, "
					<< region.Height << "h" << endl
				<< "does not intersect the image - "
					<< Image_Size.Width << "w, "
					<< Image_Size.Height << "h";
		throw out_of_range (message.str ());
		}
	JPEG2000_Codestream->map_region (0, image_size, *region_rectangle, true);
	#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
	clog << "               region mapped = " << *region_rectangle << endl;
	#endif
	Image_Region = *region_rectangle;
	}
else
	//	Use the entire image.
	Image_Region = Image_Size;

//	Apply the selected resolution level (again) and region.
JPEG2000_Codestream->apply_input_restrictions
	(0, 0, level - 1, 0, region_rectangle, KDU_WANT_OUTPUT_COMPONENTS);

//	Effective rendered image size.
JPEG2000_Codestream->get_dims (0, image_size, true);
Rendered_Size = image_size;

#if ((DEBUG) & (DEBUG_ACCESSORS | DEBUG_DECODE))
clog << "        Image_Region = "
		<< Image_Region.X << "x, "     << Image_Region.Y << "y, "
		<< Image_Region.Width << "w, " << Image_Region.Height << "h" << endl
	 << "       Rendered_Size = "
		<< Rendered_Size.Width << ',' << Rendered_Size.Height << endl
	 << "<<< JP2_Decoder::set_resolution_and_region" << endl;
#endif
}


bool
JP2_Decoder::is_open () const
{return  JP2_Source != NULL;}


unsigned long long
JP2_Decoder::write_image_data ()
{
#if ((DEBUG) & DEBUG_DECODE)
clog << ">>> JP2_Decoder::write_image_data" << endl;
#endif
if (! is_open ())
	open ();
if (! ready ())
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to write the image data." << endl
			<< reasons ();
	throw logic_error (message.str ());
	}

//	Construct a codestream stripe-decompressor.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Starting a kdu_stripe_decompressor on the codestream" << endl;
#endif
kdu_stripe_decompressor
	decompressor;

kdu_thread_env
   env;
env.create();
for (unsigned int
             num_threads = 0;
             num_threads < 4;
             num_threads++)
      if (! env.add_thread())
          break;
decompressor.start (*JPEG2000_Codestream, false, false, &env);

//	Incremental image data processing:

int
	*stripe_lines       = new int[Image_Bands],
	*stripe_heights     = new int[Image_Bands],
	*max_stripe_heights = new int[Image_Bands],
	*precisions         = new int[Image_Bands];

//	Allocate stripe buffers.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Allocating the stripe buffers" << endl;
#endif
decompressor.get_recommended_stripe_heights
	(MIN_STRIPE_HEIGHT, MAX_STRIPE_HEIGHT, stripe_heights, max_stripe_heights);
#if ((DEBUG) & DEBUG_DECODE)
clog << "           MIN_STRIPE_HEIGHT = " << MIN_STRIPE_HEIGHT << endl
	 << "           MAX_STRIPE_HEIGHT = " << MAX_STRIPE_HEIGHT << endl;
for (unsigned int
		band = 0;
		band < Image_Bands;
		band++)
	clog << "    Band " << band << " max stripe height = "
			<< max_stripe_heights[band] << endl;
#endif
kdu_int16
	**stripe_buffers_2 = NULL;
kdu_int32
	**stripe_buffers_4 = NULL;
if (Pixel_Bytes <= 2)
	stripe_buffers_2 = new kdu_int16*[Image_Bands];
else
	stripe_buffers_4 = new kdu_int32*[Image_Bands];

for (unsigned int
		band = 0;
		band < Image_Bands;
		band++)
	{
	precisions[band] = Pixel_Bits;
	stripe_lines[band] = 0;
	if (stripe_buffers_2)
		{
		if ((stripe_buffers_2[band] =
				new kdu_int16[Rendered_Size.Width * max_stripe_heights[band]])
			== NULL)
			{
			ostringstream
				message;
			message << ID << endl
					<< "Unable to allocate image data decoding buffers." << endl
					<< "Couldn't allocate "
						<< (Rendered_Size.Width * max_stripe_heights[band]
							* sizeof (kdu_int16)) << " byte buffer for band "
						<< band << '.';
			throw runtime_error (message.str ());
			}
		}
	else
		{
		if ((stripe_buffers_4[band] = 
				new kdu_int32[Rendered_Size.Width * max_stripe_heights[band]])
			== NULL)
			{
			ostringstream
				message;
			message << ID << endl
					<< "Unable to allocate image data encoding buffers." << endl
					<< "Couldn't allocate "
						<< (Rendered_Size.Width * max_stripe_heights[band]
							* sizeof (kdu_int32)) << " byte buffer for band "
						<< band << '.';
			throw runtime_error (message.str ());
			}
		}
	}

//	Open the destination file for appending.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Opening the destination file: " << Image_Destination << endl;
#endif
/*
	N.B.: The file can not simply be opened in append mode (out | app)
	because writing will then only be allowed at the end of the file;
	i.e. file seeks within or beyond the end of the file will not work.

	However, it is likely that the file already exists with a label, so
	it can't simply be opened in output mode or it will be emptied.

	Thus the mode to use when opening the file depends on whether it exists.
*/
ios::openmode
	mode = ios::binary | ios::out;
if (file_exists (Image_Destination))
	mode |= ios::in;	//	Prevent truncation.
fstream
	data_destination (Image_Destination.c_str (), mode);
if (! data_destination)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to open image data destination file \""
				<< Image_Destination << "\".";
	throw std::ios::failure (message.str ());
	}
streamoff
	file_offset = file_size (Image_Destination);
#if ((DEBUG) & DEBUG_DECODE)
clog << "    File size = " << file_offset << endl;
#endif

//	Decompress the source stripes.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Decompressing image stripes ..." << endl;
#endif
Bytes_Written = 0;
bool
	more_stripes = true;
while (more_stripes)
	{
	//	N.B.: stripe_heights will never exceed max_stripe_heights.
    decompressor.get_recommended_stripe_heights
		(MIN_STRIPE_HEIGHT, MAX_STRIPE_HEIGHT, stripe_heights, NULL);
	if (stripe_buffers_2)
		more_stripes = decompressor.pull_stripe
			(stripe_buffers_2, stripe_heights, NULL, NULL, precisions);
	else
		more_stripes = decompressor.pull_stripe
			(stripe_buffers_4, stripe_heights, NULL, NULL, precisions);
	for (unsigned int
			band = 0;
			band < Image_Bands;
			band++)
		{
		if (stripe_buffers_2)
			Bytes_Written += write_stripe (data_destination, file_offset, band,
				stripe_lines[band], stripe_heights[band], stripe_buffers_2[band]);
		else
        	Bytes_Written += write_stripe (data_destination, file_offset, band,
				stripe_lines[band], stripe_heights[band], stripe_buffers_4[band]);
		stripe_lines[band] += stripe_heights[band];
		}
	}

//	Finish up.
#if ((DEBUG) & DEBUG_DECODE)
clog << "    Finishing" << endl;
#endif
decompressor.finish ();

if (env.exists())
      env.destroy();

for (unsigned int
		band = 0;
		band < Image_Bands;
		band++)
	{
	if (stripe_buffers_2)
		delete[] stripe_buffers_2[band];
	else
		delete[] stripe_buffers_4[band];
	}
if (stripe_buffers_2)
	delete[] stripe_buffers_2;
else
	delete[] stripe_buffers_4;
delete[] stripe_lines;
delete[] stripe_heights;
delete[] max_stripe_heights;
delete[] precisions;

#if ((DEBUG) & DEBUG_DECODE)
clog << "<<< JP2_Decoder::write_codestream: " << Bytes_Written << endl;
#endif
return Bytes_Written;
}


void
JP2_Decoder::close ()
{
#if ((DEBUG) & DEBUG_DECODE)
clog << ">>> JP2_Decoder::close" << endl;
#endif
//	Release the codestream management machinery.
if (JPEG2000_Codestream)
	JPEG2000_Codestream->destroy ();
JPEG2000_Codestream = NULL;

//	Close the JP2 source.
if (JP2_Source)
	JP2_Source->close ();
delete JP2_Source;
JP2_Source = NULL;

//	Close the stream bound to the JP2 source.
if (JP2_Stream)
	JP2_Stream->close ();
delete JP2_Stream;
JP2_Stream = NULL;

//	Reset source image characterization info.
Image_Bands       = 0;
Image_Size.Width  =
Image_Size.Height = 0;
Pixel_Bytes       = 0;
Pixel_Bits        = 0;
Resolution_Levels = 0;
delete UUID_Info_UUID;
UUID_Info_UUID    = NULL;
UUID_Info_URL.clear ();

//	Reset destination info.
Rendered_Size.Width  =
Rendered_Size.Height = 0;
Image_Region.X       =
Image_Region.Y       = 0;
Image_Region.Width   =
Image_Region.Height  = 0;
Resolution_Level     = 0;
  
#if ((DEBUG) & DEBUG_DECODE)
clog << "<<< JP2_Decoder::close" << endl;
#endif
}


bool
JP2_Decoder::ready () const
{
if (JP2_Pathname.empty () ||
	Image_Destination.empty ())
	return false;
return true;
}


string
JP2_Decoder::reasons () const
{
string
	reason;
if (JP2_Pathname.empty ())
	reason += "No image source filename.";
if (Image_Destination.empty ())
	reason += string (reason.empty () ? "" : "\n")
		+ "No image destination filename.";
return reason;
}


JP2_Decoder_Error*
JP2_Decoder::decoder_error () const
{return Decoder_Error;}

/*==============================================================================
	Pixel data writers
*/

#if ((DEBUG) & DEBUG_WRITE_STRIPE)
#ifndef DOXYGEN_PROCESSING
namespace
{
void
print_buffer
	(
	unsigned char*	buffer,
	int				amount
	)
{
clog << "    8-bit buffer -" << hex << setfill ('0') << endl;
for (int index = 0;
		 index < amount;
		 index++)
	{
	if (! (index % 16))
		{
		if (index)
			clog << endl;
		clog << setw (7) << index << "  ";
		}
	clog << "  " << setw (2) << ((int)buffer[index] & 0xFF);
	}
clog << dec << setfill (' ') << endl;
}


void
print_buffer
	(
	kdu_int16*		buffer,
	int				amount
	)
{
clog << "    16-bit buffer -" << hex << setfill ('0') << endl;
for (int index = 0;
		 index < amount;
		 index++)
	{
	if (! (index % 16))
		{
		if (index)
			clog << endl;
		clog << setw (7) << index << "  ";
		}
	clog << "  " << setw (4) << buffer[index];
	}
clog << dec << setfill (' ') << endl;
}


void
print_buffer
	(
	kdu_int32*		buffer,
	int				amount
	)
{
clog << "    32-bit buffer -" << hex << setfill ('0') << endl;
for (int index = 0;
		 index < amount;
		 index++)
	{
	if (! (index % 16))
		{
		if (index)
			clog << endl;
		clog << setw (7) << index << "  ";
		}
	clog << "  " << setw (8) << buffer[index];
	}
clog << dec << setfill (' ') << endl;
}

}	//	local namespace.
#endif
#endif

//------------------------------------------------------------------------------
std::streamsize
JP2_Decoder::write_stripe
	(
	std::ostream&	destination,
	std::streamoff	file_offset,
	int				band,
	int				line,
	int				lines,
	kdu_int16*		buffer
	)
{
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
clog << ">>> JP2_Decoder::write_stripe:" << endl
	 << "    File offset - " << file_offset << endl
	 << "           Band - " << band << endl
	 << "     First line - " << line << endl
	 << "   Stripe lines - " << lines << endl;

static int
	report_lines = 1;
#if ! ((DEBUG) & DEBUG_ONE_LINE)
report_lines = lines;
#endif
if (report_lines)
	{
	kdu_int16
		*report_buffer = buffer;
	for (int
			report_line = 0;
			report_line < report_lines;
			report_line++,
				report_buffer += Rendered_Size.Width)
		{
		clog << "    Decompressed line " << report_line << ":" << endl;
		print_buffer (report_buffer, Rendered_Size.Width);
		}
	}
#endif
streamsize
	stripe_bytes = Pixel_Bytes * Rendered_Size.Width * lines;
if (! stripe_bytes)
	{
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	clog << "<<< JP2_Decoder::write_stripe: " << stripe_bytes << endl;
	#endif
	return stripe_bytes;
	}

kdu_int16
	*data = buffer - 1,
	*data_end = buffer + (Rendered_Size.Width * lines),
	level_shift = Signed_Data ? 0 : ((1 << Pixel_Bits) >> 1);
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
if (report_lines)
	clog << "    Data value level shift - " << level_shift << endl;
#endif

if (Pixel_Bytes == 1)
	{
	//	Reduce to an 8-bit unsigned representation.
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	if (report_lines)
		clog << "    Pixel values reduced to 8-bit" << endl;
	#endif
	unsigned char
		*data_bytes = (unsigned char*)buffer;
	if (Signed_Data)
		while (++data < data_end)
			*data_bytes++ = (unsigned char)(*data);
	else
		{
		#if ((DEBUG) & DEBUG_WRITE_STRIPE)
		if (report_lines)
			clog << "    Pixel values level shifted to unsigned" << endl;
		#endif
		while (++data < data_end)
			*data_bytes++ = (unsigned char)(*data + level_shift);
		}
	}
else if (Swap_Pixel_Bytes)
	{
	// Swap byte order.
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	if (report_lines)
		clog << "    Pixel bytes swapped" << endl;
	#endif
	kdu_int16
		datum;
	if (Signed_Data)
		{
		while (++data < data_end)
			{
			datum = *data;
			*data = (datum << 8) + ((datum >> 8) & 0xFF);
			}
		}
	else
		{
		// Level shift to unsigned.
		#if ((DEBUG) & DEBUG_WRITE_STRIPE)
		if (report_lines)
			clog << "    Pixel values level shifted to unsigned" << endl;
		#endif
		while (++data < data_end)
			{
			datum = *data + level_shift;
			*data = (datum << 8) + ((datum >> 8) & 0xFF);
			}
		}
	}
else if (! Signed_Data)
	{
	// Level shift to unsigned.
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	if (report_lines)
		clog << "    Pixel values level shifted to unsigned" << endl;
	#endif
	while (++data < data_end)
		*data += level_shift;
	}
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
if (report_lines)
	{
	kdu_int16
		*report_buffer = buffer;
	for (int
			report_line = 0;
			report_line < report_lines;
			report_line++,
				report_buffer += Rendered_Size.Width)
		{
		clog << "    Output line " << report_line << ":" << endl;
		if (Pixel_Bytes == 1)
			print_buffer ((unsigned char*)report_buffer, Rendered_Size.Width);
		else
			print_buffer (report_buffer, Rendered_Size.Width);
		}
	}
#endif

file_offset +=
	//	Previous image bytes.
	Pixel_Bytes *
		(
		//	Previous bands.
		((streamoff)Rendered_Size.Width * Rendered_Size.Height * band) +
		//	Previous lines in the current band.
		((streamoff)Rendered_Size.Width * line)
		);
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
clog << "    Stripe file location - " << file_offset << endl;
#endif
destination.seekp (file_offset, ios::beg);
if (! destination)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to position the destination file to location "
				<< file_offset << endl
			<< "  at line " << line << " of band " << band << '.';
	throw std::ios::failure (message.str ());
	}
if (! destination.write ((char*)buffer, stripe_bytes))
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to write a " << stripe_bytes
				<< " byte line of image data" << endl
			<< "  at line " << line << " of band " << band << '.';
	throw std::ios::failure (message.str ());
	}
destination.flush ();

#if ((DEBUG) & DEBUG_WRITE_STRIPE)
#if ((DEBUG) & DEBUG_ONE_LINE)
report_lines = 0;
#endif
clog << "<<< JP2_Decoder::write_stripe: " << stripe_bytes << endl;
#endif
return stripe_bytes;
}


std::streamsize
JP2_Decoder::write_stripe
	(
	std::ostream&	destination,
	std::streamoff	file_offset,
	int				band,
	int				line,
	int				lines,
	kdu_int32*		buffer
	)
{
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
clog << ">>> JP2_Decoder::write_stripe:" << endl
	 << "    File offset - " << file_offset << endl
	 << "           Band - " << band << endl
	 << "     First line - " << line << endl
	 << "   Stripe lines - " << lines << endl;

static int
	report_lines = 1;
#if ! ((DEBUG) & DEBUG_ONE_LINE)
report_lines = lines;
#endif
if (report_lines)
	{
	kdu_int32
		*report_buffer = buffer;
	for (int
			report_line = 0;
			report_line < report_lines;
			report_line++,
				report_buffer += Rendered_Size.Width)
		{
		clog << "    Decompressed line " << report_line << ":" << endl;
		print_buffer (report_buffer, Rendered_Size.Width);
		}
	}
#endif
//	Stripe pixel data bytes for all lines.
streamsize
	stripe_bytes = Rendered_Size.Width * lines * Pixel_Bytes;
if (! stripe_bytes)
	{
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	clog << "<<< JP2_Decoder::write_stripe: " << stripe_bytes << endl;
	#endif
	return stripe_bytes;
	}

if (! Signed_Data)
	{
	// Make signed representation.
	kdu_int32
		//	End of data.
		*data = buffer + (Rendered_Size.Width * lines),
		level_shift = 1 << (Pixel_Bits - 1);
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	if (report_lines)
		clog << "    Pixel values level shifted: " << level_shift << endl;
	#endif
	while (--data >= buffer)
		*data += level_shift;
	}
if (Swap_Pixel_Bytes)
	{
	#if ((DEBUG) & DEBUG_WRITE_STRIPE)
	if (report_lines)
		clog << "    Pixel bytes swapped" << endl;
	#endif
	swap_bytes ((unsigned char*)buffer, Rendered_Size.Width * lines, 4);
	}
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
if (report_lines)
	{
	kdu_int32
		*report_buffer = buffer;
	for (int
			report_line = 0;
			report_line < report_lines;
			report_line++,
				report_buffer += Rendered_Size.Width)
		{
		clog << "    Output line " << report_line << ":" << endl;
		print_buffer (report_buffer, Rendered_Size.Width);
		}
	}
#endif

file_offset +=
	//	Previous image bytes.
	Pixel_Bytes *
		(
		//	Previous bands.
		((streamoff)Rendered_Size.Width * Rendered_Size.Height * band) +
		//	Previous lines in the current band.
		((streamoff)Rendered_Size.Width * line)
		);
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
clog << "    Stripe file location - " << file_offset << endl;
#endif
destination.seekp (file_offset, ios::beg);
if (! destination)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to position the destination file to location "
				<< file_offset << endl
			<< "  at line " << line << " of band " << band << '.';
	throw std::ios::failure (message.str ());
	}

if (! destination.write ((char*)buffer, stripe_bytes))
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to write a " << stripe_bytes
				<< " byte line of image data" << endl
			<< "  at line " << line << " of band " << band << '.';
	throw std::ios::failure (message.str ());
	}
#if ((DEBUG) & DEBUG_WRITE_STRIPE)
#if ((DEBUG) & DEBUG_ONE_LINE)
report_lines = 0;
#endif
clog << "<<< JP2_Decoder::write_stripe: " << stripe_bytes << endl;
#endif
return stripe_bytes;
}

#ifndef DOXYGEN_PROCESSING
/*=*****************************************************************************
	JP2_Decoder_Error
*/
void
JP2_Decoder_Error::put_text
	(
	const char*	message
	)
{Message += message;}


void
JP2_Decoder_Error::flush
	(
	bool	end_of_message
	)
{
//	Signal that an error occured.
throw JP2_Decoder::DECODER_EXCEPTION;
}
#endif


}	//	namespace HiRISE
}	//	namespace UA
