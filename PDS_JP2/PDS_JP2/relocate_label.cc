/*	relocate_label

HiROC CVS ID: relocate_label.cc,v 1.2 2012/02/04 01:29:26 castalia Exp

Copyright (C) 2012 Arizona Board of Regents on behalf of the
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

//	Kakadu
#include	"jp2.h"

#include	"Files.hh"
#include	"endian.hh"
using namespace PIRL;

#include	<iostream>
#include	<iomanip>
#include	<fstream>
#include	<sstream>
#include	<string>
#include	<algorithm>
#include	<stdexcept>
#include	<cstdio>
#include	<cstdlib>
#include	<cctype>
#include	<cstring>
#include	<cerrno>
using namespace std;

#ifdef _WIN32
#	include <Windows.h>
#endif

/*==============================================================================
	Parameters
*/
//!	Exit status values.
const int
	SUCCESS						= 0,
	BAD_SYNTAX					= 1,
	NO_INPUT_FILE				= 20,
	NO_LABEL_LOCATION			= 21,
	EXISTING_BACKUP_FILE		= 22,
	IO_FAILURE					= 29,
	JP2_ERROR					= 30;

/*==============================================================================
	Constants
*/
#ifndef MODULE_VERSION
#define _VERSION_ " "
#else
#define _VERSION_ " v" MODULE_VERSION " "
#endif
//!	Application identification name with source code version and date.
const char
	*ID =
		"relocate_label"
		_VERSION_
		"(1.2 2012/02/04 01:29:26)";

//!	The runtime command name.
char
	*Program_Name;

//!	Suffix appended to input pathname to create backup pathname.
#ifndef BACKUP_FILENAME_SUFFIX
#define BACKUP_FILENAME_SUFFIX			"-backup"
#endif

//!	JP2 UUID Info and URL box names.
const char
	* const UUID_INFO_BOX_NAME			= "uinf",
	* const URL_BOX_NAME				= "url ";

const int
	VERS_AND_FLAG_BYTES					= 4;
	
#ifdef _WIN32
/*==============================================================================
	realpath
*/
/**	Implemented for Windows compatibility.
	See http://man7.org/linux/man-pages/man3/realpath.3.html for details.
*/
char*
realpath
	(
	const char*	path,
	char*		resolved_path
	)
{
if (resolved_path == NULL)
	{
	resolved_path = (char*)malloc(MAX_PATH * sizeof(char));
	}
	
GetFullPathNameA(path, MAX_PATH, resolved_path, NULL);

return resolved_path;
}
#endif

