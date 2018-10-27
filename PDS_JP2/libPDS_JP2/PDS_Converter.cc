/*	PDS_Converter

HiROC CVS ID: PDS_Converter.cc,v 1.14 2012/01/24 03:08:13 castalia Exp

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

#include	"PDS_Converter.hh"

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
using idaeim::PVL::Lister;
using namespace idaeim;

#include	<string>
using std::string;
#include	<iomanip>
using std::endl;
using std::flush;
#include	<fstream>
using std::ofstream;
using std::ios;
#include	<sstream>
using std::ostringstream;
#include	<stdexcept>
using std::runtime_error;


#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			(-1)
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_ACCESSORS		(1 << 1)
#define DEBUG_LABEL			(1 << 5)
#include	<iostream>
using std::clog;
#endif  // DEBUG


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	PDS_Converter
*/
/*==============================================================================
	Constants
*/
const char* const
	PDS_Converter::ID =
		"UA::HiRISE::PDS_Converter (1.14 2012/01/24 03:08:13)";

const char
	*PDS_Converter::DEFAULT_PRODUCT_TYPE
		= "unspecified";

const char
	*PDS_Converter::UNCOMPRESSED_FILE_PARAMETERS_GROUP
		= "UNCOMPRESSED_FILE",
	*PDS_Converter::COMPRESSED_FILE_PARAMETERS_GROUP
		= "COMPRESSED_FILE";

const char
	*PDS_Converter::GeoTIFF_PARAMETER_NAME
		= "GeoTIFF_Included",
	*PDS_Converter::GML_PARAMETER_NAME
		= "GML_Included",
	*PDS_Converter::NO_VERSION_CHANGE_PARAMETER_NAME
		= "No_Version_Change";

/*==============================================================================
	Constructors
*/
PDS_Converter::PDS_Converter ()
	:	PDS_Data (),
		Excluded_Data_Block_Names (NULL),
		Data_Blocks (NULL),
		Image_Data_Block_Names (NULL),
		IMAGE_Data_Block (NULL),
		Label_Size (0)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< PDS_Converter" << endl;
#endif
}


PDS_Converter::PDS_Converter
	(
	const std::string&	pathname,
	const char**		excluded_names,
	const char**		image_names
	)
	:	PDS_Data (pathname),
		Excluded_Data_Block_Names (excluded_names),
		Data_Blocks (NULL),
		Image_Data_Block_Names (image_names),
		IMAGE_Data_Block (NULL),
		Label_Size (0)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">>> PDS_Converter: " << pathname << endl;
#endif
Data_Blocks =
	PDS_Data::data_blocks (Excluded_Data_Block_Names, Image_Data_Block_Names);
IMAGE_Data_Block = image_data ();
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << "<<< PDS_Converter" << endl;
#endif
}


PDS_Converter::PDS_Converter
	(
	const PDS_Converter&	converter
	)
{*this = converter;}


PDS_Converter&
PDS_Converter::operator=
	(
	const PDS_Converter&	converter
	)
{
if (this != &converter)
	{
	//	Copy the parameters of the converter.
	parameters (converter);

	//	Copy the excluded and image data block names lists (they're constant).
	Excluded_Data_Block_Names = converter.Excluded_Data_Block_Names;
	Image_Data_Block_Names    = converter.Image_Data_Block_Names;

	//	Delete the current list of data blocks.
	clear_data_blocks ();
	if (converter.Data_Blocks)
		{
		//	Copy the data blocks on the list.
		Data_Blocks = new PDS_Data_Block_List;
		Image_Data_Block
			*image_data_block;
		for (PDS_Data_Block_List::iterator
				block  = converter.Data_Blocks->begin ();
				block != converter.Data_Blocks->end ();
			  ++block)
			{
			if ((image_data_block = dynamic_cast<Image_Data_Block*>(*block)))
				Data_Blocks->push_back (image_data_block);
			else
				Data_Blocks->push_back (new PDS_Data_Block (**block));
			}
		//	Identify the primary IMAGE data block.
		IMAGE_Data_Block = PDS_Data::image_data (Data_Blocks);
		}
	Label_Size = converter.Label_Size;
	}
return *this;
}


PDS_Converter::~PDS_Converter ()
{clear_data_blocks ();}

