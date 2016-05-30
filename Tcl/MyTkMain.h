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

/** Main program for Wish and most other Tk-based applications.
 * Adaption is done to extract Tk-event loop into event-loop of own application.
 * @param argc number of arguments
 * @param argv array of argument strings
 * @param appInitProc application-specific initialization function to call after most initialization but before starting to execute commands
 * @param interp used Tcl interpreter
 */
void My_Tk_MainEx(int argc, TCHAR **argv, Tcl_AppInitProc *appInitProc, Tcl_Interp *interp);

/** Termination of main program of Tk-based application.
 * @param interp used Tcl interpreter
 */
void My_TK_EndMainEx(Tcl_Interp *interp);

