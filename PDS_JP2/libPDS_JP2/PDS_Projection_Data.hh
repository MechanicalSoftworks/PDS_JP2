/*	PDS_Projection_Data

HiROC CVS ID: PDS_Projection_Data.hh,v 1.11 2012/08/23 22:18:21 castalia Exp

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

#ifndef _PDS_Projection_Data_
#define _PDS_Projection_Data_

#include	"PDS_Data.hh"

#include	"JP2_Box.hh"
#include	"Dimensions.hh"

//	GDAL/OGR
#include	"ogr_spatialref.h"


namespace UA
{
namespace HiRISE
{

/**	The <i>PDS_Projection_Data</i> provides geographic projection
	capabilities between image and real world coordinates.

	The projection information is defined by a set of PDS_Data parameters,
	of which this is a subclass. Parameters of known names are sought to
	provide the required values to assemble the projection definition.
	As usual, this dependency on parameter names can be a source of
	misunderstanding. If a required parameter is not found this will
	be reported in an expception that names the missing parameter.

	At the very least, an affine geo-transform array for the identity
	projection - in which image coordinates and world coordinates are
	identical - is available. PDS parameters may be provided that enable
	the identification and assembly of other projections. In addition to
	a geo-transform array a GDAL (Geospatial Data Abstraction Library,
	http://www.gdal.org) OGRSpatialReference object may be assembled using
	PDS parameter values.

	The PDS_Projection_Data class provides methods for generating JP2_Box
	objects containing GeoTIFF
	(http://www.remotesensing.org/geotiff/geotiff.html) and GML
	(Geography Markup Language of the Open Geospatial Consortium;
	http://www.opengeospatial.org/standards/gml and
	http://www.ogcnetwork.net/gml-jp2) data. GeoTIFF is an informal
	public domain metadata standard which allows georeferencing
	information to be embedded within a tagged image file format (TIFF;
	the JP2 format employs the TIFF mechanism for identifying box
	contents). The GeoTIFF format was originally created by Dr. Niles
	Ritter while he was working at the NASA Jet Propulsion Laboratory.
	GML is part of a complex of ISO (International Standards
	Organization) specifications for managing geospatial information.

	Software interfaces provided by GDAL for generating the
	OGRSpatialReference and JP2_Box contents are used in the
	implementation of the PDS_Projection_Data class. In particular, the
	JP2_GeoTIFF method is based on the GDALJP2Metadata::CreateJP2GeoTIFF
	method and the JP2_GML method is based on the
	GDALJP2Metadata::CreateGMLJP2 method.

	<b>N.B.</b>: The projection managment capabilities of this class
	depend on providing correct PDS parameters and the functions of the
	GDAL software. There is considerable uncertainty about the correct
	mapping of PDS parameter values to GDAL projection values. This
	class has been successfully tested with HiRISE PDS RDR data products
	using the GeoTIFF box contents with image location projection values
	reported by IDL/ENVI having no significant difference from the same
	location projection values reported by the USGS/ISIS software.
	However, the accuracy of results with other PDS data products can
	not be assured. Also, as of this writing the GML box contents have
	not been successfully tested. 
	
	@author		Bradford Castalia, UA/HiROC
	@version	1.11
*/
class PDS_Projection_Data
:	public PDS_Data
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

//!	Name of the parameter providing the planet name.
static const char
	*PLANET_PARAMETER_NAME;
//!	Name of the parameter group containing projection parameters.
static const char
	*IMAGE_MAP_PROJECTION_GROUP_NAME;
//!	Name of the parameter specifying the type of projection.
static const char
	*PROJECTION_TYPE_PARAMETER_NAME;
//!	Name of the parameter specifying the type of coordinate system.
static const char
	*COORDINATE_SYSTEM_PARAMETER_NAME;
//!	Name of the parameter specifying the type of coordinate system.
static const char
	*LATITUDE_TYPE_PARAMETER_NAME;
/**	Name of the parameter specifying the horizontal offset of the
	projection origin from the image origin.
*/
static const char
	*HORIZONATAL_OFFSET_PARAMETER_NAME;
