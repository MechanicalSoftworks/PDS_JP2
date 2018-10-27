/*	Generic_PDS_Converter

HiROC CVS ID: Generic_PDS_Converter.cc,v 1.11 2009/10/01 06:05:35 castalia Exp

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

#include	"Generic_PDS_Converter.hh"

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
#define DEBUG_ALL			(-1)
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_LABEL			(1 << 5)
#define	DEBUG_PROJECTION	(1 << 6)
#define	DEBUG_TIME			(1 << 7)
#include	<iostream>
using std::clog;
#endif  // DEBUG


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	Generic_PDS_Converter
*/
/*==============================================================================
	Constants
*/
const char* const
	Generic_PDS_Converter::ID =
		"UA::HiRISE::Generic_PDS_Converter (1.11 2009/10/01 06:05:35)";

const char
	*Generic_PDS_Converter::PRODUCT_TYPE
		= "generic";

const char
	*Generic_PDS_Converter::DATA_POINTER_PARAMETER_UNITS
		= "BYTES";

const char*
	Generic_PDS_Converter::REMOVED_PDS_PARAMETER_NAMES[] =
		{
		RECORD_TYPE_PARAMETER_NAME,
		LABEL_RECORDS_PARAMETER_NAME,
		RECORD_BYTES_PARAMETER_NAME,
		FILE_RECORDS_PARAMETER_NAME,
		INTERCHANGE_FORMAT_PARAMETER_NAME,
		0
		};

const char*
	Generic_PDS_Converter::REMOVED_PDS_JP2_PARAMETER_NAMES[] =
		{
		UNCOMPRESSED_FILE_PARAMETERS_GROUP,
		COMPRESSED_FILE_PARAMETERS_GROUP,
		0
		};

const int
	Generic_PDS_Converter::DEFAULT_PDS_LABEL_SIZE	= 2048;

/*==============================================================================
	Constructors
*/		
Generic_PDS_Converter::Generic_PDS_Converter ()
{}


Generic_PDS_Converter::Generic_PDS_Converter
	(
	const std::string&	pathname,
	const char**		excluded_names,
	const char**		image_names
	)
	:	PDS_Converter (pathname, excluded_names, image_names)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< Generic_PDS_Converter" << endl;
#endif
label_size (DEFAULT_PDS_LABEL_SIZE);
}

/*==============================================================================
	PDS_Converter Implementation
*/
string
Generic_PDS_Converter::product_names () const
{return PRODUCT_TYPE;}


bool
Generic_PDS_Converter::label_recognized () const
{
if (const_cast<Generic_PDS_Converter&>(*this).image_data ())
	return true;
return false;
}


