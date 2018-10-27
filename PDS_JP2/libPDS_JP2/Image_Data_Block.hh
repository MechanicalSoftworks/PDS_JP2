/*	Image_Data_Block

HiROC CVS ID: Image_Data_Block.hh,v 1.13 2013/03/14 21:00:43 guym Exp

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

#ifndef _Image_Data_Block_
#define _Image_Data_Block_

#include	"PDS_Data_Block.hh"

#include <string>

namespace UA
{
namespace HiRISE
{
/**	An <i>Image_Data_Block</i> describes PDS image data. 

	An Image_Data_Block is a PDS_Data_Block that specializes in describing
	PDS image data.

	@author		Bradford Castalia, Drew Davidson and Ben Pearson, UA/HiROC
	@version	1.13
	@see		PDS_Data_Block
*/
class Image_Data_Block
:	public PDS_Data_Block
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const ID;

//!	The name of the parameter used to obtain the image bands value.
static const char* const
	IMAGE_BANDS_PARAMETER_NAME;

//!	The name of the parameter used to obtain the image width value.
static const char* const
	IMAGE_WIDTH_PARAMETER_NAME;

//!	The name of the parameter used to obtain the image height value.
static const char* const
	IMAGE_HEIGHT_PARAMETER_NAME;

//!	The name of the parameter used to obtain the pixel storage bytes value.
static const char* const
	PIXEL_BYTES_PARAMETER_NAME;

//!	The name of the parameter used to obtain the valid pixel bits value.
static const char* const
	PIXEL_BITS_PARAMETER_NAME;

//!	The name of the parameter used to obtain the pixel data type values.
static const char* const
	PIXEL_DATA_TYPE_PARAMETER_NAME;

/**	Substring of the PIXEL_DATA_TYPE_PARAMETER_NAME parameter
	that identifies an unsigned pixel value.
*/
static const char* const
	UNSIGNED_PIXEL_TYPE_IDENTIFIER;

/**	Substring of the PIXEL_DATA_TYPE_PARAMETER_NAME parameter
	that identifies a signed pixel value.
*/
static const char* const
	SIGNED_PIXEL_TYPE_IDENTIFIER;

/**	Substring of the PIXEL_DATA_TYPE_PARAMETER_NAME parameter
	that identifies an LSB ordered pixel.
*/
static const char* const
	LSB_PIXEL_TYPE_IDENTIFIER;

/**	Substring of the PIXEL_DATA_TYPE_PARAMETER_NAME parameter
	that identifies an MSB ordered pixel.
*/
static const char* const
	MSB_PIXEL_TYPE_IDENTIFIER;

//!	The name of the parameter used to obtain the line prefix bytes value.
static const char* const
	LINE_PREFIX_BYTES_PARAMETER_NAME;

//!	The name of the parameter used to obtain the line suffix bytes value.
static const char* const
	LINE_SUFFIX_BYTES_PARAMETER_NAME;

/*==============================================================================
	Constructors
*/
/**	Constructs an empty Image_Data_Block.
*/
Image_Data_Block ();

/**	Constructs an Image_Data_Block for an IMAGE OBJECT.

	@param	parameters	Parameter Aggregate describing the data block
	@param	file_offset	Image data block offset location in the source file.
*/
Image_Data_Block
	(
	const idaeim::PVL::Aggregate&	parameters,
	std::ios::off_type				file_offset
	);

/**   Constructs an Image_Data_Block for an IMAGE OBJECT in a detached file.

   @param   parameters  Parameter Aggregate describing the data block
   @param   filename    Name of file containing the image.
*/
Image_Data_Block
   (
   const idaeim::PVL::Aggregate& parameters,
   const std::string& filename
   );


/*==============================================================================
	Accessors:
*/
/**	Get the number of bands in the image.

	The number of image bands is assumed to be 1 if it can not be
	determined from the IMAGE_BANDS_PARAMETER_NAME parameter.

	@return	The number of image bands.
*/
unsigned int image_bands ()
{return Image_Bands;}

/**	Get the width of the image.

	@return	The number of pixels in each line of the image. This will be
		zero if the value could not be determined from the
		IMAGE_WIDTH_PARAMETER_NAME parameter.
*/
unsigned int image_width ()
{return Image_Width;}

