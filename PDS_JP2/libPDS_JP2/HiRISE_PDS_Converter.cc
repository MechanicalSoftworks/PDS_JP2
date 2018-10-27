/*	HiRISE_PDS_Converter

HiROC CVS ID: HiRISE_PDS_Converter.cc,v 1.21 2015/01/09 19:42:28 guym Exp

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

#include	"HiRISE_PDS_Converter.hh"

#include	"Files.hh"
using namespace PIRL;

#include	"PVL.hh"
using idaeim::PVL::Parser;
using idaeim::PVL::Parameter;
using idaeim::PVL::Aggregate;
using idaeim::PVL::Assignment;
using idaeim::PVL::Value;
using idaeim::PVL::String;
using idaeim::PVL::Integer;
using namespace idaeim;

#include	<string>
#include	<iostream>
#include	<iomanip>
#include	<fstream>
#include	<sstream>
#include	<cstring>
#include	<cstdlib>
#include	<cctype>
#include	<exception>
#include	<stdexcept>
#include	<vector>
using namespace std;


#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL				(-1)
#define DEBUG_CONSTRUCTORS		(1 << 0)
#define DEBUG_DATA_SET_VERSION	(1 << 1)
#define DEBUG_LABEL				(1 << 5)
#define	DEBUG_PROJECTION		(1 << 6)
#include	<iostream>
using std::clog;
#endif  // DEBUG


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	HiRISE_PDS_Converter
*/
/*==============================================================================
	Constants
*/
const char* const
	HiRISE_PDS_Converter::ID =
		"UA::HiRISE::HiRISE_PDS_Converter (1.21 2015/01/09 19:42:28)";

const char
	*HiRISE_PDS_Converter::PRODUCT_TYPE_PARAMETER_NAME
		= "INSTRUMENT_ID",
	*HiRISE_PDS_Converter::HIRISE_PRODUCT_TYPE
		= "HIRISE";

const char*
	HiRISE_PDS_Converter::EXCLUDED_DATA_BLOCK_NAMES[] =
		{
		"CALIBRATION_LINE_PREFIX_TABLE",
		"CALIBRATION_LINE_SUFFIX_TABLE",
		"LINE_PREFIX_TABLE",
		"LINE_SUFFIX_TABLE",
		0
		};

const char*
	HiRISE_PDS_Converter::IMAGE_DATA_BLOCK_NAMES[] =
		{
		"CALIBRATION_IMAGE",
		0
		};

const int
	HiRISE_PDS_Converter::DEFAULT_PDS_LABEL_SIZE
		= 32768;

const char*
	HiRISE_PDS_Converter::UPDATE_VERSION_PARAMETER_NAMES[] =
		{
		"DATA_SET_ID",
		"DATA_SET_NAME",
		NULL
		};
const int
	HiRISE_PDS_Converter::DATA_SET_VERSION_MINOR_VALUE
		= 1;

//	IMAGE_MAP_PROJECTION parameters to be adjusted.
const char
	*HiRISE_PDS_Converter::IMAGE_MAP_PROJECTION_GROUP_NAME
		= "IMAGE_MAP_PROJECTION",
	*HiRISE_PDS_Converter::PROJECTION_TYPE_PARAMETER_NAME
		= "MAP_PROJECTION_TYPE",
	*HiRISE_PDS_Converter::HORIZONATAL_OFFSET_PARAMETER_NAME
		= "SAMPLE_PROJECTION_OFFSET",
	*HiRISE_PDS_Converter::VERTICAL_OFFSET_PARAMETER_NAME
		= "LINE_PROJECTION_OFFSET",
	*HiRISE_PDS_Converter::IMAGE_HEIGHT_PARAMETER_NAME
		= "LINE_LAST_PIXEL",
	*HiRISE_PDS_Converter::IMAGE_WDITH_PARAMETER_NAME
		= "SAMPLE_LAST_PIXEL",
	*HiRISE_PDS_Converter::PIXELS_PER_DEGREE_PARAMETER_NAME
		= "MAP_RESOLUTION",
	*HiRISE_PDS_Converter::METERS_PER_PIXEL_PARAMETER_NAME
		= "MAP_SCALE",
	*HiRISE_PDS_Converter::MINIMUM_LATITUDE_PARAMETER_NAME
		= "MINIMUM_LATITUDE",
	*HiRISE_PDS_Converter::MAXIMUM_LATITUDE_PARAMETER_NAME
		= "MAXIMUM_LATITUDE",
	*HiRISE_PDS_Converter::EASTERN_LONGITUDE_PARAMETER_NAME
		= "EASTERNMOST_LONGITUDE",
	*HiRISE_PDS_Converter::WESTERN_LONGITUDE_PARAMETER_NAME
		= "WESTERNMOST_LONGITUDE";