/**	Name of the parameter specifying the vertical offset of the
	projection origin from the image origin.
*/
static const char
	*VERTICAL_OFFSET_PARAMETER_NAME;
//!	Name of the parameter specifying the number of image lines.
static const char
	*IMAGE_HEIGHT_PARAMETER_NAME;
//!	Name of the parameter specifying the number of pixels per image line.
static const char
	*IMAGE_WIDTH_PARAMETER_NAME;
//!	Name of the parameter specifying the number of pixels per world degree.
static const char
	*PIXELS_PER_DEGREE_PARAMETER_NAME;
//!	Name of the parameter specifying the real world size of a pixel.
static const char
	*PIXEL_SIZE_PARAMETER_NAME;
//!	Name of the parameter specifying the planet's semi-major axis radius.
static const char
	*SEMI_MAJOR_RADIUS_PARAMETER_NAME;
//!	Name of the parameter specifying the planet's semi-minor axis radius.
static const char
	*SEMI_MINOR_RADIUS_PARAMETER_NAME;
//!	Name of the parameter specifying the projection first standard parallel.
static const char
	*FIRST_STANDARD_PARALLEL_PARAMETER_NAME;
//!	Name of the parameter specifying the projection second standard parallel.
static const char
	*SECOND_STANDARD_PARALLEL_PARAMETER_NAME; 
//!	Name of the parameter specifying the projection center longitude.
static const char
	*CENTER_LONGITUDE_PARAMETER_NAME;
//!	Name of the parameter specifying the projection center latitude.
static const char
	*CENTER_LATITUDE_PARAMETER_NAME;
//!	Name of the parameter specifying the image minimum latitude.
static const char
	*MINIMUM_LATITUDE_PARAMETER_NAME;
//!	Name of the parameter specifying the image maximum latitude.
static const char
	*MAXIMUM_LATITUDE_PARAMETER_NAME;
//!	Name of the parameter specifying the image minimum longitude.
static const char
	*MINIMUM_LONGITUDE_PARAMETER_NAME;
//!	Name of the parameter specifying the image maximum longitude.
static const char
	*MAXIMUM_LONGITUDE_PARAMETER_NAME;
//!	Name of the parameter specifying the projection rotation.
static const char
	*PROJECTION_ROTATION_PARAMETER_NAME;

//!	Projection types.
enum Projection_Type
	{
	UNKNOWN_PROJECTION	= -1,
	/*
		Well known projections are placed first in the list.
	*/
	EQUIRECTANGULAR		= 0,
	POLAR_STEREOGRAPHIC,
	/*
		The remaining projections are listed alphabetically.
	*/
	ALBERS,
	BONNE,
	CYLINDRICAL_EQUAL_AREA,
	GNOMONIC,
	LAMBERT_AZIMUTHAL_EQUAL_AREA,
	LAMBERT_CONFORMAL_CONIC,
	MERCATOR,
	MOLLWEIDE,
	OBLIQUE_CYLINDRICAL,
	ORTHOGRAPHIC,
	SINUSOIDAL,
	STEREOGRAPHIC,
	TRANSVERSE_MERCATOR,
	VANDERGRINTEN,

	TOTAL_PROJECTION_TYPES
	};

