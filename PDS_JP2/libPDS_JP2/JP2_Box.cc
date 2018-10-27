/*	JP2_Box

HiROC CVS ID: JP2_Box.cc,v 1.6 2010/11/24 03:32:14 castalia Exp

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
*/

#include	"JP2_Box.hh"

#include	<string>
using std::string;
#include	<algorithm>
using std::find;
#include	<sstream>
using std::ostringstream;
#include	<iomanip>
using std::endl;
using std::setw;
using std::setfill;
using std::hex;
#include	<stdexcept>
using std::logic_error;
using std::invalid_argument;
using std::length_error;
using std::bad_alloc;
#include	<cstring>


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
using std::dec;
#endif  // DEBUG


#ifndef DOXYGEN_PROCESSING
namespace
{
unsigned int
box_code
	(
	const std::string&	name
	)
{
try {return UA::HiRISE::JP2_Box::type_code (name);}
catch (invalid_argument&) {return (unsigned int)-1;}
}


std::string
box_name
	(
	unsigned int	code
	)
{
try {return UA::HiRISE::JP2_Box::type_name (code);}
catch (invalid_argument&) {return "INVALID";}
}


const char*
plural
	(
	unsigned int	amount
	)
{return (amount == 1) ? "" : "s";}
}
#endif


namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	JP2_Box
*/
/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
const char* const
	JP2_Box::ID =
		"UA::HiRISE::JP2_Box (1.6 2010/11/24 03:32:14)";

const unsigned int
	JP2_Box::UUID_BOX_TYPE					= 0x75756964,		//	"uuid"
		JP2_Box::UUID_SIZE						= 16,
	JP2_Box::UUID_INFO_BOX_TYPE				= 0x75696E66,		//	"uinf"
		JP2_Box::UUID_LIST_BOX_TYPE				= 0x756C7374,	//	"ulst"
		JP2_Box::URL_BOX_TYPE					= 0x75726C20,	//	"url "
	JP2_Box::XML_BOX_TYPE					= 0x786D6C20,		//	"xml "
	JP2_Box::ASSOCIATION_BOX_TYPE			= 0X61736F63,		//	"asoc"
	JP2_Box::LABEL_BOX_TYPE					= 0X6C626C20,		//	"lbl "
	JP2_Box::INTELLECTUAL_PROPERTY_BOX_TYPE	= 0x6A703269;		//	"jp2i"

/*==============================================================================
	Constructors:
*/
/**	Construct JP2_Box with no content.
*/
JP2_Box::JP2_Box ()
	:	Type (0),
		Content (NULL),
		Content_Amount (0),
		Locally_Owned_Content (false),
		Container (NULL)
{}


JP2_Box::JP2_Box
	(
	unsigned int			box_type,
	const unsigned char*	data,
	unsigned int			amount
	)
	:	Type (0),
		Content (NULL),
		Content_Amount (0),
		Locally_Owned_Content (false),
		Container (NULL)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< JP2_Box: \"" << box_name (box_type) << "\" "
		<< "(0x" << hex << setfill ('0') << setw (8) << box_type << ')'
		<< dec << setfill (' ') << endl
	 << "    content amount - " << amount << endl;
#endif
type_code (box_type);
content (data, amount);
}


JP2_Box::JP2_Box
	(
	unsigned int			box_type,
	const std::string&		text
	)
	:	Type (0),
		Content (NULL),
		Content_Amount (0),
		Locally_Owned_Content (false),
		Container (NULL)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">-< JP2_Box: \"" << box_name (box_type) << "\" "
		<< "(0x" << hex << setfill ('0') << setw (8) << box_type << ')'
		<< dec << setfill (' ') << endl
	 << "    text - \"" << text << '"' << endl;
#endif
type_code (box_type);
content (text);
}


JP2_Box::~JP2_Box ()
{
if (Locally_Owned_Content)
	delete Content;

if (! Sub_Boxes.empty ())
	for (JP2_Box_List::iterator
			sub_box = Sub_Boxes.begin ();
			sub_box != Sub_Boxes.end ();
		   ++sub_box)
		delete *sub_box;
}

/*==============================================================================
	Accessors:
*/
JP2_Box&
JP2_Box::type_name
	(
	const std::string&	name
	)
{
Type = type_code (name);
return *this;
}


JP2_Box&
JP2_Box::type_code
	(
	unsigned int	box_type
	)
{
//	Check that the type_code value is valid.
type_name (box_type);
Type = box_type;
return *this;
}


JP2_Box&
JP2_Box::content
	(
	const unsigned char*	data,
	unsigned int			amount
	)
{
unsigned char*
	new_data = NULL;
if (data &&
	amount)
	{
	try {new_data = new unsigned char[amount];}
	catch (bad_alloc&)
		{
		ostringstream
			message;
		message << ID << endl
				<< "Insufficient memory to copy " << amount
					<< " byte" << plural (amount) << " of data content." << endl
				<< "Use attach_content instead.";
		throw length_error (message.str ());
		}
	memcpy (new_data, data, amount);
	}
if (Locally_Owned_Content)
	delete Content;
Locally_Owned_Content = true;
Content = new_data;
if (Content)
	Content_Amount = amount;
else
	Content_Amount = 0;
return *this;
}


