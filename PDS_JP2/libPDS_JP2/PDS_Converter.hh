/*	PDS_Converter

HiROC CVS ID: PDS_Converter.hh,v 1.16 2012/01/24 03:08:13 castalia Exp

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

#ifndef _PDS_Converter_
#define _PDS_Converter_

#include	"PDS_Data.hh"
#include	"Image_Data_Block.hh"
#include	"Dimensions.hh"

namespace UA
{
namespace HiRISE
{
/**	A <i>PDS_Converter</i> is used to convert an attached PDS image label
	to or from a detached PDS/JP2 label.

	A PDS_Converter inherits from PDS_Data which contains the label to be
	converted.

	This abstract class provides a base for product-specific label
	converter classes. Each implementation must provide the
	label_recognized, write_PDS_JP2_label and write_PDS_label methods.

	@author	Bradford Castalia; UA/HiROC
	@version	1.16

	@see	PDS_Converter::label_recognized()
	@see	PDS_Converter::write_PDS_JP2_label(const std::string&,
				const std::string&, const char**, PDS_Data*)
	@see	PDS_Converter::write_PDS_label(const std::string&,
				const Rectangle*, unsigned int, const char**, PDS*)
*/
class PDS_Converter
:	public PDS_Data
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

/**	Default product name.

	@see	product_names() const
*/
static const char
	*DEFAULT_PRODUCT_TYPE;

/**	Name of the PDS/JP2 label parameter group describing the source
	uncompressed file.
*/
static const char
	*UNCOMPRESSED_FILE_PARAMETERS_GROUP;

/**	Names of the PDS/JP2 label parameter group describing the destination
	compressed file.
*/
static const char
	*COMPRESSED_FILE_PARAMETERS_GROUP;

//	Common additional parameters:

//!	GeoTIFF included.
static const char
	*GeoTIFF_PARAMETER_NAME;
//!	GML included.
static const char
	*GML_PARAMETER_NAME;
//!	No Version number change.
static const char
	*NO_VERSION_CHANGE_PARAMETER_NAME;

/*==============================================================================
	Constructors:
*/
/**	Constructs an empty PDS_Converter.
*/
PDS_Converter ();

/**	Constructs a PDS_Converter from a named file.

	The PDS file may be a detached PDS/JP2 file or a PDS file with an
	attached label. Either the write_PDS_label or write_PDS_JP2_label
	methods can be used to convert either source, respectively.

	@param	pathname	The pathname string to a source file with a PDS
		label.
	@param	excluded_names	The NULL-terminated array of character
		strings naming data blocks to be excluded from conversion
		consideration. May be NULL.
	@param	image_names		The NULL-terminated array of character
		strings naming data blocks that describe image data. <b>N.B.</b>:
		The {@link PDS_Data::IMAGE_DATA_BLOCK_NAME} is always implicitly
		included. May be NULL.
	@throws	invalid_argument	If the converter is not capable of
		converting the source file.
*/
explicit PDS_Converter (const std::string& pathname,
	const char** excluded_names = NULL, const char** image_names = NULL);

/**	Copies a PDS_Converter.

	@param	converter	The PDS_Converter to be copied.
*/
PDS_Converter (const PDS_Converter& converter);

/**	Assigns another PDS_Converter to this PDS_Converter.

	@param	converter	The PDS_Converter whose contents are to be
		assigned to this PDS_Converter.
*/
virtual PDS_Converter& operator= (const PDS_Converter& converter);

/**	Frees the PDS_Data::PDS_Data_Block_List and its contents.
*/
virtual ~PDS_Converter ();