/**	A <i>Projection_Definition</i> maps GDAL OGRSpatialReference parameter
	names to their required PDS parameter names and default values.
*/
struct Projection_Definition
	{
	//!	The Projection_Type for the projection being defined.
	Projection_Type
		Code;

	/**	The maximum number of entries in any array contained in a
		Projection_Definition.

		<b>N.B.</b>: The end of valid entries in an array is marked
		by a NULL value.
	*/
	static const int
		MAX_ARRAY_ENTRIES	= 8;
		
	/**	Projection type name aliases.

		Projection names are to have no spaces; underbars are to be used
		where spaces might otherwise occur.

		The first name in the list is the required SRS_PP_xxx name required
		by the GDAL OGRSpatialReference::SetProjection method.

		@see	projection_type (const std::string) const
	*/
	const char*
		Aliases[MAX_ARRAY_ENTRIES];

	/**	Parameters that are required to define the projection.
		
		Associates a GDAL SRS parameter name with a PDS parameter name.
		The PDS parameter must exist and have a single assignment value.
		This value is used to set the SRS parameter value.
	*/
	struct Required_Projection_Parameter
		{
		//!	The name with the GDAL OGRSpatialReference::SetNormProjParm method.
		const char*
			SRS_Parameter_Name;
		//!	The name of the required PDS parameter.
		const char*
			PDS_Parameter_Name;
		}
		Required_Parameters[MAX_ARRAY_ENTRIES];

	/**	Projection parameters with default values.

		Associates a GDAL SRS parameter name with a constant value.
		This value is used to set the SRS parameter value.
	*/
	struct Default_Projection_Parameter
		{
		//!	The name with the GDAL OGRSpatialReference::SetNormProjParm method.
		const char*
			SRS_Parameter_Name;
		//!	The value assigned to the parameter.
		double
			Value;
		}
		Default_Parameters[MAX_ARRAY_ENTRIES];
	};
//!	A Projection_Definition is provided for each known Projection_Type.
static const Projection_Definition
	Projection_Definitions[TOTAL_PROJECTION_TYPES];

/**	The default identity affine transformation matrix.

	@see	geo_transform()
*/
static const double
	DEFAULT_GEO_TIFF_TRANSFORM[6];

//!	UUID for the GeoTIFF JP2_Box.
static const unsigned char
	GEO_TIFF_UUID[16];

/*==============================================================================
	Constructors:
*/
/**	Construct a default identity projection.

	Only the default identity {@link geo_transform() geo-transform}
	matrix will be available.
*/
PDS_Projection_Data ();

/**	Construct a projection from a set of PDS data parameters.

	An attempt will be made to assemble geo-transform and spatial
	reference information from the parameter values.

	@param	PDS_data	A reference to a set of PDS data parameters
		that will be copied into this PDS_Projection_Data object.
	@see	initialize_geo_transform()
	@see	initialize_spatial_reference()
*/
PDS_Projection_Data (const PDS_Data& PDS_data);

/**	Construct a projection from a file source of PDS parameters.

	The source file is parsed for PDS parameters that will be used to
	assemble geo-transform and spatial reference information.

	@param	pathname	A pathname to a file that is will be parsed
		as a source of PDS parameters.
	@see	initialize_geo_transform()
	@see	initialize_spatial_reference()
*/
PDS_Projection_Data (const std::string& pathname);

/**	Destructor.

	All memory owned by the object is released.
*/
virtual ~PDS_Projection_Data ();

/*==============================================================================
	Accessors
*/
/**	Set the PDS parameters from a source file.

	The current parameters are cleared before the new parameters are
	moved in, but not before the new parameters have been successfully
	obtained from the source file. Then the projection information is
	initialized.

	<b>N.B.</b>: The name of the parameters group is set to the source
	file pathname.

	@param	pathname	The pathname to the source file that will be
		parsed for PVL parameters.
	@return	This PDS_Projection_Data object.
	@throws	std::ios::failure	If the source file can not be accessed
		or read.
	@throws idaeim::PVL::Invalid_Syntax	If the source file contains
		contains invalid PVL syntax.  
	@see	idaeim::PVL::Parser
	@see	initialize_geo_transform()
	@see	initialize_spatial_reference()
*/
virtual PDS_Data& parameters (const std::string& pathname);

/**	Set the PDS parameters from a Parameter Aggregate.

	The current parameters are cleared before the new parameters are
	moved in. Then the projection information is initialized.

	<b>N.B.</b>: The name of the parameters group is set to the
	name of the Parameter Aggregate.

	@param	parameters	A Parameter Aggregate that is the source of
		new parameters.
	@return	This PDS_Projection_Data object.
	@see	initialize_geo_transform()
	@see	initialize_spatial_reference()
*/
virtual PDS_Data& parameters (const idaeim::PVL::Aggregate& parameters);

