/*	HiRISE_PDS_Converter

HiROC CVS ID: HiPrecision_PDS_Converter.hh,v 1.1 2013/01/29 20:01:33 guym Exp

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

#ifndef _HiPrecision_PDS_Converter_
#define _HiPrecision_PDS_Converter_

#include	"Generic_PDS_Converter.hh"


namespace UA
{
namespace HiRISE
{
/**	A <i>HiRISE_PDS_Converter</i> is used to convert a HiRISE image data
	product PDS label between its attached PDS form and its detached
	PDS/JP2 form.

	This class provides the HiRISE product-specific implementation of
	a PDS_Converter.

	@author	Bradford Castalia, UA/HiROC
	@version	1.1
	@see	PDS_Converter
*/
class HiPrecision_PDS_Converter
:	public Generic_PDS_Converter
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

/**	Name of the parameter whose value is the product name being converted.

	@see	product_names() const
*/
static const char*
	PRODUCT_TYPE_PARAMETER_NAME;

/**	Default product name if the PRODUCT_TYPE_PARAMETER_NAME is not
	found.

	@see	product_names() const
*/
static const char*
	HIPRECISION_PRODUCT_TYPE;


//!	Names of data blocks to be ignored (redundant with other data blocks).
static const char*
	EXCLUDED_DATA_BLOCK_NAMES[];

//!	Names of additional Image_Data_Block parameter aggregates.
static const char*
	IMAGE_DATA_BLOCK_NAMES[];

//!	Default size (bytes) of an attached PDS label.
static const int
	DEFAULT_PDS_LABEL_SIZE;


//	The parameters that are to have their version specification updated.
static const char*
	UPDATE_VERSION_PARAMETER_NAMES[];

//!	DATA_SET_xxx version minor value.
static const int
	DATA_SET_VERSION_MINOR_VALUE;
/*
//!	IMAGE_MAP_PROJECTION parameters to be adjusted.
static const char*
	IMAGE_MAP_PROJECTION_GROUP_NAME;

//!	Projection type.
static const char*
	PROJECTION_TYPE_PARAMETER_NAME;

//!	Horizonatal offset.
static const char*
	HORIZONATAL_OFFSET_PARAMETER_NAME;

//!	Vertical offset.
static const char*
	VERTICAL_OFFSET_PARAMETER_NAME;
*/
//!	Image height.
static const char*
	IMAGE_HEIGHT_PARAMETER_NAME;

//!	Image width.
static const char*
	IMAGE_WDITH_PARAMETER_NAME;
/*
//!	Pixels per degree.
static const char*
	PIXELS_PER_DEGREE_PARAMETER_NAME;

//!	Meters per pixel.
static const char*
	METERS_PER_PIXEL_PARAMETER_NAME;

//!	Minimum latitude.
static const char*
	MINIMUM_LATITUDE_PARAMETER_NAME;

//!	Maximum latitude.
static const char*
	MAXIMUM_LATITUDE_PARAMETER_NAME;

//!	Eastern longitude.
static const char*
	EASTERN_LONGITUDE_PARAMETER_NAME;

//!	Western longitude.
static const char*
	WESTERN_LONGITUDE_PARAMETER_NAME;
*/
/*==============================================================================
	Constructors:
*/
/**	Constructs an empty HiPrecision_PDS_Converter.
*/
HiPrecision_PDS_Converter ();

/**	Constructs a HiRISE_PDS_Converter from a named file.

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
explicit HiPrecision_PDS_Converter (const std::string& pathname,
	const char** excluded_names = NULL, const char** image_names = NULL);

/*==============================================================================
	Manipulators:
*/
/*------------------------------------------------------------------------------
	PDS_Converter implementation
*/
/**	Test whether the label parameters are recognized by this converter.

	The test will succeed if an {@link image_data() image data block} can
	be found in the source file label and a PRODUCT_TYPE_PARAMETER_NAME
	is found with the HIRISE_PRODUCT_TYPE value.

	@return	true if the label parameters are recognized by this converter;
		false otherwise.
*/
bool label_recognized () const;

/**	Write a detached PDS/JP2 label file.

	A copy is made of the source label represented by the Parameter
	Aggregate of the PDS_Converter base class. The original parameters
	are then have {@link data_set_version(PDS_Data*) data set version
	updates applied} if appropriate.

	Then the base class write_PDS_JP2_label method is called to apply the
	generic label modifications and write the label file. Finally the
	copy of the original parameters is restored to the content of this
	converter.

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
	@see	Generic_PDS_Converter::write_PDS_JP2_label(const std::string&,
		const std::string&, const char**, PDS_Data*)
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
	Aggregate of the PDS_Converter base class. The original parameters
	then have their image map projection parameters adjusted to
	be consistent with the selected image region and rendering
	resolution.

	Then the base class write_PDS_label method is called to apply the
	generic label modifications and write the label file. Finally the
	copy of the original parameters is restored to the content of this
	converter.

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
	@see	adjust_image_map_projection(idaeim::PVL::Aggregate*,
		const Rectangle&, unsigned int)
	@see	Generic_PDS_Converter::write_PDS_label(const std::string&,
		const Rectangle*, unsigned int, const char**, PDS_Data*)
*/
void write_PDS_label
	(
	const std::string&	PDS_label_pathname,
	const Rectangle*	image_region = NULL,
	unsigned int		resolution_level = 1,
	const char**		removed_parameter_names = NULL,
	PDS_Data*			additional_parameters = NULL
	);

