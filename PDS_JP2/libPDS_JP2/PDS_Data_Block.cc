/*	PDS_Data_Block

HiROC CVS ID: PDS_Data_Block.cc,v 1.12 2013/03/18 04:59:11 guym Exp

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

#include "PDS_Data_Block.hh"

using namespace idaeim::PVL;


#if defined (DEBUG)
/*	DEBUG controls

	DEBUG report selection options.
	Define any of the following options to obtain the desired debug reports:
*/
#define DEBUG_ALL			-1
#define DEBUG_CONSTRUCTORS	(1 << 0)
#define DEBUG_ACCESSORS		(1 << 1)
#include	<iostream>
#include	<iomanip>
using std::clog;
using std::endl;
#endif  // DEBUG

#include <fstream>
using std::ifstream;

namespace UA
{
namespace HiRISE
{
/*******************************************************************************
	PDS_Data_Block
*/
/*==============================================================================
	Constants:
*/
const char* const
	PDS_Data_Block::ID =
		"UA::HiRISE::PDS_Data_Block (1.12 2013/03/18 04:59:11)";

const char
	*PDS_Data_Block::BLOCK_WIDTH_PARAMETER_NAME	= "ROW_BYTES",
	*PDS_Data_Block::BLOCK_HEIGHT_PARAMETER_NAME	= "ROWS";

/*==============================================================================
	Constructors
*/
PDS_Data_Block::PDS_Data_Block ()
	:	Location (0),
		Size (0)
{}


PDS_Data_Block::PDS_Data_Block
	(
	const idaeim::PVL::Aggregate&	parameters,
	std::ios::off_type				file_offset
	)
	:	PDS_Data (parameters),
		Location (file_offset)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">>> PDS_Data_Block: " << parameters.name ()
		<< " at file offset " << file_offset << endl;
#endif
Size = data_block_size ();
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << "<<< PDS_Data_Block" << endl;
#endif
}

PDS_Data_Block::PDS_Data_Block
   (
   const idaeim::PVL::Aggregate& parameters,
   const std::string& filename
   ) : PDS_Data (parameters, filename), Location (0)
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">>> PDS_Data_Block: " << parameters.name ()
      << " in detached file " << filename << endl;
#endif

if (! filename.empty())
{
   std::ifstream detached(filename.c_str(), std::ifstream::in | std::ifstream::binary);

if (!detached.good())
{
#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">>> PDS_Data_Block: " << parameters.name ()
      << " detached file " << filename << " could not be read." << endl;
#endif
}
else
{
detached.seekg(0, std::ifstream::end);

Size = detached.tellg ();

#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << ">>> PDS_Data_Block: " << parameters.name ()
         << " in " << filename << " has " << Size << " bytes." << endl;
#endif

detached.close();
}
}

#if ((DEBUG) & DEBUG_CONSTRUCTORS)
clog << "<<< PDS_Data_Block" << endl;
#endif
}

/*==============================================================================
	Accessors
*/
unsigned long long
PDS_Data_Block::data_block_size ()
{
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << ">>> PDS_Data_Block::data_block_size" << endl;
#endif
unsigned long long
	rows = 0,
	row_bytes = 0;
const Parameter
	*parameter = find_parameter (BLOCK_HEIGHT_PARAMETER_NAME);

if (parameter &&
	(rows = parameter->value ()))
	{
	if ((parameter = find_parameter (BLOCK_WIDTH_PARAMETER_NAME)))
		row_bytes = parameter->value ();
	}
#if ((DEBUG) & DEBUG_ACCESSORS)
clog << "<<< PDS_Data_Block::data_block_size: "
	<< (rows * row_bytes) << endl;
#endif
return rows * row_bytes;
}

}	//	namespace HiRISE
}	//	namespace UA