/**	Get the geo-transform array.

	The geo-transform contains the six coefficients of a two-dimensional
	affine transformation. In the classic expression of the
	two-dimensional affine transformation matrix by Newman and Sproull
	(Newman, W.M. and Sproull, R.F., "Principles of Interactive Computer
	Graphics", McGraw-Hill, 1979, section 4-3 Matrix Representations, p.
	57ff) a 3x3 matrix representation is used. The last column is elided
	away because it is always the identity vector:

<pre>
    [x' y'] = [x y 1]|a d 0|
                     |b e 0|
                     |c f 1|
</pre>

	or

<pre>
    x' = a*x + b*y + c
    y' = d*x + e*y + f
</pre>

	For an image translation operation by Ox,Oy the matrix values are:

<pre>
    | 1   0|
    | 0   1|
    |Ox  Oy|
</pre>

	For an image scaling operation by Sx,Sy the matrix values are:

<pre>
    |Sx   0|
    | 0  Sy|
    | 0   0|
</pre>

	For an image rotation operation by an angle A the matrix values are:

<pre>
    |cos (A)  -sin (A)|
    |sin (A)   cos (A)|
    |      0         0|
</pre>

	These operations can be concatenated - each operation matrix,
	including the third column identity vector, multiplied by the
	subsequent operation matrix - to produce a single matrix that
	incorporates all of the individual transformation operations.

	For the geo-transform array the corresponding values are, by array
	index, GT[0]=c, GT[1]=a, GT[2]=b, GT[3]=f, GT[4]=d, GT[5]=e, or:

<pre>
    |GT[1]  GT[4]|
    |GT[2]  GT[5]|
    |GT[0]  GT[3]|
</pre>

	The geo-transform array contains the six coefficients that result
	from concatenating an offset of the image back (negative) to the
	projection origin, rotating the image to align with the projection
	(north up), and scaling from pixel units to world unit (meters):

<ol>
<li>-(Sx * Ox * cos (A)) - (Sx * Oy * sin (A))</li>
<li>Sx * cos (A)</li>
<li>Sx * sin (A)</li>
<li>(Sy * Ox * sin (A)) - (Sy * Oy * cos (A))</li>
<li>Sy * -sin (A)</li>
<li>Sy * cos (A)</li>
</ol>

	Where:

<dl>
<dt>Ox,Oy
	<dd>The offset, in pixels, of the projection origin relative to the
	upper-left corner of the upper-left image pixel.
<dt>Sx,Sy
	<dd>The pixel size dimensions, in meters.
<dt>A
	<dd>The clockwise angle of rotation about the projection origin
	relative to the vertical (north-pointing) axis.
</dl>

	For the normal case of an unrotated image projection this reduces to:

<ol>
<li>-Sx * Ox</li>
<li>Sx</li>
<li>0</li>
<li>-Sy * Oy</li>
<li>0</li>
<li>Sy</li>
</ol>

	<b>N.B.</b>: Image pixel coordinates use a left-handed coordinate
	system in which the horizontal x-axis is positive to the right from
	the origin at the upper left corner of the upper left pixel along
	increasing sample numbers and the vertical y-axis is positive
	downwards from the origin along increasing line numbers. However the
	geo-transform operates in the conventional right-handed coordinate
	system (in meter units) in which the x-axis is positive to the right
	from the projection origin and the vertical y-axis is positive
	upwards from the origin. This reversal of the positive vertical
	direction can be the source of confusion when using the
	geo-transform values.
	
	@return	A pointer to the array of six double values of the
		geo-transform. <b>N.B.</b>: This array is owned by the
		PDS_Projection_Data object; modifying it will affect the
		results of its use in subsequent projection operations.
*/
const double* geo_transform () const
	{return Geo_Transform;}

/**	Get the OGRSpatialReference.

	@return	If a OGRSpatialReference was assembled from the available
		parameter values a copy is returned; otherwise NULL is returned.
*/
OGRSpatialReference* spatial_reference () const
	{return Spatial_Reference ? Spatial_Reference->Clone () : NULL;}