JP2_Box&
JP2_Box::content
	(
	const std::string&	text
	)
{return content ((const unsigned char*)text.c_str (), text.length ());}


JP2_Box&
JP2_Box::append_content
	(
	const unsigned char*	data,
	unsigned int			amount
	)
{
if (! data ||
	! amount)
	return *this;

if (Content_Amount &&
	! Locally_Owned_Content)
	{
	string
		box_type ("(unknown)");
	try {box_type = type_name ();}
	catch (invalid_argument&) {}
	ostringstream
		message;
	message << ID << endl
			<< "Attempt to append " << amount << " byte" << plural (amount)
				<< " of data to a \"" << box_type
				<< "\" box" << endl
			<< "with " << Content_Amount << " byte" << plural (amount)
				<< " of content that is not locally owned." << endl;
	throw logic_error (message.str ());
	}
unsigned char
	*content;
try {content = new unsigned char[Content_Amount + amount];}
catch (bad_alloc&)
	{
	ostringstream
		message;
	message << ID << endl
			<< "Insufficient memory to append "
				<< amount << " byte" << plural (amount) << " of data" << endl
			<< "to the current "
				<< Content_Amount << " byte" << plural (Content_Amount)
				<< " of content.";
	throw length_error (message.str ());
	}
if (Content_Amount)
	memcpy (content, Content, Content_Amount);
memcpy (content + Content_Amount, data, amount);
if (Locally_Owned_Content)
	delete Content;
Content = content;
Content_Amount += amount;
return *this;
}


JP2_Box&
JP2_Box::append_content
	(
	const std::string&	text
	)
{return append_content ((const unsigned char*)text.c_str (), text.length ());}


JP2_Box&
JP2_Box::attach_content
	(
	unsigned char*	data,
	unsigned int	amount
	)
{
if (Locally_Owned_Content)
	delete Content;
Locally_Owned_Content = false;
Content = data;
if (Content)
	Content_Amount = amount;
else
	Content_Amount = 0;
return *this;
}

//------------------------------------------------------------------------------
//	Sub-boxes
JP2_Box&
JP2_Box::add
	(
	JP2_Box*	sub_box
	)
{
if (sub_box)
	{
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << ">>> JP2_Box::add: sub_box \"" << box_name (sub_box->Type) << "\" "
		<< "(0x" << hex << setfill ('0') << setw (8) << sub_box->Type << ')'
		<< " to \"" << box_name (Type) << "\" "
		<< "(0x" << setw (8) << Type << ')'
		<< dec << setfill (' ') << endl;
	#endif
	if (sub_box == this)
		{
		ostringstream
			message;
		message << ID << endl
				<< "Attempt to add a \"";
		try {message << sub_box->type_name ();}
		catch (invalid_argument&)
			{message << "0x" << hex << setfill ('0') << setw (8) << sub_box->Type;}
		message << "\" box to itself.";
		throw invalid_argument (message.str ());
		}
	if (sub_box->Container)
		sub_box->Container->remove (sub_box);
	Sub_Boxes.push_back (sub_box);
	sub_box->Container = this;
	#if ((DEBUG) & DEBUG_MANIPULATORS)
	clog << "<<< JP2_Box::add" << endl;
	#endif
	}
return *this;
}


bool
JP2_Box::remove
	(
	JP2_Box*	sub_box
	)
{
JP2_Box_List::iterator
	position = find (Sub_Boxes.begin (), Sub_Boxes.end (), sub_box);
if (position == Sub_Boxes.end ())
	return false;
Sub_Boxes.erase (position);
if (sub_box)
	sub_box->Container = NULL;
return true;
}


/*==============================================================================
	Helpers
*/
std::string
JP2_Box::type_name
	(
	unsigned int	box_type
	)
{
string
	name;
char
	character;
for (unsigned int
		mask = 0xFF000000,
		shift = 24;
	 	mask;
	 	mask >>= 8,
		shift -= 8)
	{
	//	Pull out the next byte as a char.
	character = (char)((box_type & mask) >> shift);
	if (character < 32 ||
		character > 126)
		{
		ostringstream
			message;
		message
			<< ID << endl
			<< "Byte " << (shift >> 3)
				<< " of box type " << box_type
				<< " (0x" << hex << setfill ('0') << setw (8) << box_type
				<< ") is not a printable type name character.";
		throw invalid_argument (message.str ());
		}
	else
		name += character;
	}
return name;
}


unsigned int
JP2_Box::type_code
	(
	const std::string&	name
	)
{
if (name.length () != 4)
	{
	ostringstream
		message;
	message
		<< ID << endl
		<< "The type name used to produce a type code must have 4 characters." << endl
		<< "The specified string has " << name.length () << " characters:" << endl
		<< '"' << name << '"';
	throw invalid_argument (message.str ());
	}
int
	code = 0,
	character;
for (unsigned int
		index = 0;
		index < name.length ();
		index++)
	{
	character = (int)name[index] & 0xFF;
	if (character < 32 ||
		character > 126)
		{
		ostringstream
			message;
		message
			<< ID << endl
			<< "Character " << index << " is not a printable character" << endl
			<< "for convering to a type code value from string" << endl
			<< '"' << name << '"';
		throw invalid_argument (message.str ());
		}
	code <<= 8;
	code |= character;
	}
return code;
}


}	//	namespace HiRISE
}	//	namespace UA