/*==============================================================================
	Manipulators:
*/
/**	Write a detached PDS/JP2 label file.

	<b>N.B.</b>: This is a pure virtual method that must be provided
	by the implementing class.

	This method converts the PDS label held by this PDS_Converter,
	which is expected to be from a file with an attached label, to its
	detached PDS/JP2 form and writes the results to a file at the
	specified pathname. Though the method is free to convert the source
	label in place, this is strongly discouraged; instead modifications
	should be made to a copy of the source label. For example:

	<code>
	// Copy the source PDS label.
	PDS_Data
	  PDS_label (*this);
	// Modify the label.
	...
	// Write the label file.
	write_label (pathname, PDS_label);
	</code>

	@param PDS_label_pathname The pathname for the detached label file.
	@param JP2_pathname The name of the JP2 image data file
		referened by the label file.
	@param	removed_parameter_names	A NULL terminated array of character
		strings that are the names of parameters to be removed from the
		source label before being written. May be NULL.
	@param	additional_parameters	A pointer to PDS_Data that contains
		additional parameters to be used by the label converter. May be NULL. 
	@param	additional_parameters	A pointer to PDS_Data that contains
		additional parameters with product-specific label conversion
		information. May be NULL.
	@see	write_label(const std::string&, PDS_Data&,
		idaeim::PVL::Lister*, bool)
*/
virtual void write_PDS_JP2_label
	(
	const std::string&	PDS_label_pathname,
	const std::string&	JP2_pathname,
	const char**		removed_parameter_names = NULL,
	PDS_Data*			additional_parameters = NULL
	) = 0;

/**	Write a PDS label file for image data to be appended.

	<b>N.B.</b>: This is a pure virtual method that must be provided
	by the implementing class.

	This method converts the the PDS label held by this PDS_Converter,
	which is expected to be from a detached PDS/JP2 label, to its
	attached PDS form and writes the results to a file at the specified
	pathname. Though the method is free to convert the source label in
	place, this is strongly discouraged; instead modifications should be
	made to a copy of the source label. For example:

	<code>
	// Copy the source PDS label.
	PDS_Data
	  PDS_label (*this);
	// Modify the label.
	...
	// Write the label file.
	write_label (pathname, PDS_label);
	</code>

	@param PDS_label_pathname The pathname for the file that begins with
		the converted PDS label.
	@param	image_region	A Rectangle pointer that specifies a region
		within the image that was selected. If NULL, the entire image was
		selected.
	@param	resolution_level	The resolution level at which the image is
		rendereed from the JP2 codestream is rendered. 1 is full resolution,
		2 is half resolution, 3 is quarter resolution, etc.; i.e. the
		rendering scale is 1 / (2**(L - 1)).
	@param	removed_parameter_names	A NULL terminated array of character
		strings that are the names of parameters to be removed from the
		source label before being written. May be NULL.
	@param	additional_parameters	A pointer to PDS_Data that contains
		additional parameters with product-specific label conversion
		information. May be NULL.
	@see	write_label(const std::string&, PDS_Data&,
		idaeim::PVL::Lister*, bool)
*/
virtual void write_PDS_label
	(
	const std::string&	PDS_label_pathname,
	const Rectangle*	image_region = NULL,
	unsigned int		resolution_level = 1,
	const char**		removed_parameter_names = NULL,
	PDS_Data*			additional_parameters = NULL
	) = 0;

/*==============================================================================
	Accessors:
*/
/**	Get the name of the product types that this converter is intended
	to process.

	There is no particular meaning to the string that is returned. Each
	PDS_Converter implementation may choose whatever name(s) it sees fit.
	Nevertheless, it is recommended that each space separated word in the
	returned string be chosen to name a recognizable product such as the
	value of a label parameter that is known to identify the type of
	product. For example, the value of the INSTRUMENT_ID parameter might
	be used.

	@return	A string used to identify the type of products recognized
		by this PDS_Converter. This will be the #DEFAULT_PRODUCT_TYPE
		name if the PDS_Converter implementation does not provide this
		method.
*/
virtual std::string product_names () const;

/**	Test whether the label parameters are recognized by this converter.

	<b>N.B.</b>: A false return value does not necessarily mean that
	this converter will be unable to process the label; only
	that the label does not describe a {@link product_names() product type}
	recognized by the converter.

	@return	true if the label parameters are recognized by this converter;
		false otherwise.
*/
virtual bool label_recognized () const = 0;