/*==============================================================================
	Usage
*/
/**	Application command line syntax and usage.

	<h3>Command line syntax:
	</h3>

	<b>relocate_label</b> [<i>Options</i>] [-Input] &lt;<i>pathname</i>&gt;
		-Location &lt;<i>pathname</i>&gt;

	<h3>Command line options:
	</h3>

	<h4>[<b>-I</b>nput] &lt;<i>pathname</i>&gt;
	</h4>
	The pathname of the input JP2 file.

	<h4><b>-L</b>ocation &lt;<i>pathname</i>&gt;
	</h4>
	The pathname of the label file. The pathname must be relative to the
	location of the JP2 file.

	<h4><b>-N</b>o_]<b>B</b>ackup
	</h4>
	When the JP2 file is modified it is first renamed by appending a
	"-backup" suffix the the filename before being copied to a file with
	the original name and modified contents. If the -Backup option is
	specified the original file, now with the "-backup" suffix in its
	filename, will remain; otherwise the backup file is deleted when
	the operation completes.

	Default: Do not leave a backup file.

	<h4><b>-H</b>elp
	</h4>
		Prints this usage description.

	@param	program_name	The name of the executable. This is expected to
		be the first entry in the main arguments list.
	@param	exit_status	This method always result in program exit. If the
		exit status value is not specified the #BAD_SYNTAX value will be used.
	@param	list_descriptions	If true, long option descriptions will be
		listed; otherwise only the brief option syntax is listed.
	@see	main(int, char**)
*/
void
usage
	(
	const char*	program_name,
	int			exit_status = BAD_SYNTAX,
	bool		list_descriptions = false
	)
{
cout
	<< "Usage: " << program_name << " [options] [-Input] <pathname> "
		<< "-Location <pathname>" << endl;
if (list_descriptions)
	cout
	<< endl
	<< "The pathname reference to the location of the external label file" << endl
	<< "associated with a PDS/JP2 data set is changed in a JP2 file." << endl
	<< endl
	<< "The specification of a PDS/JP2 data set requires that the JP2 file" << endl
	<< "contains a URL box, a sub-box of a UUID Info box, with a value that" << endl
	<< "provides the pathname of the external PDS metadata label file for the" << endl
	<< "data set. The URL value is a simple filesystem pathname (no" << endl
	<< "protocol/scheme prefix) that must be relative the location of the JP2" << endl
	<< "file." << endl
	<< endl
	<< "<b>N.B.</b>: The external label file is not modified or moved. If" << endl
	<< "the file does not exist at the new location a warning is provided." << endl
	<< endl
	<< "The input file is checked for being a valid JP2 file with a UUID Info" << endl
	<< "box containing the required URL box. If the existing pathname that is" << endl
	<< "found is the same as the specified new pathname nothing is done." << endl
	<< "Otherwise the JP2 file is moved to a backup file having the same name" << endl
	<< "with a \"-backup\" suffix and this is copied to a new file having the" << endl
	<< "original name with the modified UUID Info box replacing the previous" << endl
	<< "box; no other changes are made to the JP2 file. The backup file is" << endl
	<< "removed after the new JP2 file is successfully written unless the" << endl
	<< "-No_Backup option is specified." << endl
	<< endl;

cout
	<< "Options -" << endl;

cout
	<< "  [-Input] <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    The pathname of the input JP2 file." << endl
	<< endl;

cout
	<< "  -Location <pathname>" << endl;
if (list_descriptions)
	cout
	<< "    The pathname of the label file. The pathname must be relative to the" << endl
	<< "    location of the JP2 file." << endl
	<< endl;

cout
	<< "  -[No_]Backup" << endl;
if (list_descriptions)
	cout
	<< "    When the JP2 file is modified it is first renamed by appending a" << endl
	<< "    \"-backup\" suffix the the filename before being copied to a file with" << endl
	<< "    the original name and modified contents. If the -Backup option is" << endl
	<< "    specified the original file, now with the \"-backup\" suffix in its" << endl
	<< "    filename, will remain; otherwise the backup file is deleted when" << endl
	<< "    the operation completes." << endl
	<< endl
	<< "    Default: Do not leave a backup file." << endl
	<< endl;

cout
	<< "  -Force" << endl;
if (list_descriptions)
	cout
	<< "    If a backup file already exists, remove it before creating the new" << endl
	<< "    backup file." << endl
	<< endl
	<< "    Default: Exit without replacing an existing backup file." << endl
	<< endl;

cout
	<< "  -Help" << endl;
if (list_descriptions)
	cout
	<< "    Prints this usage description." << endl
	<< endl;

exit (exit_status); 
}

#if defined (DEBUG)
/*******************************************************************************
	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL		-1
#define DEBUG_JP2		(1 << 1)
#define DEBUG_IO		(1 << 2)
#endif  // DEBUG

/*==============================================================================
	Local functions
*/
kdu_uint32 box_type (const char* box_name);
string box_name (kdu_uint32 box_type);