/**	Get the projection type.

	The Projection_Type code, other than UNKNOWN_PROJECTION,
	can be used as an index into the Projection_Definitions array to
	obtain details of the mapping between PDS parameters and GDAL SRS
	paramters.

	@return A Projection_Type code. If a projection could not be {@link
		initialize_spatial_reference() initialized} this will be the
		UNKNOWN_PROJECTION value.
*/
Projection_Type projection_type () const
	{return Projection_Type_Code;}

/**	Get the name of the applicable projection.

	Any given type of projection may have several aliases for its name.
	The name returned by this method is the one that is specified by
	the PDS PROJECTION_TYPE_PARAMETER_NAME parameter. To obtain the
	projection name recognized by
	the GDAL OGRSpatialReference class, use the {@link projection_type()
	projection type code}, if it is not UNKNOWN_PROJECTION, as the
	index into the {@link #Projection_Definitions list of projection
	definitions} and use the first entry in the Aliases array:

<pre>
    string
        formal_projection_name;
    if (projection_type () != UNKNOWN_PROJECTION)
        formal_projection_name =
            Projection_Definitions[projection_type ()].Aliases[0];
</pre>

	@return	A string having the formal name of the applicable projection.
		If a projection could not be {@link
		initialize_spatial_reference() initialized} this will be an empty
		string.
*/
std::string projection_name () const
	{return Projection_Name;}

/*==============================================================================
	Manipulators
*/
/**	Initialized the geo-transform array values from the PDS parameter
	values.

	There are three required parameters: PIXEL_SIZE_PARAMETER_NAME,
	HORIZONATAL_OFFSET_PARAMETER_NAME and VERTICAL_OFFSET_PARAMETER_NAME.
	If a parameter group with the IMAGE_MAP_PROJECTION_GROUP_NAME is
	present the parameters will be sought in this group; otherwise they
	may occur anywhere in the current PDS_Data. If none of the required
	parameters can be found the geo-transform array will be set to the
	identity values.

	The geo-transform values are set as follows:

<pre>
    GT[1] = PIXEL_SIZE * units_scale
    GT[5] = -GT[1]
    GT[0] = -(GT[1] * (HORIZONTAL_OFFSET - 1))
    GT[3] = -(GT[5] * (VERTICAL_OFFSET   - 1))
    GT[2] = GT[4] = 0
</pre>

	The pixel is presumed to have a square shape; thus the PIXEL_SIZE
	value of the PIXEL_SIZE_PARAMETER_NAME parameter applies to both the
	horizontal and vertical dimension. 

	The geo-transform values are in a real world space in which distance
	is measured in meters. The PDS Data Dictionary specifies that the
	units for the PIXEL_SIZE_PARAMETER_NAME parameter should be
	"KM/PIX". However, for some data products (e.g. HiRISE) the pixel
	size is measured in meters. The only way to distinguish which units
	apply is to examine the units string associated with the value.
	However, if the value has no units string it must be assumed that
	the PDS Data Dictionary units are in effect. Thus the units_scale is
	1000 if the parameter units string is empty or specifies kilometers;
	otherwise it is 1.

	<b>N.B.</b>: The pixel vertical (GT[5]) dimension is negative to
	compensate for the left-handed image coordinate system in which
	positive vertical is downwards and the right-handed geographic
	coordinate system in which positive vertical is upwards.

	The HORIZONTAL_OFFSET and VERTICAL_OFFSET values of the
	HORIZONATAL_OFFSET_PARAMETER_NAME and VERTICAL_OFFSET_PARAMETER_NAME
	parameters, respectively, are the offsets of the map projection
	origin from the image origin in image coordinate space
	(sample,line). Because the PDS image origin is (1,1) - there is no
	(0,0) pixel - while the geographic projection origin is (0,0) the
	offset values are adjusted to a conventional (0,0) image origin.

	<b>Warning</b>: Different PDS data products locate the image origin
	differently: Some use the upper left corner of the upper
	left pixel, while others use the center of the upper left
	pixel. Unfortuntately there is nothing in the PDS label to indicate
	which location is being used. This implementation assumes that
	the image origin is located at the upper left corner of the
	upper left pixel.

	@return	This PDS_Projection_Data object.
	@throws	std::logic_error	If the PROJECTION_ROTATION_PARAMETER_NAME
		parameter is found and it has a non-zero value (hopefully this
		can be supported in a future version of this class).
	@throws	idaeim::PVL_Invalid_Value	If any of the required PDS
		parameters is not an assignment of a single numeric value.
	@see	geo_transform()
*/
PDS_Projection_Data& initialize_geo_transform ();