/**	Set the preferred size of a label file.

	<b>N.B.</b>: The preferred label size is a hint; the actual size of
	the label may be larger, but will not be smaller. If the label will
	not fit in the preferred size the label size is increased the to
	minimum size required rounded up to the nearest 1K (1024) bytes.

	@param	size	The preferred size, in characters, of a label file.
	@return	This PDS_Converter.
	@see	write_label(const std::string&, PDS_Data&,
		idaeim::PVL::Lister*, bool)
*/
PDS_Converter& label_size (unsigned int size)
	{Label_Size = size; return *this;}

/**	Get the preferred size of a label file.

	@return	The preferred size, in characters, of a label file.
*/
unsigned int label_size () const
	{return Label_Size;}

/**	Get the list of data blocks in the PDS label.

	@return	A pointer to the current {@link PDS_Data::PDS_Data_Block_List
		data block list}. This will be NULL if no data blocks are
		currently identified identified in the label. <b>N.B.</b> The
		list may not be current if the label {@link
		parameters(const std::string&) parameters} have been changed or
		otherwise modified; a {@link refresh_data_blocks() refresh} of the
		data blocks can be used in this case.
*/
PDS_Data::PDS_Data_Block_List* data_blocks () const
	{return Data_Blocks;}

/**	Refresh the list of data blocks.

	Both the general {@link data_blocks() data blocks list} and the
	{@link image_data() image data block} pointer are refreshed from the
	current PDS label parameters. The previous data blocks are deleted.
*/
void refresh_data_blocks ();

/**	Get the Image_Data_Block from the PDS_Data::PDS_Data_Block_List.

	If the Image_Data_Block has has not yet been found the
	PDS_Data::PDS_Data_Block_List is searched for it. If there is
	currently no list of data blocks, an attempt is made get a new {@link
	PDS_Data::data_blocks(const char**, const char**) data block list}.
	If this fails to identify an image data block an attempt is made to
	find a Parameter Aggregate with the PDS_Data::IMAGE_DATA_BLOCK_NAME
	regardless of whether a corresponding record pointer parameter is
	present in the label. If this succeeds an IMAGE_Data_Block is
	constructed from the parameter group that is found.

	@return	A pointer to the Image_Data_Block, or NULL if none can be found.
	@see	PDS_Data::image_data(PDS_Data::PDS_Data_Block_List*)
*/
Image_Data_Block* image_data ();

/**	Set the names of parameters to be excluded from the data block list.

	The list of known {@link data_blocks() data blocks} is updated.
	<b>N.B.</b>: The current {@link image_data_block_names(const char**)
	image data block names} are used to refresh the data block list, so
	if they are to be set they should be set first.

	@param	names	A NULL-terminated array of character strings. May be
		NULL if no data blocks are to be excluded.
	@return	This PDS_Converter.
*/
PDS_Converter& excluded_data_block_names (const char** names);

/**	Get the names of parameters to be excluded from the data block list.

	@return	A NULL-terminated array of character strings. May be
		NULL if no data blocks are to be excluded.
	@see	excluded_data_block_names(const char**)
*/
const char** excluded_data_block_names () const
	{return Excluded_Data_Block_Names;}

/** Set the parameter names of image data blocks.

	<b>N.B.</b>: The {@link PDS_Data::IMAGE_DATA_BLOCK_NAME} is always
	implicitly included even if the image names array is NULL.

	The label's {@link image_data() image data block} is located. At
	the same time the list of known {@link data_blocks() data blocks} is
	also refreshed.

	@param	names	A NULL-terminated array of character strings. May be
		NULL if only the {@link PDS_Data::IMAGE_DATA_BLOCK_NAME} is to be
		used.
	@return	This PDS_Converter.
*/
PDS_Converter& image_data_block_names (const char** names);

/**	Get the parameter names of image data blocks.

	@return	A NULL-terminated array of character strings. May be
		NULL if only the {@link PDS_Data::IMAGE_DATA_BLOCK_NAME} is to be
		used.
	@see	image_data_block_names(const char**)
*/
const char** image_data_block_names () const
	{return Image_Data_Block_Names;}

