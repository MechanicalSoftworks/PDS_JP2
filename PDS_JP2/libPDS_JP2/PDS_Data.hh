/*	PDS_Data

HiROC CVS ID: PDS_Data.hh,v 1.26 2013/03/14 21:00:43 guym Exp

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

#ifndef _PDS_Data_
#define _PDS_Data_

#include	"PVL.hh"

#include	<vector>


namespace UA
{
namespace HiRISE
{
//	Forward references.
class PDS_Data_Block;
class Image_Data_Block;


/**	<i>PDS_Data</i> contains PDS label PVL parameters.

	Common PDS label description constants and methods to locate and
	modify the label parameters to assist in label conversion operations
	are provided.

	@author		Bradford Castalia, Drew Davidson and Ben Pearson; UA/HiROC
	@version	1.26
	@see	idaeim::PVL::Aggregate
*/
class PDS_Data
:	public idaeim::PVL::Aggregate
{
public:
/*==============================================================================
	Types
*/
//!	A vector of PDS_Data_Block object pointers.
typedef	std::vector<PDS_Data_Block*>	PDS_Data_Block_List;

/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

//! Name of the parameter providing the PDS ID.
static const char*
	PDS_ID_PARAMETER_NAME;

//!	Name of the parameter specifying the type of label records.
static const char
	*RECORD_TYPE_PARAMETER_NAME;

//!	The record type used to define byte count based records.
static const char
	*BYTE_RECORD_TYPE;

//!	The record type used to define fixed length records.
static const char
	*FIXED_LENGTH_RECORD_TYPE;

//!	Name of the parameter specifying the number of records in the label.
static const char
	*LABEL_RECORDS_PARAMETER_NAME;

//!	Name of the parameter specifying the number of bytes per record.
static const char
	*RECORD_BYTES_PARAMETER_NAME;

//!	Name of the parameter specifying the number of records in the file.
static const char
	*FILE_RECORDS_PARAMETER_NAME;

//!	Name of the parameter indicating the data format.
static const char
	*INTERCHANGE_FORMAT_PARAMETER_NAME;

//!	Name of the Image_Data_Block parameter group.
static const char*
	IMAGE_DATA_BLOCK_NAME;

//!	Units name for storage measured in bytes.
static const char*
	BYTES_UNITS;

/**	Record pointer parameter prefix.

	When this character is the first character of a parameter name it is
	marked as a record pointer parameter for a data block. An associated
	group of parameters having the same name, but without the initial
	marker character, is expected to be present that describes the
	content of the data block.
*/
static const char
	RECORD_POINTER_PARAMETER_MARKER;

/*==============================================================================
	Constructors:
*/
/**	Construct PDS_Data with no parameters.
*/
PDS_Data ();

/**	Construct PDS_Data from a PVL Parameter Aggregate.

	@param	parameters	A Parameter Aggregate that provides the PDS data
		parameters.
*/
PDS_Data (const idaeim::PVL::Aggregate& parameters);

/**	Construct PDS_Data from a PVL Parameter Aggregate.

	@param	parameters	A Parameter Aggregate that provides the PDS data
		parameters.
*/
PDS_Data (const idaeim::PVL::Aggregate& parameters, const std::string& detached);

/**	Construct PDS_Data from a named file.

	@param	pathname	The pathname to the source file that will be
		parsed for PVL parameters.
	@see	parameters(const std::string&)
*/
explicit PDS_Data (const std::string& pathname);


/*==============================================================================
	Accessors:
*/
/**	Get a list of all binary data blocks in the PDS data. 

	A binary data block is located by a data block record pointer
	parameter. A record pointer parameter has a name that begins with the
	RECORD_POINTER_PARAMETER_MARKER character. If a parameter Aggregate
	with the same name, but without the record pointer marker, is found
	it is used to construct a new PDS_Data_Block object that is added to
	the list of data blocks. <b>N.B.</b>: Each PDS_Data_Block contains a
	copy of the data block description parameters.

	The value of a record pointer parameter is the location of the data
	block in the file in terms of records. The size of a record is
	assumed to be one byte unless a parameter with the
	RECORD_BYTES_PARAMETER_NAME is found in which case its value is the
	size of a record. The location of the data block in the file as a
	byte offset, which is used when constructing the PDS_Data_Block to
	add to the PDS_Data_Block_List, is the record pointer value times the
	record size.

	<b>N.B.</b>: Only top level parameters are searched.

	@param	excluded	A NULL terminated array of data block names
		(character strings) that are to be excluded from the list of
		data blocks that are assembled. <b>N.B.</b>: The data block
		names do not include the RECORD_POINTER_PARAMETER_MARKER.
	@param	image_block_names	A NULL terminated array of data block
		names (character strings) that, if found, are to be treated as
		Image_Data_Block parameter groups. The IMAGE_DATA_BLOCK_NAME
		parameter group is always treated as an Image_Data_Block.
	@return	A pointer to a PDS_Data_Block_List, which is a vector
		of PDS_Data_Block pointers.
*/
PDS_Data_Block_List* data_blocks
	(const char** excluded = NULL, const char** image_block_names = NULL);

/**	Selects the class of parameter to find.
*/
enum Parameter_Class_Selection
	{
	AGGREGATE_PARAMETER	 = -1,
	ANY_PARAMETER        =  0,
	ASSIGNMENT_PARAMETER =  1
	};

/**	Find a named Parameter.

	The Parameter to be found may be specified by a simple name, a
	relative pathname or an absolute pathname. A simple name is the name
	of a Parameter itself. A relative pathname is a simple name preceeded
	by the pathname of an Aggregate Parameter that must contain the
	Parameter with the simple name. An absolute pathname is a pathname
	that begins with a pathname delimiter ('/'); i.e. it is a fully
	qualified pathname beginning at the root of the Aggregate hierarchy,
	compared to a relative pathname that may begin at any Aggregate in
	the hierarchy.

	Since it is not necessary that the pathname to each Parameter be
	unique, the number of matching pathnames to skip before selecting a
	Parameter may need to be specified to get the desired Parameter.
	Also, a specific type of Parameter - an Aggregate of Parameters or an
	Assignment of Values - may be specified. When skipping parameters,
	only the specified type, if any, are counted.

	@param	pathname	The pathname of the parameter to find.
	@param	case_sensitive	If true, the name search is case
		sensitive; case insensitive otherwise.
	@param	skip		The number of parameters that match the
		name to skip before selecting a matching parameter.
	@param	parameter_class		A #Parameter_Class_Selection: If
		AGGREGATE_PARAMETER, only Aggregate parameters will be selected;
		if ASSIGNMENT_PARAMETER, only Assignment parameters will be
		selected; otherwise any type of parameter (ANY_PARAMETER) is
		acceptable.
	@return	A pointer to the matching parameter, or NULL if it could not
		be found.
	@see	find_parameter(const idaeim::PVL::Aggregate&,
		const std::string&, bool, int, Parameter_Class_Selection)
*/
idaeim::PVL::Parameter*
find_parameter
	(
	const std::string&			pathname,
	bool						case_sensitive = false,
	int							skip = 0,
	Parameter_Class_Selection	parameter_class = ANY_PARAMETER
	)
	const;

/*==============================================================================
	Manipulators:
*/
/**	Set the parameters from a source file.

	The current parameters are cleared before the new parameters are
	moved in, but not before the new parameters have been successfully
	obtained from the source file.

	<b>N.B.</b>: The name of the parameters group is set to the source file
	pathname.

	@param	pathname	The pathname to the source file that will be
		parsed for PVL parameters.
	@return	This PDS_Data object.
	@throws	std::ios::failure	If the source file can not be accessed
		or read.
	@throws idaeim::PVL::Invalid_Syntax	If the source file contains
		contains invalid PVL syntax.  
	@see	idaeim::PVL::Parser
*/
virtual PDS_Data& parameters (const std::string& pathname);

/**	Set the parameters from a Parameter Aggregate.

	The current parameters are cleared before the new parameters are
	moved in.

	<b>N.B.</b>: The name of the parameters group is set to the
	name of the Parameter Aggregate.

	@param	parameters	A Parameter Aggregate that is the source of
		new parameters.
	@return	This PDS_Data object.
*/
virtual PDS_Data& parameters (const idaeim::PVL::Aggregate& parameters);

/**	Removes a named Parameter.

	@param	pathname	The name of the parameter to find.
	@param	case_sensitive	If true, the name search is case sensitive;
		case insensitive otherwise.
	@param	skip	The number of parameters that match the name to skip
		before selecting a matching parameter.
	@param	parameter_class		A Parameter_Class_Selection: If
		AGGREGATE_PARAMETER, only Aggregate parameters will be selected;
		if ASSIGNMENT_PARAMETER, only Assignment parameters will be
		selected; otherwise any type of parameter (ANY_PARAMETER) is
		acceptable.
	@return	A pointer to the parameter that was removed, or NULL if it
		could not be found.
	@see	find_parameter(const std::string&, bool, int,
				Parameter_Class_Selection)
*/
idaeim::PVL::Parameter*
remove_parameter
	(
	const std::string&			pathname,
	bool						case_sensitive = false,
	int							skip = 0,
	Parameter_Class_Selection	parameter_class = ANY_PARAMETER
	);

/**	Set the value of a named parameter.

	Only Assignment Parameters with a Value that is not an Array will be
	modified. However, the search for a matching name does not make this
	distinction.

	@param	pathname	The name of the parameter to find.
	@param	value	The value to assign to the parameter.
	@param	case_sensitive	If true, the name search is case sensitive;
		case insensitive otherwise.
	@param	skip	The number of parameters that match the pathname to
		skip before selecting the parameter to modify.
	@return	true if the parameter was found; false otherwise.
	@see	find_parameter(const std::string&, bool, int,
				Parameter_Class_Selection)
*/
template <typename T>
bool
parameter_value
	(
	const std::string&	pathname,
	T&					value,
	bool				case_sensitive = false,
	int					skip = 0
	)
{
idaeim::PVL::Parameter
	*parameter =
		find_parameter (pathname, case_sensitive, skip, ASSIGNMENT_PARAMETER);
if (! parameter ||
	  parameter->value ().is_Array ())
	return false;
parameter->value () = value;
return true;
}

/**	Get the numeric value of a named parameter.

	@param	pathname	The name of the parameter to find.
	@param	case_sensitive	If true, the name search is case sensitive;
		case insensitive otherwise.
	@param	skip	The number of parameters that match the pathname to
		skip before selecting the parameter to modify.
	@return	The value of the parameter as a double.
	@throws	idaeim::Invalid_Argument	If an assignment parameter can
		not be found at the pathname.
	@throws	idaeim::PVL_Invalid_Value	If the Value is not Numeric.
	@see	find_parameter(const std::string&, bool, int,
				Parameter_Class_Selection)
*/
double
numeric_value
	(
	const std::string&	pathname,
	bool				case_sensitive = false,
	int					skip = 0
	)
	const;

/**	Get the string value of a named parameter.

	@param	pathname	The name of the parameter to find.
	@param	case_sensitive	If true, the name search is case sensitive;
		case insensitive otherwise.
	@param	skip	The number of parameters that match the pathname to
		skip before selecting the parameter to modify.
	@return	The string value of the parameter.
	@throws	idaeim::Invalid_Argument	If an assignment parameter can
		not be found at the pathname.
	@throws	idaeim::PVL_Invalid_Value	If the Value is not a String.
	@see	find_parameter(const idaeim::PVL::Aggregate&,
		const std::string&, bool, int, Parameter_Class_Selection)
*/
std::string
string_value
	(
	const std::string&	pathname,
	bool				case_sensitive = false,
	int					skip = 0
	)
	const;

/*==============================================================================
	Helpers
*/
/**	Get the Image_Data_Block from a PDS_Data::PDS_Data_Block_List.

	The data block list, if non-NULL, is searched for the first
	entry having the IMAGE_DATA_BLOCK_NAME that is an Image_Data_Block.

	@param	data_block_list	A pointer to a PDS_Data_Block_List to be
		searched. May be NULL.
	@return	A pointer to the Image_Data_Block, or NULL if none can be found.
	@throws	logic_error	If an entry with the IMAGE_DATA_BLOCK_NAME is found
		but it is not an Image_Data_Block.
	@see	data_blocks(const char**)
*/
static Image_Data_Block* image_data (PDS_Data_Block_List* data_block_list);

};	//	class PDS_Data


