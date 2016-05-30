#pragma once

/**
* On Windows, this file needs to be compiled twice, once with
* TK_ASCII_MAIN defined. This way both Tk_MainEx and Tk_MainExW
* can be implemented, sharing the same source code.
*/
#if defined(TK_ASCII_MAIN)
#   ifdef UNICODE
#	undef UNICODE
#	undef _UNICODE
#   else
#	define UNICODE
#	define _UNICODE
#   endif
#endif

#include "tkInt.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#ifdef NO_STDLIB_H
#   include "../compat/stdlib.h"
#else
#   include <stdlib.h>
#endif


void My_Tk_MainEx(
int argc,			/* Number of arguments. */
TCHAR **argv,		/* Array of argument strings. */
Tcl_AppInitProc *appInitProc,
/* Application-specific initialization
* function to call after most initialization
* but before starting to execute commands. */
Tcl_Interp *interp);

void My_TK_EndMainEx(Tcl_Interp *interp);

