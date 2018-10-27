/*	PDS_Projection_Data

HiROC CVS ID: PDS_Projection_Data.cc,v 1.28 2015/09/17 20:05:35 guym Exp

Copyright (C) 2007 Arizona Board of Regents on behalf of the
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

#include	"PDS_Projection_Data.hh"

#include	"gdal.h"

#include "PVL.hh"
using idaeim::PVL::Parameter;

#include	<string>
using std::string;
#include	<sstream>
using std::ostringstream;
#include	<stdexcept>
using std::logic_error;
#include	<iomanip>
using std::endl;
using std::showpoint;
using std::setprecision;
#include	<cmath>
using std::abs;


#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			-1
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_ACCESSORS		(1 << 1)
#define DEBUG_XML			(1 << 2)
#define DEBUG_MANIPULATORS	(1 << 3)
#define DEBUG_HELPERS		(1 << 3)
#include	<iostream>
using std::clog;
using std::boolalpha;
using std::dec;
using std::hex;
using std::setw;
using std::setfill;
using std::fixed;
#endif  // DEBUG


//	GDAL C functions that are not declared in a header file!
extern "C"
{
CPLErr GTIFMemBufFromWkt
	(
	const char*		WKT, 
	const double*	geo_transform,
	int				GCPList_size,
	const GDAL_GCP*	GCPList,
	int*			pointer_to_returned_size,
	unsigned char**	pointer_to_returned_data_buffer
	);

#if ((DEBUG) & DEBUG_ACCESSORS)
CPLErr GTIFWktFromMemBuf
	(
	int				count,
	unsigned char*	data_buffer, 
	char**			WKT,
	double*			geo_transform,
	int*			pointer_to_GCPList_size,
	GDAL_GCP**		pointer_to_GCPList
	);
#endif
}


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	PDS_Data
*/
/*==============================================================================
	Constants:
*/
const char* const
	PDS_Projection_Data::ID =
		"UA::HiRISE::PDS_Projection_Data (1.28 2015/09/17 20:05:35)";

const char
	*PDS_Projection_Data::PLANET_PARAMETER_NAME
		= "TARGET_NAME",
	*PDS_Projection_Data::IMAGE_MAP_PROJECTION_GROUP_NAME
		= "IMAGE_MAP_PROJECTION",
	*PDS_Projection_Data::PROJECTION_TYPE_PARAMETER_NAME
		= "MAP_PROJECTION_TYPE",
	*PDS_Projection_Data::COORDINATE_SYSTEM_PARAMETER_NAME
		= "COORDINATE_SYSTEM_NAME",
	*PDS_Projection_Data::LATITUDE_TYPE_PARAMETER_NAME
		= "PROJECTION_LATITUDE_TYPE",
	*PDS_Projection_Data::HORIZONATAL_OFFSET_PARAMETER_NAME
		= "SAMPLE_PROJECTION_OFFSET",
	*PDS_Projection_Data::VERTICAL_OFFSET_PARAMETER_NAME
		= "LINE_PROJECTION_OFFSET",
	*PDS_Projection_Data::IMAGE_HEIGHT_PARAMETER_NAME
		= "LINE_LAST_PIXEL",
	*PDS_Projection_Data::IMAGE_WIDTH_PARAMETER_NAME
		= "SAMPLE_LAST_PIXEL",
	*PDS_Projection_Data::PIXELS_PER_DEGREE_PARAMETER_NAME
		= "MAP_RESOLUTION",
	*PDS_Projection_Data::PIXEL_SIZE_PARAMETER_NAME
		= "MAP_SCALE",
	*PDS_Projection_Data::SEMI_MAJOR_RADIUS_PARAMETER_NAME
		= "A_AXIS_RADIUS",
	*PDS_Projection_Data::SEMI_MINOR_RADIUS_PARAMETER_NAME
		= "C_AXIS_RADIUS",
	*PDS_Projection_Data::FIRST_STANDARD_PARALLEL_PARAMETER_NAME
		= "FIRST_STANDARD_PARALLEL",
	*PDS_Projection_Data::SECOND_STANDARD_PARALLEL_PARAMETER_NAME
		= "SECOND_STANDARD_PARALLEL",
	*PDS_Projection_Data::MINIMUM_LATITUDE_PARAMETER_NAME
		= "MINIMUM_LATITUDE",
	*PDS_Projection_Data::CENTER_LATITUDE_PARAMETER_NAME
		= "CENTER_LATITUDE",
	*PDS_Projection_Data::MAXIMUM_LATITUDE_PARAMETER_NAME
		= "MAXIMUM_LATITUDE",
	*PDS_Projection_Data::MINIMUM_LONGITUDE_PARAMETER_NAME
		= "WESTERNMOST_LONGITUDE",
	*PDS_Projection_Data::CENTER_LONGITUDE_PARAMETER_NAME
		= "CENTER_LONGITUDE",
	*PDS_Projection_Data::MAXIMUM_LONGITUDE_PARAMETER_NAME
		= "EASTERNMOST_LONGITUDE",
	*PDS_Projection_Data::PROJECTION_ROTATION_PARAMETER_NAME
		= "MAP_PROJECTION_ROTATION";

// latitude of origin = The latitude value that defines the origin of the y-coordinate values for a projection
// standard parallel = The line of latitude in a conic or cylindrical projection in normal aspect where the projection surface touches the globe.

