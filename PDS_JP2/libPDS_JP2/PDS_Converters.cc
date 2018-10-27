/*	PDS_Converters

HiROC CVS ID: PDS_Converters.cc,v 1.7 2013/05/17 21:35:21 guym Exp

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

#include	"PDS_Converters.hh"

#include	<string>
using std::string;

/*	Class definitions for each PDS_Converter implementation.
*/
#ifdef		HiRISE_PDS_CONVERTER
#include	"HiRISE_PDS_Converter.hh"
#endif

#ifdef      HiPrecision_PDS_CONVERTER
#include "HiPrecision_PDS_Converter.hh"
#endif

#include	"Generic_PDS_Converter.hh"

#if defined (DEBUG)
/*      DEBUG controls
 *
 *      DEBUG report selection options.
 *      Define any of the following options to obtain the desired debug reports:
 *                      */
#define DEBUG_ALL               -1
#define DEBUG_HELPERS           (1 << 3)
#include        <iostream>
using std::clog;
using std::endl;
#endif  // DEBUG

#include <exception>
using std::exception;

namespace UA
{
namespace HiRISE
{
#ifndef DOXYGEN_PROCESSING
namespace
{
PDS_Converter*
possible
	(
	PDS_Converter*	converter
	)
{
if (converter->label_recognized ())
{
#if ((DEBUG) & DEBUG_HELPERS)
      clog << converter->name() << " recognized the label" << endl;
#endif
}
	return converter;

#if ((DEBUG) & DEBUG_HELPERS)
      clog << converter->name() << " did not recognize the label" << endl;
#endif

delete converter;
return NULL;
}

}
#endif


PDS_Converter*
converter_for
	(
	const std::string&	pathname
	)
{
/*	PDS Converters.
	Each known converter is tried. The first one to succeed is used.
*/

#if ((DEBUG) & DEBUG_HELPERS)

#ifndef HiRISE_PDS_CONVERTER
clog << "HiRISE PDS label checker was not compiled in" << endl;
#endif

#ifndef HiPrecision_PDS_CONVERTER
clog << "HiPrecision PDS label checker was not compiled in" << endl;
#endif

#endif

PDS_Converter
	*converter;
#if ((DEBUG) & DEBUG_HELPERS)
      clog << "Checking for a HiRISE PDS label" << endl;
#endif

#ifdef	HiRISE_PDS_CONVERTER
try
{
	if ((converter = possible (new HiRISE_PDS_Converter (pathname))))
		return converter;
}
catch (exception& e)
{
#if ((DEBUG) & DEBUG_HELPERS)
      clog << "HiRISE PDS Converter caught exception " << e.what() << endl;
#endif
}
catch (...)
{
#if ((DEBUG) & DEBUG_HELPERS)
      clog << "HiRISE PDS Converter caught unknown exception " << endl;
#endif

}
#endif

#if ((DEBUG) & DEBUG_HELPERS)
         clog << "Checking for a HiPrecision PDS label" << endl;
#endif

#ifdef   HiPrecision_PDS_CONVERTER
try
{
   if ((converter = possible (new HiPrecision_PDS_Converter (pathname))))
      return converter;
}
catch (exception& e)
{
#if ((DEBUG) & DEBUG_HELPERS)
      clog << "HiPrecesion PDS Converter caught exception " << e.what() << endl;
#endif

}
#endif

	//	Add new converters here.

#if ((DEBUG) & DEBUG_HELPERS)
      clog << "Checking for a generic PDS label" << endl;
#endif

try
{
if ((converter = possible (new Generic_PDS_Converter (pathname))))
	return converter;
}
catch (exception& e)
{
   std::cerr << "Could not determine label type due to exception " << e.what() << std::endl;

}

return NULL;
}

}	//	namespace HiRISE
}	//	namespace UA
