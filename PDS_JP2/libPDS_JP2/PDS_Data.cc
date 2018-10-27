/*	PDS_Data

HiROC CVS ID: PDS_Data.cc,v 1.27 2013/03/14 21:00:43 guym Exp

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

#include "PDS_Data.hh"

#include "Image_Data_Block.hh"

#include "PVL.hh"
using idaeim::PVL::Parser;
using idaeim::PVL::Parameter;
using idaeim::PVL::Aggregate;
using idaeim::PVL::Value;
using idaeim::PVL::Lister;

#include	<fstream>
using std::ifstream;
#include	<string>
using std::string;
#include	<sstream>
using std::ostringstream;
#include    <stdexcept>
using std::logic_error;
#include	<iomanip>
using std::endl;

#include <exception>
using std::exception;

#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			-1
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_ACCESSORS		(1 << 1)
#define DEBUG_MANIPULATORS	(1 << 2)
#define DEBUG_HELPERS		(1 << 3)
#include	<iostream>
using std::clog;
using std::boolalpha;
#endif  // DEBUG


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
	PDS_Data::ID =
		"UA::HiRISE::PDS_Data (1.27 2013/03/14 21:00:43)";

const char
	*PDS_Data::PDS_ID_PARAMETER_NAME				   = "PDS_VERSION_ID",
	*PDS_Data::RECORD_TYPE_PARAMETER_NAME			= "RECORD_TYPE",
	*PDS_Data::BYTE_RECORD_TYPE						= "UNDEFINED",
	*PDS_Data::FIXED_LENGTH_RECORD_TYPE			   = "FIXED_LENGTH",
	*PDS_Data::LABEL_RECORDS_PARAMETER_NAME	   = "LABEL_RECORDS",
	*PDS_Data::RECORD_BYTES_PARAMETER_NAME			= "RECORD_BYTES",
	*PDS_Data::FILE_RECORDS_PARAMETER_NAME			= "FILE_RECORDS",
	*PDS_Data::INTERCHANGE_FORMAT_PARAMETER_NAME	= "INTERCHANGE_FORMAT",
	*PDS_Data::IMAGE_DATA_BLOCK_NAME				   = "IMAGE",
	*PDS_Data::BYTES_UNITS							   = "BYTES";

const char
	PDS_Data::RECORD_POINTER_PARAMETER_MARKER		= '^';

/*==============================================================================
	Constructors
*/
PDS_Data::PDS_Data ()
{}


PDS_Data::PDS_Data
	(
	const idaeim::PVL::Aggregate& parameters
	)
	:	Aggregate (parameters)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< PDS_Data: from Aggregate: \"" <<  parameters.name () << '"' << endl;
#endif
}


PDS_Data::PDS_Data
	(
	const std::string&	pathname
	)
	:	Aggregate (pathname)	//	Sets the name of the PDS_Data.
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< PDS_Data: from file " << pathname << endl;
#endif
parameters (pathname);
}

PDS_Data::PDS_Data
	(
	const idaeim::PVL::Aggregate& parameters,
	const std::string&	detached
	)
	:	Aggregate (parameters)	//	Sets the name of the PDS_Data.
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< PDS_Data: from Aggregate: \"" <<  parameters.name () << '"' << endl;
clog << ">-< PDS_Data: data in detached file " << detached << endl;
#endif
//parameters (pathname);
}

/*==============================================================================
	Accessors
*/
PDS_Data::PDS_Data_Block_List*
PDS_Data::data_blocks
	(
	const char**	excluded,
	const char**	image_block_names
	)
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">>> PDS_Data::data_blocks" << endl;
#endif

//	Determine the size of records used to locate data blocks in the file.
Value::Unsigned_Integer_type
	record_bytes = 1;
Parameter
	*record_bytes_parameter = find_parameter (RECORD_BYTES_PARAMETER_NAME);
if (record_bytes_parameter)
	record_bytes = record_bytes_parameter->value ();

PDS_Data_Block_List
	*blocks = new PDS_Data_Block_List;
Parameter
	*data_block_parameters;
PDS_Data_Block
	*data_block;