const PDS_Projection_Data::Projection_Definition
	PDS_Projection_Data::Projection_Definitions[TOTAL_PROJECTION_TYPES] =
	{
	//	Well known projections:
	{
	EQUIRECTANGULAR,
	//	Aliases.
		{
		SRS_PT_EQUIRECTANGULAR,
		"EQUIRECTANGULAR_CYLINDRICAL",
		"EQUIDISTANT",
		"EQUIDISTANT_CYLINDRICAL",
		"SIMPLE_CYLINDRICAL",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_STANDARD_PARALLEL_1,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_LATITUDE_OF_ORIGIN,		0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	POLAR_STEREOGRAPHIC,
	//	Aliases.
		{
		SRS_PT_POLAR_STEREOGRAPHIC,
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_ORIGIN,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_STANDARD_PARALLEL_1,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_SCALE_FACTOR,			1.0},
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	//	Alphabetically listed projections:
	{
	ALBERS,
	//	Aliases.
		{
		SRS_PT_ALBERS_CONIC_EQUAL_AREA,
		"ALBERS_EQUAL-AREA_CONIC",
		"ALBERS_EQUAL_AREA_CONIC",
		"ALBERS",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_STANDARD_PARALLEL_1,	FIRST_STANDARD_PARALLEL_PARAMETER_NAME},
		{SRS_PP_STANDARD_PARALLEL_2,	SECOND_STANDARD_PARALLEL_PARAMETER_NAME},
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_LONGITUDE_OF_CENTER,	CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	BONNE,
	//	Aliases.
		{
		SRS_PT_BONNE,
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_STANDARD_PARALLEL_1,	FIRST_STANDARD_PARALLEL_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	CYLINDRICAL_EQUAL_AREA,
	//	Aliases.
		{
		SRS_PT_CYLINDRICAL_EQUAL_AREA,
		"NORMAL_AUTHALIC_CYLINDRICAL",
		"LAMBERT_CYLINDRICAL_EQUAL_AREA",
		"BEHRMANN",
		"GALL_ORTHOGRAPHIC",
		"PETERS",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_STANDARD_PARALLEL_1,	FIRST_STANDARD_PARALLEL_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	GNOMONIC,
	//	Aliases.
		{
		SRS_PT_GNOMONIC,
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	LAMBERT_AZIMUTHAL_EQUAL_AREA,
	//	Aliases.
		{
		SRS_PT_LAMBERT_AZIMUTHAL_EQUAL_AREA,
		"LAMBERT_AZIMUTHAL",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_LONGITUDE_OF_CENTER,	CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	LAMBERT_CONFORMAL_CONIC,
	//	Aliases.
		{
		SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP,
		"LAMBERT_CONFORMAL_CONIC",
		"LAMBERT_CONIC_CONFORMAL",
		"LAMBERT_CONFORMAL",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_STANDARD_PARALLEL_1,	FIRST_STANDARD_PARALLEL_PARAMETER_NAME},
		{SRS_PP_STANDARD_PARALLEL_2,	SECOND_STANDARD_PARALLEL_PARAMETER_NAME},
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	MERCATOR,
	//	Aliases.
		{
		SRS_PT_MERCATOR_1SP,
		"MERCATOR",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_SCALE_FACTOR,			1.0},
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	MOLLWEIDE,
	//	Aliases.
		{
		SRS_PT_MOLLWEIDE,
		"HORNOLOGRAPHIC",
		"HORNALOGRAPHIC",
		"BABINET",
		"ELLIPTICAL",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	OBLIQUE_CYLINDRICAL,
	//	Aliases.
		{
		SRS_PT_SWISS_OBLIQUE_CYLINDRICAL,
		"OBLIQUE_CYLINDRICAL",
		"SWISS_OBLIQUE_MERCATOR",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	ORTHOGRAPHIC,
	//	Aliases.
		{
		SRS_PT_ORTHOGRAPHIC,
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	SINUSOIDAL,
	//	Aliases.
		{
		SRS_PT_SINUSOIDAL,
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LONGITUDE_OF_CENTER,	CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	STEREOGRAPHIC,
	//	Aliases.
		{
		SRS_PT_STEREOGRAPHIC,
		NULL
		},
	//	Required parameters.
		{
//		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_SCALE_FACTOR,			1.0},
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	TRANSVERSE_MERCATOR,
	//	Aliases.
		{
		SRS_PT_TRANSVERSE_MERCATOR,
		"GAUSS-KRUGER",
		"GAUSS_KRUGER",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_LATITUDE_OF_CENTER,		CENTER_LATITUDE_PARAMETER_NAME},
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_SCALE_FACTOR,			1.0},
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	},
	{
	VANDERGRINTEN,
	//	Aliases.
		{
		SRS_PT_VANDERGRINTEN,
		"VAN_DER_GRINTEN",
		NULL
		},
	//	Required parameters.
		{
		{SRS_PP_CENTRAL_MERIDIAN,		CENTER_LONGITUDE_PARAMETER_NAME},
		{NULL}
		},
	//	Default parameters.
		{
		{SRS_PP_FALSE_EASTING,			0.0},
		{SRS_PP_FALSE_NORTHING,			0.0},
		{NULL}
		}
	}
	};

const double
	PDS_Projection_Data::DEFAULT_GEO_TIFF_TRANSFORM[6] =
		{0.0, 1.0, 0.0, 0.0, 0.0, 1.0};

const unsigned char
	PDS_Projection_Data::GEO_TIFF_UUID[16] =
		{
		0xb1, 0x4b, 0xf8, 0xbd, 0x08, 0x3d, 0x4b, 0x43,
		0xa5, 0xae, 0x8c, 0xd7, 0xd5, 0xa6, 0xce, 0x03
		}; 

/*==============================================================================
	Constructors
*/
PDS_Projection_Data::PDS_Projection_Data ()
	:	PDS_Data (),
		Projection_Name (),
		Projection_Type_Code (UNKNOWN_PROJECTION),
		Spatial_Reference (NULL)
{
memcpy (Geo_Transform, DEFAULT_GEO_TIFF_TRANSFORM,
	sizeof (DEFAULT_GEO_TIFF_TRANSFORM));
}


PDS_Projection_Data::PDS_Projection_Data
	(
	const PDS_Data&		PDS_data
	)
	:	PDS_Data (PDS_data),
		Projection_Name (),
		Projection_Type_Code (UNKNOWN_PROJECTION),
		Spatial_Reference (NULL)
{
initialize_geo_transform ();
initialize_spatial_reference ();
}


PDS_Projection_Data::PDS_Projection_Data
	(
	const std::string&	pathname
	)
	:	PDS_Data (pathname),
		Projection_Name (),
		Projection_Type_Code (UNKNOWN_PROJECTION),
		Spatial_Reference (NULL)
{
initialize_geo_transform ();
initialize_spatial_reference ();
}


//	Destructor.
PDS_Projection_Data::~PDS_Projection_Data()
{
delete Spatial_Reference;
}

/*==============================================================================
	Accessors
*/
PDS_Data&
PDS_Projection_Data::parameters
	(
	const std::string&	pathname
	)
{
//	Ingest the parameters.
PDS_Data::parameters (pathname);

//	Initialize the projection information.
initialize_geo_transform ();
initialize_spatial_reference ();
return *this;
}


PDS_Data&
PDS_Projection_Data::parameters
	(
	const idaeim::PVL::Aggregate&	params
	)
{
//	Ingest the parameters.
PDS_Data::parameters (params);

//	Initialize the projection information.
initialize_geo_transform ();
initialize_spatial_reference ();
return *this;
}

/*==============================================================================
	Manipulators
*/
PDS_Projection_Data&
PDS_Projection_Data::initialize_geo_transform ()
{
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << ">>> PDS_Projection_Data::initialize_geo_transform" << endl;
#endif
Parameter
	*parameter;

//	Path to the projection parameters.
string
	path_to;
if ((parameter = find_parameter (IMAGE_MAP_PROJECTION_GROUP_NAME)) &&
	 parameter->is_Aggregate ())
	path_to =
		(string)IMAGE_MAP_PROJECTION_GROUP_NAME + Parameter::path_delimiter ();

//	Test for non-zero projection rotation.
try
	{
	if (numeric_value (path_to + PROJECTION_ROTATION_PARAMETER_NAME) != 0.0)
		{
		ostringstream
			message;
		message << ID << endl
				<< (path_to + PROJECTION_ROTATION_PARAMETER_NAME) << " = "
					<< numeric_value
						(path_to + PROJECTION_ROTATION_PARAMETER_NAME) << endl
				<< "Projection rotation is not supported.";
		throw logic_error (message.str ());
		}
	}
catch (idaeim::Exception& except) {}

if (find_parameter (path_to + PIXEL_SIZE_PARAMETER_NAME) ||
	find_parameter (path_to + HORIZONATAL_OFFSET_PARAMETER_NAME) ||
	find_parameter (path_to + VERTICAL_OFFSET_PARAMETER_NAME))
	{
	try
		{
		/*	Pixel size, in meters.

			The PDS Data Dictionary specifies that the units for the
			pixel size (MAP_SCALE) parameter are KM/PIX. However, for
			some data products (e.g. HiRISE) the pixel size is measured
			in meters. The only way to distinguish which units apply is
			to examine the units string associated with the value. However,
			if the value has no units string it must be assumed that the
			PDS Data Dictionary units are in effect.
		*/
		Geo_Transform[1] =
			numeric_value (path_to + PIXEL_SIZE_PARAMETER_NAME);
		string
			units (find_parameter (path_to + PIXEL_SIZE_PARAMETER_NAME)
				->value ().units ());
		if (units.empty () ||
			to_uppercase (units).find ('K') != string::npos)
			Geo_Transform[1] *= 1000.0;

		/*	Note:

			The pixel vertical (y) dimension is negative because the
			geographic coordinate system uses a right-handed coordinate
			system with the origin at the upper-left pixel. With the
			x-axis positive to the right from the origin, the y-axis
			positive is upwards from the origin and thus negative
			downwards (increasing row numbers).
		*/
		Geo_Transform[5] =
			-Geo_Transform[1];

		/*	Note:

			The value of the offset parameter values are in the
			left-handed image coordinate space with the horizontal
			x-axis positive to the right from the origin and the
			vertical y-axis positive downwards from the origin. The
			offset values are the location of the projection origin
			(CENTER_{LONGITUDE,LATITUDE}) relative to the image origin.

			WARNING: Different PDS data products set the image origin
			differently: Some use the upper left corner of the upper
			left pixel, while others use the center of the upper left
			pixel. Also, the PDS image origin is 1,1 while the
			conventional origin is (0,0). This implementation adjusts
			the PDS offset values to the pixel center and conventional origin.
		*/
		Geo_Transform[0] =
			-((numeric_value (path_to + HORIZONATAL_OFFSET_PARAMETER_NAME) - 0.5)
			* Geo_Transform[1]);

		Geo_Transform[3] =
			-((numeric_value (path_to + VERTICAL_OFFSET_PARAMETER_NAME) - 0.5)
			* Geo_Transform[5]);

		Geo_Transform[2] = 0.0;
		Geo_Transform[4] = 0.0;
		#if ((DEBUG) & DEBUG_MANIPULATORS)
		clog << showpoint << fixed
			 << "    " << path_to << PIXEL_SIZE_PARAMETER_NAME << " = "
				<< numeric_value (path_to + PIXEL_SIZE_PARAMETER_NAME) << endl
			 << "    " << path_to << HORIZONATAL_OFFSET_PARAMETER_NAME << " = "
			 	<< numeric_value (path_to + HORIZONATAL_OFFSET_PARAMETER_NAME) << endl
			 << "    " << path_to << VERTICAL_OFFSET_PARAMETER_NAME << " = "
			 	<< numeric_value (path_to + VERTICAL_OFFSET_PARAMETER_NAME) << endl
			 << "    Geo_Transform = [";
		for (int
				index = 0;
				index < 6;
				index++)
			{
			if (index)
				clog << ", ";
			clog << Geo_Transform[index];
			}
		clog << ']' << endl;
		#endif
		}
	catch (idaeim::Exception& except)
		{
		//	Set the default values.
		memcpy (Geo_Transform, DEFAULT_GEO_TIFF_TRANSFORM,
			sizeof (DEFAULT_GEO_TIFF_TRANSFORM));

		ostringstream
			message;
		message << ID << endl
				<< except.message () << endl
				<< "While setting the Geo_TIFF transform values.";
		except.message (message.str ());
		throw;
		}
	}
else
	//	Set the default values.
	memcpy (Geo_Transform, DEFAULT_GEO_TIFF_TRANSFORM,
		sizeof (DEFAULT_GEO_TIFF_TRANSFORM));

#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "<<< PDS_Projection_Data::initialize_geo_transform" << endl;
#endif
return *this;
}


PDS_Projection_Data&
PDS_Projection_Data::initialize_spatial_reference ()
{
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << ">>> PDS_Projection_Data::initialize_spatial_reference" << endl;
#endif
//	Initialize the data members to unset state.
Projection_Name.erase ();
Projection_Type_Code = UNKNOWN_PROJECTION;
delete Spatial_Reference;
Spatial_Reference = NULL;

Parameter
	*parameter;
double
	value;

//	Path to the projection parameters.
string
	path_to;
if ((parameter = find_parameter (IMAGE_MAP_PROJECTION_GROUP_NAME)) &&
	 parameter->is_Aggregate ())
	path_to =
		(string)IMAGE_MAP_PROJECTION_GROUP_NAME + Parameter::path_delimiter ();

//	Get the projection name.
Projection_Name = string_value (path_to + PROJECTION_TYPE_PARAMETER_NAME);
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    " << path_to << PROJECTION_TYPE_PARAMETER_NAME << " = "
		<< Projection_Name << endl;
#endif

//	Get the known projection type.
if ((Projection_Type_Code = projection_type (Projection_Name))
		== UNKNOWN_PROJECTION)
	{
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "<<< PDS_Projection_Data::initialize_spatial_reference: Unknown projection" << endl;
	#endif
	return *this;
	}
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    Projection_Type_Code = " << Projection_Type_Code << endl;
#endif

//	Use the projection description to set the spatial reference parameters.
const Projection_Definition
	*projection_definition =
		&Projection_Definitions[Projection_Type_Code];
OGRSpatialReference
	*spatial_reference = new OGRSpatialReference ();
OGRErr
	error_code;

//	Projection name:
if ((error_code = spatial_reference->SetProjection
			(projection_definition->Aliases[0]))
		!= OGRERR_NONE)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Failed to set the " << Projection_Name;
	if (Projection_Name != projection_definition->Aliases[0])
		message << " (" << projection_definition->Aliases[0] << ')';
	message << " projection." << endl
			<< "OGRSpatialReference error code " << error_code << '.';
	delete spatial_reference;
	throw logic_error (message.str ());
	}

//	Required parameters:
for (const Projection_Definition::Required_Projection_Parameter
		*required_parameter =
			projection_definition->Required_Parameters;
		required_parameter->SRS_Parameter_Name != NULL &&
		required_parameter->PDS_Parameter_Name != NULL;
		required_parameter++)
	{
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "    Required parameter "
			<< (path_to + required_parameter->PDS_Parameter_Name) << endl;
	#endif
	try {value = numeric_value (path_to +
			required_parameter->PDS_Parameter_Name);}
	catch (idaeim::Exception& except)
		{
		ostringstream
			message;
		message << except.message () << endl
				<< ID << endl
				<< "For the " << Projection_Name;
		if (Projection_Name != projection_definition->Aliases[0])
			message << " (" << projection_definition->Aliases[0] << ')';
		message << " projection.";
		except.message (message.str ());
		delete spatial_reference;
		throw;
		}
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "      " << required_parameter->SRS_Parameter_Name
			<< " = " << value << endl;
	#endif
	if ((error_code = spatial_reference->SetNormProjParm
				(required_parameter->SRS_Parameter_Name, value))
			!= OGRERR_NONE)
		{
		ostringstream
			message;
		message << ID << endl
				<< "Failed to set the "
					<< required_parameter->SRS_Parameter_Name << " ("
					<< path_to << required_parameter->PDS_Parameter_Name
					<< ") parameter" << endl
				<< "to the " << value << " value" << endl
				<< "for the " << Projection_Name;
		if (Projection_Name != projection_definition->Aliases[0])
			message << " (" << projection_definition->Aliases[0] << ')';
		message << " projection." << endl
				<< "OGRSpatialReference error code " << error_code << '.';
		delete spatial_reference;
		throw logic_error (message.str ());
		}
	}

//	Default parameters:
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    Default parameters -" << endl;
#endif
for (const Projection_Definition::Default_Projection_Parameter
		*default_parameter =
			projection_definition->Default_Parameters;
		default_parameter->SRS_Parameter_Name != NULL;
		default_parameter++)
	{
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "      " << default_parameter->SRS_Parameter_Name
			<< " = " << default_parameter->Value << endl;
	#endif
	if ((error_code = spatial_reference->SetNormProjParm
				(default_parameter->SRS_Parameter_Name,
				 default_parameter->Value))
			!= OGRERR_NONE)
		{
		ostringstream
			message;
		message << ID << endl
				<< "Failed to set the "
					<< default_parameter->SRS_Parameter_Name
					<< " parameter" << endl
				<< "to the " << default_parameter->Value << " value" << endl
				<< "for the " << Projection_Name;
		if (Projection_Name != projection_definition->Aliases[0])
			message << " (" << projection_definition->Aliases[0] << ')';
		message << " projection." << endl
				<< "OGRSpatialReference error code " << error_code << '.';
		delete spatial_reference;
		throw logic_error (message.str ());
		}
	}

//	Geographic coordinate system settings:

//	Get the planet name.
string
	planet_name;
try {planet_name = string_value (PLANET_PARAMETER_NAME);}
catch (idaeim::Exception& except)
	{planet_name = "Unknown";}
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    " << PLANET_PARAMETER_NAME << " = " << planet_name << endl;
#endif

//	Set the projection coordinate system name.
string
	coordinate_system_name =
		(string)(projection_definition->Aliases[0]) + " " + planet_name;
if ((error_code = spatial_reference->SetProjCS (coordinate_system_name.c_str ()))
		!= OGRERR_NONE)
	{
	//	This error should never happen.
	ostringstream
		message;
	message << ID << endl
			<< "Failed to set the projection coordinate system name to \""
				<< coordinate_system_name << '"' << endl
			<< "for the " << Projection_Name;
	if (Projection_Name != projection_definition->Aliases[0])
		message << " (" << projection_definition->Aliases[0] << ')';
	message << " projection." << endl
			<< "OGRSpatialReference error code " << error_code << '.';
	delete spatial_reference;
	throw logic_error (message.str ());
	}

bool
	geographic = true;
if (Projection_Type_Code == EQUIRECTANGULAR ||
	Projection_Type_Code == ORTHOGRAPHIC ||
	Projection_Type_Code == SINUSOIDAL)
	geographic = false;
else
if (((parameter = find_parameter (path_to + COORDINATE_SYSTEM_PARAMETER_NAME)) ||
	 (parameter = find_parameter (path_to + LATITUDE_TYPE_PARAMETER_NAME))) &&
	parameter->value ().is_String () &&
	to_uppercase ((string)parameter->value ()) == "PLANETOCENTRIC")
	geographic = false;

#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    Geographic coordinate system: " << boolalpha << geographic << endl;
if (parameter)
	clog << "    " << *parameter;
clog << "    axis_radius" << endl;
#endif

//	Planet axis radius and inverse flattening.
double
	axis_radius,
	inverse_flattening = 0.0;

if (! geographic &&
	(Projection_Type_Code == POLAR_STEREOGRAPHIC ||
	(Projection_Type_Code == STEREOGRAPHIC &&
		abs (numeric_value (path_to + CENTER_LATITUDE_PARAMETER_NAME)) == 90.0)))
	{
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "      from "
			<< (path_to + SEMI_MINOR_RADIUS_PARAMETER_NAME) << endl;
	#endif
	try {axis_radius = numeric_value (path_to +
			SEMI_MINOR_RADIUS_PARAMETER_NAME);}
	catch (idaeim::Exception& except)
		{
		ostringstream
			message;
		message << except.message () << endl
				<< ID << endl
				<< "For the " << Projection_Name;
		if (Projection_Name != projection_definition->Aliases[0])
			message << " (" << projection_definition->Aliases[0] << ')';
		message << " projection.";
		except.message (message.str ());
		delete spatial_reference;
		throw;
		}
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "      = " << axis_radius << endl;
	#endif
	}
else
	{
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "      from "
			<< (path_to + SEMI_MAJOR_RADIUS_PARAMETER_NAME) << endl;
	#endif
	try {axis_radius = numeric_value (path_to +
			SEMI_MAJOR_RADIUS_PARAMETER_NAME);}
	catch (idaeim::Exception& except)
		{
		ostringstream
			message;
		message << except.message () << endl
				<< ID << endl
				<< "For the " << Projection_Name;
		if (Projection_Name != projection_definition->Aliases[0])
			message << " (" << projection_definition->Aliases[0] << ')';
		message << " projection.";
		except.message (message.str ());
		delete spatial_reference;
		throw;
		}
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "      = " << axis_radius << endl;
	#endif
	if (geographic)
		{
		#if ((DEBUG) & DEBUG_MANIPULATORS)
		clog << "      semi-minor axis "
				<< (path_to + SEMI_MINOR_RADIUS_PARAMETER_NAME) << endl;
		#endif
		try {value = numeric_value (path_to +
				SEMI_MINOR_RADIUS_PARAMETER_NAME);}
		catch (idaeim::Exception& except)
			{
			ostringstream
				message;
			message << except.message () << endl
					<< ID << endl
					<< "For the " << Projection_Name;
			if (Projection_Name != projection_definition->Aliases[0])
				message << " (" << projection_definition->Aliases[0] << ')';
			message << " projection.";
			except.message (message.str ());
			delete spatial_reference;
			throw;
			}
		#if ((DEBUG) & DEBUG_MANIPULATORS)
		clog << "      = " << value << endl;
		#endif
		if ((value -= axis_radius) > 0.00000001)
			inverse_flattening = axis_radius / value;
		}
	}
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    inverse_flattening = " << inverse_flattening << endl;
#endif

//	Set the geographic and datum names.
string
	geographic_name = "GCS_" + planet_name,
	datum_name = "D_" + planet_name;

//	Special case qualified planet name!
if (Projection_Type_Code == EQUIRECTANGULAR)
	planet_name += "_localRadius";
if (Projection_Type_Code == POLAR_STEREOGRAPHIC &&
	! geographic)
	planet_name += "_polarRadius";

#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "    geographic_name - " << geographic_name << endl
	 << "         datum_name - " << datum_name << endl
	 << "        planet_name - " << planet_name << endl;
#endif
if ((error_code = spatial_reference->SetGeogCS
		(geographic_name.c_str (), datum_name.c_str (), planet_name.c_str (),
		axis_radius * 1000.0, inverse_flattening, "Reference_Meridian", 0.0))
		!= OGRERR_NONE)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Failed to set the geographic coordinate system" << endl
			<< "for the " << Projection_Name;
	if (Projection_Name != projection_definition->Aliases[0])
		message << " (" << projection_definition->Aliases[0] << ')';
	message << " projection." << endl
			<< "OGRSpatialReference error code " << error_code << '.';
	delete spatial_reference;
	throw logic_error (message.str ());
	}

//	OK!
Spatial_Reference = spatial_reference;
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "<<< PDS_Projection_Data::initialize_spatial_reference" << endl;
#endif
return *this;
}

/*==============================================================================
	JP2 Boxes
*/
#if DEBUG
#ifndef DOXYGEN_PROCESSING
namespace
{
void
print_bytes
	(
	unsigned int			amount,
	const unsigned char*	characters
	)
{
clog << setfill ('0') << hex;
for (unsigned int
		index = 0;
		index < amount;
		index++)
	{
	if (index & 1)
		clog << ' ';
	if (characters[index] < 33 ||
		characters[index] > 126)
		clog << "0x" << setw (2) << ((int)characters[index] & 0xFF);
	else
		clog << "   " << (char)characters[index];
	if (index & 1)
		clog << endl;
	}
if (amount & 1)
	clog << endl;
clog << setfill (' ') << dec;
}

}
#endif
#endif


/*	Based on the GDALJP2Metadata::CreateJP2GeoTIFF method.
*/
JP2_Box*
PDS_Projection_Data::JP2_GeoTIFF () const
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">>> PDS_Projection_Data::JP2_GeoTIFF" << endl;
#endif
JP2_Box
	*box = NULL;
if (Spatial_Reference)
	{
	//	Initialize the box with the GeoTIFF UUID content.
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << "    Constructing JP2_Box with GeoTIFF UUID -"
			<< setfill ('0') << hex << endl;
	for (unsigned int
			index = 0;
			index < sizeof (GEO_TIFF_UUID);
			index++)
		{
		if (index)
			clog << ", ";
		clog << "0x" << setw (2) << ((int)GEO_TIFF_UUID[index] & 0xFF);
		}
	clog << setfill (' ') << dec << endl;
	#endif
	box = new JP2_Box (JP2_Box::UUID_BOX_TYPE,
			GEO_TIFF_UUID, sizeof (GEO_TIFF_UUID));
	
	//	Convert the Spatial Reference to its Well-Known-Text representation.
	char
		*SRS_WKT = NULL;
	Spatial_Reference->exportToWkt (&SRS_WKT);
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << "    Spatial_Reference Well-Known-Text -" << endl
		 << SRS_WKT << endl;
	#endif

	//	Generate box content.
	int
		amount = 0;
	unsigned char
		*data = NULL;
	if (GTIFMemBufFromWkt (SRS_WKT, Geo_Transform, 0, NULL,
			&amount, &data) == CE_None &&
		amount)
		{
		//	Append the GeoTIFF data to the UUID in the box content.
		#if ((DEBUG) & DEBUG_ACCESSORS)
		clog << "    GeoTIFF data, " << amount << " bytes -" << endl;
		print_bytes (amount, data);
		clog << endl;

		double
			transform[6];
		int
			count;
		GDAL_GCP
			*GCPList = NULL;
		if (GTIFWktFromMemBuf (amount, data, &SRS_WKT, transform,
				&count, &GCPList) == CE_None)
			{
			clog << "    GeoTIFF data interpreted." << endl
				 << "      Spatial_Reference Well-Known-Text -" << endl
				 << (SRS_WKT ? SRS_WKT : "NULL") << endl
				 << "      Geo_Transform = [";
			for (int
					index = 0;
					index < 6;
					index++)
				{
				if (index)
					clog << ", ";
				clog <<transform[index];
				}
			clog << ']' << endl;
			}
		else
			clog << "    GeoTIFF data not interpreted." << endl;
		#endif
		box->append_content (data, amount);

		//	Delete the intermediate data.
		delete SRS_WKT;
		delete data;
		}
	else
		{
		ostringstream
			message;
		message << ID << endl
				<< "Unable to obtain the GeoTIFF data" << endl
				<< "from the spatial reference well-known-text -" << endl
				<< SRS_WKT;
		delete SRS_WKT;
		throw logic_error (message.str ());
		}
	}
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << "<<< PDS_Projection_Data::JP2_GeoTIFF" << endl;
#endif
return box;
}


/*	Based on the GDALJP2Metadata::CreateGMLJP2 method.
*/
JP2_Box*
PDS_Projection_Data::JP2_GML
	(
	unsigned int	image_width,
	unsigned int	image_height
	)
	const
{
if (! Spatial_Reference)
	return NULL;
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">>> PDS_Projection_Data::JP2_GML: "
		<< image_width << "w, "<< image_height << 'h' << endl;
#endif

if (! image_width ||
	! image_height)
	{
	try
		{
		image_width  = (unsigned int)numeric_value (IMAGE_WIDTH_PARAMETER_NAME);
		image_height = (unsigned int)numeric_value (IMAGE_HEIGHT_PARAMETER_NAME);
		}
	catch (idaeim::Exception& except)
		{
		ostringstream
			message;
		message << except.message () << endl
				<< ID << endl
				<< "While getting the image size for the JP2 GML definition.";
		except.message (message.str ());
		throw;
		}
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << "    Image width from " << IMAGE_WIDTH_PARAMETER_NAME
			<< " = " << image_width << endl
		 << "    Image height from " << IMAGE_HEIGHT_PARAMETER_NAME
			<< " = " << image_height << endl;
	#endif
	}

//	Minimal instance format.
ostringstream
	XML_document;
XML_document
	<< "<gml:FeatureCollection" << endl
	<< "   xmlns:gml=\"http://www.opengis.net/gml\"" << endl
	<< "   xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl
	<< "   xsi:schemaLocation=\""
		<< "http://www.opengeospatial.net/gml "
		<< "http://schemas.opengis.net/gml/"
			<< "3.1.1/profiles/gmlJP2Profile/1.0.0/gmlJP2Profile.xsd\">" << endl
	<< "  <gml:boundedBy>" << endl
	<< "    <gml:Null>withheld</gml:Null>" << endl
	<< "  </gml:boundedBy>" << endl
	<< "  <gml:featureMember>" << endl
	<< "    <gml:FeatureCollection>" << endl
	<< "      <gml:featureMember>" << endl
	<< "        <gml:RectifiedGridCoverage dimension=\"2\" "
					<< "gml:id=\"RGC0001\">" << endl
	<< "          <gml:rectifiedGridDomain>" << endl
	<< "            <gml:RectifiedGrid dimension=\"2\">" << endl
	<< "              <gml:limits>" << endl
	<< "                <gml:GridEnvelope>" << endl
	<< "                  <gml:low>0 0</gml:low>" << endl
	<< "                  <gml:high>"
							<< (image_width  - 1) << ' '
							<< (image_height - 1)
							<< "</gml:high>" << endl
	<< "                </gml:GridEnvelope>" << endl
	<< "              </gml:limits>" << endl
	<< "              <gml:axisName>x</gml:axisName>" << endl
	<< "              <gml:axisName>y</gml:axisName>" << endl
	<< "              <gml:origin>" << endl
	<< "                <gml:Point gml:id=\"P0001\" ";

//	Determine the Spatial Reference System name.
string
	SRS_name;
//	Check for a Projected or Geographic Coordinate System code name.
const char*
	EPSG_code = NULL;
if (Spatial_Reference->IsProjected ())
    {
    EPSG_code = Spatial_Reference->GetAuthorityName ("PROJCS");
    if (EPSG_code &&
		to_uppercase (EPSG_code) == "EPSG")
        EPSG_code = Spatial_Reference->GetAuthorityCode ("PROJCS");
    }
else if (Spatial_Reference->IsGeographic ())
    {
    EPSG_code = Spatial_Reference->GetAuthorityName ("GEOGCS");
    if (EPSG_code &&
		string (EPSG_code) == "epsg")
        EPSG_code = Spatial_Reference->GetAuthorityCode ("GEOGCS");
	}
if (EPSG_code)
	SRS_name = string ("urn:ogc:def:crs:EPSG::") + EPSG_code;
else
	SRS_name = "gmljp2://xml/CRSDictionary.gml#ogrcrs1";
XML_document << "srsName=\"" << SRS_name << "\">" << endl;

XML_document
	<< "                  <gml:pos>"
							<< showpoint << setprecision (15)
							<< (Geo_Transform[0]
							  + Geo_Transform[1] * 0.5
							  + Geo_Transform[4] * 0.5) << ' '
							<< (Geo_Transform[3]
							  + Geo_Transform[2] * 0.5
							  + Geo_Transform[5] * 0.5)
							<< "</gml:pos>" << endl
	<< "                </gml:Point>" << endl
	<< "              </gml:origin>" << endl
	<< "              <gml:offsetVector srsName=\"" << SRS_name << "\">"
							<< Geo_Transform[1] << ' '
							<< Geo_Transform[2]
							<< "</gml:offsetVector>" << endl
	<< "              <gml:offsetVector srsName=\"" << SRS_name << "\">"
							<< Geo_Transform[4] << ' '
							<< Geo_Transform[5]
							<< "</gml:offsetVector>" << endl
	<< "            </gml:RectifiedGrid>" << endl
	<< "          </gml:rectifiedGridDomain>" << endl
	<< "          <gml:rangeSet>" << endl
	<< "            <gml:File>" << endl
	<< "              <gml:fileName>"
						<< "gmljp2://codestream/0</gml:fileName>" << endl
	<< "              <gml:fileStructure>"
						<< "Record Interleaved</gml:fileStructure>" << endl
	<< "            </gml:File>" << endl
	<< "          </gml:rangeSet>" << endl
	<< "        </gml:RectifiedGridCoverage>" << endl
	<< "      </gml:featureMember>" << endl
	<< "    </gml:FeatureCollection>" << endl
	<< "  </gml:featureMember>" << endl
	<< "</gml:FeatureCollection>" << endl;
#if ((DEBUG) & DEBUG_XML)
clog << "    XML document, "
		<< XML_document.str ().length () << " bytes -" << endl
	 << XML_document.str ();
#endif
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << endl
	 << "    Constructing accociation JP2_Box" << endl
	 << "    to contain label and labeled XML assocation sub-boxes." << endl;
#endif
JP2_Box
	*box = new JP2_Box (JP2_Box::ASSOCIATION_BOX_TYPE);
box->add (new JP2_Box (JP2_Box::LABEL_BOX_TYPE, "gml.data"))
	.add ((new JP2_Box (JP2_Box::ASSOCIATION_BOX_TYPE))
		->add (new JP2_Box (JP2_Box::LABEL_BOX_TYPE, "gml.root-instance"))
		 .add (new JP2_Box (JP2_Box::XML_BOX_TYPE, XML_document.str ())));

if (! EPSG_code)
	{
	//	Add optional dictionary.
	char
		*XML_dictionary = NULL;
	OGRErr
		error_code;
	if ((error_code = Spatial_Reference->exportToXML (&XML_dictionary, NULL))
			!= OGRERR_NONE)
		{
		ostringstream
			message;
		message << ID << endl
				<< "Failed to obtain the GML dictionary for the "
					<< Projection_Name << " projection." << endl
				<< "OGRSpatialReference error code " << error_code << '.';
		throw logic_error (message.str ());
		}
	XML_document.str ("");
	XML_document
		<< "<gml:Dictionary gml:id=\"CRSU1\" " << endl
		<< "  xmlns:gml=\"http://www.opengis.net/gml\"" << endl
		<< "  xmlns:xlink=\"http://www.w3.org/1999/xlink\"" << endl
		<< "  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">" << endl
		<< "<gml:dictionaryEntry>" << endl
		<< XML_dictionary
		<< "</gml:dictionaryEntry>" << endl
		<< "</gml:Dictionary>" << endl;
	delete XML_dictionary;
	#if ((DEBUG) & DEBUG_XML)
	clog << "    XML dictionary, "
			<< XML_document.str ().length () << " bytes -" << endl
		 << XML_document.str ();
	#endif
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << endl
		 << "    Adding association JP2_Box with labeled XML sub-boxes." << endl;
	#endif

	box->add ((new JP2_Box (JP2_Box::ASSOCIATION_BOX_TYPE))
			->add (new JP2_Box (JP2_Box::LABEL_BOX_TYPE, "CRSDictionary.gml"))
			 .add (new JP2_Box (JP2_Box::XML_BOX_TYPE, XML_document.str ())));
    }
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << "<<< PDS_Projection_Data::JP2_GML" << endl;
#endif
return box;
}

/*==============================================================================
	Helpers
*/
#ifndef DOXYGEN_PROCESSING
namespace
{
string
uppercase
	(
	string	a_string
	)
{
string
	A_STRING (a_string);
for (string::iterator
		character = A_STRING.begin ();
		character < A_STRING.end ();
		character++)
		*character = (char)toupper (*character);
return A_STRING;
}
}
#endif


bool
PDS_Projection_Data::named_in_list
	(
	std::string			name,
	const char* const*	aliases
	)
{
#if ((DEBUG) & DEBUG_HELPERS)
clog << ">>> PDS_Projection_Data::named_in_list: " << name << endl;
#endif
for (string::iterator
		character = name.begin ();
		character < name.end ();
		character++)
	{
	if (*character == ' ')
		*character =  '_';
	else
		*character = (char)toupper (*character);
	}
#if ((DEBUG) & DEBUG_HELPERS)
clog << "    name - " << name << endl;
#endif
const char* const*
	alias = aliases;
for (alias = aliases;
	*alias;
	 alias++)
	{
	#if ((DEBUG) & DEBUG_HELPERS)
	clog << "    alias - " << *alias << endl;
	#endif
	if (name == uppercase (*alias))
		{
		#if ((DEBUG) & DEBUG_HELPERS)
		clog << "<<< PDS_Projection_Data::named_in_list: true" << endl;
		#endif
		return true;
		}
	}

bool
	check;
string
	alias_name;
for (alias = aliases;
	*alias;
	 alias++)
	{
	check = false;
	alias_name = uppercase (*alias);
	string::size_type
		index = alias_name.length ();
	while (index--)
		{
		if (alias_name[index] == '_')
			{
			alias_name.erase (index, 1);
			check = true;;
			}
		}
	#if ((DEBUG) & DEBUG_HELPERS)
	if (check)
		clog << "    modified alias - " << alias_name << endl;
	#endif
	if (check &&
		name == alias_name)
		{
		#if ((DEBUG) & DEBUG_HELPERS)
		clog << "<<< PDS_Projection_Data::named_in_list: true" << endl;
		#endif
		return true;
		}
	}
#if ((DEBUG) & DEBUG_HELPERS)
clog << "<<< PDS_Projection_Data::named_in_list: false" << endl;
#endif
return false;
}


PDS_Projection_Data::Projection_Type
PDS_Projection_Data::projection_type
	(
	const std::string&	projection_name
	)
{
const Projection_Definition
	*projection_definition = Projection_Definitions;
for (int
		projection_type = 0;
		projection_type < TOTAL_PROJECTION_TYPES;
		projection_type++,
			projection_definition++)
	if (named_in_list (projection_name, projection_definition->Aliases))
		return static_cast<Projection_Type>(projection_type);
return UNKNOWN_PROJECTION;
}


}   //  namespace HiRISE
}   //  namespace UA

