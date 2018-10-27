/*	HiPrecision_PDS_Converter

HiROC CVS ID: HiPrecision_PDS_Converter.cc,v 1.2 2013/03/14 21:00:43 guym Exp

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

#include	"HiPrecision_PDS_Converter.hh"

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
	HiPrecision_PDS_Converter
*/
/*==============================================================================
	Constants
*/
const char* const
	HiPrecision_PDS_Converter::ID =
		"UA::HiRISE::HiPrecision_PDS_Converter (1.2 2013/03/14 21:00:43)";

const char
	*HiPrecision_PDS_Converter::PRODUCT_TYPE_PARAMETER_NAME
		= "INSTRUMENT_ID",
	*HiPrecision_PDS_Converter::HIPRECISION_PRODUCT_TYPE
		= "HIRISE_IDEAL_CAMERA";

const char*
	HiPrecision_PDS_Converter::EXCLUDED_DATA_BLOCK_NAMES[] =
		{
		    "INSTRUMENT_POINTING_TABLE",
		    "INSTRUMENT_POSITION_TABLE",
		    "BODY_ROTATION_TABLE",
		    "SUN_POSITION_TABLE",
		    0
		};

const char*
	HiPrecision_PDS_Converter::IMAGE_DATA_BLOCK_NAMES[] =
		{
		    "IMAGE",
		    0
		};

const int
	HiPrecision_PDS_Converter::DEFAULT_PDS_LABEL_SIZE
		= 32768;

const char*
	HiPrecision_PDS_Converter::UPDATE_VERSION_PARAMETER_NAMES[] =
		{
		"DATA_SET_ID",
		"DATA_SET_NAME",
		NULL
		};
const int
	HiPrecision_PDS_Converter::DATA_SET_VERSION_MINOR_VALUE
		= 1;

//	IMAGE parameters to be adjusted.


/*==============================================================================
	Constructors
*/
HiPrecision_PDS_Converter::HiPrecision_PDS_Converter ()
{}


HiPrecision_PDS_Converter::HiPrecision_PDS_Converter
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
clog << ">-< HiPrecision_PDS_Converter" << endl;
#endif
label_size (DEFAULT_PDS_LABEL_SIZE);
}

/*==============================================================================
	PDS_Converter Implementation
*/
bool
HiPrecision_PDS_Converter::label_recognized () const
{
if (const_cast<HiPrecision_PDS_Converter&>(*this).image_data ())
	{
	Parameter
		*parameter = const_cast<HiPrecision_PDS_Converter&>(*this)
			.find_parameter (PRODUCT_TYPE_PARAMETER_NAME);
	if (parameter &&
		(string)parameter->value () == HIPRECISION_PRODUCT_TYPE)
   {
#if ((DEBUG) & DEBUG_LABEL)
clog << ">-< Found a HiPrecision PDS label" << endl;
#endif
		return true;
   }
   else if (parameter)
   {
#if ((DEBUG) & DEBUG_LABEL)
clog << PRODUCT_TYPE_PARAMETER_NAME << " is not " << HIPRECISION_PRODUCT_TYPE << endl;
#endif
   }
   else
   {
#if ((DEBUG) & DEBUG_LABEL)
clog << PRODUCT_TYPE_PARAMETER_NAME << " was not found" << endl;
#endif
   }
	}
return false;
}


string
HiPrecision_PDS_Converter::product_names () const
{
Parameter
	*parameter = const_cast<HiPrecision_PDS_Converter&>(*this)
		.find_parameter (PRODUCT_TYPE_PARAMETER_NAME);
if (parameter)
	return parameter->value ();
else
	return HIPRECISION_PRODUCT_TYPE;
}


void
HiPrecision_PDS_Converter::write_PDS_JP2_label
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
HiPrecision_PDS_Converter::write_PDS_label
	(
	const std::string&	PDS_label_pathname,
	const Rectangle*	image_region,
	unsigned int		resolution_level,
	const char**		removed_parameter_names,
	PDS_Data*			additional_parameters
	)
{
#if ((DEBUG) & DEBUG_LABEL)
clog << ">>> HiPrecision_PDS_Converter::write_PDS_label:" << endl
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
/*
//	IMAGE_MAP_PROJECTION parameters.
adjust_image_map_projection (dynamic_cast<Aggregate*>
	(find_parameter (IMAGE_MAP_PROJECTION_GROUP_NAME,
		false, 0, AGGREGATE_PARAMETER)),
	*image_region, (1 << resolution_level));
*/
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
	Manipulators
*/
void
HiPrecision_PDS_Converter::data_set_version
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
HiPrecision_PDS_Converter::adjust_image_map_projection
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


#if ((DEBUG) & (DEBUG_LABEL | DEBUG_PROJECTION))
clog << "    Adjusted -" << endl
	 << *image_map_projection << endl
	 << "<<< adjust_image_map_projection" << endl;
#endif
}


}	//	namespace HiRISE
}	//	namespace UA
