/*	Generic_PDS_Converter

HiROC CVS ID: Generic_PDS_Converter.hh,v 1.9 2009/10/01 06:06:44 castalia Exp

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

#ifndef _Generic_PDS_Converter_
#define _Generic_PDS_Converter_

#include	"PDS_Converter.hh"


namespace UA
{
namespace HiRISE
{
/**	A <i>Generic_PDS_Converter</i> is used to convert a generic image data
	product PDS label between its attached PDS form and its detached
	PDS/JP2 form.

	<b>N.B.</b>: Only the IMAGE description is modified; no
	product-specific modfications are made. Thus this class is intended
	as a catch-all PDS_Converter implementation.

	@author	Bradford Castalia, UA/HiROC
	@version	1.9
	@see	PDS_Converter
*/
class Generic_PDS_Converter
:	public PDS_Converter
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

//!	The PDS product type name.
static const char
	*PRODUCT_TYPE;

//!	Units of parameters pointing to data blocks.
static const char
	*DATA_POINTER_PARAMETER_UNITS;

/**	Names of parameters to be removed from the copy of the source PDS label
	when generating the converted PDS/JP2 label.
*/
static const char*
	REMOVED_PDS_PARAMETER_NAMES[];

/**	Names of parameters to be removed from the copy of the source
	PDS/JP2 label when generating the converted PDS label.
*/
static const char*
	REMOVED_PDS_JP2_PARAMETER_NAMES[];

//!	Default size (bytes) of an attached PDS label.
static const int
	DEFAULT_PDS_LABEL_SIZE;

/*==============================================================================
	Constructors:
*/
/**	Constructs an empty Generic_PDS_Converter.
*/
Generic_PDS_Converter ();

/**	Constructs a Generic_PDS_Converter from a named file.

	The PDS file may contain an attached PDS label or be a detached
	PDS/JP2 label file. Either the write_PDS_label or write_PDS_JP2_label
	methods can be used to convert either source, respectively.

	@param	pathname	The pathname to the source file containing the
		PDS label.
	@param	excluded_names	The NULL-terminated array of character
		strings naming data blocks to be excluded from conversion
		consideration. May be NULL.
	@param	image_names		The NULL-terminated array of character
		strings naming data blocks that describe image data. <b>N.B.</b>:
		The {@link PDS_Data::IMAGE_DATA_BLOCK_NAME} is always implicitly
		included. May be NULL.
*/
explicit Generic_PDS_Converter (const std::string& pathname,
	const char** excluded_names = NULL, const char** image_names = NULL);

/*==============================================================================
	Accessors:
*/
/**	Get the name of the product types that this converter is intended
	to process.

	@return	Always returns the "generic".
*/
std::string product_names () const;

/*==============================================================================
	Manipulators:
*//*------------------------------------------------------------------------------
	PDS_Converter implementation
*/
/**	Test whether the label parameters are recognized by this converter.

	The test will succeed if an {@link image_data() image data block} is
	found in the source file label.

	@return	true if the label parameters are recognized by this converter;
		false otherwise.
*/
bool label_recognized () const;

/**	Write a detached PDS/JP2 label file.

	A copy is made of the source label represented by the Parameter
	Aggregate of the PDS_Converter base class. The parameters with the
	REMOVED_PDS_PARAMETER_NAMES are removed from the new label
	parameters. If a removed_parameter_names list is provided these
	additional parameters are also removed. In addition, any data block
	groups are removed. <b>N.B.</b>: If applied to a HiRISE EDR data
	product all the binary data blocks will be dropped; this may not be
	what is desired.

	The new {@link PDS_JP2_image_parameters(const std::string&) image
	file parameter groups} are then added to the label, after any
	Image_Data_Block::LINE_PREFIX_BYTES_PARAMETER_NAME or
	Image_Data_Block::LINE_SUFFIX_BYTES_PARAMETER_NAME parameters have
	been removed (<b>N.B.</b>: This assumes that the JP2_Encoder does
	not include line prefix or suffix bytes when processing the image
	data block). These parameters replace the original image data block
	parameters.

	The new PDS label file is then written with PDS standard label
	formatting applied.

	@param PDS_label_pathname The pathname for the detached label file.
	@param JP2_pathname The name of the JP2 image data file
		referened by the label file.
	@param	removed_parameter_names	A NULL terminated array of character
		strings that are the names of parameters to be removed from the
		source label before being written. May be NULL.
	@param	additional_parameters	A pointer to PDS_Data that contains
		additional parameters with product-specific label conversion
		information. May be NULL.
	@throws ios::failure	If the label file could no be created.
*/
void write_PDS_JP2_label
	(
	const std::string&	PDS_label_pathname,
	const std::string&	JP2_pathname,
	const char**		removed_parameter_names = NULL,
	PDS_Data*			additional_parameters = NULL
	);

