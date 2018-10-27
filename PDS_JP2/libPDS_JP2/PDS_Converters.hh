/*	PDS_Converters

HiROC CVS ID: PDS_Converters.hh,v 1.3 2008/07/12 04:08:30 castalia Exp

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

#ifndef _PDS_Converters_
#define _PDS_Converters_

#include	"PDS_Converter.hh"
#include	<string>


namespace UA
{
namespace HiRISE
{
/**	Get a PDS_Converter for a data source.

	An attempt is made to construct a specific PDS_Converter on the
	source pathname. The most specific converters are tried before the
	Generic_PDS_Converter is finally tried. Each known PDS_Converter
	implementation is tried until one can be constructed and the source
	file {@link PDS_Converter::label_recognized() label is recognized}.
	If the constructor throws an exception it, and the converter, will
	be ignored.

	<b>N.B.</b>: When a new PDS_Converter is implemented it must be
	added to the sequence of constructor tries. The converter's
	label_recognized method must return true to indicate that it is
	suitable for the specified source.

	Any exception thrown by the Generic_PDS_Converter will be propogated.

	@param	pathname	The pathname string to the data source.
	@return	A pointer to a PDS_Converter, or NULL if no suitable
		converter can be constructed.
	@see	PDS_Converter
	@see	Generic_PDS_Converter
	@see	HiRISE_PDS_Converter
*/
PDS_Converter*
converter_for
	(
	const std::string&	pathname
	);

}	//	namespace HiRISE
}	//	namespace UA
#endif