for (Aggregate::iterator
		parameter = begin ();
		parameter != end ();
		++parameter)
	{
	if ((parameter->name ())[0] == RECORD_POINTER_PARAMETER_MARKER)
		{
		string
			data_block_name = (parameter->name ()).substr (1);
		#if ((DEBUG) & DEBUG_ACCESSORS)
		clog << "    Record pointer for: " << data_block_name << endl;
		#endif

		if (excluded)
			{
			//	Check for an excluded data block.
			const char**
				 exclude;
			for (exclude = excluded;
				*exclude;
				 exclude++)
				if (data_block_name == *exclude)
					break;
			if (*exclude)
				{
				#if ((DEBUG) & DEBUG_ACCESSORS)
				clog 	<< "    Excluded " << *exclude << endl;
				#endif
				continue;
				}
			}

		if ((data_block_parameters = find_parameter (data_block_name)) &&
			 data_block_parameters->is_Aggregate ())
			{
			bool
				is_image_data_block = false;

			if (data_block_name == IMAGE_DATA_BLOCK_NAME)
				is_image_data_block = true;
			else if (image_block_names)
				{
				const char**
					 image_block_name;
				for (image_block_name = image_block_names;
					*image_block_name;
					 image_block_name++)
					{
					if (data_block_name == *image_block_name)
						{
						is_image_data_block = true;
						break;
						}
					}
				}

         if (parameter->value().is_Integer())
         {
			if (is_image_data_block)
				{
				#if ((DEBUG) & DEBUG_ACCESSORS)
				clog << "      Image_Data_Block at location "
						<< ((std::ios::off_type)parameter->value () - 1) << endl;
				#endif
				data_block =
					new Image_Data_Block
						(
						*data_block_parameters, 
						((Value::Unsigned_Integer_type)parameter->value () - 1)
							* record_bytes
						);
				}
			else
				{
				#if ((DEBUG) & DEBUG_ACCESSORS)
				clog << "      PDS_Data_Block at location "
						<< ((std::ios::off_type)parameter->value () - 1) << endl;
				#endif
				data_block =
					new PDS_Data_Block
						(
				    	*data_block_parameters,
						(Value::Unsigned_Integer_type)parameter->value () - 1
						);
				}
         }
         else if (parameter->value().is_String())
         {
            if (is_image_data_block)
            {
            #if ((DEBUG) & DEBUG_ACCESSORS)
            clog << "      PDS_Data_Block in file "
                  << parameter->value () << endl;

            clog << "Creating an image data block with " << parameter->value().type_name() << endl;
            #endif
try {
            data_block =
               new Image_Data_Block
               (
                *data_block_parameters,
                static_cast<idaeim::PVL::Value::String_type>(parameter->value())
               );
} catch (exception& e)
{
         #if ((DEBUG) & DEBUG_ACCESSORS)
         clog << e.what() << endl;
         #endif
}
            }
         }

         #if ((DEBUG) & DEBUG_ACCESSORS)
         clog << "PDS_Data <<<      Found data block" << endl;
         #endif

			blocks->push_back (data_block);
			}
		#if ((DEBUG) & DEBUG_ACCESSORS)
		else
			clog << "      No data block parameters found!" << endl;
		#endif
		}
	}
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << "<<< PDS_Data::data_blocks" << endl;
#endif
return blocks;
}

/*==============================================================================
	Manipulators
*/
PDS_Data&
PDS_Data::parameters
	(
	const std::string&	pathname
	)
{
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << ">>> PDS_Data::parameters: " << pathname << endl;
#endif
ifstream
	file (pathname.c_str());
if (file)
	{
	Parser
		parser (file);
	Aggregate
		*parameters;
	try {parameters = new Aggregate (parser, pathname);}
	catch (idaeim::PVL::Invalid_Syntax& exception)
		{
		file.close ();
		exception.message (string (ID) + '\n'
			+ "Unable to set parameters from file " + pathname + ".\n"
			+ exception.message ());
		throw exception;
		}
	file.close ();

	//	Clear out the current parameters.
	clear ();
	//	Move in the new parameters.
	move_in (*parameters);
	//	Set the name of the Aggregate to the source pathname.
	name (pathname);
	//	Delete the remaining container shell.
	delete parameters;
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "    PDS_Data::parameters:" << endl
		 << *this << endl;
	#endif
	}
else
	throw std::ios::failure (string (ID) + '\n'
		+ "Unable to access parameters in file " + pathname);
#if ((DEBUG) & DEBUG_MANIPULATORS)
clog << "<<< PDS_Data::parameters" << endl;
#endif
return *this;
}


