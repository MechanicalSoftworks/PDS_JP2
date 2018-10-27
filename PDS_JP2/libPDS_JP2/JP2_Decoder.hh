/*	JP2_Decoder

HiROC CVS ID: JP2_Decoder.hh,v 1.14 2007/12/13 05:18:56 castalia Exp

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
*/

#ifndef _JP2_Decoder_
#define _JP2_Decoder_

#include	"Dimensions.hh"

//	Kakadu
#include	"jp2.h"

#include	<string>
#include	<iosfwd>

namespace UA
{
namespace HiRISE
{
//	Forward reference.
class JP2_Decoder_Error;

/**	A <i>JP2_Decoder</i> decodes image pixel data from a JPEG2000 JP2
	image file.

	After a JP2_Decoder is constructed it must be configured. The
	decoder must be configured with at least an input JP2 {@link
	source(const std::string&) source} file before it can be {@link
	open() opened}. Once opened numerous accessors can be used to get
	information from the JP2 file, especially image data
	characterization. A JP2_Decoder may be configured to {@link
	swap_pixel_bytes(bool) reorder} muli-byte pixel data (the codestream
	is expected to produce MSB ordered data by default), decompress a
	selected {@link image_region(const Rectangle&) region} of the entire
	image or render at less than the full {@link
	resolution_level(unsigned int) resolution level}. It must also be
	configured with an output image data {@link
	destination(const std::string&) destination} file to be {@link
	ready() ready} to {@link decode() decode} the source which includes
	opening the source and {@link write_image_data() writing the image
	data}.

	A JP2_Decoder may be reused with or without between uses. Other than
	the source and destination, its configuration is reset to the
	default values whenever it is {@link close() closed}.

	This implementation employs the
	<a href="http://www.kakadusoftware.com/" target="_top">Kakadu
	Software</a> libraries.

	@author		Bradford Castalia, UA/HiROC
	@version	1.14
*/
class JP2_Decoder
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

//!	PDS label reference information UUID Info JP2 container box name.
static const char* const
	UUID_INFO_BOX_NAME;
//!	Data provider UUID JP2 box name.
static const char* const
	UUID_BOX_NAME;
//!	Size of the UUID data content.
#define UUID_SIZE	16
//!	PDS label relative filename URL JP2 box name.
static const char* const
	URL_BOX_NAME;

//!	Image data stripe minimum and maximum number of lines.
static const int
	MIN_STRIPE_HEIGHT,
	MAX_STRIPE_HEIGHT;

//!	JP2_Decoder_Error exception signal value.
static const int
	DECODER_EXCEPTION;

/*==============================================================================
	Constructors:
*/
/**	Constructs a JP2_Decoder.

	The decoder must be configured with at least an input JP2 {@link
	source(const std::string&) source} before it can be {@link open()
	opened}. It must also be configured with an output image data {@link
	destination(const std::string&) destination} to be {@link ready()
	ready} to do its job.
*/
JP2_Decoder ();

/*==============================================================================
	Accessors:
*/
//------------------------------------------------------------------------------
//	Input

/**	Get the JP2 source pathname.

	@return	The pathname string for the JP2 source. This will be the empty
		string if no source has been bound to this JP2_Decoder.
*/
std::string source () const
	{return JP2_Pathname;}

/**	Set the pathname to the JP2 source.

	<b>N.B.</b>: If the source has already been {@link #open() opened}
	and the pathname is different than the previous pathname, the
	source is {@link #close() closed}.

	@param	pathname	The JP2 source pathname.
	@return	This JP2_Decoder.
*/
JP2_Decoder& source (const std::string& pathname);

/**	Get the size of the JP2 source image.

	<b>N.B.</b>: Use the image_width() and image_height() methods for
	fast access to the image size values.

	@return	A Size_2D object containing the image width and height.
		These values will be zero until the JP2 source has been {@link
		open() opened}.
*/
Size_2D image_size () const
	{return Image_Size;}

/**	Get the width of the JP2 source image.

	@return	The width of the image in pixels. This will be zero until
		the JP2 source has been {@link open() opened}.
*/
unsigned int image_width () const
	{return Image_Size.Width;}

/**	Get the height of the JP2 source image.

	@return	The height of the image in lines. This will be zero until
		the JP2 source has been {@link open() opened}.
*/
unsigned int image_height () const
	{return Image_Size.Height;}

/**	Get the number of bands (components) in the JP2 image.

	@return	The number of bands in the JP2 image. This will be zero
		until the JP2 source has been {@link open() opened}.
*/
unsigned int image_bands () const
	{return Image_Bands;}

/**	Get the total number of codestream resolution levels.

	<b>N.B.</b>: The number of resolution levels is one more than the
	number of JPEG2000 decomposition levels.

	The number of resolution levels is determined from the default
	codestream (COD segment) values. Tile segments may override this
	value.

	@return	The total number of codestream resolution levels. This will
		be zero until the JP2 source has been {@link open() opened}.
*/
unsigned int resolution_levels () const
	{return Resolution_Levels;}

/**	Get the number of bytes per pixel.

	@return	The number of storage bytes used by each pixel. This will be
		zero until the JP2 source has been {@link open() opened}.
*/
unsigned int pixel_bytes () const
	{return Pixel_Bytes;}

/**	Get the pixel precision.

	@return	The number of valid bits used by each pixel. This will be
		zero until the JP2 source has been {@link open() opened}.
*/
unsigned int pixel_bits () const
	{return Pixel_Bits;}

/**	Get the signedness of the pixel data.

	@return	true if the pixel data is treated as signed; false
		otherwise. This information will be meaningless until the JP2
		source has been {@link open() opened}.
*/
bool signed_data () const
	{return Signed_Data;}

/**	Get the UUID found in the JP2 source.

	The first UUID value in a UUID List box of a UUID Info super box
	is copied. There may be additional UUID values, List boxes or
	Info boxes but these are ignored.

	@return	A 16 byte (UUID_SIZE) array. <b>N.B.</b>: This is not
		null-terminated C-string character array. If no UUID has
		been found, or the JP2 source has not been {@link open() opened},
		this will be NULL.
*/
unsigned char* const producer_UUID () const
	{return UUID_Info_UUID;}

/**	Get the URL found in the JP2 source.

	The first URL box contents of a UUID Info super box is copied.
	There may be additional URL boxes but they are ignored.

	@return	A URL string. This will be empty if no URL has been found
		or the JP2 source has not been {@link open() opened}.
*/
std::string URL () const
	{return UUID_Info_URL;}

//------------------------------------------------------------------------------
//	Output

/**	Get the destination file pathname for the rendered image data.

	@return	The destination file pathname string. This will be empty
		if no destination has been bound to this JP2_Decoder.
*/
std::string destination () const
	{return Image_Destination;}

/**	Set the destination file pathname for the rendered image data.

	@param	pathname	The destination file pathname string.
	@return	This JP2_Decoder.
*/
JP2_Decoder& destination (const std::string& pathname)
	{Image_Destination = pathname; return *this;}

/**	Get the size of the rendered image.

	@return	A Size_2D object containing the rendered image width and height.
		These values will be zero until the JP2 source has been {@link
		open() opened}.
	@see	rendered_width()
	@see	rendered_height()
*/
Size_2D rendered_size () const;

/**	Get the width of the rendered image.

	@return	The width of the rendered image in pixels. This will be zero
		until the JP2 source has been {@link open() opened}.
	@see	rendered_size()
*/
unsigned int rendered_width () const;

/**	Get the height of the rendered image.

	@return	The height of the rendered image in lines. This will be zero
		until the JP2 source has been {@link open() opened}.
	@see	rendered_size()
*/
unsigned int rendered_height () const;

/**	Get the image region that will be rendered from the JP2 source.

	@return	The Rectangle specifying the image region to be rendered.
		If no image region has been specified and the JP2 source has not
		yet been {@link open() opened} all the Rectangle values will be
		zero. When the JP2 source is opened, if no image region has been
		specified it will be initialized to the entire {@link
		image_size() image size}. If an image region has been specified
		it will be set to the intersection of the image size and the
		image region.
	@see	image_region(const Rectangle&)
	@see	image_size()
*/
Rectangle image_region () const
	{return Image_Region;}

/**	Set the image region that will be rendered from the JP2 source.

	The image region is specified relative to the full resolution
	image. Specifying a rendering {@link resolution_level(unsigned int)
	resolution level} greater than 1 will result in a correspondingly
	smaller image region.

	The actual image region rendered will be the intersection of the
	region with the {@link image_size() image size}.

	@param	region	A Rectangle specifying the image region to be
		rendered.	
	@return	This JP2_Decoder.
	@throws	out_of_range	If the decoder has been {@link open()
		opened} and selected region does not intersect with the
		image.
	@see	image_region(int, int, int, int)
*/
JP2_Decoder& image_region (const Rectangle& region);

/**	Set the image region that will be rendered from the JP2 source.

	@param	x	The horizontal (x-axis) position of the image region.
	@param	y	The vertical (y-axis) position of the image region.
	@param	width	The width of the image region.
	@param	height	The height of the image region.
	@return	This JP2_Decoder.
	@throws	out_of_range	If the decoder has been {@link open()
		opened} and selected region does not intersect with the
		image.
	@see	image_region(const Rectangle&)
*/
JP2_Decoder& image_region (int x, int y, int width, int height);

/**	Get the resolution level at which the codestream will be rendered.

	@return	The codestream rendering resolution level.
	@see	resolution_level(unsigned int)
*/
unsigned int resolution_level () const
	{return Resolution_Level;}

/**	Set the resolution level at which the codestream will be rendered.

	Level 1 is full resolution. Level 2 renders the image at half size,
	level 3 at quarter size, etc.; i.e. the image size is divided by
	2**(level-1).

	<b>N.B.</b>: The resolution level is one more than the JPEG2000
	decomposition level.

	@param	level	The codestream rendering resolution level.
	@return	This JP2_Encoder.
	@throws	out_of_range	If the decoder has been {@link open()
		opened} since the {@link image_region(const Rectangle&) image
		region} was previously set and selected region does not
		intersect with the image.
*/
JP2_Decoder& resolution_level (unsigned int level);

/**	Tests if multi-byte pixels will be reordered before being written.

	@return	true if multi-byte pixels are to be reordered before
		writing; false otherwise.
*/
bool swap_pixel_bytes () const
	{return Swap_Pixel_Bytes;}

/**	Sets whether multi-byte pixels will be reordered before being written.

	By default multi-byte pixels will not be reordered. <b>N.B.</b>: The
	pixel data rendered from the JP2 file has no defined order. It is
	necessary to obtain correct pixel data ordering information elsewhere.

	@param	swap_data	true if multi-byte pixels are to be reordered
		before writing; false otherwise.
	@return	This JP2_Decoder.
*/
JP2_Decoder& swap_pixel_bytes (bool swap_data)
	{Swap_Pixel_Bytes = swap_data; return *this;}

/**	Get the number of image data bytes written.

	@return	The number of image data bytes {@link write_image_data()
		written}.
*/
unsigned long long bytes_written () const
	{return Bytes_Written;}

/*==============================================================================
	Decoder
*/
/**	Tests if the decoder has the information it needs to do its job.

	Both the {@link source() JP2 source} and {@link destination()
	rendered image destination} must be specified.

	@return	true if the decoder is ready; false otherwise.
*/
bool ready () const;

/**	Describe the reasons that the decoder is not ready.

	@return	A string, possibly of more than one line, that decribes
		the reasons for the decoder not being ready. This will be the
		empty string if the decoder is ready.
	@see	ready()
*/
std::string reasons () const;

/**	Deocde the pixel data from the JPEG2000 JP2 source and write the
	rendered results to the image data destination.
	
	The {@link source() JP2 source} is {@link open() opened}, the
	contents are rendered and {@link write_image_data() written} to
	the {@link destination() destination file}, and then the source
	is {@link close() closed}.

	@return	The number of bytes written to the image data file.
*/
unsigned long long decode ();

/**	Open the source JP2 file.

	If the source is already open nothing is done.

	Access to the {@link source() JP2 source} is opened and checked
	that it contains the required JP2 format content. The
	producer_UUID() and URL are extracted, if present. The image
	characterization - image_bands(), image_size(), pixel_bytes(),
	pixel_bits() and resolution_levels() - are determined. If the
	resolution level to be rendered is greater than the number of
	resolution levels, it is reduced to the maximum value. All the
	bands are compared to make suse they have the same image and
	pixel structure. The selected image_region(const Rectangle&),
	if any, is clipped to the image extent.

	@throws	logic_error	If no {@link source() JP2 source} has been
		specified
	@throws	out_of_range	If any of the image bands (JP2 components)
		do not have identical image structure (image and pixel).
	@throws	out_of_range	If the selected image region does not
		intersect the image extent.
*/
void open ();

/**	Test if the decoder is open.

	@return	true if this JP2_Decoder has been successfully {@link open()
		opened} and not yet closed; false otherwise.
*/
bool is_open () const;

/**	Write rendered image data.

	The JP2 source is {@link open() opened} if this has not yet
	been done, and the decoder is checked that it is {@link ready()
	ready}. Data buffers to hold horizontal stripes of rendered image
	data are allocated.

	The destination file is opened for writing. <b>N.B.</b>: If the file
	already exists the image data will be appended to the current
	content.

	@return	The number of image data bytes that were written to the
		destination file.
	@throws	logic_error	If the decoder is not ready().
	@throws	runtime_error	If insufficient memory is available to
		allocate the rendered image data buffers.
*/
unsigned long long write_image_data ();

/**	Close access to the JP2 source.

	The JP2 source stream is closed and all resources associated with it
	are deleted. In addition, the JP2 source image characterization
	information - image_bands(), image_size(), pixel_bytes(),
	pixel_bits(), resolution_levels() producer_UUID() and URL() - is
	reset to the unknown state. However, neither the source() nor
	destination() pathname is reset so this JP2_Decoder is ready to be
	reused.

	<b>N.B.</b>: Output specifications remain unchanged.
*/
void close ();

JP2_Decoder_Error* decoder_error () const;

/*============================================================================
	Image Data Writers:
*/
protected:

/**	Write an image data buffer with pixel data to a stream.

	The contents of the data buffer are expected to contain the results
	of codestream decoding of a horizontal stripe of the source image.
	This data is modified in place to adjust for data order and signedness.

	The lines of image data starting with the specified line of the
	specified band are written to the buffer as a contiguous sequence of
	bytes.

	@param	destination	An ostream that has been opened on the
		destination file.
	@param	file_offset	File offset to the start of the image data.
	@param	band	The index of the image band to which pixel data is
		to be written.
	@param	line	The starting index of the image line to which
		pixel data it to be written.
	@param	lines	The number of image lines to write.
	@param	buffer	Buffer storage containing lines * image_width
		pixels where each pixel is stored as a 16-bit signed integer.
	@return	The number of image data bytes that were written to the
		destination file.
*/
std::streamsize write_stripe
	(std::ostream& destination, std::streamoff file_offset,
		int band, int line, int lines, kdu_int16* buffer);

/**	Write an image data buffer with pixel data to a stream.

	The contents of the data buffer are expected to contain the results
	of codestream decoding of a horizontal stripe of the source image.
	This data is modified in place to adjust for data order and signedness.

	The lines of image data starting with the specified line of the
	specified band are written to the buffer as a contiguous sequence of
	bytes.

	@param	destination	An ostream that has been opened on the
		destination file.
	@param	file_offset	File offset to the start of the image data.
	@param	band	The index of the image band to which pixel data is
		to be written.
	@param	line	The starting index of the image line to which
		pixel data it to be written.
	@param	lines	The number of image lines to write.
	@param	buffer	Buffer storage containing lines * image_width
		pixels where each pixel is stored as a 16-bit signed integer.
	@return	The number of image data bytes that were written to the
		destination file.
*/
std::streamsize write_stripe
	(std::ostream& destination, std::streamoff file_offset,
		int band, int line, int lines, kdu_int32* buffer);

/*============================================================================
	Helpers:
*/
protected:

/**	Set the effective rendering resolution level and image region.

	The {@link resolution_level(unsigned int) resolution level} and
	{@link image_region(const Rectangle&) image region} interact to
	affect the {@link rendered_size() rendered image size} so they are
	set together.

	If the decoder has not been {@link open() opened} nothing is done.

	The efective resolution level is limited to the range 1-{@link
	resolution_levels() resolution levels} and applied as an input
	restriction on the codestream rendering machinery. Any existing image
	area restriction is lifted at the same time.

	If the image region is empty the entire {@link image_size() image
	size} is used as the effective {@link image_region() image region}.
	Otherwise the dimensions of the image region are adjusted by the
	resolution level (divided by  2**(level - 1)), intersected with the
	image size at the rendering resolution and the resulting effective
	image region is applied as an input restriction on the codestream
	rendering machinery.

	The effective {@link rendered_size() rendered image size} is set.

	@param	level	The rendering resolution level.
	@param	region	The selected image area to be rendered relative to
		the full resolution image.
	@throws	out_of_range	If the selected image are does not intersect
		with the source image.
*/
void
set_resolution_and_region
	(unsigned int level, const Rectangle& region);

/*==============================================================================
	Data Members:
*/
protected:
//------------------------------------------------------------------------------
//	Input:

//!	JP2 source pathname.
std::string
	JP2_Pathname;

//!	Total image bands (components).
unsigned int
	Image_Bands;

//!	Dimensions of the source image.
Size_2D
	Image_Size;

//!	Pixel datum size in bytes.
unsigned int
	Pixel_Bytes;

//!	Pixel precision bits.
unsigned int
	Pixel_Bits;

//! Whether pixel data is signed.
bool
	Signed_Data;

/**	Resolution levels available.

	This is the minimum number of available resolution levels as
	determined from the default coding style (COD) information. The
	minimum resolution level available in the tile segments may be lower
	still, but that won't be known until the tiles have been read.

	<b>N.B.</b>: The number of resolution levels is one more than the
	number of JPEG2000 decomposition levels.
*/
unsigned int
	Resolution_Levels;

/**	First UUID value found in a UUID List box of a UUID Info super box.

	This will be NULL if no UUID has been found. It will be a 16 byte
	(UUID_SIZE) array otherwise.
*/
unsigned char
	*UUID_Info_UUID;

//!	First URL value found in a URL box of a UUID Info super box.
std::string
	UUID_Info_URL;

//------------------------------------------------------------------------------
//	Output:

//!	Image data destination pathname.
std::string
	Image_Destination;

//!	Rendered image size.
Size_2D
	Rendered_Size;

//!	Image region to be rendered.
Rectangle
	Image_Region;

/**	Resolution level to render.

	<b>N.B.</b>: The resolution level is one more than the JPEG2000
	decomposition level.
*/
unsigned int
	Resolution_Level;

//!	Whether pixel bytes should be reordered when written.
bool
	Swap_Pixel_Bytes;

//!	Total number of pixel bytes written.
unsigned long long
	Bytes_Written;

private:
//------------------------------------------------------------------------------
//	Kakadu classes used during JP2 file rendering.

//!	JP2 file input stream.
jp2_family_src
	*JP2_Stream;

//!	JP2 content source.
jp2_source
	*JP2_Source;

//!	JPEG2000 codestream.
kdu_codestream
	*JPEG2000_Codestream;


//!	Kakadu error.
JP2_Decoder_Error
	*Decoder_Error;

};	//	Class JP2_Decoder


#ifndef DOXYGEN_PROCESSING
/*=*****************************************************************************
	JP2_Decoder_Error
*/
class JP2_Decoder_Error
:	public kdu_thread_safe_message
{
public:

void put_text (const char* message);
void flush (bool end_of_message = false);

std::string
	Message;
};
#endif	//	DOXYGEN_PROCESSING


}	//	namespace HiRISE
}	//	namespace UA
#endif
