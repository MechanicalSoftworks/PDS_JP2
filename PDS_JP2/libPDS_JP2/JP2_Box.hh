/*	JP2_Box

HiROC CVS ID: JP2_Box.hh,v 1.4 2007/10/20 00:39:47 castalia Exp

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

#ifndef _JP2_Box_
#define _JP2_Box_

#include	<string>
#include	<vector>


namespace UA
{
namespace HiRISE
{
/**	A <i>JP2_Box</i> contains JP2 file format box data.

	@author		Bradford Castalia; UA/HiROC
	@version	1.4
*/
class JP2_Box
{
public:
/*==============================================================================
	Types:
*/
//!	List of JP2 boxes.
typedef	std::vector<JP2_Box*>	JP2_Box_List;

/*==============================================================================
	Constants:
*/
//!	Class identification name with source code version and date.
static const char* const
	ID;

//!	UUID box type.
static const unsigned int
	UUID_BOX_TYPE;
//!	Size of the UUID data content.
static const unsigned int
	UUID_SIZE;
//!	UUID Info box type.
static const unsigned int
	UUID_INFO_BOX_TYPE;
//!	UUID List box type.
static const unsigned int
	UUID_LIST_BOX_TYPE;

//!	URL box type.
static const unsigned int
	URL_BOX_TYPE;

//!	XML box type.
static const unsigned int
	XML_BOX_TYPE;

//!	Association box type.
static const unsigned int
	ASSOCIATION_BOX_TYPE;

//!	Label box type.
static const unsigned int
	LABEL_BOX_TYPE;

//!	Intellectual Property box type.
static const unsigned int
	INTELLECTUAL_PROPERTY_BOX_TYPE;

/*==============================================================================
	Constructors:
*/
/**	Construct a JP2_Box with no data content.
*/
JP2_Box ();

/**	Construct a JP2_Box of some type and with optional data content.

	@param	box_type	The 32-bit integer box type code value.
	@param	amount	The number of data content bytes. If zero the box
		will be emptied and the data will be ignored.
	@param	data	A pointer (const unsigned char*) to the data content.
		<b>N.B.</b>: The data will be copied to a {@link
		locally_owned_content() locally owned data} buffer. If NULL the
		box will be emptied and the amount will be ignored.
	@throws	invalid_argument	If a type code byte value does not
		correspond to a printable character (<32 or >126).
	@throws	length_error	If insufficient memory is available to
		allocate the data content buffer.
	@see	content(unsigned int, const unsigned char*)
*/
explicit JP2_Box (unsigned int box_type,
	const unsigned char* data = NULL, unsigned int amount = 0);

/**	Construct a JP2_Box of some type with text content.

	@param	box_type	The 32-bit integer box type code value.
	@param	text	The text string to be set as the box content.
	@see	content(const std::string&)
*/
explicit JP2_Box (unsigned int box_type, const std::string& text);

/**	Destroy this JP2_Box.

	Any {@link locally_owned_content() locally owned content} data
	is freed.
*/
virtual ~JP2_Box ();

/*==============================================================================
	Accessors:
*/
/**	Get the type name of the box.

	The type name is the string representation of the {@link type_code()
	type code} bytes that are stored as the second value of each JP2 box.

	@return	The type name of the box. This will be the empty string if
		the box is undefined.
	@throws	invalid_argument	If the {@link type_code() type code}
		is an invalid value.
	@see type_name(unsigned int)
*/
std::string type_name () const
	{return Type ? type_name (Type) : "";}

/**	Set the type name of the box.

	@param	name	The type name to be applied to the JP2 box.
	@return	This JP2_Box.
	@throws	invalid_argument	If the string does not contain exactly
		four characters or any character is not printable (<32 or >126).
	@see	type_code(const std::string&)
*/
JP2_Box& type_name (const std::string& name);

/**	Get the type code of the box.

	The type code is the second value of each JP2 box.

	@return	The JP2 box type code value. This will be zero if the box is
		undefined.
*/
unsigned int type_code () const
	{return Type;}

/**	Set the type code of the box.

	@param	box_type	The 32-bit integer box type code value.
	@return	This JP2_Box.
	@throws	invalid_argument	If a type code byte value does not
		correspond to a printable character (<32 or >126).
*/
JP2_Box& type_code (unsigned int box_type);

/**	Get the box data content amount.

	The box data content amount is the size of the {@link content()
	content} buffer, in bytes.

	@return	The size of the box data content data buffer, in bytes. This
		will be zero if the box has no data content.
*/
unsigned int content_amount () const
	{return Content_Amount;}

/**	Get the box data content.

	@return	A pointer to the box data content as an unsigned char*.
		<b>Caution</b>: The box data content is not copied.
*/
unsigned char* content () const
	{return Content;}

/**	Set the box data content.

	Any current content is replaced.

	@param	data	A pointer (const unsigned char*) to the data content.
		<b>N.B.</b>: The data will be copied to a {@link
		locally_owned_content() locally owned content} buffer. If NULL
		the box will be emptied and the amount will be ignored.
	@param	amount	The number of data bytes. If zero the box will be
		emptied and the data will be ignored.
	@return	This JP2_Box.
	@throws	length_error	If insufficient memory is available to
		allocate the data content buffer.
	@see	attach_content(unsigned int, unsigned char*)
*/
JP2_Box& content (const unsigned char* data, unsigned int amount = 0);

/**	Set the box data content.

	Any current content is replaced.

	The characters of the string, plus a terminating zero-value character,
	are copied into the box content.

	@param	text	The text string to be set as the box content.
	@return	This JP2_Box.
	@throws	length_error	If insufficient memory is available to
		allocate the data content buffer.
	@see	content(unsigned int, const unsigned char*)
*/
JP2_Box& content (const std::string& text);

/**	Test if the box data content buffer is locally owned.

	A locally owned data content buffer has been allocated by the JP2_Box
	and will be deleted when the JP2_Box is destroyed. If the data
	content buffer was {@link attach_content(unsigned char*, unsigned int)
	attached} to the JP2_Box it is externally owned and will not
	be deleted when the JP2_Box is destroyed; in this case it is the
	responsibility of the data buffer owner to ensure that the buffer
	remains valid until the JP2_Box will no longer be used.

	<b>N.B.</b>: Data content that is not locally owned will not be
	freed when the JP2_Box is destroyed.

	@return	true if the data content buffer is locally owned, false
		otherwise.
*/
bool locally_owned_content () const
	{return Locally_Owned_Content;}

/**	Set the box data content.

	Any current content is replaced.

	@param	data	A pointer (const unsigned char*) to the data content.
		<b>N.B.</b>: The data data will not be copied. If NULL the box
		will be emptied and the amount will be ignored.
	@param	amount	The number of data bytes. If zero the box will be
		emptied and the data will be ignored.
	@return	This JP2_Box.
	@see	content(unsigned int, const unsigned char*)
*/
JP2_Box& attach_content (unsigned char* data, unsigned int amount = 0);

/*==============================================================================
	Manipulators:
*/
/**	Append data to the box data content.

	<b>N.B.</b>: Data can only be appended to {@link locally_owned_content()
	locally owned content}.

	A new data content buffer is provided that is the size of the current
	{@link content_amount() content amount} plus the amount of new data.
	The current content and new data are copied into the new buffer. The
	previous buffer is deleted, the new buffer becomes the current
	{@link content() content} and content amount is updated.

	@param	amount	The number of data bytes. If zero nothing is done.
	@param	data	A pointer (const unsigned char*) to the additional
		data content. If NULL nothing is done.
	@return	This JP2_Box.
	@throws	logic_error		If there is a non-zero amount of content
		that is not locally owned.
	@throws	length_error	If insufficient memory is available to
		allocate the data content buffer.
*/
JP2_Box& append_content (const unsigned char* data, unsigned int amount);

/**	Append text to the box data content.

	<b>N.B.</b>: Data can only be appended to {@link locally_owned_content()
	locally owned content}.

	The characters of the text string, plus a terminating null
	character, are {@link append_content(const unsigned char *, unsigned int)
	appended} to the current box content.

	@param	text	The text string to be appended to the box content.
	@return	This JP2_Box.
*/
JP2_Box& append_content (const std::string& text);

//------------------------------------------------------------------------------
//	Sub-boxes

/**	Add a sub-box to this box.

	If the sub-box is contained in another box it is {@link
	remove(JP2_Box*) remove}d from its {@link container() container}.

	The sub-box is added to the end of the list of {@link sub_boxes()
	sub-boxes} and its {@link container() container} is set to this
	JP2_Box.

	@param	sub_box	A pointer to the JP2_Box that is to be added to this
		box. If NULL nothing is done.
	@return	This JP2_Box.
	@throws	invalid_argument	If the sub-box is this JP2_Box.
	@see	remove(JP2_Box*)
*/
JP2_Box& add (JP2_Box* sub_box);

/**	Add a sub-box to this box.

	@param	sub_box	A pointer to the JP2_Box that is to be added to this
		box. If NULL nothing is done.
	@return	This JP2_Box.
	@throws	invalid_argument	If the sub-box is this JP2_Box.
	@see	add(JP2_Box*)
*/
JP2_Box& add (JP2_Box& sub_box)
	{return add (&sub_box);}

/**	Remove a sub-box from this box.

	If the sub-box is found in the list of {@link sub_boxes() sub-boxes}
	it is removed from the list and its {@link container() container}
	is set to NULL.

	@param	sub_box	A pointer to the JP2_Box that is to be removed from
		this box. A NULL argument is allowed and will be used to remove
		a NULL entry if one is present, however this should not occur
		if the {@link add(JP2_Box&) add} method is always used to add
		sub-boxes to the box.
	@return	true if the sub-box was removed, or false if the sub-box
		was not found in this box.
	@see	add(JP2_Box*)
*/
bool remove (JP2_Box* sub_box);

/**	Get the list of sub-boxes contained in this box.

	<b>Caution</b>: The JP2_Box_List is a vector of JP2_Box pointers
	which can be manipulated (re-ordered, etc.) as desired, however
	adding and removing entries should only be done with the
	{@link add(JP2_Box&) add} and {@link remove(JP2_Box*) remove}
	methods to maintain the correct {@link container() container}
	relationships.

	@return	A reference to the JP2_Box_List for this box.
*/
JP2_Box_List& sub_boxes ()
	{return Sub_Boxes;}

/**	Get the container of this box.

	@return	A pointer to the JP2_Box that has this box in its list
		of {@link sub_boxes() sub-boxes}. This will be NULL if this
		box is not contained in another box.
*/
JP2_Box* container () const
	{return Container;}

/*==============================================================================
	Helpers
*/
/**	Convert a JP2 box type code to a string.

	Each byte, starting with the most significant byte, of the type value
	is appended as a character to a string.

	@param	box_type	The box type code value to be converted.
	@return	The string repesentation of the type value.
	@throws	invalid_argument	If a type code byte value does not
		correspond to a printable character (<32 or >126).
	@see	type_code(const std::string)
*/
static std::string type_name (unsigned int box_type);

/**	Convert a JP2 box type string to an integer code.

	Each character of the string is placed as a byte value in the
	corresponding location of the type code, starting with the most
	significant byte.

	@param	name	The type name string to be converted.
	@return	The integer type code value.
	@throws	invalid_argument	If the string does not contain
		exactly four characters or any character is not
		printable (<32 or >126).
	@see	type_name(unsigned int)

*/
static unsigned int type_code (const std::string& name);

/*==============================================================================
	Data members:
*/
protected:

//!	The JP2 box type code.
unsigned int
	Type;

//!	The data content buffer.
unsigned char
	*Content;

//!	The amount (bytes) of content data.
unsigned int
	Content_Amount;

//!	Flag for a locally owned data content buffer.
bool
	Locally_Owned_Content;

//!	Pointer to the JP2_Box that contains this box.
JP2_Box
	*Container;

//!	List of boxes contained in this box.
JP2_Box_List
	Sub_Boxes;

};	//	class JP2_Box


}	//	namespace HiRISE
}	//	namespace UA
#endif