/*==============================================================================
	Constructors
*/
HiRISE_PDS_Converter::HiRISE_PDS_Converter ()
{}


HiRISE_PDS_Converter::HiRISE_PDS_Converter
	(
	const std::string&	pathname,
	const char**		excluded_names,
	const char**		image_names
	)
	:	Generic_PDS_Converter (pathname,
			(excluded_names ? excluded_names : EXCLUDED_DATA_BLOCK_NAMES),
			(image_names ?    image_names    : IMAGE_DATA_BLOCK_NAMES))
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< HiRISE_PDS_Converter" << endl;
#endif
label_size (DEFAULT_PDS_LABEL_SIZE);
}

/*==============================================================================
	PDS_Converter Implementation
*/
bool
HiRISE_PDS_Converter::label_recognized () const
{
if (const_cast<HiRISE_PDS_Converter&>(*this).image_data ())
	{
	Parameter
		*parameter = const_cast<HiRISE_PDS_Converter&>(*this)
			.find_parameter (PRODUCT_TYPE_PARAMETER_NAME);
	if (parameter &&
		(string)parameter->value () == HIRISE_PRODUCT_TYPE)
		return true;
	}
return false;
}


string
HiRISE_PDS_Converter::product_names () const
{
Parameter
	*parameter = const_cast<HiRISE_PDS_Converter&>(*this)
		.find_parameter (PRODUCT_TYPE_PARAMETER_NAME);
if (parameter)
	return parameter->value ();
else
	return HIRISE_PRODUCT_TYPE;
}


void
HiRISE_PDS_Converter::write_PDS_JP2_label
	(
	const std::string&	PDS_label_pathname,
	const std::string&	JP2_pathname,
	const char**		removed_parameter_names,
	PDS_Data*			additional_parameters
	)
{
//	Copy the source label.
PDS_Data
	label_copy (*this);

//	DATA_SET_xxx version updates.
data_set_version (additional_parameters);

Generic_PDS_Converter::write_PDS_JP2_label
	(PDS_label_pathname, JP2_pathname,
	removed_parameter_names, additional_parameters);

//	Restore the original label.
parameters (label_copy);
}


void
HiRISE_PDS_Converter::write_PDS_label
	(
	const std::string&	PDS_label_pathname,
	const Rectangle*	image_region,
	unsigned int		resolution_level,
	const char**		removed_parameter_names,
	PDS_Data*			additional_parameters
	)
{
#if ((DEBUG) & DEBUG_LABEL)
clog << ">>> HiRISE_PDS_Converter::write_PDS_label:" << endl
	 << "    PDS_label_pathname - " << PDS_label_pathname << endl
	 << "    image_region - " << *image_region << endl
	 << "    resolution_level - " << resolution_level << endl;
#endif
//	Copy the source label.
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Copying the source label." << endl;
#endif
PDS_Data
	label_copy (*this);

if (! resolution_level)
	resolution_level = 1;

//	IMAGE_MAP_PROJECTION parameters.
adjust_image_map_projection (dynamic_cast<Aggregate*>
	(find_parameter (IMAGE_MAP_PROJECTION_GROUP_NAME,
		false, 0, AGGREGATE_PARAMETER)),
	*image_region, (1 << ( resolution_level - 1)));

Generic_PDS_Converter::write_PDS_label
	(PDS_label_pathname, image_region, resolution_level,
	removed_parameter_names, additional_parameters);

//	Restore the original label.
parameters (label_copy);

#if ((DEBUG) & DEBUG_LABEL)
clog << "<<< HiRISE_PDS_Converter::write_PDS_label" << endl;
#endif
}