/**	Write a PDS label for image data to be appended.

	A copy is made of the source label represented by the Parameter
	Aggregate of the PDS_Converter base class. The parameters with the
	REMOVED_PDS_JP2_PARAMETER_NAMES are removed from the new label
	parameters. If a removed_parameter_names list is provided these
	additional parameters are also removed.

	Immediately following the PDS_Data::PDS_ID_PARAMETER_NAME parameter a
	PDS_Data::RECORD_TYPE_PARAMETER_NAME parameter with the
	BYTE_RECORD_TYPE value is inserted. This is followed by a
	PDS_Data::LABEL_RECORDS_PARAMETER_NAME parameter with the
	DEFAULT_PDS_LABEL_SIZE value. Next a PDS_Data::IMAGE_DATA_BLOCK_NAME
	parameter with a PDS_Data::RECORD_POINTER_PARAMETER_MARKER prefix
	with a value of DEFAULT_PDS_LABEL_SIZE + 1 is inserted.

	The original image data block parameters are copied and the
	Image_Data_Block::IMAGE_WIDTH_PARAMETER_NAME and
	Image_Data_Block::IMAGE_HEIGHT_PARAMETER_NAME parameter values are
	changed to the image width and image height values, respectively. The
	modified image data block parameters are then appended to the
	modified label parameters.

	The new PDS label file is then written with PDS standard label
	formatting applied. The file is appended with space characters to pad
	out the DEFAULT_PDS_LABEL_SIZE. If the size of the label is greater
	than the DEFAULT_PDS_LABEL_SIZE, then it is rewritten with a size
	expanded to the next 2K byte increment and the
	PDS_Data::LABEL_RECORDS_PARAMETER_NAME and
	Image_Data_Block::IMAGE_HEIGHT_PARAMETER_NAME pointer parameter
	values adjusted accordingly.

	@param PDS_label_pathname The pathname for the file that begins with
		the converted PDS label.
	@param	image_region	A Rectangle pointer that specifies a region
		within the image that was rendered. <b>N.B.</b>: The rendered
		image region is specifed after any resolution change has been
		applied (don't just shift the full resolution image region by
		the resolution level, which may be inaccurate, get the rendered
		image size from the JP2 decoder). If NULL, the entire image was
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
	@throws	runtime_error	If the source label does not contain the
		expected parameters required to achieve the conversion.
	@throws ios::failure	If the label file could no be created.
*/
void write_PDS_label
	(
	const std::string&	PDS_label_pathname,
	const Rectangle*	image_region = NULL,
	unsigned int		resolution_level = 1,
	const char**		removed_parameter_names = NULL,
	PDS_Data*			additional_parameters = NULL
	);

/*==============================================================================
	Helpers
*/
protected:

/**	Convenience parameter finder function that may throw an exception
	on failure.

	@param	parameters	An Aggregate reference that contains the parameters
		to be searched.
	@param	name	The name of the parameter to find. The first parameter
		with a case insensitive matching name is selected.
	@param	throw_unless_found	If true, a runtime_error will be thrown
		if a matching parameter name is not found; otherwise a NULL value
		will be returned in this case.
	@return	A pointer to the Parameter that was found. This will be NULL
		if a matching parameter name was not found and throw_unless_found
		is false.
	@throws runtime_error	If a matching parameter name was not found
		and throw_unless_found is true.
*/
Parameter*
parameter_of (idaeim::PVL::Aggregate& parameters, const char* name,
	bool throw_unless_found = true);

};	//	End class Generic_PDS_Converter

}	//	namespace HiRISE
}	//	namespace UA
#endif