/*==============================================================================
	Main
*/
/**	relocate_label application.

	The pathname reference to the location of the external label file
	associated with a PDS/JP2 data set is changed in a JP2 file.

	The specification of a PDS/JP2 data set requires that the JP2 file
	contains a URL box, a sub-box of a UUID Info box, with a value that
	provides the pathname of the external PDS metadata label file for the
	data set. The URL value is a simple filesystem pathname (no
	protocol/scheme prefix) that must be relative the location of the JP2
	file.

	<b>N.B.</b>: The external label file is not modified or moved. If
	the file does not exist at the new location a warning is provided.

	The input file is checked for being a valid JP2 file with a UUID Info
	box containing the required URL box. If the existing pathname that is
	found is the same as the specified new pathname nothing is done.
	Otherwise the JP2 file is moved to a backup file having the same name
	with a "-backup" suffix and this is copied to a new file having the
	original name with the modified UUID Info box replacing the previous
	box; no other changes are made to the JP2 file. The backup file is
	removed after the new JP2 file is successfully written unless the
	-No_Backup option is specified.

	<h3>Exit status values:
	</h3>

	<dl>
	<dt>#SUCCESS
	<dd>The application completed successfully.
	<dt>#BAD_SYNTAX
	<dd>There was a syntax problem in the command line, or the label
		file location is an absolute pathname rather than being relative
		to the JP2 file location.
	<dt>#NO_INPUT_FILE
	<dd>No input JP2 file pathname was specified or the pathname does not
		exist.
	<dt>#NO_LABEL_LOCATION
	<dd>No PDS label file location was specified on the command line.
	<dt>#EXISTING_BACKUP_FILE
	<dd>A file with the name of the input JP2 and a "-backup" suffix exists,
		but the -Force option was not specified to force overwriting.
	<dt>#IO_FAILURE
	<dd>A filesystem I/O failure has occurred. This will occur it the
		input file or its backup can not be read, or the new output file
		can not be written.
	<dt>#JP2_ERROR
	<dd>The input file is not a valid JP2 file or does not contain the
		required URL box with a pathname value.
	</dl>

	@param	argument_count	The number of command line arguments.
	@param	arguments	The array of command line arguments.
	@see	#usage(const char*, int, bool)

	@author		Bradford Castalia, UA/HiROC
	@version	1.2
*/
int
main
	(
	int		argument_count,
	char	**arguments
	)
{
//	Application identification.
cout << ID << endl << endl;

string
	JP2_pathname,
	JP2_backup_pathname,
	new_label_pathname,
	pathname;
bool
	no_backup_file	= false,
	force_overwrite	= false;

/*------------------------------------------------------------------------------
   Command line arguments
*/
if (argument_count == 1)
    usage (*arguments);

int
	index;
for (index = 1;
	 index < argument_count;
	 index++)
	{
	if (arguments[index][0]== '-')
		{
		switch (toupper (arguments[index][1]))
			{
			case 'I':	//	Input pathname.
			case 'J':	//	JP2 pathname.
				if (++index == argument_count || 
					arguments[index][0] == '-')
					{
					cout << "Missing JP2 input file pathname." << endl
						 << endl;
					usage (*arguments);
					}
				JP2_Pathname_Argument:
				if (! JP2_pathname.empty ())
					{
					cout << "Only one JP2 input file, please." << endl
						 << "   First filename: " << JP2_pathname << endl
						 << "  Second filename: " << arguments[index] << endl
						 << endl;
					usage (*arguments);
					}
				  JP2_pathname = arguments[index];
				break;

			case 'L':	//	Label Location pathname.
				if (++index == argument_count || 
					arguments[index][0] == '-')
					{
					cout << "Missing PDS label file pathname." << endl
						 << endl;
					usage (*arguments);
					}
				if (! new_label_pathname.empty ())
					{
					cout << "Only one PDS label file pathname, please." << endl
						 << "   First filename: " << new_label_pathname << endl
						 << "  Second filename: " << arguments[index] << endl
						 << endl;
					usage (*arguments);
					}
				  new_label_pathname = arguments[index];
				break;

			case 'N':	//	No backup file.
				no_backup_file = true;
				break;

			case 'B':	//	Backup file retained.
				no_backup_file = false;
				break;

			case 'F':	//	Force backup file replacement.
				force_overwrite = true;
				break;

			case 'H':	//	Help.
				usage (*arguments, SUCCESS, true);
				break;

			default:
				cout << "Unrecognized argument: "  << arguments[index] << endl
					 << endl;
				usage (*arguments);
			}
		}
	else
		goto JP2_Pathname_Argument;
	}

//	Check for required arguments.
if (JP2_pathname.empty ())
	{
	cout << "Missing JP2 input file pathname." << endl
		 << endl;
	usage (*arguments, NO_INPUT_FILE);
    }

if (new_label_pathname.empty ())
	{
	cout << "Missing PDS label file pathname." << endl
		 << endl;
	usage (*arguments, NO_LABEL_LOCATION);
    }
if (new_label_pathname[0] == FILE_PATHNAME_DELIMITER)
	{
	cout << "Absolute PDS label file pathname: " << new_label_pathname << endl
		 << "The pathname must be relative to the JP2 file pathname" << endl;
	exit (BAD_SYNTAX);
	}

/*------------------------------------------------------------------------------
	JP2 input file.
*/
cout << "JP2 file: " << JP2_pathname << endl;
if (! file_exists (JP2_pathname))
	{
	cout << "No such file." << endl;
	exit (NO_INPUT_FILE);
	}
char
	*real_pathname = realpath (JP2_pathname.c_str (), NULL);
if (! real_pathname)
	{
	cout << "Unable to obtain the canonical pathname." << endl;
	exit (IO_FAILURE);
	}
if (JP2_pathname != real_pathname)
	{
	JP2_pathname = real_pathname;
	cout << "Pathname: " << JP2_pathname << endl;
	}

if (! file_is_normal (JP2_pathname) ||
	! file_is_readable (JP2_pathname))
	{
	cout << "Not a readable file." << endl;
	exit (IO_FAILURE);
	}
if (! file_is_writeable (file_directory_pathname (JP2_pathname)))
	{
	cout << "The file's directory is not writeable." << endl;
	exit (IO_FAILURE);
	}

/*..............................................................................
	Validate the contents of the JP2 file.
*/
jp2_family_src
	*JP2_Stream = new jp2_family_src ();
JP2_Stream->open (JP2_pathname.c_str ());

//	Confirm that the file has the JP2 Signature and File Type boxes.
string
	missing_box_name;
jp2_input_box
	box;
if (! box.open (JP2_Stream) ||
	  box.get_box_type () != jp2_signature_4cc)
	{
	missing_box_name = "JP2 Signature";

	Invalid_Source:
	cout << "The file does not have valid JP2 format content." << endl
		 << "Missing " << missing_box_name << " box." << endl;
	exit (JP2_ERROR);
	}
box.close ();
if (! box.open_next () ||
	  box.get_box_type () != jp2_file_type_4cc)
	{
	missing_box_name = "File Type";
	goto Invalid_Source;
	}
box.close ();

//	Confirm the presence of the UUID Info and its URL box.
jp2_input_box
	UUID_info_box;
streamoff
	UUID_info_box_position = 0,
	URL_box_position = 0;
streamsize
	old_UUID_info_box_size = 0,
	URL_box_size = 0;
kdu_uint32
	size;
int
	URL_box_header_size = 0,
	size_change;
pathname.clear ();

while (pathname.empty () &&
		box.open_next ())
	{
	#if ((DEBUG) & DEBUG_JP2)
	clog << "    JP2 " << box_name (box.get_box_type ())
			<< " box type " << hex << box.get_box_type () << dec
			<< ", position " << box.get_locator ().get_file_pos ()
			<< ", header length " << box.get_box_header_length ()
			<< ", remaining " << box.get_remaining_bytes () << endl;
	#endif
	if (box.get_box_type () == box_type (UUID_INFO_BOX_NAME))
		{
		UUID_info_box_position = box.get_locator ().get_file_pos ();
		old_UUID_info_box_size =
			box.get_box_header_length () +
			box.get_remaining_bytes ();
		if (UUID_info_box.open (&box))
			{
			#if ((DEBUG) & DEBUG_JP2)
			clog << "    --> Sub-boxes -" <<endl;
			#endif
			do
				{
				#if ((DEBUG) & DEBUG_JP2)
				clog << "    JP2 " << box_name (UUID_info_box.get_box_type ())
						<< " box type "
							<< hex << UUID_info_box.get_box_type () << dec
						<< ", position "
							<< UUID_info_box.get_locator ().get_file_pos ()
						<< ", header length "
							<< UUID_info_box.get_box_header_length ()
						<< ", remaining "
							<< UUID_info_box.get_remaining_bytes () << endl;
				#endif
				if (UUID_info_box.get_box_type () == box_type (URL_BOX_NAME) &&
					pathname.empty () &&
					UUID_info_box.get_remaining_bytes () > VERS_AND_FLAG_BYTES)
					{
					URL_box_position =
						UUID_info_box.get_locator ().get_file_pos ();
					URL_box_header_size =
						UUID_info_box.get_box_header_length ();
					URL_box_size =
						URL_box_header_size +
						UUID_info_box.get_remaining_bytes ();
					unsigned char
						character[VERS_AND_FLAG_BYTES];
					UUID_info_box.read (character, VERS_AND_FLAG_BYTES);
					UUID_info_box.read (character, 1);	//	First URL char.
					while (*character)
						{
						pathname += *character;
						if (UUID_info_box.get_remaining_bytes ())
							UUID_info_box.read (character, 1);
						else
							break;
						}
					#if ((DEBUG) & DEBUG_JP2)
					clog << "    URL: " << pathname << endl;
					#endif
					}
				UUID_info_box.close ();
				}
				while (pathname.empty () &&
						UUID_info_box.open_next ());
			#if ((DEBUG) & DEBUG_JP2)
			clog << "    <-- Sub-boxes" <<endl;
			#endif
			}
		}
	box.close ();
	}
JP2_Stream->close ();

if (pathname.empty ())
	{
	cout << "No label pathname URL box was found in the JP2 file." << endl;
	exit (JP2_ERROR);
	}

cout << endl
	 << "Old label file pathname: " << pathname << endl
	 << "New label file pathname: " << new_label_pathname << endl;
#if ((DEBUG) & DEBUG_JP2)
clog << "    UUID_info_box_position = " << UUID_info_box_position << endl
	 << "    old_UUID_info_box_size = " << old_UUID_info_box_size << endl
	 << "          URL_box_position = " << URL_box_position << endl
	 << "              URL_box_size = " << URL_box_size << endl;
#endif
if (pathname == new_label_pathname)
	{
	cout << "Unchanged." << endl;
	exit (SUCCESS);
	}

size_change = new_label_pathname.size () - pathname.size ();

pathname = file_directory_pathname (JP2_pathname);
pathname += FILE_PATHNAME_DELIMITER;
pathname += new_label_pathname;
if (! file_exists (pathname))
	cout << "Warning: No file at " << pathname << endl;

/*------------------------------------------------------------------------------
	Backup file.
*/
JP2_backup_pathname = JP2_pathname;
JP2_backup_pathname += BACKUP_FILENAME_SUFFIX;
cout << endl
	 << "JP2 backup file: " << JP2_backup_pathname << endl;
if (file_exists (JP2_backup_pathname) &&
	! force_overwrite)
	{
	cout << "Existing file not replaced." << endl;
	exit (EXISTING_BACKUP_FILE);
	}
if (rename (JP2_pathname.c_str (), JP2_backup_pathname.c_str ()))
	{
	cout << "Could not move the JP2 file to the backup file - "
			<< strerror (errno) << '.' << endl;
	exit (IO_FAILURE);
	}
#if ((DEBUG) & DEBUG_IO)
clog << JP2_pathname.c_str () << endl
	 << "renamed" << endl
	 << JP2_backup_pathname.c_str () << endl;
#endif

//	Open the backup file.
ifstream
	input_file (JP2_backup_pathname.c_str ());
if (! input_file)
	{
	cout << "Could not open the backup file for reading!" << endl;
	exit (IO_FAILURE);
	}

/*------------------------------------------------------------------------------
	JP2 output file.
*/
ofstream
	output_file (JP2_pathname.c_str (), std::ios::binary);
if (! output_file)
	{
	cout << "Could not open the new JP2 output file!" << endl;
	exit (IO_FAILURE);
	}

//	Copy the boxes preceeding the UUID Info box.
streamsize
	new_UUID_info_box_size = old_UUID_info_box_size + size_change,
	buffer_size = max (old_UUID_info_box_size, new_UUID_info_box_size);
#if ((DEBUG) & DEBUG_IO)
clog << "           box size change = " << size_change << endl
	 << "    new_UUID_info_box_size = " << new_UUID_info_box_size << endl;
#endif
char
	*buffer = new char[buffer_size];

#if ((DEBUG) & DEBUG_IO)
clog << "copying JP2 content before UUID Info box" << endl;
#endif
streamsize
	amount = UUID_info_box_position;
while (amount > 0)
	{
	#if ((DEBUG) & DEBUG_IO)
	clog << "  copying " << min (buffer_size, amount) << " bytes" << endl;
	#endif
	if (! input_file.read (buffer, min (buffer_size, amount)))
		{
		Read_Failure:
		cout << "Reading the backup JP2 file content failed!" << endl;
		output_file.close ();
		exit (IO_FAILURE);
		}
	if (! output_file.write (buffer, min (buffer_size, amount)))
		{
		Write_Failure:
		cout << "Writing the new JP2 file content failed!" << endl;
		output_file.close ();
		exit (IO_FAILURE);
		}
	amount -= min (buffer_size, amount);
	}

/*..............................................................................
	Patch the UUID Info box.
*/
if (! input_file.read (buffer, old_UUID_info_box_size))
	goto Read_Failure;

//	UUID Info box size.
#if ((DEBUG) & DEBUG_JP2)
clog << "UUID Info box length bytes (hex): " << hex
		<< (unsigned int)buffer[0] << ' '
		<< (unsigned int)buffer[1] << ' '
		<< (unsigned int)buffer[2] << ' '
		<< (unsigned int)buffer[3] << ' ' << dec << endl;
#endif
size = new_UUID_info_box_size;
MSB_native (size);
char*
	byte = (char*)(&size);
buffer[0] = *byte++;
buffer[1] = *byte++;
buffer[2] = *byte++;
buffer[3] = *byte;

if (size_change)
	{
	//	URL box size.
	size = URL_box_size + size_change;
	index = (int)(URL_box_position - UUID_info_box_position);
	#if ((DEBUG) & DEBUG_JP2)
	clog << "          new URL_box_size = " << size << endl
		 << "           at buffer index = " << index << endl;
	#endif
	MSB_native (size);
	byte = (char*)(&size);
	buffer[index++] = *byte++;
	buffer[index++] = *byte++;
	buffer[index++] = *byte++;
	buffer[index]   = *byte;

	//	UUID Info box content following the URL box.
	index = (int)(URL_box_position + URL_box_size - UUID_info_box_position);
	size = old_UUID_info_box_size - index;
	#if ((DEBUG) & DEBUG_JP2)
	clog << " UUID Info box tail amount = " << size << endl
		 << "           at buffer index = " << index << endl;
	#endif
	if (size)
		{
		#if ((DEBUG) & DEBUG_JP2)
		clog << "moving UUID Info box tail from buffer index "
				<< index << " to " << index + size_change << endl;
		#endif
		memmove (&buffer[index + size_change], &buffer[index], size);
		}
	}

//	New label pathname.
index = (int)(URL_box_position - UUID_info_box_position)
	+ URL_box_header_size + VERS_AND_FLAG_BYTES;
#if ((DEBUG) & DEBUG_JP2)
clog << "copying " << (new_label_pathname.size () + 1)
		<< " new_label_pathname characters (plus EOS) to buffer index "
		<< index << endl;
#endif
memmove (&buffer[index],
	new_label_pathname.c_str (), new_label_pathname.size () + 1);

//	Write the patched UUID Info box to the output file.
#if ((DEBUG) & DEBUG_IO)
clog << "writing patched UUID Info box" << endl;
#endif
if (! output_file.write (buffer, new_UUID_info_box_size))
	goto Write_Failure;

/*..............................................................................
	Copy the remainder of the JP2 file.
*/
#if ((DEBUG) & DEBUG_IO)
clog << "copying remainder of JP2 content" << endl;
#endif
output_file << input_file.rdbuf ();
if (! output_file)
	{
	cout << "Copying the backup JP2 file to the new JP2 file failed!" << endl;
	output_file.flush ();
	output_file.close ();
	exit (IO_FAILURE);
	}
output_file.flush ();
output_file.close ();
input_file.close ();

#if ((DEBUG) & DEBUG_IO)
if (no_backup_file)
	clog << "removing the backup file" << endl;
#endif
if (no_backup_file)
	{
	//	Remove the temporary backup file.
	if (unlink (JP2_backup_pathname.c_str ()))
		cout << "Could not remove the backup file - "
				<< strerror (errno) << '.' << endl;
	else
		cout << "Backup file removed." << endl;
	}

exit (SUCCESS);
}








kdu_uint32
box_type
	(
	const char*	box_name
	)
{
kdu_uint32
	code = (kdu_uint32)box_name[0];
for (int
		index = 1;
		index < 4;
		index++)
	{
	code <<= 8;
	code += (kdu_uint32)box_name[index];
	}
return code;
}


string
box_name
	(
	kdu_uint32	box_type
	)
{
string
	name;
for (int
		shift = 24,
		mask = 0x7F000000;
		shift >= 0;
		shift -= 8,
		mask >>= 8)
	name += (char)((box_type & mask) >> shift);
return name;
}