/**	Initialize the spatial reference information of a new
	OGRSpatialReference object.

	A GDAL OGRSpatialReference object
	(http://www.gdal.org/ogr/classOGRSpatialReference.html) is
	initialized if all its required PDS parameter values are
	successfully found.

	First the {@link projection_name() projection name} is erased, the
	{@link projection_type() projection type} is initialized to
	UNKNOWN_PROJECTION, any existing OGRSpatialReference object is
	deleted and the {@link spatial_reference() spatial reference} set to
	NULL.

	If a parameter group with the IMAGE_MAP_PROJECTION_GROUP_NAME is
	present all remaining PDS parameters will be sought in this group;
	otherwise they may occur anywhere in the current PDS_Data.

	A PROJECTION_TYPE_PARAMETER_NAME parameter is required that names
	the type of applicable projection. This determines the {@link
	projection_name() projection name} which is used to {@link
	projection_type(const std::string&) search} the {@link
	#Projection_Definitions list of known projection definitions} for a
	Projection_Definition with a matching name in its Aliases list. If
	no match is found nothing more is done.

	A tentative OGRSpatialReference object is constructed and
	initialized (OGRSpatialReference::SetProjection) with the formal
	projection name - the first name in the projection definition's
	Aliases list - which may be different from the PDS projection name.
	The value of each {@link
	Projection_Definition::Required_Projection_Parameter::PDS_Parameter_Name
	required PDS parameter} of the projection definition is used to
	initialize (OGRSpatialReference::SetNormProjParm) the associated
	OGRSpatialReference object's {@link
	Projection_Definition::Required_Projection_Parameter::SRS_Parameter_Name
	spatial reference system parameter}. In addition, each {@link
	Projection_Definition::Default_Projection_Parameter::Value default
	value} of the projection definition is used to initialize the
	associated OGRSpatialReference object's {@link
	Projection_Definition::Default_Projection_Parameter::SRS_Parameter_Name
	spatial reference system parameter}.

	The OGRSpatialReference object's projection coordinate system name
	is initialized (OGRSpatialReference::SetProjCS) with the formal
	projection name followed, after a single space character, by the
	planet name. The planet name is obtained from the PLANET_PARAMETER_NAME
	PDS parameter; if this can't be found "Unknown" is used. The
	geographic coordinate system specification is initialized
	(OGRSpatialReference::SetGeogCS) with the following values:

<dl>
<dt>Planet name
	<dd>The planet name, as determined above. If the {@link projection_type()
	projection type} is EQUIRECTANGULAR a "_localRadius" suffix is applied.
	If the projection type is POLAR_STEREOGRAPHIC a "_polarRadius" suffix
	is applied.
<dt>Geographic name
	<dd>The unaltered planet name with a "GCS_" prefix.
<dt>Datum name
	<dd>The unaltered planet name with a "D_" prefix.
<dt>Planet axis radius
	<dd>The planet axis radius is the value of the
	SEMI_MAJOR_RADIUS_PARAMETER_NAME parameter. However, if the
	projection is not geocentric based and the {@link projection_type()
	projection type} is POLAR_STEREOGRAPHIC or STEREOGRAPHIC with a
	CENTER_LATITUDE_PARAMETER_NAME parameter absoulte value of 90 (i.e.
	stereographic centered at a pole) then the
	SEMI_MINOR_RADIUS_PARAMETER_NAME parameter value is used.

	The use of a geocentric based projection (i.e. planetographic) is
	determined by the COORDINATE_SYSTEM_PARAMETER_NAME parameter, or the
	LATITUDE_TYPE_PARAMETER_NAME if the former is not found. Unless the
	parameter value is "planetocentric" (case insensitive) planetographic
	applies. However, the EQUIRECTANGULAR, ORTHOGRAPHIC and SINUSOIDAL
	projection types are not subject to this condition; they are always
	deemed to be planetocentric.
<dt>Planet inverse flattening
	<dd>The inverse of an elipsoidal planet model flattening is the ratio
	of the semi-major axis radius to this value minus the semi-minor axis
	radius (using the parameters indicated above). Note that as the two
	values approach equality the ratio approaches infiniity, if the
	difference is less than or equal to 0.00000001 the inverse flattening
	is set to zero which indicates a spherical planet model. Also, if the
	projection is planetocentric (as determined above) or pole centered
	stereographic (as determined above) then the inverse flattening is
	always set to zero.
<dt>Prime meridian name
	<dd>This descriptive name is set to "Reference_Meridian".
<dt>Prime meridian offset
	<dd>Set to 0.
</dl>

	If the tentative OGRSpatialReference object can not be initialized
	for any reason it is deleted. Otherwise it is set as the current
	{@link spatial_reference() spatial reference} object. Note that it
	is possible to have identified a {@link projection_name() projection
	name} and {@link projection_type() projection type} but fail to
	initialize a {@link spatial_reference() spatial reference} object.

	@return	This PDS_Projection_Data object.
	@throws	idaeim::Invalid_Argument	If a required PDS parameter can
		not be found.
	@throws	idaeim::PVL_Invalid_Value	If a required PDS parameter is
		not an assignment of a single numeric (or string, as the
		situation requires) value.
	@throws	std::logic_error	If an OGRSpatialReference initialization
		operation fails.
*/
PDS_Projection_Data& initialize_spatial_reference ();