PDS_Data&
PDS_Data::parameters
	(
	const idaeim::PVL::Aggregate&	params
	)
{
clear ();
copy_in (params);
name (params.name ());
return *this;
}

/*==============================================================================
	Helpers
*/
Image_Data_Block*
PDS_Data::image_data
	(
	PDS_Data_Block_List*	data_block_list
	)
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">>> PDS_Data.image_data" << endl;
#endif
Image_Data_Block
	*IMAGE_data_block = NULL;
if (data_block_list)
	{
	//	Search for an IMAGE data block.
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << "    Searching for the "
		<< IMAGE_DATA_BLOCK_NAME << " data block." << endl;
	#endif
	for (PDS_Data_Block_List::iterator
			block  = data_block_list->begin ();
			block != data_block_list->end ();
		  ++block)
		{
		if ((*block)->name () == IMAGE_DATA_BLOCK_NAME)
			{
			#if ((DEBUG) & DEBUG_ACCESSORS)
			clog << "    Found." << endl;
			#endif
			if ((IMAGE_data_block = dynamic_cast<Image_Data_Block*>(*block)))
				break;
			#if ((DEBUG) & DEBUG_ACCESSORS)
			clog << "      But it is not an Image_Data_Block!" << endl;
			#endif
			ostringstream
				message;
			message << ID << endl
					<< IMAGE_DATA_BLOCK_NAME << " data block found,"
						<< " but it is not an Image_Data_Block!";
			throw logic_error (message.str ());
			}
		}
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << "    " << (IMAGE_data_block ? "" : "not ") << "found" << endl;
	#endif
	}
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << "<<< PDS_Data.image_data" << endl;
#endif
return IMAGE_data_block;
}

/*==============================================================================
	PVL Methods and Functions
*/
Parameter*
find_parameter
	(
	const idaeim::PVL::Aggregate&		parameters,
	const std::string&					pathname,
	bool								case_sensitive,
	int									skip,
	PDS_Data::Parameter_Class_Selection	parameter_class
	)
{
#if ((DEBUG) & DEBUG_HELPERS)
clog << ">>> PDS_Data::find_parameter: " << pathname << endl
	 << "     case_sensitive: " << boolalpha << case_sensitive << endl
	 << "               skip: " << skip << endl
	 << "    parameter_class: " << parameter_class << endl;
#endif
Aggregate::depth_iterator
	parameter,
	aggregate_end = (const_cast<Aggregate&>(parameters)).end_depth ();
for (parameter = (const_cast<Aggregate&>(parameters)).begin_depth ();
	 parameter != aggregate_end;
	 ++parameter)
	{
	if (parameter->at_pathname (pathname, case_sensitive, parameters))
		{
		if (parameter_class < 0 &&
			! parameter->is_Aggregate ())
			continue;
		if (parameter_class > 0 &&
			! parameter->is_Assignment ())
			continue;
		if (! skip--)
			break;
		}
	}
#if ((DEBUG) & DEBUG_HELPERS)
clog << "<<< PVL_Parameter: ";
#endif
if (parameter == aggregate_end)
	{
	#if ((DEBUG) & DEBUG_HELPERS)
	clog << "not found" << endl;
	#endif
	return NULL;
	}
#if ((DEBUG) & DEBUG_HELPERS)
clog << parameter->name () << " " << parameter->type_name () << endl;
#endif
return &(*parameter);
}


Parameter*
PDS_Data::find_parameter
	(
	const std::string&			pathname,
	bool						case_sensitive,
	int							skip,
	Parameter_Class_Selection	parameter_class
	)
	const
{return UA::HiRISE::find_parameter
	(*this, pathname, case_sensitive, skip, parameter_class);}