/**	Find a named Parameter within a Parameter Aggregate.

	The Parameter to be found may be specified by a simple name, a
	relative pathname or an absolute pathname. A simple name is the name
	of a Parameter itself. A relative pathname is a simple name preceeded
	by the pathname of an Aggregate Parameter that must contain the
	Parameter with the simple name. An absolute pathname is a pathname
	that begins with a pathname delimiter ('/'); i.e. it is a fully
	qualified pathname beginning at the root of the Aggregate hierarchy,
	compared to a relative pathname that may begin at any Aggregate in
	the hierarchy.

	Since it is not necessary that the pathname to each Parameter be
	unique, the number of matching pathnames to skip before selecting a
	Parameter may need to be specified to get the desired Parameter.
	Also, a specific type of Parameter - an Aggregate of Parameters or an
	Assignment of Values - may be specified. When skipping parameters,
	only the specified type, if any, are counted.

	@param	parameters	The Aggregate within which to search.
	@param	pathname	The pathname of the parameter to find.
	@param	case_sensitive	If true, the name search is case
		sensitive; case insensitive otherwise.
	@param	skip		The number of parameters that match the
		name to skip before selecting a matching parameter.
	@param	parameter_class		A PDS::Parameter_Class_Selection: If
		PDS_Data::AGGREGATE_PARAMETER, only Aggregate parameters will be
		selected; if PDS_Data::ASSIGNMENT_PARAMETER, only Assignment
		parameters will be selected; otherwise any type of parameter
		(PDS_Data::ANY_PARAMETER) is acceptable.
	@return	A pointer to the matching parameter, or NULL if it could not
		be found.
	@see	PVL::Parameter::at_pathname()
*/
idaeim::PVL::Parameter*
find_parameter
	(
	const idaeim::PVL::Aggregate&		parameters,
	const std::string&					pathname,
	bool								case_sensitive = false,
	int									skip = 0,
	PDS_Data::Parameter_Class_Selection	parameter_class
											= PDS_Data::ANY_PARAMETER
	);