/*==============================================================================
	JP2 Boxes
*/
/**	Get a JP2_Box with GeoTIFF data content.

	The GeoTIFF JP2_Box is a JP2_Box::UUID_BOX_TYPE with content that
	begins with the GEO_TIFF_UUID signature. Immediately following the
	signature is binary data produced by the GDAL GTIFMemBufFromWkt
	function that operates on Spatial Reference System Well-Known_Text
	representation of the {@link spatial_reference() current projection
	specifications} (generated by the OGRSpatialReference::exportToWkt
	method), and the current {@link geo_transform() geo-transform array}.

	@return	A pointer to a JP2_Box containing the GeoTIFF data, or NULL
		if no {@link spatial_reference() spatial reference} object has
		been {@link initialize_spatial_reference() initialized}.
		<b>N.B.</b>: Ownership of the JP2_Box is transferred to the
		caller.
	@throws	std::logic_error	If the GeoTIFF data production by GDAL
		fails.
*/
JP2_Box* JP2_GeoTIFF () const;

/**	Get a JP2_Box with GML data content.

	If the either the image width or height arguments are not specified
	the PDS IMAGE_WIDTH_PARAMETER_NAME and IMAGE_HEIGHT_PARAMETER_NAME
	parameters will be used to obtain the required values.

	The GML JP2_Box is a JP2_Box::ASSOCIATION_BOX_TYPE containing a
	JP2_Box::LABEL_BOX_TYPE with a "gml.data" label and a
	JP2_Box::ASSOCIATION_BOX_TYPE containing a JP2_Box::LABEL_BOX_TYPE
	with a "gml.root-instance" label followed by a JP2_Box::XML_BOX_TYPE
	containing a "gml:FeatureCollection" XML document that provides the
	current {@link geo_transform() geo-transform} specifications.
	<b>N.B.</b> This XML document is a hardcoded copy of the document
	format text taken verbatim from the GDAL
	GDALJP2Metadata::CreateGMLJP2 method.

	If the current {@link spatial_reference() spatial reference object}
	is flagged as projected (OGRSpatialReference::IsProjected) or
	geographic (OGRSpatialReference::IsGeographic) its corrsponding
	authority name (OGRSpatialReference::GetAuthorityName) is "epsg"
	(case insensitive) the XML "srsName" will be "urn:ogc:def:crs:EPSG::"
	followed by the spatial reference authority code
	(OGRSpatialReference::GetAuthorityCode).

	If no EGSG authority code is found then the XML "srsName" will be
	"gmljp2://xml/CRSDictionary.gml#ogrcrs1" and an additional
	JP2_Box::ASSOCIATION_BOX_TYPE will be added to the primary JP2_Box.
	This will contain a JP2_Box::LABEL_BOX_TYPE with a "CRSDictionary.gml"
	label followed by a JP2_Box::XML_BOX_TYPE containing a "gml:Dictionary"
	XML document with the following references:

<ul>
<li>gml:id="CRSU1"
<li>xmlns:gml="http://www.opengis.net/gml"
<li>xmlns:xlink="http://www.w3.org/1999/xlink"
<li>xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
</ul>

	The XML dictionary document is produced by the
	OGRSpatialReference::exportToXML method of the current spatial
	reference object.

	<b>WARNING</b>: As of this writing no tests have been able to
	confirm that the GML content is correct.

	@param	image_width	The width of the image be referenced. If zero
		the {@link #IMAGE_WIDTH_PARAMETER_NAME} parameter value, if
		available, will be used.
	@param	image_height	The height of the image be referenced. If zero
		the {@link #IMAGE_HEIGHT_PARAMETER_NAME} parameter value, if
		available, will be used.
	@return	A pointer to a JP2_Box containing the GML data, or NULL if no
		{@link spatial_reference() spatial reference} object has been
		{@link initialize_spatial_reference() initialized}. <b>N.B.</b>:
		Ownership of the JP2_Box is transferred to the caller.
	@throws	idaeim::Exception	If the image width or height values can
		not be determined from the PDS_Data.
	@throws	std::logic_error	If the GeoTIFF data production by GDAL
		fails.
*/
JP2_Box* JP2_GML
	(unsigned int image_width = 0, unsigned int image_height = 0) const;