/*==============================================================================
	Accessors
*/
string
PDS_Converter::product_names () const
{return DEFAULT_PRODUCT_TYPE;}


Image_Data_Block*
PDS_Converter::image_data ()
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">>> PDS_Converter.image_data" << endl;
#endif
if (! IMAGE_Data_Block)
	{
	if ( Data_Blocks ||
		(Data_Blocks = PDS_Data::data_blocks
			(Excluded_Data_Block_Names, Image_Data_Block_Names)))
		IMAGE_Data_Block = PDS_Data::image_data (Data_Blocks);
	if (! IMAGE_Data_Block)
		{
		//	Search for a non-data block group.
		#if ((DEBUG) & DEBUG_ACCESSORS)
		clog << "    Searching for the "
			<< IMAGE_DATA_BLOCK_NAME << " parameter group." << endl;
		#endif
		Parameter
			*group = find_parameter (IMAGE_DATA_BLOCK_NAME,
				false, 0, AGGREGATE_PARAMETER);
		if (group)
			IMAGE_Data_Block = new Image_Data_Block (*group, -1);
		}
	#if ((DEBUG) & DEBUG_ACCESSORS)
	clog << "    " << (IMAGE_Data_Block ? "" : "No ")
			<< "IMAGE data block found." << endl;
	#endif
	}
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << "<<< PDS_Converter.image_data" << endl;
#endif
return IMAGE_Data_Block;
}


PDS_Converter&
PDS_Converter::excluded_data_block_names
	(
	const char**	names
	)
{
Excluded_Data_Block_Names = names;
//	Refresh the data blocks list.
refresh_data_blocks ();
return *this;
}


PDS_Converter&
PDS_Converter::image_data_block_names
	(
	const char**	names
	)
{
Image_Data_Block_Names = names;
//	Refresh the data blocks list.
refresh_data_blocks ();
return *this;
}


void
PDS_Converter::refresh_data_blocks ()
{
//	Clearing the data blocks will cause image_data to update both.
clear_data_blocks ();
image_data ();
}


void
PDS_Converter::clear_data_blocks ()
{
if (Data_Blocks)
	for (PDS_Data_Block_List::iterator
			block  = Data_Blocks->begin ();
			block != Data_Blocks->end ();
		  ++block)
		 delete *block;
delete Data_Blocks;
Data_Blocks      = NULL;
IMAGE_Data_Block = NULL;
}

/*==============================================================================
	Helpers:
*/
Aggregate*
PDS_Converter::PDS_JP2_image_parameters
	(
	const std::string&	JP2_pathname
	)
{
#if ((DEBUG) & DEBUG_LABEL)
clog << ">>> PDS_Converter::PDS_JP2_image_parameters: "
		<< JP2_pathname << endl;
#endif
if (! image_data ())
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to assemble parameters for the image files" << endl
			<< "  because " << IMAGE_DATA_BLOCK_NAME
				<< " parameters were not found in the PDS label.";
	throw runtime_error (message.str ());
	}

//	Only use the file name portion of the pathnames.
std::string
	PDS_filename (file_name (name ())),
	JP2_filename (file_name (JP2_pathname));
#if ((DEBUG) & DEBUG_LABEL)
clog << "    PDS_filename - " << PDS_filename << endl
	 << "    JP2_filename - " << JP2_filename << endl;
#endif

Aggregate
	*container = new Aggregate (Parser::CONTAINER_NAME),
	*group;

//	COMPRESSED_FILE group.
group = new Aggregate (COMPRESSED_FILE_PARAMETERS_GROUP, Parameter::OBJECT);
group->comment ("\nThe JPEG2000 image data file associated with this label.");
group->add (Assignment ("FILE_NAME")
	= String (JP2_filename)
		.type (Value::TEXT));
group->add (Assignment (RECORD_TYPE_PARAMETER_NAME)
	= String (BYTE_RECORD_TYPE)
		.type (Value::IDENTIFIER));
group->add (Assignment ("ENCODING_TYPE")
	= String ("JP2")
		.type (Value::TEXT));
group->add (Assignment ("ENCODING_TYPE_VERSION_NAME")
	= String ("ISO/IEC15444-1:2004")
		.type (Value::TEXT));