/**	Removes a named Parameter within a Parameter Aggregate.

	@param	parameters	The Aggregate within which to search.
	@param	pathname	The name of the parameter to find.
	@param	case_sensitive	If true, the name search is case sensitive;
		case insensitive otherwise.
	@param	skip	The number of parameters that match the name to skip
		before selecting a matching parameter.
	@param	parameter_class		A Parameter_Class_Selection: If
		AGGREGATE_PARAMETER, only Aggregate parameters will be selected;
		if ASSIGNMENT_PARAMETER, only Assignment parameters will be
		selected; otherwise any type of parameter (ANY_PARAMETER) is
		acceptable.
	@return	A pointer to the parameter that was removed, or NULL if it
		could not be found.
*/
idaeim::PVL::Parameter*
remove_parameter
	(
	idaeim::PVL::Aggregate&				parameters,
	const std::string&					pathname,
	bool								case_sensitive = false,
	int									skip = 0,
	PDS_Data::Parameter_Class_Selection	parameter_class
											= PDS_Data::ANY_PARAMETER
	);

/**	Get the numeric value of a parameter.

	@param	parameter	The parameter from which to obtain a numeric value.
	@return	The value of the parameter as a double.
	@throws	idaeim::PVL_Invalid_Value	If the Value is not Numeric.
*/
double numeric_value (const idaeim::PVL::Parameter& parameter);

