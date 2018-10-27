/*	JP2_box_type

CVS ID: JP2_box_type.cc,v 1.2 2010/11/24 03:36:20 castalia Exp

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
*/

#include	<iostream>
#include	<sstream>
#include	<iomanip>
#include	<string>
#include	<stdexcept>
#include	<cstdlib>
using namespace std;

/**	Convert a JP2 box type code to a string.

	Each byte, starting with the most significant byte, of the type value
	is appended as a character to a string.

	@param	box_type	The box type code value to be converted.
	@return	The string repesentation of the type value.
	@throws	invalid_argument	If a type code byte value does not
		correspond to a printable character (<32 or >126).
	@see	type_code(const std::string)
*/
string
type_name
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
unsigned int
type_code
	(
	const string&	name
	)
{
if (name.length () != 4)
	{
	ostringstream
		message;
	message
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


int
main
	(
	int		count,
	char**	args
	)
{
if (count == 1)
	{
	cout << "Usage: " << *args << " <box_type> [...]" << endl;
	exit (1);
	}

char
	*character;
unsigned int
	code;
string
	name;

cout << setfill ('0') << uppercase << hex;
for (int
		index = 1;
		index < count;
		index++)
	{
	code = (unsigned int)strtol (args[index], &character, 0);
	if (*character)
		{
		cout << "type name \"" << args[index] << "\" == ";
		try
			{
			code = type_code (args[index]);
			cout << "0x" << setw (8) << code << endl;
			}
		catch (invalid_argument except)
			{
			cout << "invalid -" << endl
				 << except.what () << endl
				 << endl;
			}
		}
	else
		{
		cout << "type code 0x" << setw (8) << code << " == ";
		try
			{
			name = type_name (code);
			cout << '"' << name << '"' << endl;
			}
		catch (invalid_argument except)
			{
			cout << "invalid -" << endl
				 << except.what () << endl
				 << endl;
			}
		}
	}

exit (0);
}
