/*	JP2_Encoder

HiROC CVS ID: JP2_Encoder.hh,v 1.27 2010/04/30 08:01:47 castalia Exp

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
*/

#ifndef _JP2_Encoder_
#define _JP2_Encoder_

#include	"Dimensions.hh"
#include	"JP2_Box.hh"

//	Kakadu
#include	"jp2.h"

#include	<string>
#include	<iosfwd>
#include	<vector>

namespace UA
{
namespace HiRISE
{
//	Forward reference.
class JP2_Encoder_Error;

/**	A <i>JP2_Encoder</i> encodes image pixel data into a JPEG2000 JP2 file.
   
	After a JP2_Encoder is constructed it must be configured. The
	encoder must be configured with at least an input image data {@link
	source(const std::string&) source} file, an output JP2 {@link
	destination(const std::string&) destination} file and the image data
	characterization with at least the image {@link
	image_size(const Size_2D&) size} and number of {@link
	pixel_bytes(unsigned int) pixel bytes} or {@link
	pixel_bits(unsigned int) pixel bits}. By default the image data is
	assumed to be {@link image_data_location(std::streamoff) located} at
	the beginning the source file, has one {@link
	image_bands(unsigned int) band} (i.e. component), is {@link
	signed_data(bool) unsigned}, is {@link MSB_data(bool) MSB ordered}
	(if multi-byte) and has no line prefix or suffix bytes.

	The JP2_Encoder can also be configured with various JPEG2000
	codestream organization information. By default the codestream will
	be {@link tile_size(const Size_2D&) untiled}, have
	#DEFAULT_RESOLUTION_LEVELS {@link resolution_levels(unsigned int)
	resolution levels}, use Precint-Component-Resolution-Level {@link
	progression_order(const std::string&) progression order}, have a
	64x64 {@link code_block_size(const Size_2D&) code block size} and
	use precinct sizes determined by the underlying codestream generation
	machinery.

	Once the JP2_Encoder is {@link ready() ready}  {@link encode()
	encoding} can be started to generate the JP2 file from the image
	data source. Lossless image data compression will be used to
	generate the JPEG2000 codestream. A JP2_Encoder may be reused with
	or without reconfiguration between uses.

	This implementation employs the
	<a href="http://www.kakadusoftware.com/" target="_top">Kakadu
	Software</a> libraries.

	@author		Bradford Castalia, Drew Davidson and Ben Pearson, UA/HiROC
	@version	1.27
*/
class JP2_Encoder
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

//!	Default number of resolution levels.
static const unsigned int
	DEFAULT_RESOLUTION_LEVELS;
//!	Maximum number of resolution levels.
static const unsigned int
	MAX_RESOLUTION_LEVELS;
//!	Maximum number of quality layers.
static const unsigned int
	MAX_QUALITY_LAYERS;

//!	PDS label reference information UUID Info JP2 container box name.
static const char* const
	UUID_INFO_BOX_NAME;
//!	Data provider UUID JP2 box name.
static const char* const
	UUID_BOX_NAME;
//!	Size of the UUID data content.
static const int
	UUID_SIZE;
//!	PDS label relative filename URL JP2 box name.
static const char* const
	URL_BOX_NAME;

//!	Image data stripe minimum and maximum number of lines.
static const int
	MIN_STRIPE_HEIGHT,
	MAX_STRIPE_HEIGHT;

/**	What the encoder needs to do its job.

	@see	needs() const
*/
static const int
	NEEDS_SOURCE,
	NEEDS_DESTINATION,
	NEEDS_IMAGE;

//!	JP2_Encoder_Error exception signal value.
static const int
	ENCODER_EXCEPTION;

/*==============================================================================
	Constructors:
*/
JP2_Encoder ();

//	Destructor.
~JP2_Encoder (); 

/*==============================================================================
	Accessors:
*/
/**	Get the PDS image data source pathname.

	@return	The pathname string for the PDS source. This will be the empty
		string if no source has been bound to this JP2_Encoder.
*/
std::string source () const
	{return Image_Source;}

/**	Set the pathname to the PDS image data source.

	<b>N.B.</b>: If the source has already been {@link open() opened}
	and the pathname is different than the previous pathname, the
	source is {@link close() closed}.

	@param	pathname	The image data source pathname.
	@return	This JP2_Encoder.
*/
JP2_Encoder& source (const std::string& pathname);

/**	Get the destination JP2 file pathname.

	@return	The destination file pathname string. This will be empty
		if no destination has been bound to this JP2_Encoder.
	@see	destination(const std::string&)
*/
std::string destination () const
	{return JP2_Pathname;}

/**	Set the destination JP2 file pathname.

	@param	pathname	The destination file pathname string.
	@return	This JP2_Encoder.
*/
JP2_Encoder& destination (const std::string& pathname)
	{JP2_Pathname = pathname; return *this;}

/**	Get the PDS/JP2 label file pathname.

	@return	The PDS/JP2 label file pathname string. This will be empty
		if no PDS/JP2 label file has been bound to this JP2_Encoder.
	@see	PDS_label_pathname(const std::string&)
*/
std::string PDS_label_pathname () const
	{return PDS_Label_Pathname;}

/**	Set the PDS/JP2 label file pathname.

	Only the filename portion of the pathname is used for the relative
	filename URL reference when the {@link write_user_boxes() user boxes}
	are written to the JP2 file.

	@param	pathname	The PDS/JP2 label file pathname string.
		If NULL no label filename reference URL box or producer
		signature UUUID box will be included in the JP2 file.
	@return	This JP2_Encoder.
	@see	producer_UUID(const unsigned char*)
*/
JP2_Encoder& PDS_label_pathname (const std::string& pathname)
	{PDS_Label_Pathname = pathname; return *this;}

/**	Get the location of the image data in the source file.

	@return	The byte offset where the image data starts in
		the source file.
	@see	image_data_location(std::ios::off_type)
*/
std::streamoff image_data_location () const
	{return Image_Offset;}

/**	Set the location of the image data in the source file.

	@param	file_offset	The byte offset where the image data starts in
		the source file.
	@return	This JP2_Encoder.
*/
JP2_Encoder& image_data_location (std::streamoff file_offset)
	{Image_Offset = file_offset; return *this;}

/**	Get the number of bands (components) in the PDS image.

	@return	The number of bands in the PDS image.
	@see	image_bands(unsigned int)
*/
unsigned int image_bands () const
	{return Image_Bands;}

/**	Set the number of bands (components) in the PDS image.

	@param	bands	The number of bands in the PDS image.
	@return	This JP2_Encoder.
*/
JP2_Encoder& image_bands (unsigned int bands)
	{Image_Bands = bands; return *this;}

/**	Get the size of the source PDS image data.

	@return	A Size_2D object containing the image width and height.
	@see	image_size(const Size_2D&)
*/
const Size_2D image_size () const
	{return Image_Size;}

/**	Set the size of the source PDS image data.

	@param	size	A Size_2D object containing the image width and
		height.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If either the image width or height
		is zero.
*/
JP2_Encoder& image_size (const Size_2D& size);

/**	Get the number of bytes per pixel.

	@return	The number of storage bytes used by each pixel.
	@see	pixel_bytes(unsigned int)
*/
unsigned int pixel_bytes () const
	{return Pixel_Bytes;}

/**	Set the number of bytes per pixel.

	<b>N.B.</b>: If the number of pixel bytes is 1 the data
	will be set to {@link signed_data(bool) unsigned}.

	@param	bytes_per_pixel	The number of bytes per pixel. Only
		the values 1, 2 and 4 are allowed.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If the argument is not 1, 2 or 4.
	@throws	length_error	If the number of pixel bytes is less
		than are needed to hold the {@link pixel_bits(unsigned int)
		pixel bits}.
*/
JP2_Encoder& pixel_bytes (unsigned int bytes_per_pixel);

/**	Get the pixel precision.

	@return	The number of valid bits used by each pixel.
	@see	pixel_bits(unsigned int)
*/
unsigned int pixel_bits () const
	{return Pixel_Bits;}

/**	Set the number of bits per pixel.

	The number of {@link pixel_bytes(unsigned int) pixel bytes} is
	enlarged, if necessary, to accommodate all the pixel bits.

	<b>N.B.</b>: If the number of pixel bits is less than the number of
	bits in the {@link pixel_bytes(unsigned int) pixel bytes} the data
	will be set to {@link signed_data(bool) unsigned}.

	@param	bits_per_pixel	The number of bits per pixel. The maximum
		value is 32.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If the argument is greater than 32.
*/
JP2_Encoder& pixel_bits (unsigned int bits_per_pixel);

/**	Get the signedness of the pixel data.

	@return	true if the pixel data is treated as signed; false
		otherwise.
	@see	signed_data(bool)
*/
bool signed_data () const
	{return Signed_Data;}

/**	Set the signedness of the data.

	<b>N.B.</b>: If the number of {@link pixel_bytes(unsigned int)
	pixel bytes} is 1, or the number of {@link pixel_bits(unsigned int)
	pixel bits} is less than the number of bits in the pixel bytes,
	then the data is unsigned by definition. In such cases the
	argument will be forced to false.

	@param	data_is_signed	true if the data is to be treated as signed;
		false otherwise.
	@return	This JP2_Encoder.
*/
JP2_Encoder& signed_data (bool data_is_signed);

/**	Test if the source data will be treated as MSB ordered.

	@return	true if the host system is not high endian and {@link
		swap_pixel_bytes() pixel byte swapping} has been enabled, or the
		host system is high endian and pixel byte swapping has not been
		enabled; false otherwise.
*/
bool MSB_data () const;

/**	Set the source data byte ordering.

	<b>N.B.</b>: The {@link swap_pixel_bytes() pixel byte swapping}
	state is set by this method: If the host system is not high endian
	and the source data is MSB ordered, or the host system is high
	endian and the source data is LSB ordered, pixel byte swapping will
	be enabled; otherwise pixel byte swapping will be disabled.

	@param	data_is_MSB	true if the source data is MSB ordered;
		false if the source data is LSB ordered.
	@return	This JP2_Encoder.
*/
JP2_Encoder& MSB_data (bool data_is_MSB);

/**	Test if multi-byte pixels will be reordered before being
	sent to the JPEG2000 codestream generation machinery.

	@return	true if multi-byte pixels are to be reordered; false
		otherwise.
	@see	swap_pixel_bytes(bool)
*/
bool swap_pixel_bytes () const
	{return Swap_Pixel_Bytes;}

/**	Set if multi-byte pixels will be reordered before being
	sent to the JPEG2000 codestream generation machinery.

	@param	swap_data	true if multi-byte pixels are to be reordered;
		false otherwise.
	@return	This JP2_Encoder.
	@see	MSB_data(bool)
*/
JP2_Encoder& swap_pixel_bytes (bool swap_data)
	{Swap_Pixel_Bytes = swap_data; return *this;}

/**	Get the number of bytes preceeding each line of image
	pixel data.

	@return	The number of line prefix bytes.
	@see	line_prefix_bytes(unsigned int)
*/
unsigned int line_prefix_bytes () const
	{return Line_Prefix_Bytes;}

/**	Set the number of bytes preceeding each line of image
	pixel data.

	@param	prefix_bytes	The number of line prefix bytes.
	@return	This JP2_Encoder.
*/
JP2_Encoder& line_prefix_bytes (unsigned int prefix_bytes)
	{Line_Prefix_Bytes = prefix_bytes; return *this;}

/**	Get the number of bytes following each line of image
	pixel data.

	@return	The number of line suffix bytes.
	@see	line_suffix_bytes(unsigned int)
*/
unsigned int line_suffix_bytes () const
	{return Line_Suffix_Bytes;}

/**	Set the number of bytes following each line of image
	pixel data.

	@param	suffix_bytes	The number of line suffix bytes.
	@return	This JP2_Encoder.
*/
JP2_Encoder& line_suffix_bytes (unsigned int suffix_bytes)
	{Line_Suffix_Bytes = suffix_bytes; return *this;}

/**	Get the size of the JP2 image tiles.

	@return	A Size_2D object containing the JP2 image tiles width and
		height.
	@see	tile_size(const Size_2D&)
*/
const Size_2D tile_size () const
	{return Tile_Size;}

/**	Set the size of the JP2 image tiles.

	If the tile width is zero the width of the image will be use. If
	the tile height is zero height of the image will be used.

	@param	size	A Size_2D object containing the JP2 tiles width and
		height.
	@return	This JP2_Encoder.
*/
JP2_Encoder& tile_size (const Size_2D& size)
	{Tile_Size = size; return *this;}

/**	Get the total number of codestream resolution levels.

	<b>N.B.</b>: The number of resolution levels is one more than the
	number of JPEG2000 decomposition levels.

	@return	The total number of codestream resolution levels.
	@see	resolution_levels(unsigned int)
*/
unsigned int resolution_levels () const
	{return Resolution_Levels;}

/**	Set the total number of codestream resolution levels.

	<b>N.B.</b>: The number of resolution levels is one more than the
	number of JPEG2000 decomposition levels.

	@param	resolution_levels	The total number of codestream resolution
		levels.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If the specified number of resolution
		levels is greater than the MAX_RESOLUTION_LEVELS allowed.
	@see	resolution_levels()
*/
JP2_Encoder& resolution_levels (unsigned int resolution_levels);

/**	Get the number of codestream quality layers.

	@return The number of codestream quality layers.
	@see	quality_layers(unsigned int)
*/
unsigned int quality_layers () const
	{return Quality_Layers;}

/**	Set the number of codestream quality layers.

	The default number of quality layers is 1. The maximum number of
	layers is MAX_QUALITY_LAYERS (16384).

	@param	quality_layers	The number of codestream quality layers. A
		value of zero will be set to 1.
	@return	This JP2_Encoder.
	@throws invalid_argument	If the specified number of quality layers
		is greater than the maximum of the MAX_QUALITY_LAYERS allowed.
*/
JP2_Encoder& quality_layers (unsigned int quality_layers);

/**	Get the codestream compression bit-rate.

	@return	The codestream compression bit-rate. This will be zero if
		loss-less, reversible compression is to be used.
	@see	bit_rate(double)
*/
double bit_rate () const
	{return Bit_Rate;}

/**	Set the codestream compression bit-rate.

	The compression bit-rate is expressed in terms of the ratio between
	the total number of compressed bits (including headers) and the
	product of the largest horizontal and  vertical image component
	dimensions. This may also be thought of as the number of bits per
	pixel used in the compressed codestream.

	@param	rate	The codestream compression bit-rate. A value of zero
		means that loss-less, reversible compression is to be used. A
		value less than zero is set to zero.
	@return	This JP2_Encoder.
	@see	bit_rate()
*/
JP2_Encoder& bit_rate (double rate);

/**	Get the codestream progression order descriptor.

	@return	The progression order descriptor string.
	@see	progression_order(const std::string&)
*/
std::string progression_order () const
	{return Progression_Order;}

/**	Set the codestream progression order.

	The progression order is described by a string which specifies the
	order in which the JPEG2000 codestream is written. A JPEG2000
	codestream has Position (image area), Component (image band),
	Resolution and Layer (quality) dimensions. The codestream
	progression order is specified as the first letters of each
	dimension in the order in which they are to be written; the first
	dimension specified varies the most slowly while the last dimension
	specified varies the most quickly.

	The default progression order is set at compile time by the value of
	the DEFAULT_PROGRESSION_ORDER symbol.

	@param	progression	A string specifying the progression order.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If the progression order string is
		not four characters containing 'P', 'C', 'R' and 'L' in
		some order.
*/
JP2_Encoder& progression_order (const std::string& progression);

/**	Get the precinct sizes for each resolution level.

	@return	The list of precinct sizes as a const std::vector<Size_2D>)
		with one entry for each resolution level.
	@see	precinct_sizes(const std::vector<Size_2D>& sizes)
	@see	resolution_levels(unsigned int)
*/
const std::vector<Size_2D> precinct_sizes () const
{return Precinct_Sizes;}

/**	Get the precinct size for a given resolution level.

	@param	resolution_level	The resoultion level index (0-based)
		for which the precinct size is to be obtained.
	@return	The precinct size (Size_2D) for the resolution level.
	@throws	invalid_argument	If the resolution level is greater
		than or equal to the number of resolution levels.
	@see	resolution_levels(unsigned int)
*/
const Size_2D precinct_size
	(unsigned int resolution_level = 0) const;

/**	Set the precinct sizes for each resolution level.

	Each precinct size dimension must be a non-zero power of two.

	If the number of precinct sizes is greater than the number of
	resolution levels the excess size values will be ignored. If the
	number of precinct sizes is less than the number of resolution
	levels the last size will be used for the sizes of all remaining
	resolution levels.

	@param	sizes	A list (vector<Size_2D>) of precinct sizes in
		resolution number order.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If any precinct size dimension is not
		a non-zero power of two.
	@see	invalid_precinct_size(const std::vector<Size_2D>& sizes)
*/
JP2_Encoder& precinct_sizes
	(const std::vector<Size_2D>& sizes);

/**	Set the precinct size for a given resolution level.

	@param	size	A precinct size (Size_2D) for the resolution level.
	@param	resolution_level	The resoultion level index (0-based)
		for which the precinct size is to be obtained.
	@throws	invalid_argument	If the resolution level is greater
		than or equal to the number of resolution levels.
	@see	resolution_levels(unsigned int)
*/
JP2_Encoder& precinct_size
	(const Size_2D& size, unsigned int resolution_level = 0);

/**	Get the code block size.

	@return	The size (Size_2D) of the code block.
	@see	code_block_size(const Size_2D&)
*/
const Size_2D code_block_size () const
	{return Code_Block_Size;}

/**	Set the code block size.

	@param	size	The size (Size_2D) of the code block.
	@return	This JP2_Encoder.
	@throws	invalid_argument	If either dimension is 0 or greater
		than 64.
*/
JP2_Encoder& code_block_size (const Size_2D& size);

/**	Get the list of user specified data boxes added to the JP2 file.

	@return A reference to a JP2_Box::JP2_Box_List, a vector of
		JP2_Box objects that will be {@link write_user_boxes() added}
		to the JP2 file, or that were added if the file has already
		been {@link encode() written}.
*/
JP2_Box::JP2_Box_List& added_boxes ()
	{return Added_Boxes;}

/**	Add a data box to the JP2 file.

	The box is placed on the list of {@link added_boxes() user specified
	boxes} that will be {@link write_user_boxes() added} to included in
	the JP2 file when it is {@link encode() written}.

	@param	box	A JP2_Box pointer.
	@return	This JP2_Encoder.
*/
JP2_Encoder& add_box (JP2_Box* box);

/**	Remove a data box from the list of user specified
	boxes.

	@param	box	A JP2_Box pointer.
	@return	true if the specified box was found in the list of user
		specifed boxes; false otherwise.
	@see	added_boxes()
*/
bool remove_box (JP2_Box* box);

/**	Get the product producer signature UUID value.

	@return	An array of UUID_SIZE (16) characters (<b>N.B.</b>: This
		is not a null-terminated character string) containing the
		product producer UUID value. This will be NULL if a product
		producer signature of all zeros is to be used.
	@see	producer_UUID(const unsigned char*)
*/
const unsigned char* producer_UUID () const
	{return Producer_UUID;}

/**	Set the product producer signature UUID value.

	The producer signature UUID value is intended to provide a unique
	identifier for the product. The UUID will be placed in a UUID List
	box inside a UUID Info box.

	<b>N.B.</b>: A producer signature will only be included in the JP2
	file if a {@link PDS_label_pathname(const std::string&) PDS label
	pathname} has been specified.

	@param	id	An array of UUID_SIZE (16) characters (<b>N.B.</b>: This
		is not a null-terminated character string) containing the
		product producer UUID value. If NULL no product producer
		signature is to be used.
	@return	This JP2_Encoder.
*/
JP2_Encoder& producer_UUID (const unsigned char* id);

/**	Get the codestream comment.

	@return	The string that will be added as a comment to the codestream.
		This will be an empty string if no comment is specified.
	@see	comment(const std::string& text)
*/
std::string comment () const
	{return Comment;}

/**	Set comment text to be added to the codestream.

	@param	text	A string to be added to the codestream as a comment.
		If the string is empty no comment will be added to the codestream.
	@return	This JP2_Encoder.
	@see	comment()
*/
JP2_Encoder& comment (const std::string& text)
	{Comment = text; return *this;}

/**	Test if the encoder is ready to compress the image data.

	@return	true if the encoder is ready; false otherwise.
	@see	needs() const
	@see	reasons() const
*/
bool ready () const;

/**	Get a description of the reasons that the encoder is not ready.

	@return	A string describing what the encoder {@link needs() needs}.
		This will be the empty string if the encoder is {@link ready()
		ready} to compress image data.
*/
std::string reasons () const;

/**	Indicates what the encoder needs to do its job.

	The returned bit flag value will be zero if the encoder has
	all the required user-supplied information. Otherwise it will
	have one or more of the following bits set:
<dl>
<dt>NEEDS_SOURCE (0)
	<dd>A {@link source(const std::string&) source} PDS file pathname
	has not been specified.
<dt>NEEDS_DESTINATION (1)
	<dd>A {@link destination(const std::string&) destination} PDS/JP2
	file pathname has not been specified.
<dt>NEEDS_IMAGE
	<dd>The source image structure - image {@link image_size(const Size_2D&)
	size}, number of {@link image_bands(unsigned int) bands} and {@link
	pixel_bytes(unsigned int) bytes per pixel} - has not been completely
	defined.
</dl>

	@return	A bit flag value.
*/
int needs () const;

/**	Get the JP2_Encoder_Error describing the last encoder error that
	occurred.

	The JP2_Encoder_Error contains a Message string data member
	describing the last error. This will be the empty string if no error
	has occurred.

	@return	A pointer to a JP2_Encoder_Error object.
*/
JP2_Encoder_Error* encoder_error () const;

/*==============================================================================
	Encoder
*/
/**	Encode the image source to a JPEG2000 JP2 destination.

	This function is the main workhorse of the class. It is responsible
	for  doing the actual work of generating a JP2 file.

	The destination JP2 file is {@link open() opened}. The JP2 metadata
	boxes are written to the file, including the required {@link
	write_header() header} boxes and any {@link write_user_boxes() user
	boxes} that have been {@link add_box(JP2_Box*) added} and the box to
	contain a {@link producer_UUID(const unsigned char*) producer
	signature} UUID and {@link PDS_label_pathname(const std::string&)
	PDS label filename} URL if this has been specified. The source pixel
	data is written to a {@link write_codestream() codestream} box. The
	completed JP2 file is then {@link close() closed}.

	@return	The number of bytes written to the JP2 file.
*/
long long encode ();

/**	Open the source JP2 file.
*/
void open ();

/**	Write the required metadata boxes to the JP2 file.

	@return	The number of bytes written to the JP2 file.
*/
long long write_header ();

/**	Write user specified boxes to the JP2 file.

	If a {@link PDS_label_pathname(const std::string&) PDS label
	filename} has been specified a UUID Info box containing a UUID box
	with {@link producer_UUID(const unsigned char*) producer signature}
	and a URL box with a relative file reference to the PDS label
	filename is written to the JP2 file.

	@return	The number of bytes written to the JP2 file.
*/
long long write_user_boxes ();

/**	Generate the compressed image data JPEG2000 codestream and
	write it to the JP2 file.
*/
long long write_codestream ();

/**	Set the rate at which compressed image data will be written to the
	output JP2 file.

	Incremental codestream flushing is when the compressed image data
	that has accumulated in memory is periodically written to the output
	JP2 file during the process of {@link write_codestream() codestream
	generation}. Incremental codestream flushing is desirable to avoid
	retaining the entire codestream in memory when a large image is
	being processed; the memory requirements to hold the entire
	codestream may be more than the system can provide. The rate of
	codestream flushing is controlled by the number of image lines that
	have been compressed since the last flush or the start of
	compression. Since the issue of incremental codestream flushing is
	the amount of system memory that is used this method allows the rate
	to be expressed in terms of bytes. This should be as large as
	possible, or zero to disable incremental flushing, to allow for the
	most efficient compression operations as possible.

	However, incremental flushing may not actually occur at the requested
	rate, or may not occur at all, depending on the progression order and
	other codestream organization issues. In addition, incremental
	flushing may generate additional JPEG2000 tile-part segments beyond
	the initial tile-part segment for each tile, and each of these
	additional tile-parts will require that additional space be reserved
	in the tile-part length segments of the main header. Since the actual
	number of tile-parts generated by incremental flushing depends on the
	data and thus will not be known until the codestream generation has
	been completed - at which time the reserved space for the tile-part
	length segments are overwritten with the actual location information
	- an estimate of the number of tile-parts is necessary. If the actual
	number of tile-parts is less than what has been reserved empty tile
	parts will be provided as place holders. <b>N.B.</b>: If the actual
	number is larger than what has been reserved the generation of the
	codestream will fail.

	The default flush rate is set at compile time by the value of the
	INCREMENTAL_FLUSH_BYTES symbol.

	@param	bytes	The requested maximum amount of memory to use in
		generating the compressed image data codestream before the
		codestream will be flushed to the output JP2 file. If zero
		incremental flushing is disabled.
	@return	This JP2_Encoder.
	@see	incremental_flush_lines()
*/
JP2_Encoder& incremental_flush_bytes (long long bytes)
	{Incremental_Flush_Bytes = ((bytes < 0) ? 0 : bytes); return *this;}

/**	Get the rate at which compressed image data will be written to the
	output JP2 file.

	@return	The requested maximum amount of memory to use in generating
		the compressed image data codestream before the codestream will
		be flushed to the output JP2 file. If zero incremental flushing
		is disabled.
*/
long long incremental_flush_bytes () const
	{return Incremental_Flush_Bytes;}

/**	Set the rate at which compressed image data will be written to the
	output JP2 file.

	The incremental flush rate is set in terms of the number of image
	lines to compress before flushing the codestream from memory to
	the JP2 file. This will set the {@link incremental_flush_bytes(long long)
	maximum flush bytes}.

	<b>Warning</b>: Since the determining the maximum flush bytes from
	a number of image lines depends on the {@link image_size(const Size_2D&)
	image width} and number of {@link pixel_bytes(unsigned int) pixel bytes}
	if these have not yet been set the maximum flush bytes will be set to
	zero thus disabling incremental flushing.

	@param	lines	The number of image lines to compress before
		flushing the codestream. If zero incremental flushing is
		disabled.
*/
JP2_Encoder& incremental_flush_lines (unsigned int lines);

/**	Get the rate at which compressed image data will be written to the
	output JP2 file.

	The incremental flush rate, in terms of the number of image lines,
	is determined by the requested {@link incremental_flush_bytes(long long)
	maximum flush bytes}. If the maximum flush bytes is zero or
	the size of an image band is greater than or equal to the maximum
	flush bytes the flush lines will be zero (no incremental flusing
	will occur). Otherwise the number of flush lines is set to the
	height of an image tile. If number of bytes in these image lines for
	a single band is greater than the maximum flush bytes the number of
	flush lines is reduced by 1024 until the number of bytes in the
	lines is less than or equal to the maximum flush bytes.

	@return	The rate, in terms of image lines, at which the compressed
		image data codestream will be requested to be flushed to the
		output JP2 file. If zero incremental flushing is disabled.
*/
int incremental_flush_lines () const;

long long close ();

/*============================================================================
	Helpers:
*/
/**	Check for valid precinct sizes.

	Valid precinct sizes are non-zero powers of 2.

	@param	sizes	A vector of precinct Size_2D values.
	@return	If all sizes are valid, 0. Otherwise the vector entry number
		(i.e. index + 1) of the first invalid entry encountered.
*/
int
invalid_precinct_size (const std::vector<Size_2D>& sizes);

protected:

/**	Fill an image data buffer with pixel data from a source stream.

	The lines of source image data starting with the specified line of the
	specified band are read into the buffer as a contiguous sequence of
	bytes.

	@param	source	An istream that has been opened on the source file.
	@param	band	The index of the image band from which pixel data is
		to be read.
	@param	line	The starting index of the image line from which
		pixel data it to be read.
	@param	lines	The number of image lines to read.
	@param	buffer	Buffer storage to hold at least lines * image_width
		pixels where each pixel is stored as a 16-bit signed integer.
*/
void read_stripe
	(std::istream& source, int band, int line, int lines, kdu_int16* buffer);

/**	Fill an image data buffer with pixel data from a source stream.

	The lines of source image data starting with the specified line of the
	specified band are read into the buffer as a contiguous sequence of
	bytes.

	@param	source	An istream that has been opened on the source file.
	@param	band	The index of the image band from which pixel data is
		to be read.
	@param	line	The starting index of the image line from which
		pixel data it to be read.
	@param	lines	The number of image lines to read.
	@param	buffer	Buffer storage to hold at least lines * image_width
		pixels where each pixel is stored as a 32-bit signed integer.
*/
void read_stripe
	(std::istream& source, int band, int line, int lines, kdu_int32* buffer);

/*==============================================================================
	Data Members:
*/
protected:
//------------------------------------------------------------------------------
//	Input:

//!	Image source pathname.
std::string
	Image_Source;

//!	Image destination pathname.
std::string
	JP2_Pathname;

//!	Image data location as a byte offset within the source file.
std::streamoff
	Image_Offset;

//!	Total image bands (components).
unsigned int
	Image_Bands;

//	Dimensions of the image.
Size_2D
	Image_Size;

/**	The number of bytes preceeding and following each line of pixel bytes.

	The line prefix and suffix bytes are to be skipped when the image data
	is being read.
*/
unsigned int
	Line_Prefix_Bytes,
	Line_Suffix_Bytes;

//!	Pixel datum size in bytes.
unsigned int
	Pixel_Bytes;

//!	Pixel precision bits.
unsigned int
	Pixel_Bits;

//! Whether pixel data is to be treated as signed.
bool
	Signed_Data;

//	JP2 boxes beyond the minimum required.
JP2_Box::JP2_Box_List
	Added_Boxes;

//------------------------------------------------------------------------------
//	Output:

//!	PDS label file pathname to be placed in a UUID Info URL box.
std::string
	PDS_Label_Pathname;

//!	The UUID to be placed in a UUID List box inside a UUID Info box.
unsigned char
	*Producer_UUID;

//!	Comment segment to be added to the codestream.
std::string
	Comment;

//!	Whether pixel bytes should be reordered before be encoded.
bool
	Swap_Pixel_Bytes;

/**	The number of resolution levels to encode.

	<b>N.B.</b>: The number of resolution levels is one more than the
	number of JPEG2000 decomposition levels.
*/
unsigned int
	Resolution_Levels;

unsigned int
	Quality_Layers;

double
	Bit_Rate;

//!	The codestream progression order to be used.
std::string
	Progression_Order;

//!	Tile size for codestream structure organization.
Size_2D
	Tile_Size;

//!	Precinct sizes for codestream structure organization within tiles.
std::vector<Size_2D>
	Precinct_Sizes;

//!	Code block size for codestream packet encoding within precincts.
Size_2D
	Code_Block_Size;

long long
	Incremental_Flush_Bytes;

private:
//------------------------------------------------------------------------------
//	Kakadu classes used during JP2 file generation.

//!	JP2 file output stream.
jp2_family_tgt
	*JP2_Stream;

//!	JP2 boxes for the JP2_Stream.
jp2_target
	*JP2_Boxes;

//!	JPEG2000 codestream for the jp2c box of JP2_Boxes.
kdu_codestream
	*JPEG2000_Codestream;

//!	Kakadu error.
JP2_Encoder_Error
	*Encoder_Error;

};	//	Class JP2_Encoder


#ifndef DOXYGEN_PROCESSING
/*=*****************************************************************************
	JP2_Encoder_Error
*/
class JP2_Encoder_Error
:	public kdu_thread_safe_message
{
public:

void put_text (const char* message);
void add_text (const std::string& message);
void flush (bool end_of_message = false);

std::string
	Message;
};
#endif	//	DOXYGEN_PROCESSING


/*=*****************************************************************************
	Functions
*/
/**	Test if a value is a power of 2.

	@param	value	An unsigned integer value.
	@return	true if the value is a power of 2 (including 0); false otherwise.
*/
bool power_of_2 (unsigned int value);


}	//	namespace HiRISE
}	//	namespace UA
#endif
