/*	PDS_Data_Block

HiROC CVS ID: PDS_Data_Block.hh,v 1.9 2013/03/14 21:00:43 guym Exp

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
*/

#ifndef _PDS_Data_Block_
#define _PDS_Data_Block_

#include	"PDS_Data.hh"

#include	<string>
#include	<iosfwd>


namespace UA
{
namespace HiRISE
{
/**	A <i>PDS_Data_Block</i> describes a binary data block in a PDS
	label. 
 
	A PDS_Data_Block is the PDS_Data parameters that describes a binary
	data block along with the location and size of the binary data in the
	source file. A binary data block is located in a PDS label by a data
	block record pointer parameter. A record pointer parameter has a name
	that begins with the PDS_Data::RECORD_POINTER_PARAMETER_MARKER
	character. The value of a pointer parameter is the record number
	(offset + 1) where the binary data is located in the file. A
	Parameter Aggregate with the same name, but without the record
	pointer marker, contains the parameters that desrcribe the data
	block.

	@author		Bradford Castalia, Drew Davidson and Ben Pearson, UA/HiROC
	@version	1.9
	@see	PDS_Data
*/
class PDS_Data_Block
:	public PDS_Data
{
public:
/*==============================================================================
	Constants:
*/
//!	Class identification.
static const char* const
	ID;

//!	Name of the parameter specifying the binary block row width in bytes.
static const char
	*BLOCK_WIDTH_PARAMETER_NAME;

//!	Name of the parameter specifying the binary block height in rows.
static const char
	*BLOCK_HEIGHT_PARAMETER_NAME;

/*==============================================================================
	Constructors:
*/
/**	Constructs an empty PDS_Data_Block.
*/
PDS_Data_Block ();

/**	Constructs a PDS_Data_Block from its PDS label parameters and
	source file data location.

	<b>N.B.</b>: The Parameter Aggregate describing the data block
	is copied.

	@param	parameters	Parameter Aggregate describing the data block
	@param	file_offset	Data block offset location in the source file.
*/
PDS_Data_Block 
	(
	const idaeim::PVL::Aggregate&	parameters, 
	std::ios::off_type				file_offset
	);

/**   Constructs a PDS_Data_Block from its PDS label parameters and
   detached source file.

   <b>N.B.</b>: The Parameter Aggregate describing the data block
   is copied.

   @param   parameters  Parameter Aggregate describing the data block
   @param   file_offset Data block offset location in the source file.
*/
PDS_Data_Block
   (
   const idaeim::PVL::Aggregate& parameters,
   const std::string& filename
   );


/*==============================================================================
	Accessors:
*/
/**	Get the offset location of the binary data block in the source file.

	@return	The file offset location of the binary data block.
*/
std::ios::off_type location ()
{return Location;}

/**	Get the size of the data block.

	@return	The size of the data block, in bytes.
*/
unsigned long long size ()
{return Size;}

/*==============================================================================
	Data:
*/
protected:

//!	Offset location of the data block in the source file.
std::ios::off_type
	Location;

//!	Size of the data block in bytes.
unsigned long long
	Size;

/**	Calculate the size of the binary data block.

	The value of the BLOCK_WIDTH_PARAMETER_NAME parameter is multiplied
	by the value of the BLOCK_HEIGHT_PARAMETER_NAME parameter. If either
	of these parameters are not found in the data block description the
	result will be zero.

	<b>N.B.</b>: This method may be overriden by subclasses that need to
	specialize how the data block {@link size() size} is determined.

	@return	The size (bytes) of the binary data block in the source file.
*/
virtual unsigned long long data_block_size ();

};	//	class PDS_Data_Block

}	//	namespace HiRISE
}	//	namespace UA
#endif