/*==============================================================================
	Helpers:
*/
/**	Assemble PDS/JP2 image file description parameters.

	Two groups of parameters are generated: A COMPRESSED_FILE group that
	refers to an associated JP2 file, and an UNCOMPRESSED_FILE group
	that describes the source image data file used to generate the JP2
	file. The UNCOMPRESSED_FILE group also includes the complete IMAGE
	parameters group. The source image data filename is found in the
	{@link idaeim::PVL::Parameter::name() name} of the Parameter
	Aggregate containing this PDS label representation. The {@link
	image_data() image data block} is used to obtain the image data
	definitions.

	Example:

<code><pre>
    OBJECT = COMPRESSED_FILE
        FILE_NAME                  = "PSP_002068_2635_RED.JP2"
        RECORD_TYPE                = UNDEFINED
        ENCODING_TYPE              = "JP2"
        ENCODING_TYPE_VERSION_NAME = "ISO/IEC15444-1:2004"
        INTERCHANGE_FORMAT         = BINARY
        UNCOMPRESSED_FILE_NAME     = "PSP_002068_2635_RED.IMG"
        REQUIRED_STORAGE_BYTES     = 68624340 <BYTES>
        ^DESCRIPTION               = "JP2INFO.TXT"
    END_OBJECT = COMPRESSED_FILE
    OBJECT = UNCOMPRESSED_FILE
        FILE_NAME    = "PSP_002068_2635_RED.IMG"
        RECORD_TYPE  = FIXED_LENGTH
        RECORD_BYTES = 10860 <BYTES>
        FILE_RECORDS = 6319
        ^IMAGE       = "PSP_002068_2635_RED.IMG"
        OBJECT = IMAGE
            ...
        END_OBJECT = IMAGE
    END_OBJECT = UNCOMPRESSED_FILE
</pre></code>

	@param	JP2_pathname	The pathname to the associated JP2 file. Only
		the final filename portion is used.
	@return	A pointer to a Parameter Aggregate containing the
		COMPRESSED_FILE and UNCOMPRESSED_FILE Aggregates. <b>N.B.</b>:
		Because two parameter Aggregates are assembled they are enclosed
		in a container Aggregate that is not expected to be retained;
		only the Parameter Aggregates it carries are relevant.
	@throws	runtime_error	If an {@link image_data() image data block}
		can not be found in the source label.
*/
idaeim::PVL::Aggregate* PDS_JP2_image_parameters
	(const std::string& JP2_pathname);

/**	Write a label file.

	If a file exists at the specified pathname it will be replaced with
	the new file.

	If label padding is enabled (it is not by default) and the size of
	the label file after writing the label parameters is less than the
	{@link label_size() preferred label size} the file will be padded
	with space characters up to the preferred size.

	@param	pathname	The pathname to the label file.
	@param	label	A reference to the PDS_Data containing the label
		parameters.
	@param	lister	The idaeim::PVL::Lister that will apply formatting
		to the label parameters as they are written. May be null (the
		default) and a standard PDS style lister will be {@link
		label_lister() provided}.
	@param	pad_label	If true label file padding will be applied
		to ensure the label size is at least the preferred size; if
		false no padding will be applied.
	@return	The total number of characters written to the label file.
	@throws	std::ios::failure	If the label file can not be opened
		for writing.
*/
unsigned int
write_label
	(
	const std::string&		pathname,
	PDS_Data&				label,
	idaeim::PVL::Lister*	lister = NULL,
	bool					pad_label = false
	);


protected:

/**	Clear the data blocks list.

	The current data blocks are deleted and the pointers set to NULL.
*/
void clear_data_blocks ();

/*==============================================================================
	Data Members:
*/
protected:

/**	Names (NULL-terminated array) of data blocks to be exluded
	from the list of data blocks (probably because they are
	redundant with other data blocks).
*/
const char**
	Excluded_Data_Block_Names;

//!	Pointer to the list of data blocks found in the PDS label.
PDS_Data::PDS_Data_Block_List
	*Data_Blocks;

//!	Names (NULL-terminated array) of data blocks that are Image_Data_Blocks.
const char**
	Image_Data_Block_Names;

//!	Pointer to the IMAGE data block in the Data_Blocks list.
Image_Data_Block
	*IMAGE_Data_Block;

//!	The preferred size of the attached PDS label.
unsigned int
	Label_Size;

};	//	End class PDS_Converter

}	//	namespace HiRISE
}	//	namespace UA
#endif
