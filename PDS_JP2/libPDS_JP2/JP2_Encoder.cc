/*	JP2_Encoder

HiROC CVS ID: JP2_Encoder.cc,v 1.29 2010/11/24 03:32:14 castalia Exp

Copyright (C) 2006-2007  Arizona Board of Regents on behalf of the
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

#include	"JP2_Encoder.hh"

#include	"Files.hh"
#include	"endian.hh"
using namespace PIRL;

//	Kakadu
#include	"jp2.h"
#include	"kdu_stripe_compressor.h"

#include	<iostream>
using std::streamoff;
using std::streamsize;
#include	<fstream>
using std::ifstream;
#include	<sstream>
using std::ostringstream;
#include	<iomanip>
using std::endl;
using std::hex;
using std::setfill;
using std::setw;
#include	<string>
using std::string;
#include	<vector>
using std::vector;
#include	<algorithm>
using std::find;
#include	<cmath>
#include	<stdexcept>
using std::logic_error;
using std::invalid_argument;
using std::length_error;
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
#define DEBUG_ENCODE		(1 << 4)
#define DEBUG_READ_STRIPE	(1 << 5)
#define	DEBUG_ONE_LINE		(1 << 6)

#include	<iomanip>
using std::boolalpha;
using std::dec;
using std::clog;
#endif	//	DEBUG


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	JP2_Encoder
*/
/*==============================================================================
	Constants
*/
const char* const
	JP2_Encoder::ID =
		"UA::HiRISE::JP2_Encoder (1.29 2010/11/24 03:32:14)";

const unsigned int
	JP2_Encoder::DEFAULT_RESOLUTION_LEVELS	= 6;
const unsigned int
	JP2_Encoder::MAX_RESOLUTION_LEVELS		= 32;
const unsigned int
	JP2_Encoder::MAX_QUALITY_LAYERS			= 16384;

const char* const
	JP2_Encoder::UUID_INFO_BOX_NAME			= "uinf";
const char* const
	JP2_Encoder::UUID_BOX_NAME				= "ulst";
const int
	JP2_Encoder::UUID_SIZE					= 16;
const char* const
	JP2_Encoder::URL_BOX_NAME				= "url ";

const int
	JP2_Encoder::MIN_STRIPE_HEIGHT			= 256,
	JP2_Encoder::MAX_STRIPE_HEIGHT			= 8192;

const int
	JP2_Encoder::NEEDS_SOURCE				= 1 << 0,
	JP2_Encoder::NEEDS_DESTINATION			= 1 << 1,
	JP2_Encoder::NEEDS_IMAGE				= 1 << 2;

const int
	JP2_Encoder::ENCODER_EXCEPTION			= 66;

#ifndef	PROGRESSION_ORDER
#define PROGRESSION_ORDER					"PCRL"
#endif

#ifndef INCREMENTAL_FLUSH_BYTES
#define INCREMENTAL_FLUSH_BYTES				(256 * 1024 * 1024)
#endif

/*==============================================================================
	Constructors
*/
JP2_Encoder::JP2_Encoder ()
	:	Image_Source (),
		JP2_Pathname (),
		Image_Offset (0),
		Image_Bands (1),
		Image_Size (0, 0),
		Line_Prefix_Bytes (0),
		Line_Suffix_Bytes (0),
		Pixel_Bytes (0),
		Pixel_Bits (0),
		Signed_Data (false),

		PDS_Label_Pathname (),
		Producer_UUID (NULL),
		Swap_Pixel_Bytes (false),
		Resolution_Levels (DEFAULT_RESOLUTION_LEVELS),
		Quality_Layers (1),
		Bit_Rate (0.0),
		Progression_Order (PROGRESSION_ORDER),
		Tile_Size (0, 0),
		Precinct_Sizes (),
		Code_Block_Size (64, 64),
		Incremental_Flush_Bytes ((long long)INCREMENTAL_FLUSH_BYTES),
		JP2_Stream (NULL),
		JP2_Boxes (NULL),
		JPEG2000_Codestream (NULL),
		Encoder_Error (new JP2_Encoder_Error)
{
#if (DEBUG & DEBUG_CONSTRUCTORS)
clog << ">-< JP2_Encoder" << endl;
#endif
//	Register the Kakadu error handler.
kdu_customize_errors (Encoder_Error);
}


JP2_Encoder::~JP2_Encoder ()
{
if (Producer_UUID)
	delete[] Producer_UUID;
}

/*==============================================================================
	Accessors
*/
JP2_Encoder&
JP2_Encoder::producer_UUID
	(
	const unsigned char*	id
	)
{
if (id)
	{
	if (! Producer_UUID)
		Producer_UUID = new unsigned char[UUID_SIZE];
	memmove (Producer_UUID, id, UUID_SIZE);
	}
else if (Producer_UUID)
	{
	delete[] Producer_UUID;
	Producer_UUID = NULL;
	}
return *this;
}


JP2_Encoder&
JP2_Encoder::add_box
	(
	JP2_Box*	box
	)
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">-< JP2_Encoder::add_box" << endl;
#endif
if (box)
	Added_Boxes.push_back (box);
return *this;
}


bool
JP2_Encoder::remove_box
	(
	JP2_Box*	box
	)
{
JP2_Box::JP2_Box_List::iterator
	position = find (Added_Boxes.begin (), Added_Boxes.end (), box);
if (position == Added_Boxes.end ())
	return false;
Added_Boxes.erase (position);
return true;
}


JP2_Encoder&
JP2_Encoder::source
	(
	const std::string&	pathname
	)
{
if (JP2_Stream &&
	Image_Source != pathname)
	close ();
Image_Source = pathname;
return *this;
}


JP2_Encoder&
JP2_Encoder::image_size
	(
	const Size_2D&	size
	)
{
if (! size.Width ||
	! size.Height)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Image size (" << size.Width << ", " << size.Height
			<< ") is invalid.";
	throw invalid_argument (message.str ());
	}
Image_Size = size;
return *this;
}


JP2_Encoder&
JP2_Encoder::pixel_bytes
	(
	unsigned int	bytes_per_pixel
	)
{
if (bytes_per_pixel == 0 ||
	bytes_per_pixel == 3 ||
	bytes_per_pixel > 4)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Invalid number of pixel bytes: "
				<< bytes_per_pixel << '.' << endl
			<< "Allowable values are 1, 2 and 4.";
	throw invalid_argument (message.str ());
	}