Parameter*
remove_parameter
	(
	idaeim::PVL::Aggregate&				parameters,
	const std::string&					pathname,
	bool								case_sensitive,
	int									skip,
	PDS_Data::Parameter_Class_Selection	parameter_class
	)
{
#if ((DEBUG) & DEBUG_HELPERS)
clog << ">>> PDS_Data::remove_parameter: " << pathname << endl;
#endif
Parameter
	*parameter =
		UA::HiRISE::find_parameter
			(parameters, pathname, case_sensitive, skip, parameter_class);
if (parameter)
	parameter = parameter->parent ()->remove (parameter);
#if ((DEBUG) & DEBUG_HELPERS)
clog << "<<< PDS_Data::remove_parameter: removed - "
		<< boolalpha << (parameter != NULL) << endl;
#endif
return parameter;
}


Parameter*
PDS_Data::remove_parameter
	(
	const std::string&			pathname,
	bool						case_sensitive,
	int							skip,
	Parameter_Class_Selection	parameter_class
	)
{return UA::HiRISE::remove_parameter
	(*this, pathname, case_sensitive, skip, parameter_class);}


double
numeric_value
	(
	const idaeim::PVL::Parameter&	parameter
	)
{
if (! parameter.value ().is_Numeric ())
	{
	ostringstream
		message;
	message << "Numeric value expected for parameter "
				<< parameter.pathname () << endl
			<< "but " << parameter.value ().type_name () << " value found.";
	throw idaeim::PVL::Invalid_Value (message.str (), -1, PDS_Data::ID);
	}
return static_cast<double>(parameter.value ());
}


double
PDS_Data::numeric_value
	(
	const std::string&	pathname,
	bool				case_sensitive,
	int					skip
	)
	const
{
Parameter
	*parameter =
		find_parameter (pathname, case_sensitive, skip, ASSIGNMENT_PARAMETER);
if (! parameter)
	{
	ostringstream
		message;
	message << "Can't find the assignment parameter " << pathname;
	throw idaeim::Invalid_Argument (message.str (), ID);
	}
return UA::HiRISE::numeric_value (*parameter);
}


std::string
string_value
	(
	const idaeim::PVL::Parameter&	parameter
	)
{
if (! parameter.value ().is_String ())
	{
	ostringstream
		message;
	message << "String value expected for parameter "
				<< parameter.pathname () << endl
			<< "but " << parameter.value ().type_name () << " value found.";
	throw idaeim::PVL::Invalid_Value (message.str (), -1, PDS_Data::ID);
	}
return static_cast<string>(parameter.value ());
}


std::string
PDS_Data::string_value
	(
	const std::string&	pathname,
	bool				case_sensitive,
	int					skip
	)
	const
{
Parameter
	*parameter =
		find_parameter (pathname, case_sensitive, skip, ASSIGNMENT_PARAMETER);
if (! parameter)
	{
	ostringstream
		message;
	message << "Can't find the " << pathname << " assignment parameter.";
	throw idaeim::Invalid_Argument (message.str (), ID);
	}
return UA::HiRISE::string_value (*parameter);
}


std::string
absolute_pathname
	(
	const std::string&			pathname
	)
{
char
	delimiter = Parameter::path_delimiter ();
if (pathname.empty () ||
	pathname[0] == delimiter)
	return pathname;
string
	absolute_path (1, delimiter);
return absolute_path += pathname;
}


string
to_uppercase
	(
	const string&	a_string
	)
{
string
	uppercased_string (a_string);
for (string::iterator
		character = uppercased_string.begin ();
		character < uppercased_string.end ();
		character++)
	*character = (char)toupper (*character);
return uppercased_string;
}


string
indent
	(
	std::string		lines,
	int				amount
	)
{
if (amount &&
	! lines.empty ())
	{
	std::string::size_type
		index = lines.size ();
	if (lines[--index] == '\n')
		//	Skip the trailing NL.
		--index;
	while (index)
		{
		if (lines[index] == '\n')
			//	Shift the following line.
			lines.insert (index + 1, amount, ' ');
		--index;
		}
	//	Shift first line.
	lines.insert (index, amount, ' ');
	}
return lines;
}


idaeim::PVL::Lister*
label_lister ()
{
Lister
	*lister = new Lister ();
(*lister)
	.strict					(true)			
	.begin_aggregates		(false)
	.uppercase_aggregates	(true)
	.name_end_aggregates	(true)
	.assign_align			(true)
	.array_indenting		(false)
	.use_statement_delimiter(false)
	.single_line_comments	(true);
return lister;
}


}   //  namespace HiRISE
}   //  namespace UA