/*==============================================================================
	Local Helper Functions
*/		
#ifndef DOXYGEN_PROCESSING
namespace
{
string&
uppercase
	(
	string&	a_string
	)
{
//	Uppercase a string in place.
for (char* character = const_cast<char*>(a_string.c_str ());
	 *character;
	 character++)
	*character = (char)toupper (*character);
return a_string;
}

}	//	local namespace.
#endif

/*==============================================================================
	Manipulators
*/
void
HiRISE_PDS_Converter::data_set_version
	(
	PDS_Data*	additional_parameters
	)
{
#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
clog << ">>> data_set_version:" << endl
	 << "    additional_parameters -";
if (additional_parameters)
	clog << endl << *additional_parameters;
else
	clog << " null" << endl;
#endif
Parameter
	*parameter = NULL;
if (! additional_parameters ||
	(parameter =
		UA::HiRISE::find_parameter
			(*additional_parameters, NO_VERSION_CHANGE_PARAMETER_NAME,
			false, 0, ASSIGNMENT_PARAMETER)) ||
	(! (parameter =
		UA::HiRISE::find_parameter
			(*additional_parameters, GeoTIFF_PARAMETER_NAME,
			false, 0, ASSIGNMENT_PARAMETER)) &&
	 ! (parameter =
		UA::HiRISE::find_parameter
			(*additional_parameters, GML_PARAMETER_NAME,
			false, 0, ASSIGNMENT_PARAMETER))))
	{
	#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
	clog << "<<< data_set_version" << endl;
	#endif
	return;
	}
string
	value;
value = to_uppercase (parameter->value ());
#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
clog << "    " << parameter->name () << " = " << value << endl;
#endif
if (value != "TRUE" &&
	value != "1")
	{
	#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
	clog << "<<< data_set_version" << endl;
	#endif
	return;
	}

for (const char**
		name = UPDATE_VERSION_PARAMETER_NAMES;
	   *name;
	  ++name)
	{
	#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
	clog << "    " << *name << endl;
	#endif
	try {value = string_value (*name);}
	catch (...) {continue;}
	#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
	clog << "    = " << value << endl;
	#endif
	string::size_type
		index;
	if ((index = value.rfind ('.')) == string::npos ||
		++index == value.length ())
		continue;
	long
		number;
	try {number = Value::string_to_integer (value.substr (index), 10);}
	catch (idaeim::Exception& except) {continue;}
	#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
	clog << "    number = " << number << endl
		 << "    DATA_SET_VERSION_MINOR_VALUE = "
		 	<< DATA_SET_VERSION_MINOR_VALUE << endl;
	#endif
	if (number < DATA_SET_VERSION_MINOR_VALUE)
		{
		ostringstream
			new_value;
		new_value << value.substr (0, index) << DATA_SET_VERSION_MINOR_VALUE;
		value = new_value.str ();
		#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
		clog << "    new value = " << value << endl;
		#endif
		parameter_value (*name, value);
		}
	}
#if ((DEBUG) & (DEBUG_LABEL | DEBUG_DATA_SET_VERSION))
clog << "<<< data_set_version" << endl;
#endif
}