if (Pixel_Bits > (bytes_per_pixel << 3))
	{
	ostringstream
		message;
	message << ID << endl
			<< "Invalid number of pixel bytes: "
				<< bytes_per_pixel << '.' << endl
			<< Pixel_Bits << " pixel bits needs more storage bytes.";
	throw length_error (message.str ());
	}
Pixel_Bytes = bytes_per_pixel;
if (! Pixel_Bits)
	Pixel_Bits = bytes_per_pixel << 3;

if (Pixel_Bytes == 1)
	signed_data (false);
return *this;
}


JP2_Encoder&
JP2_Encoder::pixel_bits
	(
	unsigned int	bits_per_pixel
	)
{
if (bits_per_pixel)
	{
	if (bits_per_pixel > 32)
		{
		ostringstream
			message;
		message << ID << endl
				<< "Invalid number of pixel bits: "
					<< bits_per_pixel << '.' << endl
				<< "Maximum value is 32.";
		throw invalid_argument (message.str ());
		}
	if (bits_per_pixel > (Pixel_Bytes << 3))
		{
		//	Enlarge the bytes per pixel storage size.
		unsigned int
			bytes_per_pixel =
				(bits_per_pixel >> 3) + ((bits_per_pixel % 8) ? 1 : 0);
		if (bytes_per_pixel == 3)
			bytes_per_pixel++;
		pixel_bytes (bytes_per_pixel);
		}
	Pixel_Bits = bits_per_pixel;
	if ((Pixel_Bytes << 3) > bits_per_pixel)
		signed_data (false);
	}
return *this;
}


JP2_Encoder&
JP2_Encoder::signed_data
	(
	bool	data_is_signed
	)
{
if (data_is_signed &&
	(Pixel_Bytes == 1 ||
	(Pixel_Bytes << 3) > Pixel_Bits))
	/*
		Single byte data and data that does not occupy all the byte bits
		is unsigned by definition.
	*/
	data_is_signed = false;
Signed_Data = data_is_signed;
return *this;
}


bool
JP2_Encoder::MSB_data () const
{
bool
	MSB_host = high_endian_host ();
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">-< JP2_Encoder::MSB_data: is " << boolalpha
		<< ((! MSB_host && Swap_Pixel_Bytes) ||
			(MSB_host && ! Swap_Pixel_Bytes)) << endl
	 << "        MSB host - " << MSB_host << endl
	 << "      swap bytes - " << Swap_Pixel_Bytes << endl;
#endif
return
	(! MSB_host && Swap_Pixel_Bytes) ||
	(MSB_host && ! Swap_Pixel_Bytes);
}

JP2_Encoder&
JP2_Encoder::MSB_data
	(
	bool	data_is_MSB
	)
{
bool
	MSB_host = high_endian_host ();
Swap_Pixel_Bytes =
	(! MSB_host && data_is_MSB) ||
	(MSB_host && ! data_is_MSB);
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">-< JP2_Encoder::MSB_data: to " << boolalpha << data_is_MSB << endl
	 << "        MSB host - " << MSB_host << endl
	 << "      swap bytes - " << Swap_Pixel_Bytes << endl;
#endif
return *this;
}


JP2_Encoder&
JP2_Encoder::resolution_levels
	(
	unsigned int	resolution_levels
	)
{
if (resolution_levels > MAX_RESOLUTION_LEVELS)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Invalid number of resolution levels: "
				<< resolution_levels << endl
			<< "Maximum number of resolution levels is "
				<< MAX_RESOLUTION_LEVELS << '.';
	throw invalid_argument (message.str ());
	}
if ((Resolution_Levels = resolution_levels) == 0)
	 Resolution_Levels = 1;

if (Precinct_Sizes.size () &&
	Precinct_Sizes.size () != resolution_levels)
	//	Adjust the number of precinct sizes to the number of resolution levels.
	Precinct_Sizes.resize (resolution_levels,
		Precinct_Sizes[Precinct_Sizes.size () - 1]);
return *this;
}


JP2_Encoder&
JP2_Encoder::quality_layers
	(
	unsigned int	quality_layers
	)
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">-< JP2_Encoder::quality_layers: " << quality_layers << endl;
#endif
if (quality_layers > MAX_QUALITY_LAYERS)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Invalid number of quality layers: "
				<< quality_layers << endl
			<< "Maximum number of quality layers is "
				<< MAX_QUALITY_LAYERS << '.';
	throw invalid_argument (message.str ());
	}
if ((Quality_Layers = quality_layers) == 0)
	 Quality_Layers = 1;
return *this;
}


JP2_Encoder&
JP2_Encoder::bit_rate
	(
	double	rate
	)
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">-< JP2_Encoder::bit_rate: " << rate << endl;
#endif
if ((Bit_Rate = rate) < 0)
	 Bit_Rate = 0;
return *this;
}


JP2_Encoder&
JP2_Encoder::progression_order
	(
	const std::string&	progression
	)
{
string
	indicator;
if (progression.length () != 4)
	{
	Invalid_Indicators:
	ostringstream
		message;
	message << ID << endl
			<< "Invalid progression order indicators: " << progression << endl
			<< "Four characters are allowed: one each of "
				<< "'R'esolution, 'P'recint, 'C'omponet, and 'L'evel.";
	throw invalid_argument (message.str ());
	}
for (int
		index = 0;
		index < 4;
		index++)
	{
	char
		character = toupper (progression[index]);
	if (character == 'R' ||
		character == 'P' ||
		character == 'C' ||
		character == 'L')
		{
		if (indicator.find (character) != string::npos)
			goto Invalid_Indicators;
		indicator += character;
		}
	}
Progression_Order = indicator;
return *this;
}


const Size_2D
JP2_Encoder::precinct_size
	(
	unsigned int	resolution_level
	) const
{
if ((resolution_level + 1) <= Precinct_Sizes.size ())
	return Precinct_Sizes[resolution_level];
else
	{
	ostringstream
		message;
	message << ID << endl
			<< "No precinct size for resolution level "
				<< resolution_level << '.' << endl;
	throw invalid_argument (message.str ());
	}
}


