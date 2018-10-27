/*	Kakadu architecture test

	PIRL CVS ID: kdu_arch_test.cc,v 1.2 2009/07/13 23:56:11 castalia Exp
*/

#include	"kdu_arch.h"

#include	<iostream>
using namespace std;


const char*
	MMX_SSE_SUPPORT[] =
		{
		"No MMX/SSE support",
		"MMX support only; no SSE support",
		"MMX, SSE and SSE2 support.",
		"MMX, SSE, SSE2 and SSE3 support.",
		"MMX, SSE, SSE2, SSE3 and SSSE3 support."
		};
	


int
main
	(
	int		argument_count,
	char	**arguments
	)
{
cout << "     CPU threads: " << kdu_get_num_processors () << endl
	 << "      sizeof int: " << sizeof (int) << endl
	 << "     sizeof long: " << sizeof (long) << endl
	 << "sizeof long long: " << sizeof (long long) << endl
	 << "    sizeof void*: " << sizeof (void*) << endl << endl;

cout << MMX_SSE_SUPPORT[kdu_mmx_level] << endl;

cout << boolalpha
	 << "x86 CMOV (conditional move) instruction exists: "
	 	<< kdu_pentium_cmov_exists << endl
	 << "        SPARC visual instruction set available: "
	 	<< kdu_sparcvis_exists << endl
	 << "                      Altivec engine available: "
	 	<< kdu_altivec_exists << endl;
}