void
Generic_PDS_Converter::write_PDS_JP2_label
	(
	const std::string&	PDS_label_pathname,
	const std::string&	JP2_pathname,
	const char**		removed_parameter_names,
	PDS_Data*			additional_parameters
	)
{
#if ((DEBUG) & DEBUG_LABEL)
clog << ">>> Generic_PDS_Converter::write_PDS_JP2_label:" << endl
	 << "    PDS_label_pathname - " << PDS_label_pathname << endl
	 << "          JP2_pathname - " << JP2_pathname << endl;
#endif
//	Copy the source label.
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Copying the source label." << endl;
#endif
PDS_Data
	PDS_label (*this);

//	Clean out irrelevant parameters.
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Generic_PDS_Converter::write_PDS_JP2_label: "
		<< "Removing irrelevant parameters ..."
		<< endl;
#endif

//	Remove statically defined parameters.
const char
	**parameter_names = REMOVED_PDS_PARAMETER_NAMES;
if (parameter_names)
	{
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    From the REMOVED_PDS_PARAMETER_NAMES list -" << endl;
	#endif
	while (*parameter_names)
		{
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "      " << absolute_pathname (*parameter_names) << endl;
		Parameter*
			parameter =
		#endif
		PDS_label.remove_parameter
			(absolute_pathname (*parameter_names++));
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		#endif
		}
	}

//	Remove user-specified parameters.
if (removed_parameter_names)
	{
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    From the removed_parameter_names list -" << endl;
	#endif
	while (*removed_parameter_names)
		{
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "      " << absolute_pathname (*removed_parameter_names) << endl;
		Parameter*
			parameter =
		#endif
		PDS_label.remove_parameter
			(absolute_pathname (*removed_parameter_names++));
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		#endif
		}
	}

//	Remove data block parameters.
if (Data_Blocks)
	{
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    From the Data_Blocks list -" << endl;
	#endif
	for (PDS_Data_Block_List::iterator
			block  = Data_Blocks->begin ();
			block != Data_Blocks->end ();
		  ++block)
		{
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "      " << (RECORD_POINTER_PARAMETER_MARKER + (*block)->name ()) << endl;
		Parameter*
			parameter =
		#endif
		PDS_label.remove_parameter
			(RECORD_POINTER_PARAMETER_MARKER + (*block)->name ());
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		clog << "      " << (*block)->name () << endl;
		parameter =
		#endif
		PDS_label.remove_parameter ((*block)->name ());
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		#endif
		}
	}

//	Remove excluded data block parameters.
parameter_names = excluded_data_block_names ();
if (parameter_names)
	{
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    From the excluded_data_block_names list -" << endl;
	#endif
	while (*parameter_names)
		{
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "      "
				<< (RECORD_POINTER_PARAMETER_MARKER + string (*parameter_names)) << endl;
		Parameter*
			parameter =
		#endif
		PDS_label.remove_parameter
			(RECORD_POINTER_PARAMETER_MARKER + string (*parameter_names));
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		clog << "      " << *parameter_names << endl;
		parameter =
		#endif
		PDS_label.remove_parameter (*parameter_names++);
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		#endif
		}
	}

//	New image file parameters replace the IMAGE parameters.
Aggregate
	*parameters = PDS_JP2_image_parameters (JP2_pathname);

PDS_label.move_in (*parameters);
delete parameters;	//	Delete the container.

//	Write out the label.
write_label (PDS_label_pathname, PDS_label);

#if ((DEBUG) & DEBUG_LABEL)
clog << "<<< Generic_PDS_Converter::write_PDS_JP2_label" << endl;
#endif
}