group->add (Assignment (INTERCHANGE_FORMAT_PARAMETER_NAME)
	= String ("BINARY")
		.type (Value::IDENTIFIER));
group->add ((Assignment ("UNCOMPRESSED_FILE_NAME")
	= String (PDS_filename)
		.type (Value::TEXT))
		.comment ("The name of the original source file."));
group->add ((Assignment ("REQUIRED_STORAGE_BYTES")
	= Integer ((unsigned long long)IMAGE_Data_Block->image_bands ()
							* IMAGE_Data_Block->image_width ()
							* IMAGE_Data_Block->image_height ()
							* IMAGE_Data_Block->pixel_bytes ())
		.units (BYTES_UNITS))
		.comment ("The amount of original image data."));
group->add (Assignment("^DESCRIPTION")
	= String ("JP2INFO.TXT")
		.type (Value::TEXT));
container->poke_back (group);
#if ((DEBUG) & DEBUG_LABEL)
clog << "    COMPRESSED_FILE parameters - " << endl
	 << *group << endl;
#endif

//	UNCOMPRESSED_FILE group.
group = new Aggregate (UNCOMPRESSED_FILE_PARAMETERS_GROUP, Parameter::OBJECT);
group->comment ("\nThe source image data definition.");
group->add (Assignment ("FILE_NAME")
	= String (PDS_filename)
		.type (Value::TEXT));
group->add (Assignment (RECORD_TYPE_PARAMETER_NAME)
	= String (FIXED_LENGTH_RECORD_TYPE)
		.type (Value::IDENTIFIER));
group->add (Assignment (RECORD_BYTES_PARAMETER_NAME)
	= Integer
		(IMAGE_Data_Block->image_width () * IMAGE_Data_Block->pixel_bytes ())
		.units (BYTES_UNITS));
group->add (Assignment (FILE_RECORDS_PARAMETER_NAME)
	= Integer
		(IMAGE_Data_Block->image_height () * IMAGE_Data_Block->image_bands ()));
group->add (Assignment
		(RECORD_POINTER_PARAMETER_MARKER + string (IMAGE_DATA_BLOCK_NAME))
	= String (PDS_filename)
		.type (Value::TEXT));

//	Add the original IMAGE parameters.
group->add (*IMAGE_Data_Block);
container->poke_back (group);
#if ((DEBUG) & DEBUG_LABEL)
clog << "    UNCOMPRESSED_FILE parameters - " << endl
	 << *group << endl;
#endif

#if ((DEBUG) & DEBUG_LABEL)
clog << "<<< PDS_Converter::PDS_JP2_image_parameters" << endl; 
#endif
return container;
}


unsigned int
PDS_Converter::write_label
	(
	const std::string&		pathname,
	PDS_Data&				label,
	idaeim::PVL::Lister*	lister,
	bool					pad_label
	)
{
#if ((DEBUG) & DEBUG_LABEL)
clog << ">>> PDS_Converter::write_label: " << pathname << endl;
#endif
//	Open the new label file.
ofstream
	label_file (pathname.c_str(), ios::trunc);
if (! label_file)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Unable to open the output label file: " << pathname;
	throw ios::failure (message.str ());
	}

Lister
	*PDS_PVL_lister = lister;
if (! PDS_PVL_lister)
	PDS_PVL_lister = label_lister ();
else
	PDS_PVL_lister->reset_total ();

/*	Change the name of the top level aggregate
	so that only its contents are listed.
*/
string
	label_name (label.name ());
label.name (Parser::CONTAINER_NAME);

//	Write out the label.
label_file 
	<< *PDS_PVL_lister
	<< label
	<< flush;

label.name (label_name);

unsigned int
	label_size = PDS_PVL_lister->total ();
if (pad_label &&
	label_size < Label_Size)
	{
	while (label_size++ < Label_Size)
		label_file << ' ';
	label_file.flush ();
	}
label_file.close ();

if (! lister)
	delete PDS_PVL_lister;
#if ((DEBUG) & DEBUG_LABEL)
clog << "<<< PDS_Converter::write_label: " << label_size << endl;
#endif
return label_size;
}


}	//	namespace HiRISE
}	//	namespace UA