/*==============================================================================
	Helpers
*/
/**	Try to match a name against an alias list.

	The name is first uppercased, spaces are replaced with underbars,
	then compared against each name in the alias list in uppercase form.
	If this fails the comparison is then made against each alias in
	uppercase form with any underbar characters removed. Note that the
	name matching is case insensitive. <b>N.B.</b>: Alias names
	containing any space characters will never be matched; don't use
	space characters in alias names.

	@param	name	The name to be checked.
	@param	aliases	The NULL-terminated list of alias names.
	@return	true if a match was found; false otherwise.
*/
static bool named_in_list (std::string name, const char* const* aliases);

/**	Get the projection type code for a projection name.

	The {@link #Projection_Definitions list of known projection
	definitions} is searched for a projection name alias that {@link
	named_in_list(std::string, const char* const*) matches} the specified
	projection name.

	@param	projection_name	The projection name to match against a
		Projection_Definition aliases list.
	@return	The Projection_Type code for the matching Projection_Definition,
		or UNKNOWN_PROJECTION if no match could be found.
*/
static Projection_Type projection_type (const std::string& projection_name);

/*==============================================================================
	Data Members:
*/
protected:

/**	The projection name specified in the PDS label.

	@see	projection_name()
*/
std::string
	Projection_Name;

/**	The projection type matching the projection name.

	@see	projection_type()
*/
Projection_Type
	Projection_Type_Code;

/**	The spatial reference object.

	@see	initialize_spatial_reference()
*/
OGRSpatialReference
	*Spatial_Reference;

/**	The geo-transform array.

	@see	initialize_geo_transform()
*/
double
	Geo_Transform[6];

};	//	End class PDS_Projection_Data

}	//	namespace HiRISE
}	//	namespace UA
#endif
