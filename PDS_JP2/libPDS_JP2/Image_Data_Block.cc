/*	Image_Data_Block

HiROC CVS ID: Image_Data_Block.cc,v 1.14 2013/03/14 21:00:43 guym Exp

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

*******************************************************************************/

#include	"Image_Data_Block.hh"

#include	"PVL.hh"
using namespace idaeim::PVL;

#include	<string>
using std::string;

#include <exception>
using std::exception;

#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			-1
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_ACCESSORS		(1 << 1)
#include	<iostream>
#include	<iomanip>
using std::clog;
using std::boolalpha;
using std::endl;
#endif  // DEBUG


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	Image_Data_Block
*/
/*==============================================================================
	Constants:
*/
const char* const
	Image_Data_Block::ID =
		"UA::HiRISE::Image_Data_Block (1.14 2013/03/14 21:00:43)";

const char* const
	Image_Data_Block::IMAGE_BANDS_PARAMETER_NAME		= "BANDS";
const char* const
	Image_Data_Block::IMAGE_WIDTH_PARAMETER_NAME		= "LINE_SAMPLES";
const char* const
	Image_Data_Block::IMAGE_HEIGHT_PARAMETER_NAME		= "LINES";
const char* const
	Image_Data_Block::PIXEL_BYTES_PARAMETER_NAME		= "SAMPLE_BITS";
const char* const
	Image_Data_Block::PIXEL_BITS_PARAMETER_NAME			= "SAMPLE_BIT_MASK";
const char* const
	Image_Data_Block::PIXEL_DATA_TYPE_PARAMETER_NAME	= "SAMPLE_TYPE";
const char* const
	Image_Data_Block::UNSIGNED_PIXEL_TYPE_IDENTIFIER	= "UNSIGNED";
const char* const
	Image_Data_Block::SIGNED_PIXEL_TYPE_IDENTIFIER		= "SIGNED";
const char* const
	Image_Data_Block::LSB_PIXEL_TYPE_IDENTIFIER			= "LSB";
const char* const
	Image_Data_Block::MSB_PIXEL_TYPE_IDENTIFIER			= "MSB";
const char* const
	Image_Data_Block::LINE_PREFIX_BYTES_PARAMETER_NAME	= "LINE_PREFIX_BYTES";
const char* const
	Image_Data_Block::LINE_SUFFIX_BYTES_PARAMETER_NAME	= "LINE_SUFFIX_BYTES";

/*==============================================================================
	Constructors
*/
Image_Data_Block::Image_Data_Block ()
	:	Image_Bands (0),
		Image_Width (0),
		Image_Height (0),
		Pixel_Bytes (0),
		Pixel_Bits (0),
		Line_Prefix_Bytes (0),
		Line_Suffix_Bytes (0),
		Signed_Data (0),
		MSB_Data (0)
{}


Image_Data_Block::Image_Data_Block
	(
	const idaeim::PVL::Aggregate&	parameters,
	std::ios::off_type				file_offset
	)
	:	PDS_Data_Block (parameters, file_offset),
		Image_Bands (0),
		Image_Width (0),
		Image_Height (0),
		Pixel_Bytes (0),
		Pixel_Bits (0),
		Line_Prefix_Bytes (0),
		Line_Suffix_Bytes (0),
		Signed_Data (0),
		MSB_Data (0)
{
#if (DEBUG & DEBUG_CONSTRUCTORS)
clog << ">>> Image_Data_Block" << endl;
#endif
Size = data_block_size ();
#if (DEBUG & DEBUG_CONSTRUCTORS)
clog << ">>> Image_Data_Block" << endl;
#endif
}

Image_Data_Block::Image_Data_Block
   (
   const idaeim::PVL::Aggregate& parameters,
   const std::string& filename
   )
   :  PDS_Data_Block (parameters, filename),
      Image_Bands (0),
      Image_Width (0),
      Image_Height (0),
      Pixel_Bytes (0),
      Pixel_Bits (0),
      Line_Prefix_Bytes (0),
      Line_Suffix_Bytes (0),
      Signed_Data (0),
      MSB_Data (0)

{
#if (DEBUG & DEBUG_CONSTRUCTORS)
clog << ">>> Image_Data_Block" << endl;
#endif
Size = data_block_size ();
Source_Filename = std::string(filename);
#if (DEBUG & DEBUG_CONSTRUCTORS)
clog << ">>> Image_Data_Block" << endl;
#endif
}