void
HiRISE_PDS_Converter::adjust_image_map_projection
	(
	idaeim::PVL::Aggregate*		image_map_projection,
	const Rectangle&			image_region,
	unsigned int				ratio
	)
{
Image_Data_Block
	*image = image_data ();
if (! image_map_projection ||
	! image)
	return;
#if ((DEBUG) & (DEBUG_LABEL | DEBUG_PROJECTION))
clog << ">>> adjust_image_map_projection" << endl
	 << "    image_region: "
	 	<< image_region.X << "x, "
		<< image_region.Y << "y, "
		<< image_region.Width << "w, "
		<< image_region.Height << "h" << endl
	 << "    ratio: " << ratio << endl
	 << "    image: "
	 	<< image->image_width () << "w, "
		<< image->image_height () << "h" << endl;
#endif
if (image->image_width ()  == image_region.Width &&
	image->image_height () == image_region.Height)
	{
	#if ((DEBUG) & (DEBUG_LABEL | DEBUG_PROJECTION))
	clog << "<<< adjust_image_map_projection: No adjustment" << endl;
	#endif
	return;
	}
if (! ratio)
	ratio = 1;
#if ((DEBUG) & (DEBUG_LABEL | DEBUG_PROJECTION))
clog << endl
	 << *image_map_projection << endl;
#endif

Parameter
	*parameter;
double
	value;

//	Output image diemensions.
parameter_of (*image_map_projection,
	IMAGE_WDITH_PARAMETER_NAME)->value () = image_region.Width;
parameter_of (*image_map_projection,
	IMAGE_HEIGHT_PARAMETER_NAME)->value () = image_region.Height;

//	Projection offsets.
parameter = parameter_of (*image_map_projection,
	HORIZONATAL_OFFSET_PARAMETER_NAME);
value = parameter->value ();
value /= ratio;
value += image_region.X;
parameter->value () = value;
	
parameter = parameter_of (*image_map_projection,
	VERTICAL_OFFSET_PARAMETER_NAME);
value = parameter->value ();
value /= ratio;
value += image_region.Y;
parameter->value () = value;

//	Pixel resolution and scale.
parameter = parameter_of (*image_map_projection,
	PIXELS_PER_DEGREE_PARAMETER_NAME);
double
	resolution = parameter->value ();
if (ratio != 1)
	{
	resolution /= ratio;
	parameter->value () = resolution;

	parameter = parameter_of (*image_map_projection,
		METERS_PER_PIXEL_PARAMETER_NAME);
	value = parameter->value ();
	value *= ratio;
	parameter->value () = value;
	}

//	Lat/lon boundaries.
if (image->image_width ()  != (image_region.Width * ratio) ||
	image->image_height () != (image_region.Height * ratio))
	{
	//	The image region is not the entire image.

	parameter = parameter_of (*image_map_projection,
		PROJECTION_TYPE_PARAMETER_NAME);
	string
		projection_type = parameter->value ();
	uppercase (projection_type);
	if (projection_type.find ("STEREOGRAPHIC") != string::npos)
		{
		/*
			Polar projections require more complex remapping of
			image boundaries than is available here, so the
			mapped boundary values will be removed rather than
			risk providing unreliable values.
		*/
		if ((parameter = parameter_of (*image_map_projection,
				MINIMUM_LATITUDE_PARAMETER_NAME, false)))
			image_map_projection->remove (parameter);
		if ((parameter = parameter_of (*image_map_projection,
				MAXIMUM_LATITUDE_PARAMETER_NAME, false)))
			image_map_projection->remove (parameter);
		if ((parameter = parameter_of (*image_map_projection,
				EASTERN_LONGITUDE_PARAMETER_NAME, false)))
			image_map_projection->remove (parameter);
		if ((parameter = parameter_of (*image_map_projection,
				WESTERN_LONGITUDE_PARAMETER_NAME, false)))
			image_map_projection->remove (parameter);
		}
	else
		{
		resolution = 1.0 / resolution;	//	Post-scaling degrees per pixel.

		parameter = parameter_of (*image_map_projection,
			MAXIMUM_LATITUDE_PARAMETER_NAME);
		value = parameter->value ();
		if (image_region.Y)
			//	Different origin.
			parameter->value () = value - (resolution * image_region.Y);
		parameter_of (*image_map_projection,
			MINIMUM_LATITUDE_PARAMETER_NAME)->value ()
				= value - (resolution * image_region.Height);

		parameter = parameter_of (*image_map_projection,
			WESTERN_LONGITUDE_PARAMETER_NAME);
		value = parameter->value ();
		if (image_region.X)
			{
			//	Different origin.
			value += resolution * image_region.X;
			if (value >= 360.0)
				value -= 360.0;
			else
			if (value < 0.0)
				value += 360.0;
			parameter->value () = value;
			}
		value += resolution * image_region.Width;
		if (value >= 360.0)
			value -= 360.0;
		else
		if (value < 0.0)
			value += 360.0;
		parameter_of (*image_map_projection,
			EASTERN_LONGITUDE_PARAMETER_NAME)->value () = value;
		}
	}
#if ((DEBUG) & (DEBUG_LABEL | DEBUG_PROJECTION))
clog << "    Adjusted -" << endl
	 << *image_map_projection << endl
	 << "<<< adjust_image_map_projection" << endl;
#endif
}


}	//	namespace HiRISE
}	//	namespace UA