bool
power_of_2
	(
	unsigned int	value
	)
{
bool
	bit_found = false;
while (value)
	{
	if (value & 1)
		{
		if (bit_found)
			return false;
		else
			bit_found = true;
		}
	value >>= 1;
	}
return true;
}


int
JP2_Encoder::invalid_precinct_size
	(
	const std::vector<Size_2D>&	sizes
	)
{
int
	index = 0;
for (vector<Size_2D>::const_iterator
		entry = sizes.begin ();
		entry < sizes.end ();
		++entry,
		++index)
	if (! entry->Width ||
		! entry->Height ||
		! power_of_2 (entry->Width) ||
		! power_of_2 (entry->Height))
		return ++index;
return 0;
}


JP2_Encoder&
JP2_Encoder::precinct_sizes
	(
	const std::vector<Size_2D>&	sizes
	)
{
int
	index = invalid_precinct_size (sizes);
if (index)
	{
	--index;
	ostringstream
		message;
	message << ID << endl
			<< "Invalid precinct size ("
				<< sizes[index].Width << ", " << sizes[index].Height
				<< ") at vector entry " << index << '.' << endl
			<< "Precinct sizes must be non-zero powers of 2.";
	throw invalid_argument (message.str ());
	}
Precinct_Sizes = sizes;
if (sizes.size () > 0 &&
	sizes.size () != Resolution_Levels)
	//	Adjust the number of precinct sizes to the number of resolution levels.
	Precinct_Sizes.resize (Resolution_Levels, Precinct_Sizes[sizes.size () - 1]);
return *this;
}

JP2_Encoder&
JP2_Encoder::precinct_size
	(
	const Size_2D&	size,
	unsigned int	resolution_level
	)
{
if (! size.Width ||
	! size.Height ||
	! power_of_2 (size.Width) ||
	! power_of_2 (size.Height))
	{
	ostringstream
		message;
	message << ID << endl
			<< "Invalid precinct size ("
				<< size.Width << ", " << size.Height << ")." << endl
			<< "Precinct sizes must be non-zero powers of 2.";
	throw invalid_argument (message.str ());
	}

if (resolution_level < Precinct_Sizes.size ())
	Precinct_Sizes[resolution_level] = size;
else if (resolution_level == 0 &&
		 Precinct_Sizes.size () == 0)
	Precinct_Sizes.resize (Resolution_Levels, size);
else
	{
	ostringstream
		message;
	message << ID << endl
			<< "Can't set a precinct size for resolution level "
				<< resolution_level << endl
			<< Resolution_Levels << " resolution level"
				<< ((Resolution_Levels == 1) ? "" : "s") << " set.";
	throw invalid_argument (message.str ());
	}
return *this;
}


JP2_Encoder&
JP2_Encoder::code_block_size
	(
	const Size_2D&	size
	)
{
if (! size.Width ||
	! size.Height ||
	size.Width > 64 ||
	size.Height > 64)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Code block size ("
				<< size.Width << ", " << size.Height
				<< ") is invalid." << endl
			<< "Maximum size is 64, 64.";
	throw invalid_argument (message.str ());
	}
Code_Block_Size = size;
return *this;
}

/*==============================================================================
	Local functions
*/
#ifndef DOXYGEN_PROCESSING
namespace
{
//	Sub-box of a JP2 box.
long long
write_box
	(
	jp2_output_box&	super_box,
	JP2_Box*		box
	)
{
if (! box)
	return 0;

#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Enocder::write_box: sub-box \""
		<< box->type_name () << "\" (0x" << setfill ('0') << hex << setw (8)
		<< box->type_code () << ')' << setfill (' ') << dec << endl;
#endif
long long
	bytes_written = 0;
jp2_output_box
	output_box;
output_box.open (&super_box, box->type_code ());
if ((box->sub_boxes ()).empty ())
	{
	//	Write the box content.
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    " << box->content_amount () << " byte content" << endl;
	#endif
	if (! output_box.write (box->content (), (int)box->content_amount ()))
		{
		ostringstream
			message;
		message << JP2_Encoder::ID << endl
				<< "Failed to write the " << box->content_amount ()
					<< " byte content of the \"" << box->type_name ()
					<< "\" (0x" << setfill ('0') << hex << setw (8)
					<< box->type_code () << ") JP2 box";
		for (JP2_Box*
				container = box->container ();
				container;
				container = container->container ())
			message << "contained in the \"" << container->type_name ()
						<< "\" (0x" << setw (8)
						<< container->type_code () << ") JP2 box";
		throw std::ios::failure (message.str ());
		}
	bytes_written = box->content_amount ();
	}
else
	{
	//	Write the sub-boxes.
	for (JP2_Box::JP2_Box_List::iterator
			sub_box  = (box->sub_boxes ()).begin ();
			sub_box != (box->sub_boxes ()).end ();
		  ++sub_box)
		bytes_written += write_box (output_box, *sub_box);
	}
if (! output_box.close ())
	{
	ostringstream
		message;
	message << JP2_Encoder::ID << endl
			<< "Failed to write the " << bytes_written
				<< " byte content of the " << (box->sub_boxes ()).size ()
				<< " sub-box" << (((box->sub_boxes ()).size () == 1) ? "" : "es")
				<< " from the top level \"" << box->type_name ()
				<< "\" (0x" << setfill ('0') << hex << setw (8)
				<< box->type_code () << ") JP2 box.";
	throw std::ios::failure (message.str ());
	}
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Enocder::write_box: sub-box" << endl;
#endif
return bytes_written;
}


//	Top level JP2 box.
long long
write_box
	(
	jp2_family_tgt*	JP2_stream,
	JP2_Box*		box
	)
{
if (! box)
	return 0;

#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Enocder::write_box: top-level \""
		<< box->type_name () << "\" (0x" << setfill ('0') << hex << setw (8)
		<< box->type_code () << ')' << setfill (' ') << dec << endl;
#endif
long long
	bytes_written = 0;
jp2_output_box
	output_box;
output_box.open (JP2_stream, box->type_code ());
if ((box->sub_boxes ()).empty ())
	{
	//	Write the box content.
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    " << box->content_amount () << " byte content" << endl;
	#endif
	if (! output_box.write (box->content (), (int)box->content_amount ()) ||
		! output_box.close ())
		{
		ostringstream
			message;
		message << JP2_Encoder::ID << endl
				<< "Failed to write the " << box->content_amount ()
					<< " byte content of the top level \"" << box->type_name ()
					<< "\" (0x" << setfill ('0') << hex << setw (8)
					<< box->type_code () << ") JP2 box.";
		throw std::ios::failure (message.str ());
		}
	bytes_written = box->content_amount ();
	}
else
	{
	//	Write the sub-boxes.
	for (JP2_Box::JP2_Box_List::iterator
			sub_box  = (box->sub_boxes ()).begin ();
			sub_box != (box->sub_boxes ()).end ();
		  ++sub_box)
		bytes_written += write_box (output_box, *sub_box);
	if (! output_box.close ())
		{
		ostringstream
			message;
		message << JP2_Encoder::ID << endl
				<< "Failed to write the " << bytes_written
					<< " byte content of the " << (box->sub_boxes ()).size ()
					<< " sub-box"
					<< (((box->sub_boxes ()).size () == 1) ? "" : "es")
					<< " from the top level \"" << box->type_name ()
					<< "\" (0x" << setfill ('0') << hex << setw (8)
					<< box->type_code () << ") JP2 box.";
		throw std::ios::failure (message.str ());
		}
	}
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Enocder::write_box: top-level" << endl;
#endif
return bytes_written;
}


kdu_long
max_image_area
	(
	kdu_codestream&	codestream
	)
{
int
	components = codestream.get_num_components (),
	max_width = 0,
	max_height = 0;
kdu_dims
	dimensions;
for (int
		component = 0;
		component < components;
		component++)
	{
	codestream.get_dims (component, dimensions);
	if (max_width < dimensions.size.x)
		max_width = dimensions.size.x;
	if (max_height < dimensions.size.y)
		max_height = dimensions.size.y;
	}
return (static_cast<kdu_long>(max_width) * static_cast<kdu_long>(max_height));
}

}	//	local namespace.
#endif	//	DOXYGEN_PROCESSING