/**	Get the string value of a parameter.

	@param	parameter	The parameter from which to obtain a string value.
	@return	The value of the parameter as a string.
	@throws	idaeim::PVL_Invalid_Value	If the Value is not a String.
*/
std::string string_value (const idaeim::PVL::Parameter& parameter);

/**	Ensure an absolute pathname.

	If the pathname does not begin with a {@link
	idaeim::PVL::Parameter::path_delimiter() Parameter pathname delimiter}
	one is prepended. An empty pathname results in an empty string.

	@param	pathname	A Parameter pathname string.
	@return	The pathname in absolute form.
*/
std::string absolute_pathname (const std::string& pathname);

/**	Convert a string to all uppercase form.

	@param	a_string	The string to be converted.
	@return	A copy of the given string with all characters converted
		to uppercase.
*/
std::string to_uppercase (const std::string& a_string);

/** Indent lines of text by the specified number of spaces.

	The beginning of each line of text - where a line is terminated by a
	new-line ('\n') character - is prepended with the specified amount of
	whitespace (' ' characters). If no new-line is present but the lines
	string is not empty it is taken to be a single line that is shifted.

	@param lines	An arbitrary string.
	@param amount	The amount of whitespace to shift the lines. If this
		is less than or equal to zero no shifting is done.
	@return	The modified lines string.
*/
std::string indent (std::string lines, int amount);

/**	Get a PVL Lister appropriately configured for PDS label generation.

	The Lister will be configured to use strict mode except: Begin and
	End name markers on Aggregates will not be included, assignment
	value alignment will be enabled, array indenting will be enabled,
	single line commenting style will be used, and the statement end
	delimiter will not be used.

	@return	A pointer to an idaeim::PVL::Lister that has been allocated
		on the heap. <b>N.B.</b>: Delete when no longer needed.
*/
idaeim::PVL::Lister* label_lister ();


}	//	namespace HiRISE
}	//	namespace UA
#endif

