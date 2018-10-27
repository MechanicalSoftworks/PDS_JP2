/*	test_PDS_Projection_Data

CVS ID: test_PDS_Projection_Data.cc,v 1.4 2007/10/08 00:33:12 castalia Exp

Copyright (C) 2006 Arizona Board of Regents on behalf of the
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

#include "PDS_Projection_Data.hh"
using namespace UA::HiRISE;

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

#include "PVL.hh"
using namespace idaeim::PVL;

/*==============================================================================
	Constants
*/
const char* const
	ID =
		"test_PDS_Projection_Data (1.4 2007/10/08 00:33:12)";

enum
	{
	SUCCESS,
	SYNTAX_ERROR,
	IO_FAILURE,
	PVL_ERROR,
	UNKNOWN_ERROR
	};

/*==============================================================================
	Main
*/
void
usage
	(
	char*	program,
	int		status = SYNTAX_ERROR
	)
{
	cout << "Usage: " << program << " <PDS data pathname>" << endl;
	exit (status);
}


int
main
	(
	int		argument_count,
	char**	arguments
	)
{
cout << ID << endl;

std::string
	pathname;

//	Argument processing:

if (argument_count == 1)
	usage (*arguments);

for (int
		count = 1;
		count < argument_count;
		count++)
	{
	if (arguments[count][0]== '-')
		{
		switch (toupper(arguments[count][1]))
			{
			default:
				cout << "Unrecognized option: " << arguments[count] <<endl;
				usage (*arguments);
			}
		}
	else
		{
		if (pathname.empty ())
			pathname = arguments[count];
		else
			{
			cout << "PDS data pathname already specified: " << pathname << endl;
			usage (*arguments);
			}
		}
	}
if (pathname.empty ())
	{
	cout << "A PDS data pathname must be specified." << endl;
	usage (*arguments);
	}

try
{
cout << "--> Constructing a PDS_Projection_Data object from "
		<< pathname << endl;
PDS_Projection_Data
	pds_projection_data (pathname);

cout << endl
	 << "--> JP2_Geo_TIFF" << endl;
JP2_Box
	*box = pds_projection_data.JP2_GeoTIFF ();

cout << endl
	 << "--> JP2_GML" << endl;
box = pds_projection_data.JP2_GML ();
}
catch (idaeim::Exception& except)
	{
	cout << except.what () << endl;
	}
catch (exception& except)
	{
	cout << except.what () << endl;
	}

exit (SUCCESS);
}