/*==============================================================================
	Encoder
*/
long long
JP2_Encoder::encode ()
{
//	Open the JP2 file.
open ();

/*
	Configure and write all required JP2 boxes up to, but not including,
	the JPEG2000 codestream (jp2c) box. This includes the Signature,
	File_Type and JP2_Header boxes with the latter including the
	Image_Header and Colour_Specification subboxes.
*/
write_header ();

//	Add any user specified boxes.
write_user_boxes ();

/*
	Push all the image data from the source through the JPEG2000 encoder
	into the JP2 codestream box.
*/
write_codestream ();

//	Close the JP2 file and return the number of bytes written.
return close ();
}


void
JP2_Encoder::open ()
{
#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Encoder::open" << endl;
#endif
if (! JP2_Stream)
	{
	if (! ready ())
		{
		string
			why_not (reasons ());
		ostringstream
			message;
		message << ID << endl
				<< "Unable to open the encoder." << endl
				<< why_not;
		throw logic_error (message.str ());
		}

	//	Open the JP2 file stream.
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    Opening a jp2_family_tgt on \"" << JP2_Pathname << '"' << endl;
	#endif
	JP2_Stream = new jp2_family_tgt ();
	JP2_Stream->open (JP2_Pathname.c_str ());

	//	Open the JP2 boxes.
	JP2_Boxes = new jp2_target ();
	JP2_Boxes->open (JP2_Stream);
	}
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Encoder::open" << endl;
#endif
}