/**	Get the height of the image.

	@return	The number of lines in the image. This will be zero if the
		value could not be determined from the
		IMAGE_HEIGHT_PARAMETER_NAME parameter.
*/
unsigned int image_height ()
{return Image_Height;}

/**	Get the storage size of a pixel in bytes.

	<b>N.B.</b>: The number of {@link pixel_bits() valid bits} in a pixel
	may be less than the total number of bits in the pixel bytes used to
	store the pixel.

	@return	The number of storage bytes per pixel. This will be zero if
		the value could not be determined from the
		PIXEL_BYTES_PARAMETER_NAME parameter.
*/
unsigned int pixel_bytes ()
{return Pixel_Bytes;}

/**	Get the number valid bits (data precision) in a pixel.

	If the number of bits per pixel can not be determined from the
	PIXEL_BITS_PARAMETER_NAME parameter the valid pixel bits are assumed
	to be all bits in the {@link pixel_bytes() pixel bytes}.

	<b>N.B.</b>: The number of valid bits in a pixel may be less than the
	total number of bits in the pixel bytes used to store the pixel. The
	valid pixel bits occupy the least significant bits of the pixel
	bytes.

	@return	The number of valid bits in a pixel. This will be zero if
		neither the PIXEL_BITS_PARAMETER_NAME parameter could be found
		nor the {@link pixel_bytes() bytes per pixel} determined.
*/
unsigned int pixel_bits ()
{return Pixel_Bits;}

/**	Check if the pixel data is signed.

	The signedness of the data is determined by identifying the
	UNSIGNED_PIXEL_TYPE_IDENTIFIER or SIGNED_PIXEL_TYPE_IDENTIFIER
	substring in the PIXEL_DATA_TYPE_PARAMETER_NAME parameter.

	@return	1 if the data is signed, -1 if unsigned, 0 if unknown.
*/
int signed_data ()
{return Signed_Data;}

/**	Determine if the pixel data is MSB ordered.

	The data order is determined by identifying the
	LSB_PIXEL_TYPE_IDENTIFIER or MSB_PIXEL_TYPE_IDENTIFIER substring in
	the PIXEL_DATA_TYPE_PARAMETER_NAME parameter.

	@return	1 if the data is MSB ordered, -1 if LSB ordered, 0 if unknown.
*/
int MSB_data ()
{return MSB_Data;}

/**	Get the number of line prefix bytes.

	@return	The number of bytes preceeding each image pixel data line.
		This will be zero if the value could not be determined from
		the LINE_PREFIX_BYTES_PARAMETER_NAME parameter.
*/
unsigned int line_prefix_bytes ()
{return Line_Prefix_Bytes;}

/**	Get the number of line suffix bytes.

	@return	The number of bytes following each image pixel data line.
		This will be zero if the value could not be determined from
		the LINE_SUFFIX_BYTES_PARAMETER_NAME parameter.
*/
unsigned int line_suffix_bytes ()
{return Line_Suffix_Bytes;}

std::string source_filename();

/*------------------------------------------------------------------------------
 * Manipulators
 */
std::string source_filename(std::string& pathname);

/*==============================================================================
	Data Members:
*/
protected:

 
/**	Calculate the size of the binary data block.

	The image data block size is calculated as:

<code>
	image_height() *
	(line_prefix_bytes() + (image_width() * pixel_bytes()) + line_suffix_bytes())
	* image_bands()
</code>

	<b>N.B.</b>: All of the image characterization values are determined
	in this method. It is presumed that it is called when the object is
	constructed.

	@return	The size (bytes) of the binary data block in the source file.
*/
virtual unsigned long long data_block_size ();

private:

std::string
    Source_Filename;
    
unsigned int
	Image_Bands,
	Image_Width,
	Image_Height,
	Pixel_Bytes,
	Pixel_Bits,
	Line_Prefix_Bytes,
	Line_Suffix_Bytes;

//!	Tri-state flags: false (-), true (+), unknown (0).
int
	Signed_Data,
	MSB_Data;
};

}	//	namespace HiRISE
}	//	namespace UA
#endif