std::string
Image_Data_Block::source_filename()
{
    return Source_Filename;
}

std::string
Image_Data_Block::source_filename(std::string& source_filename)
{
   return Source_Filename = source_filename;
}

unsigned long long
Image_Data_Block::data_block_size ()
{
#if (DEBUG & DEBUG_ACCESSORS)
clog << ">>> Image_Data_Block::data_block_size" << endl;
#endif
const Parameter
	*parameter;
if ((parameter = find_parameter (IMAGE_BANDS_PARAMETER_NAME)))
	Image_Bands = parameter->value ();
else
	Image_Bands = 1;
if ((parameter = find_parameter (IMAGE_WIDTH_PARAMETER_NAME)))
	Image_Width = parameter->value ();
if ((parameter = find_parameter (IMAGE_HEIGHT_PARAMETER_NAME)))
	Image_Height = parameter->value ();
if ((parameter = find_parameter (PIXEL_BYTES_PARAMETER_NAME)))
	{
	//	The parameter provides storage bits per pixel.
	Pixel_Bytes = parameter->value ();
	//	Convert to storage bytes per pixel.
	Pixel_Bytes = (Pixel_Bytes >> 3) + ((Pixel_Bytes % 8) ? 1 : 0);
	}
if ((parameter = find_parameter (PIXEL_BITS_PARAMETER_NAME)))
	{
	//	The parameter provides a mask of valid bits.
	unsigned int
		mask = parameter->value ();
	//	Count the mask bits.
	for (Pixel_Bits = 0;
		 mask;
		 Pixel_Bits++, mask >>= 1);
	if (! Pixel_Bits)
		Pixel_Bits = Pixel_Bytes << 3;
	}
else
	Pixel_Bits = Pixel_Bytes << 3;
if ((parameter = find_parameter (PIXEL_DATA_TYPE_PARAMETER_NAME)))
	{
	string
		sample_type ((string)parameter->value ());
	#if (DEBUG & DEBUG_ACCESSORS)
	clog << "    " << parameter->name () << " = " << sample_type << endl;
	#endif
	//	N.B.: The unsigned test must be first!
	Signed_Data =
		((sample_type.find (UNSIGNED_PIXEL_TYPE_IDENTIFIER)
			!= string::npos) ? -1 :
		((sample_type.find (SIGNED_PIXEL_TYPE_IDENTIFIER)
			!= string::npos) ?  1 : 0));
	MSB_Data =
		((sample_type.find (LSB_PIXEL_TYPE_IDENTIFIER)
			!= string::npos) ? -1 :
		((sample_type.find (MSB_PIXEL_TYPE_IDENTIFIER)
			!= string::npos) ?  1 : 0));
	}
if ((parameter = find_parameter (LINE_PREFIX_BYTES_PARAMETER_NAME)))
	Line_Prefix_Bytes = parameter->value ();
if ((parameter = find_parameter (LINE_SUFFIX_BYTES_PARAMETER_NAME)))
	Line_Suffix_Bytes = parameter->value ();

#if (DEBUG & DEBUG_ACCESSORS)
clog
	<< "    Image_Bands       = " << Image_Bands << endl
	<< "    Image_Width       = " << Image_Width << endl
	<< "    Image_Height      = " << Image_Height << endl
	<< "    Pixel_Bytes       = " << Pixel_Bytes << endl
	<< "    Pixel_Bits        = " << Pixel_Bits << endl
	<< "    Line_Prefix_Bytes = " << Line_Prefix_Bytes << endl
	<< "    Line_Suffix_Bytes = " << Line_Suffix_Bytes << endl
	<< "    Signed_Data       = "
		<< ((Signed_Data > 0) ? "true" :
			(Signed_Data < 0) ? "false" : "unknown") << endl
	<< "    MSB_Data          = "
		<< ((MSB_Data > 0) ? "true" :
			(MSB_Data < 0) ? "false" : "unknown") << endl
	<< "<<< Image_Data_Block::data_block_size: "
		<< ((unsigned long long)Image_Height
			* (Line_Prefix_Bytes
			+ (Image_Width * Pixel_Bytes)
			+ Line_Suffix_Bytes)
			* Image_Bands) << endl;
#endif
return
	(unsigned long long)Image_Height
	* (Line_Prefix_Bytes + (Image_Width * Pixel_Bytes) + Line_Suffix_Bytes)
	* Image_Bands;
}

}	//	namespace HiRISE
}	//	namespace UA