/*------------------------------------------------------------------------------
	Product-specific conversions
*/
/**	Get the name of the product types that this converter is intended
	to process.

	The value of the INSTRUMENT_ID parameter is used.

	@return	A string used to identify the type of products recognized
		by this PDS_Converter.
*/
std::string product_names () const;

/**	Adjust the data set version parameters.

	Unless the additional_parameters are non-null and contain a
	#GeoTIFF_PARAMETER_NAME or GML_PARAMETER_NAME parameter with a value
	of "TRUE" or "1", nothing is done.

	For each of the #UPDATE_VERSION_PARAMETER_NAMES the parameter value
	has its minor version number set to the #DATA_SET_VERSION_MINOR_VALUE
	if it is less than that value. The version number is expected to be at
	the end of the parameter value string in the format "Vm.n", where m is
	the major version number and n is the minor version number. If any of
	the #UPDATE_VERSION_PARAMETER_NAMES can not be found or a minor version
	number is not found in its value, it is left unchanged.

	@param	additional_parameters	A pointer to PDS_Data that contains
		additional parameters with product-specific label conversion
		information. May be NULL.
*/
void
data_set_version (PDS_Data* additional_parameters);

/**	Adjust the IMAGE_MAP_PROJECTION_GROUP_NAME of parameters.

	This method is only used during the write_PDS_label PDS/JP2 to PDS
	label conversion.

	<b>N.B.</b>: The parameters are modified in place.

	The following parameters are adjusted to be consistent with a
	selected subarea and/or reduced resolution rendering of the
	image:

<dl>
<dt>Image size</dt>
	<dd>The size, in pixels, of the image. The values of these parameters
	will be set to the image region width and height and are expected to
	be identical to the size of the rendered image listed in the IMAGE
	parameters group.
	<ul>
	<li>#IMAGE_WDITH_PARAMETER_NAME (SAMPLE_LAST_PIXEL)</li>
	<li>#IMAGE_HEIGHT_PARAMETER_NAME (LINE_LAST_PIXEL)</li>
	</ul>
	</dd>

<dt>Projection offsets</dt>
	<dd>Key values used to map image locations (sample,line) to
	to real world (longitude,latitude) locations. The values of
	these parameters are relative to the image origin (upper-left
	corner).
	<ul>
	<li>#HORIZONATAL_OFFSET_PARAMETER_NAME (SAMPLE_PROJECTION_OFFSET)</li>
	<li>#VERTICAL_OFFSET_PARAMETER_NAME (LINE_PROJECTION_OFFSET)</li>
	</ul>
	</dd>

<dt>Image resolution</dt>
	<dd>Defines the size of a pixel in real world units which are
	specified by the parameter. The values of these parameters are
	adjusted by the rendering ratio.
	<ul>
	<li>#METERS_PER_PIXEL_PARAMETER_NAME (MAP_SCALE)</li>
	<li>#PIXELS_PER_DEGREE_PARAMETER_NAME (MAP_RESOLUTION)</li>
	</ul>
	</dd>

<dt>Image boundaries</dt>
	<dd>Specifies the real world (longitude and latitude degrees)
	location of the image edges. The values of these parameters are
	re-mapped to the boundaries of the image region.
	<ul>
	<li>#WESTERN_LONGITUDE_PARAMETER_NAME (WESTERNMOST_LONGITUDE)</li>
	<li>#EASTERN_LONGITUDE_PARAMETER_NAME (EASTERNMOST_LONGITUDE)</li>
	<li>#MINIMUM_LATITUDE_PARAMETER_NAME (MINIMUM_LATITUDE)</li>
	<li>#MAXIMUM_LATITUDE_PARAMETER_NAME (MAXIMUM_LATITUDE)</li>
	</ul>
	</dd>
</dl>

	<b>N.B.</b>: If the #IMAGE_MAP_PROJECTION_GROUP_NAME parameter
	value specifies that a stereographicp projection was used and the image
	region is not the entire image then the image boundary parameters
	will be removed from the converted label because the linear re-mapping
	normally used would not be reliable for the non-linear projection.
	<i>An implementation of the non-linear projection algorithm is needed
	to correct this defect.</i> These parameters are not necessary to
	perform mappings between image (sample, line) and real world
	(longitude,latitude) locations using the appropriate projection
	algorithm.

	@param	image_map_projection	A pointer to the Parameter
		Aggregate that contains the IMAGE_MAP_PROJECTION parameters.
	@param	image_region	The Rectangle of image data that will be
		rendered relative to the scaled image pixel grid. The size of the
		rectangle is the size of the output image to be described. The
		origin of the rectangle is the position of the upper-left corner
		of the output image on the scaled image grid.
	@param	ratio	The ratio of full resolution image grid to the the
		scaled image grid. The ratio will always be a power of 2
		corresponding to the selected image rendering resolution level. A
		ratio of 1 means the image was not scaled, 2 means the size of
		the scaled resolution grid is half the size of the full
		resolution image grid, 4 when the grid is quarter scale, etc.
*/
void
adjust_image_map_projection
	(
	idaeim::PVL::Aggregate*		image_map_projection,
	const Rectangle&			image_region,
	unsigned int				ratio
	);

};	//	End class HiRISE_PDS_Converter

}	//	namespace HiRISE
}	//	namespace UA
#endif