long long
JP2_Encoder::write_header ()
{
#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Encoder::write_header" << endl
	 << "    Bytes written so far: "
	 	<< JP2_Stream->get_bytes_written () << endl;
#endif
long long
	bytes_written = JP2_Stream->get_bytes_written ();

if (! JP2_Boxes)
	open ();

/*	Codestream SIZ parameters.

	N.B.: The order of operations matters. By inspecting the Kakadu
	kdu_buffered_compress sample application the order used here has
	been found to work correctly. However, it is unknown what the
	criteria are for determining the correct order.
*/
siz_params
	*codestream_parameters = new siz_params ();

//	Image data organization.
codestream_parameters->set (Sdims,       0, 0, (int)Image_Size.Height);
codestream_parameters->set (Sdims,       0, 1, (int)Image_Size.Width);
if (! Pixel_Bits)
	Pixel_Bits = Pixel_Bytes << 3;
codestream_parameters->set (Sprecision,  0, 0, (int)Pixel_Bits);
if (! Tile_Size.Height)
	Tile_Size.Height = Image_Size.Height;
codestream_parameters->set (Stiles,      0, 0, (int)Tile_Size.Height);
if (! Tile_Size.Width)
	Tile_Size.Width = Image_Size.Width;
codestream_parameters->set (Stiles,      0, 1, (int)Tile_Size.Width);
codestream_parameters->set (Ssigned,     0, 0, Signed_Data);
if (! Image_Bands)
	Image_Bands = 1;
codestream_parameters->set (Scomponents, 0, 0, (int)Image_Bands);
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << Sdims << '='
		<< Image_Size.Height << ',' << Image_Size.Width << endl
	 << "    " << Sprecision << '=' << Pixel_Bits << endl
	 << "    " << Stiles << '='
		<< Tile_Size.Height << ',' << Tile_Size.Width << endl
	 << "    " << Ssigned << '=' << boolalpha << Signed_Data << endl
	 << "    " << Scomponents << '=' << Image_Bands << endl;
#endif

//	Resolution levels.
if (! Resolution_Levels)
	Resolution_Levels = DEFAULT_RESOLUTION_LEVELS;
ostringstream
	levels;
levels << "Clevels=" << (Resolution_Levels - 1);
codestream_parameters->parse_string (levels.str ().c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << levels.str () << endl;
#endif

//	Quality layers.
ostringstream
	layers;
layers << "Clayers=" << Quality_Layers;
codestream_parameters->parse_string (layers.str ().c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << layers.str () << endl;
#endif

if (Bit_Rate == 0.0)
	{
	//	Reversible (lossless) discreet wavelet transform.
	codestream_parameters->parse_string ("Creversible=yes");
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    Creversible=yes" << endl;
	#endif
	}
else
	{
	//	Irreversible (lossy) discreet wavelet transform.
	codestream_parameters->parse_string ("Creversible=no");
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    Creversible=no" << endl;
	#endif
	}

//	Encoding progression order.
string
	progression = "Corder=" + Progression_Order;
codestream_parameters->parse_string (progression.c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << progression << endl;
#endif

/*	Determining the number of tile length marker segments.

	See the description of ORGgen_tlm in the Kakadu org_params
	and kdu_codestream::flush documentation.

	Determining the number of tile-parts is very hard to do if
	incremental flusing is employed (the Kakadu documentation emphasizes
	this and does not offer any advice about how to do it). So the tile
	height divided by the number of lines requested for incremental
	flushing rounded up to the next whole number is used as an estimate.

	If incremental flushing is not employed only one TLM segment is
	needed.
*/
//	Include tile length markers.
int
	TLM_segments,
	flush_lines = incremental_flush_lines ();
if (flush_lines)
	{
	TLM_segments =
		(int)(((Tile_Size.Height ? Tile_Size.Height : Image_Size.Height) /
		(double)flush_lines) + 0.5);
	if (! TLM_segments)
		TLM_segments = 1;
	}
else
	TLM_segments = 1;
ostringstream
	segments;
segments << "ORGgen_tlm=" << TLM_segments;
codestream_parameters->parse_string (segments.str ().c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << segments.str () << endl;
#endif

//	Include packet length markers in tile headers.
codestream_parameters->parse_string ("ORGgen_plt=yes");
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    ORGgen_plt=yes" << endl;
#endif

//	Finalize the codestream parameters.
codestream_parameters->finalize_all ();

//	Construct the JPEG2000 codestream object.
JPEG2000_Codestream = new kdu_codestream ();
JPEG2000_Codestream->create (codestream_parameters, JP2_Boxes);

if (! Comment.empty ())
	JPEG2000_Codestream->add_comment () << Comment.c_str ();

//	Add a comment identifying this encoder.
JPEG2000_Codestream->add_comment () << ID;

//	>>> WARNING <<< Some parameters must be set again (or only set here?)!
codestream_parameters = JPEG2000_Codestream->access_siz ();

codestream_parameters->parse_string (levels.str ().c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << levels.str () << endl;
#endif
codestream_parameters->parse_string (layers.str ().c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << layers.str () << endl;
#endif
if (Bit_Rate == 0.0)
	{
	codestream_parameters->parse_string ("Creversible=yes");
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    Creversible=yes" << endl;
	#endif
	}
else
	{
	//	Irreversible (lossy) discreet wavelet transform.
	codestream_parameters->parse_string ("Creversible=no");
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    Creversible=no" << endl;
	#endif
	}
codestream_parameters->parse_string (progression.c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << progression << endl;
#endif
codestream_parameters->parse_string (segments.str ().c_str ());
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    " << segments.str () << endl;
#endif
codestream_parameters->parse_string ("ORGgen_plt=yes");
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    ORGgen_plt=yes" << endl;
#endif

//	Precinct sizes.
if (Precinct_Sizes.size ())
	{
	ostringstream
		sizes;
	sizes << "Cprecincts=";
	for (vector<Size_2D>::const_iterator
			size = Precinct_Sizes.begin ();
			size < Precinct_Sizes.end ();
		  ++size)
		{
		if (size != Precinct_Sizes.begin ())
			sizes << ',';
		//	Vertical dimension first.
		sizes << '{' << size->Height << ',' << size->Width << '}';
		}
	codestream_parameters->parse_string (sizes.str ().c_str ());
	}

//	Code block size.
if (Code_Block_Size.Width &&
	Code_Block_Size.Height)
	{
	ostringstream
		size;
	//	Vertical dimension first.
	size << "Cblk={"
		<< Code_Block_Size.Height << ',' << Code_Block_Size.Width << '}';
	codestream_parameters->parse_string (size.str ().c_str ());
	}

codestream_parameters->finalize_all ();

//	Image dimensions finalization.
jp2_dimensions
	dimensions = JP2_Boxes->access_dimensions ();
dimensions.init (codestream_parameters);
dimensions.finalize_compatibility (codestream_parameters);

//	Colour definition.
jp2_colour
	colour = JP2_Boxes->access_colour ();
colour.init ((Image_Bands >= 3) ? JP2_sRGB_SPACE : JP2_sLUM_SPACE);
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    colour.init "
		<< ((Image_Bands >= 3) ? "JP2_sRGB_SPACE" : "JP2_sLUM_SPACE") << endl;
#endif

//	Write all JP2 boxes up to, but not including, the codestream box.
JP2_Boxes->write_header ();

bytes_written = JP2_Stream->get_bytes_written () - bytes_written;
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Encoder::write_header: " << bytes_written << endl;
#endif
return bytes_written;
}


long long
JP2_Encoder::write_user_boxes ()
{
#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Encoder::write_user_boxes" << endl
	 << "    Bytes written so far: "
	 	<< JP2_Stream->get_bytes_written () << endl;
#endif
long long
	bytes_written = JP2_Stream->get_bytes_written ();

if (! JP2_Boxes)
	write_header ();

//	Producer signature and PDS label URL.
if (! PDS_Label_Pathname.empty ())
	{
	//	Enclosing UUID Info box.
	jp2_output_box
		uuid_info_box;
	uuid_info_box.open (JP2_Stream, JP2_Box::type_code (UUID_INFO_BOX_NAME));

	//	Add the enclosed UUID box. 
	jp2_output_box
		uuid_list_box;
	uuid_list_box.open (&uuid_info_box, JP2_Box::type_code (UUID_BOX_NAME));
	uuid_list_box.write ((kdu_int16)1);
	unsigned char
		zero_fill[UUID_SIZE] =
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	if (Producer_UUID)
		uuid_list_box.write (Producer_UUID, UUID_SIZE);
	else
		uuid_list_box.write (zero_fill, UUID_SIZE);
	uuid_list_box.close ();

	//	Add the enclosed PDS label URL box.
	jp2_output_box
		url_box;
	url_box.open (&uuid_info_box, JP2_Box::type_code (URL_BOX_NAME));
	url_box.write (zero_fill, 4);
	string
		url (file_name (PDS_Label_Pathname));
	url_box.write ((const unsigned char*)url.c_str (), url.length () + 1);
	url_box.close ();

	uuid_info_box.close ();
	}

//	Additional user-specified boxes.
if (! Added_Boxes.empty ())
	for (JP2_Box::JP2_Box_List::iterator
			sub_box  = Added_Boxes.begin ();
			sub_box != Added_Boxes.end ();
		  ++sub_box)
		write_box (JP2_Stream, *sub_box);

bytes_written = JP2_Stream->get_bytes_written () - bytes_written;
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Encoder::write_user_boxes: " << bytes_written << endl;
#endif
return bytes_written;
}


long long
JP2_Encoder::write_codestream ()
{
#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Encoder::write_codestream" << endl
	 << "    Bytes written so far: "
	 	<< JP2_Stream->get_bytes_written () << endl;
#endif
long long
	bytes_written = JP2_Stream->get_bytes_written ();

if (! JP2_Boxes)
	write_header ();

//	Open the JPEG2000 codestream (jp2c) box.
JP2_Boxes->open_codestream ();

//	Bit-rate for the quality layers.
kdu_long
	*layer_sizes = new kdu_long[Quality_Layers];
memset (layer_sizes, 0, sizeof (kdu_long) * Quality_Layers);
if (Bit_Rate > 0.0)
	{
	//	Bit rate specified for lossy compression.
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "    Bit rate = " << Bit_Rate << endl;
	#endif
	layer_sizes[0] = static_cast<kdu_long>
		(floor (Bit_Rate * 0.125 * max_image_area (*JPEG2000_Codestream)));
	}

//	Construct a codestream stripe-compressor.
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    Starting a kdu_stripe_compressor on the codestream" << endl;
#endif
kdu_stripe_compressor
	compressor;
compressor.start
	(
	*JPEG2000_Codestream,
	Quality_Layers, layer_sizes,
	NULL, 0, false,
	Pixel_Bytes == 4	//	Force precise for 32-bit values.
	);

//	Incremental image data compression:

int
	*stripe_lines       = new int[Image_Bands],
	*stripe_heights     = new int[Image_Bands],
	*max_stripe_heights = new int[Image_Bands],
	*precisions         = new int[Image_Bands];

//	Allocate stripe buffers.
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    Allocating the stripe buffers" << endl;
#endif
compressor.get_recommended_stripe_heights
	(MIN_STRIPE_HEIGHT, MAX_STRIPE_HEIGHT, stripe_heights, max_stripe_heights);
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
	#if ((DEBUG) & DEBUG_ENCODE)
	clog << "      Band " << band
			<< ": stripe height = " << stripe_heights[band]
			<< '/' << max_stripe_heights[band]
			<< ", bytes = "
			<< (Image_Size.Width * max_stripe_heights[band]
				* (stripe_buffers_2 ? 2 : 4)) << endl;
	#endif
	precisions[band] = Pixel_Bits;
	stripe_lines[band] = 0;
	if (stripe_buffers_2)
		{
		if ((stripe_buffers_2[band] =
				new kdu_int16[Image_Size.Width * max_stripe_heights[band]])
			== NULL)
			{
			ostringstream
				message;
			message << ID << endl
					<< "Unable to allocate image data encoding buffers." << endl
					<< "Couldn't allocate "
						<< (Image_Size.Width * max_stripe_heights[band]
							* sizeof (kdu_int16)) << " byte buffer for band "
						<< band << '.';
			throw runtime_error (message.str ());
			}
		}
	else
		{
		if ((stripe_buffers_4[band] = 
				new kdu_int32[Image_Size.Width * max_stripe_heights[band]])
			== NULL)
			{
			ostringstream
				message;
			message << ID << endl
					<< "Unable to allocate image data encoding buffers." << endl
					<< "Couldn't allocate "
						<< (Image_Size.Width * max_stripe_heights[band]
							* sizeof (kdu_int32)) << " byte buffer for band "
						<< band << '.';
			throw runtime_error (message.str ());
			}
		}
	}

//	Open the source file.
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    Opening the source file: " << Image_Source << endl;
#endif
ifstream
	data_source (Image_Source.c_str ());
if (! data_source)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to open image source file " << Image_Source;
	throw std::ios::failure (message.str ());
	}

//	Incremental line flush period.
int
	flush_period = incremental_flush_lines ();
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    Flush period = " << flush_period << endl;
#endif

#if ((DEBUG) & DEBUG_ENCODE)
clog << "    Compressing image stripes ..." << endl;
#endif
try
{
do 
    {
	//	N.B.: stripe_heights will never exceed max_stripe_heights.
    compressor.get_recommended_stripe_heights
		(MIN_STRIPE_HEIGHT, MAX_STRIPE_HEIGHT, stripe_heights, NULL);
	for (unsigned int
			band = 0;
			band < Image_Bands;
			band++)
		{
		if (stripe_buffers_2)
        	read_stripe (data_source, band,
				stripe_lines[band], stripe_heights[band], stripe_buffers_2[band]);
		else
        	read_stripe (data_source, band,
				stripe_lines[band], stripe_heights[band], stripe_buffers_4[band]);
		stripe_lines[band] += stripe_heights[band];
		}
	}
	while (stripe_buffers_2 ?
		compressor.push_stripe
			(stripe_buffers_2, stripe_heights, NULL, NULL, precisions, NULL,
				flush_period) :
		compressor.push_stripe
			(stripe_buffers_4, stripe_heights, NULL, NULL, precisions, NULL,
				flush_period));
}
catch (int except)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Codestream compression failure" << endl
			<< "while processing the ";
	for (unsigned int
			band = 0;
			band < Image_Bands;
			band++)
		{
		if (band)
			message << '/';
		message << stripe_lines[band] << '-'
				<< (stripe_lines[band] + stripe_heights[band] - 1);
		}
	message << " image stripe lines.";
	Encoder_Error->add_text (message.str ());
	throw JP2_Encoder::ENCODER_EXCEPTION;
	}

//	Finish up.
#if ((DEBUG) & DEBUG_ENCODE)
clog << "    Finishing" << endl;
#endif
compressor.finish ();
JPEG2000_Codestream->destroy ();

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
delete[] layer_sizes;
delete[] precisions;

bytes_written = JP2_Stream->get_bytes_written () - bytes_written;
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Encoder::write_codestream: " << bytes_written << endl;
#endif
return bytes_written;
}


int
JP2_Encoder::incremental_flush_lines () const
{
#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Encoder::incremental_flush_lines" << endl
	 << "    Incremental_Flush_Bytes = " << Incremental_Flush_Bytes << endl;
#endif
int
	lines = 0;
long long
	line_bytes = (long long)Image_Size.Width * Pixel_Bytes;
if (Incremental_Flush_Bytes > 0 &&
	Incremental_Flush_Bytes < (Image_Size.Height * line_bytes))
	{
	if (! (lines = Tile_Size.Height))
		lines = Image_Size.Height;
	while ((lines * line_bytes) > Incremental_Flush_Bytes)
		{
		lines -= 1024;
		if (lines < 0)
			lines = 0;
		}
	}
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Encoder::incremental_flush_lines: " << lines << endl;
#endif
return lines;
}


JP2_Encoder&
JP2_Encoder::incremental_flush_lines
	(
	unsigned int	lines
	)
{
return incremental_flush_bytes
	((long long)Image_Size.Width * Pixel_Bytes * lines);
}


long long
JP2_Encoder::close ()
{
#if ((DEBUG) & DEBUG_ENCODE)
clog << ">>> JP2_Encoder::close" << endl
	 << "    Bytes written so far: " << JP2_Stream->get_bytes_written () << endl;
#endif
//	Close the JP2 boxes.
JP2_Boxes->close ();

//	Close the JP2 stream.
JP2_Stream->close ();
  
#if ((DEBUG) & DEBUG_ENCODE)
clog << "<<< JP2_Encoder::close: " << JP2_Stream->get_bytes_written () << endl;
#endif
return JP2_Stream->get_bytes_written ();
}


bool
JP2_Encoder::ready () const
{
if (Image_Source.empty () ||
	JP2_Pathname.empty () ||
	! Image_Bands ||
	! Image_Size.Width ||
	! Image_Size.Height ||
	! Pixel_Bytes)
	return false;
return true;
}


int
JP2_Encoder::needs () const
{
int
	need = 0;
if (Image_Source.empty ())
	need |= NEEDS_SOURCE;
if (JP2_Pathname.empty ())
	need |= NEEDS_DESTINATION;
if (! Image_Bands ||
	! Image_Size.Width ||
	! Image_Size.Height ||
	! Pixel_Bytes)
	need |= NEEDS_IMAGE;
return need;
}


string
JP2_Encoder::reasons () const
{
string
	reason;
if (Image_Source.empty ())
	reason += "No image source pathname.";
if (JP2_Pathname.empty ())
	reason += string (reason.empty () ? "" : "\n")
		+ "No image destination pathname.";
if (! Image_Bands)
	reason += string (reason.empty () ? "" : "\n")
		+ "No image bands.";
if (! Image_Size.Width)
	reason += string (reason.empty () ? "" : "\n")
		+ "No image width.";
if (! Image_Size.Height)
	reason += string (reason.empty () ? "" : "\n")
		+ "No image height.";
if (! Pixel_Bytes)
	reason += string (reason.empty () ? "" : "\n")
		+ "No pixel bytes.";
return reason;
}


JP2_Encoder_Error*
JP2_Encoder::encoder_error () const
{return Encoder_Error;}

/*==============================================================================
	Pixel data readers
*/
#if ((DEBUG) & DEBUG_READ_STRIPE)
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
void
JP2_Encoder::read_stripe
	(
	std::istream&	source,
	int				band,
	int				line,
	int				lines,
	kdu_int16*		buffer
	)
{
#if ((DEBUG) & DEBUG_READ_STRIPE)
clog << ">>> JP2_Encoder::read_stripe:" << endl
	 << "           Band - " << band << endl
	 << "     First line - " << line << endl
	 << "   Stripe lines - " << lines << endl;
static bool
	line_report = true;
#endif
streamsize
	line_bytes = Image_Size.Width * Pixel_Bytes;
if (! line_bytes ||
	! lines)
	{
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	clog << "<<< JP2_Encoder::read_stripe: no data" << endl;
	#endif
	return;
	}
streamoff
	line_location =
		//	Start of image data.
		Image_Offset
		//	Skip previous bands.
		+ ((streamoff)(Line_Prefix_Bytes + line_bytes + Line_Suffix_Bytes)
			* Image_Size.Height
			* band)
		//	Skip previous lines.
		+ ((streamoff)(Line_Prefix_Bytes + line_bytes + Line_Suffix_Bytes)
			* line)
		//	Beginning of line.
		+ Line_Prefix_Bytes;
#if ((DEBUG) & DEBUG_READ_STRIPE)
clog << "    File offset - " << line_location << endl;
#endif
source.seekg (line_location, std::ios::beg);
if (! source)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to position the source file to location "
				<< line_location << endl
			<< "  at line " << line << " of band " << band << '.';
	throw std::ios::failure (message.str ());
	}

kdu_int16
	*data,
	level_shift = Signed_Data ? 0 : 1 << (Pixel_Bits - 1);
#if ((DEBUG) & DEBUG_READ_STRIPE)
if (line_report)
	clog << "    Data value level shift - " << level_shift << endl;
#endif
for (lines += line;
	 line < lines;
	 buffer += Image_Size.Width)
	{
	if (! source.read ((char*)buffer, line_bytes))
		{
		ostringstream
			message;
		message << ID << endl
				<< "Unable to read a " << line_bytes
					<< " byte line of image data" << endl
				<< "  at line " << line << " of band " << band << '.';
		throw std::ios::failure (message.str ());
		}
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	if (line_report)
		{
		clog << "    Input line " << line << endl;
		if (Pixel_Bytes == 1)
			print_buffer ((unsigned char*)buffer, Image_Size.Width);
		else
			print_buffer (buffer, Image_Size.Width);
		}
	#endif

	if (Pixel_Bytes == 1)
		{
		// Expand to a multi-byte signed representation.
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		if (line_report)
			clog << "    Pixel values expanded" << endl;
		#endif
		unsigned char
			*bytes = (unsigned char*)buffer + line_bytes;
		data = buffer + Image_Size.Width;
		while (--data >= buffer)
			*data = ((kdu_int16)*(--bytes)) - level_shift;
		}
	else if (Swap_Pixel_Bytes)
		{
		// Swap byte order and make signed representation.
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		if (line_report)
			clog << "    Pixel bytes swapped" << endl;
		#endif
		data = buffer + Image_Size.Width;
		while (--data >= buffer)
			*data = (*data << 8) + ((*data >> 8) & 0xFF) - level_shift;
		}
	else if (! Signed_Data)
		{
		// Make signed representation.
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		if (line_report)
			clog << "    Pixel values level shifted" << endl;
		#endif
		data = buffer + Image_Size.Width;
		while (--data >= buffer)
			*data -= level_shift;
		}
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	if (line_report)
		{
		clog << "    Output line " << line << endl;
		print_buffer (buffer, Image_Size.Width);
		}
	#endif

	if (++line < lines &&
		(Line_Prefix_Bytes ||
		 Line_Suffix_Bytes))
		 {
		//	Move to the beginning of the next line.
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		clog << "    Skipping "
				<< (Line_Prefix_Bytes + Line_Suffix_Bytes) << endl;
		#endif
		source.seekg (Line_Prefix_Bytes + Line_Suffix_Bytes, std::ios::cur);
		if (! source)
			{
			ostringstream
				message;
			message << ID << endl
					<< "Unable to skip "
						<< Line_Prefix_Bytes << " prefix bytes and "
						<< Line_Suffix_Bytes << " suffix bytes" << endl
						<< line_location << endl
					<< "  at the end of line " << line
						<< " of band " << band << '.';
			throw std::ios::failure (message.str ());
			}
		}
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	#if ((DEBUG) & DEBUG_ONE_LINE)
	line_report = false;
	#endif
	#endif
	}
#if ((DEBUG) & DEBUG_READ_STRIPE)
clog << "<<< JP2_Encoder::read_stripe" << endl;
#endif
}


void
JP2_Encoder::read_stripe
	(
	std::istream&	source,
	int				band,
	int				line,
	int				lines,
	kdu_int32*		buffer
	)
{
#if ((DEBUG) & DEBUG_READ_STRIPE)
clog << ">>> JP2_Encoder::read_stripe:" << endl
	 << "           Band - " << band << endl
	 << "     First line - " << line << endl
	 << "   Stripe lines - " << lines << endl;
static bool
	line_report = true;
#endif
streamsize
	line_bytes = Image_Size.Width * Pixel_Bytes;
if (! line_bytes ||
	! lines)
	{
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	clog << "<<< JP2_Encoder::read_stripe: no data" << endl;
	#endif
	return;
	}
streamoff
	line_location =
		//	Start of image data.
		Image_Offset
		//	Skip previous bands.
		+ ((streamoff)(Line_Prefix_Bytes + line_bytes + Line_Suffix_Bytes)
			* Image_Size.Height
			* band)
		//	Skip previous lines.
		+ ((streamoff)(Line_Prefix_Bytes + line_bytes + Line_Suffix_Bytes)
			* line)
		//	Beginning of line.
		+ Line_Prefix_Bytes;
#if ((DEBUG) & DEBUG_READ_STRIPE)
clog << "    File offset - " << line_location << endl;
#endif
source.seekg (line_location, std::ios::beg);
if (! source)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to position the source file to location "
				<< line_location << endl
			<< "  at line " << line << " of band " << band << '.';
	throw std::ios::failure (message.str ());
	}

kdu_int32
	*data = NULL,
	level_shift = Signed_Data ? 0 : 1 << (Pixel_Bits - 1);
#if ((DEBUG) & DEBUG_READ_STRIPE)
if (line_report)
	clog << "    Data value level shift - " << level_shift << endl;
#endif
for (lines += line;
	 line < lines;
	 buffer += Image_Size.Width)
	{
	if (! source.read ((char*)buffer, line_bytes))
		{
		ostringstream
			message;
		message << ID << endl
				<< "Unable to read a " << line_bytes
					<< " byte line of image data" << endl
				<< "  at line " << line << " of band " << band << '.';
		throw std::ios::failure (message.str ());
		}
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	if (line_report)
		{
		clog << "    Input line " << line << endl;
		print_buffer (buffer, Image_Size.Width);
		}
	#endif

	if (Swap_Pixel_Bytes)
		{
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		if (line_report)
			clog << "    Pixel bytes swapped" << endl;
		#endif
		swap_bytes ((unsigned char*)data, Image_Size.Width, Pixel_Bytes);
		}
	if (! Signed_Data)
		{
		// Make signed representation.
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		if (line_report)
			clog << "    Pixel values level shifted" << endl;
		#endif
		data = buffer + Image_Size.Width;
		while (--data >= buffer)
			*data -= level_shift;
		}
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	if (line_report)
		{
		clog << "    Output line " << line << endl;
		print_buffer (buffer, Image_Size.Width);
		}
	#endif

	if (++line < lines &&
		(Line_Prefix_Bytes ||
		 Line_Suffix_Bytes))
		 {
		//	Move to the beginning of the next line.
		#if ((DEBUG) & DEBUG_READ_STRIPE)
		clog << "    Skipping "
				<< (Line_Prefix_Bytes + Line_Suffix_Bytes) << endl;
		#endif
		source.seekg (Line_Prefix_Bytes + Line_Suffix_Bytes, std::ios::cur);
		if (! source)
			{
			ostringstream
				message;
			message << ID << endl
					<< "Unable to skip "
						<< Line_Prefix_Bytes << " prefix bytes and "
						<< Line_Suffix_Bytes << " suffix bytes" << endl
						<< line_location << endl
					<< "  at the end of line " << line
						<< " of band " << band << '.';
			throw std::ios::failure (message.str ());
			}
		}
	#if ((DEBUG) & DEBUG_READ_STRIPE)
	#if ((DEBUG) & DEBUG_ONE_LINE)
	line_report = false;
	#endif
	#endif
	}
#if ((DEBUG) & DEBUG_READ_STRIPE)
clog << "<<< JP2_Encoder::read_stripe" << endl;
#endif
}

#ifndef DOXYGEN_PROCESSING
/*=*****************************************************************************
	JP2_Encoder_Error
*/
void
JP2_Encoder_Error::put_text
	(
	const char*	message
	)
{Message += message;}

void
JP2_Encoder_Error::add_text
	(
	const std::string&	message
	)
{
if (! Message.empty ())
	Message += '\n';
Message += message;
}


void
JP2_Encoder_Error::flush
	(
	bool	end_of_message
	)
{
//	Signal that an error occured.
throw JP2_Encoder::ENCODER_EXCEPTION;
}
#endif


}	//	namespace HiRISE
}	//	namespace UA