void
Generic_PDS_Converter::write_PDS_label
	(
	const std::string&	PDS_label_pathname,
	const Rectangle*	image_region,
	unsigned int		resolution_level,
	const char**		removed_parameter_names,
	PDS_Data*			additional_parameters
	)
{
#if ((DEBUG) & DEBUG_LABEL)
clog << ">>> Generic_PDS_Converter::write_PDS_label:" << endl
	 << "    PDS_label_pathname - " << PDS_label_pathname << endl
	 << "    image_region - " << *image_region << endl
	 << "    resolution_level - " << resolution_level << endl;
#endif
//	Copy the source label.
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Copying the source label." << endl;
#endif
PDS_Data
	PDS_label (*this);

//	Clean out irrelevant parameters.
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Generic_PDS_Converter::write_PDS_label: "
		<< "Removing irrelevant parameters." << endl;
#endif

//	Remove statically defined parameters.
const char
	**parameter_names = REMOVED_PDS_JP2_PARAMETER_NAMES;
if (parameter_names)
	{
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    From the REMOVED_PDS_PARAMETER_NAMES list -" << endl;
	#endif
	while (*parameter_names)
		{
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "      " << absolute_pathname (*parameter_names) << endl;
		Parameter*
			parameter =
		#endif
		PDS_label.remove_parameter
			(absolute_pathname (*parameter_names++));
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		#endif
		}
	}

//	Remove user-specified parameters.
if (removed_parameter_names)
	{
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    From the removed_parameter_names list -" << endl;
	#endif
	while (*removed_parameter_names)
		{
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "      " << absolute_pathname (*removed_parameter_names) << endl;
		Parameter*
			parameter =
		#endif
		PDS_label.remove_parameter
			(absolute_pathname (*removed_parameter_names++));
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "        " << (parameter ?
				parameter->pathname () : string ("not found")) << endl;
		#endif
		}
	}

//	Insert the record type, size and pointer parameters.
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Generic_PDS_Converter::write_PDS_label: "
		<< "Locating " << PDS_ID_PARAMETER_NAME << " parameter." << endl;
#endif
Aggregate::iterator
	parameter,
	label_end;
for (parameter = PDS_label.begin (),
	 label_end = PDS_label.end ();
	 parameter != label_end;
	 ++parameter)
	if (parameter->name () == PDS_ID_PARAMETER_NAME)
		break;
if (parameter == label_end)
	{
	ostringstream
		message;
	message << ID << endl
			<< "No PDS label file written" << endl
			<< "  because the " << PDS_ID_PARAMETER_NAME
				<< " was not found in the PDS label.";
	throw runtime_error (message.str ());
	}
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Generic_PDS_Converter::write_PDS_label: "
		<< "Inserting parameters after " << *parameter;
#endif

ostringstream
	comment;
string
	comment_line;
comment << left
	<< "The " << BYTE_RECORD_TYPE << ' ' << RECORD_TYPE_PARAMETER_NAME
		<< " is used to meet PDS standards requirements.";
comment_line = comment.str ();
int
	count = comment_line.length ();
comment.str ("");
comment
	<< endl
	<< endl
		<< setw (count)
	<< "File structure:" << endl
	<< endl
		<< setw (count)
	<< "This file contains an unstructured byte stream." << endl
	<< comment_line << endl
		<< setw (count)
	<< "A label \"record\" is actually a single byte.";
parameter = PDS_label.insert (++parameter, 
	(Assignment (RECORD_TYPE_PARAMETER_NAME)
		= String (BYTE_RECORD_TYPE)
			.type (Value::IDENTIFIER))
			.comment (comment.str ()));
#if ((DEBUG) & DEBUG_LABEL)
clog << "    " << *parameter;
#endif

comment.str ("");
comment
	<< endl
	<< endl
	<< "Locations of Data Objects in the file.                   " << endl
	<< "    >>> CAUTION <<< The first byte is location 1 (not 0)!" << endl;
parameter = PDS_label.insert (++parameter, 
	(Assignment (LABEL_RECORDS_PARAMETER_NAME)
		= Integer (Label_Size,
			Value::UNSIGNED, 10)
				.units (DATA_POINTER_PARAMETER_UNITS))
			.comment (comment.str ()));
Parameter
	*label_records_parameter = &(*parameter);
#if ((DEBUG) & DEBUG_LABEL)
clog << "    " << *label_records_parameter;
#endif
parameter = PDS_label.insert (++parameter, 
	Assignment (RECORD_POINTER_PARAMETER_MARKER + string (IMAGE_DATA_BLOCK_NAME))
		= Integer (Label_Size + 1,
			Value::UNSIGNED, 10)
				.units (DATA_POINTER_PARAMETER_UNITS));
Parameter
	*image_pointer_parameter = &(*parameter);
#if ((DEBUG) & DEBUG_LABEL)
clog << "    " << *image_pointer_parameter;
#endif

//	IMAGE parameters.
PDS_Data
	*image_parameters = image_data ();
if (! image_parameters)
	{
	ostringstream
		message;
	message << ID << endl
			<< "No PDS label was file written" << endl
			<< "  because no " << IMAGE_DATA_BLOCK_NAME
				<< " parameters were found in the PDS/JP2 label.";
	throw runtime_error (message.str ());
	}
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Copying the IMAGE parameters." << endl;
#endif
image_parameters = new PDS_Data (*image_parameters);

#if ((DEBUG) & DEBUG_LABEL)
clog << "        image_region: ";
if (image_region)
	clog
	 	<< image_region->X << "x, "
		<< image_region->Y << "y, "
		<< image_region->Width << "w, "
		<< image_region->Height << "h" << endl;
else
	clog << "NULL" << endl;
clog << "    resolution_level: " << resolution_level << endl;
#endif
if (image_region)
	{
	try
		{
		//	Update the image size parameters.
		Parameter
			*parameter;
		parameter = parameter_of (*image_parameters,
			Image_Data_Block::IMAGE_WIDTH_PARAMETER_NAME);
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "    " << Image_Data_Block::IMAGE_WIDTH_PARAMETER_NAME << " -" << endl
			 << "      old = " << parameter->value () << endl
			 << "      new = " << image_region->Width << endl;
		#endif
		parameter->value () = image_region->Width;

		parameter = parameter_of (*image_parameters,
			Image_Data_Block::IMAGE_HEIGHT_PARAMETER_NAME);
		#if ((DEBUG) & DEBUG_LABEL)
		clog << "    " << Image_Data_Block::IMAGE_HEIGHT_PARAMETER_NAME << " -" << endl
			 << "      old = " << parameter->value () << endl
			 << "      new = " << image_region->Height << endl;
		#endif
		parameter->value () = image_region->Height;
		}
	catch (const runtime_error& exception)
		{
		ostringstream
			message;
		message << exception.what () << endl
				<< "No PDS label file written" << endl
				<< "  due to missing PDS/JP2 label parameters.";
		throw runtime_error (message.str ());
		}
	}

//	Remove any LINE_{PRE,SUF}FIX_BYTES parameters (not included in JP2 file).
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Removing " << Image_Data_Block::LINE_PREFIX_BYTES_PARAMETER_NAME
		<< " from the PDS_JP2_image_parameters" << endl;
Parameter*
	param =
#endif
image_parameters->remove_parameter
	(Image_Data_Block::LINE_PREFIX_BYTES_PARAMETER_NAME);
#if ((DEBUG) & DEBUG_LABEL)
clog << "      " << (param ?
		param->pathname () : string ("not found")) << endl;
clog << "    Removing " << Image_Data_Block::LINE_SUFFIX_BYTES_PARAMETER_NAME
		<< " from the PDS_JP2_image_parameters" << endl;
param =
#endif
image_parameters->remove_parameter
	(Image_Data_Block::LINE_SUFFIX_BYTES_PARAMETER_NAME);
#if ((DEBUG) & DEBUG_LABEL)
clog << "      " << (param ?
		param->pathname () : string ("not found")) << endl;
clog << "    New IMAGE parameters - " << endl
	 << *image_parameters << endl;
#endif
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Adding the IMAGE parameters to the PDS label." << endl
	 << *image_parameters;
#endif
PDS_label.add (*image_parameters);

/*	Change the name of the top level aggregate
	so that only its contents are listed.
*/
PDS_label.name (Parser::CONTAINER_NAME);

//	PDS formatted label lister.
idaeim::PVL::Lister
	*PDS_PVL_lister = label_lister ();

#if ((DEBUG) & DEBUG_LABEL)
clog << "    Determining the label size from an in-memory listing" << endl;
#endif
//	Write to memory to find the label size.
ostringstream
	label;
label
	<< *PDS_PVL_lister
	<< PDS_label;

unsigned int
	size = label_size ();
#if ((DEBUG) & DEBUG_LABEL)
clog << "    Initial label size = " << PDS_PVL_lister->total () << endl
	 << "    Desired label size = " << size << endl;
#endif
if (PDS_PVL_lister->total () > size)
	{
	//	Adjust the label size and its records and image pointer parameters.
	size = PDS_PVL_lister->total () + 2047;
	size -= size % 1024;
	label_records_parameter->value () = size;
	image_pointer_parameter->value () = size + 1;
	label_size (size);
	#if ((DEBUG) & DEBUG_LABEL)
	clog << "    Adjusted label size = " << size << endl;
	#endif
	}

//	Write out the label.
write_label (PDS_label_pathname, PDS_label, PDS_PVL_lister, true);

delete PDS_PVL_lister;
delete image_parameters;

#if ((DEBUG) & DEBUG_LABEL)
clog << "<<< Generic_PDS_Converter::write_PDS_label" << endl;
#endif
}

/*==============================================================================
	Helpers
*/		
Parameter*
Generic_PDS_Converter::parameter_of
	(
	Aggregate&	parameters,
	const char*	name,
	bool		throw_unless_found
	)
{
Parameter
	*parameter = UA::HiRISE::find_parameter (parameters,
		name, false, 0, PDS_Data::ASSIGNMENT_PARAMETER);
if (throw_unless_found &&
	! parameter)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to find the expected " << name << " parameter" << endl
			<< "  in the " << parameters.name () << " group.";
	throw runtime_error (message.str ());
	}
return parameter;
}


}	//	namespace HiRISE
}	//	namespace UA
