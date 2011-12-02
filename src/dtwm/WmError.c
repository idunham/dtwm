/* 
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1989, 1990, 1991, 1992, 1993, 1994 Open Software Foundation, Inc. 
 * Copyright (c) 1996, 1997, 1998, 1999, 2000 The Open Group
 * ALL RIGHTS RESERVED (MOTIF). See the file named COPYRIGHT.MOTIF for
 * the full copyright text.
 * 
 * This software is subject to an open license. It may only be
 * used on, with or for operating systems which are themselves open
 * source systems. You must contact The Open Group for a license
 * allowing distribution and sublicensing of this software on, with,
 * or for operating systems which are not Open Source programs.
 * 
 * See http://www.opengroup.org/openmotif/license for full
 * details of the license agreement. Any use, reproduction, or
 * distribution of the program constitutes recipient's acceptance of
 * this agreement.
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, THE PROGRAM IS
 * PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
 * WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY
 * OR FITNESS FOR A PARTICULAR PURPOSE
 * 
 * EXCEPT AS EXPRESSLY SET FORTH IN THIS AGREEMENT, NEITHER RECIPIENT
 * NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OR DISTRIBUTION OF THE PROGRAM OR THE
 * EXERCISE OF ANY RIGHTS GRANTED HEREUNDER, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
*/ 
/* 
 * Motif Release 1.2.4
*/ 
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#ifdef REV_INFO
#ifndef lint
static char rcsid[] = "$XConsortium: WmError.c /main/6 1996/10/07 14:27:34 drk $"
#endif
#endif
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

/*
 * Included Files:
 */

#include "WmGlobal.h"
#include <stdio.h>
#ifdef WSM
#include <Dt/UserMsg.h>
#endif /* WSM */
#include "WmXSMP.h"

/*
 * Function Declarations:
 */
#include "WmError.h"

#ifdef DEBUG

#define E_MAJOR_CODE		0
#define E_MINOR_CODE		1
#define E_RESOURCE_ID		2
#define E_ERROR_SERIAL		3
#define E_CURRENT_SERIAL	4

#define NUM_E_STRINGS		5

static char *pchErrorFormatNames [NUM_E_STRINGS] = {
    "MajorCode", 
    "MinorCode", 
    "ResourceID", 
    "ErrorSerial", 
    "CurrentSerial" 
};

static char *pchDefaultErrorFormat [NUM_E_STRINGS] = {
    " %d ",
    " %d ",
    " %ld ",
    " %ld ",
    " %ld "
};

static char *pchErrorFormat [NUM_E_STRINGS];

#endif /* DEBUG */




/*************************************<->*************************************
 *
 *  WmInitErrorHandler (display)
 *
 *
 *  Description:
 *  -----------
 *  This function initializes the window manager error handler.
 *
 *
 *  Inputs:
 *  ------
 *  display = display we're talking about
 *  -------
 *
 *************************************<->***********************************/

void
WmInitErrorHandler (Display *display)
{
#ifdef DEBUG
    char buffer[BUFSIZ];
    int i;

    /*
     * Fetch the X error format strings from XErrorDB
     */
    for (i = 0; i< NUM_E_STRINGS; i++)
    {
	XGetErrorDatabaseText (display, "XlibMessage", 
			       pchErrorFormatNames[i], 
			       pchDefaultErrorFormat[i], buffer, BUFSIZ);

	if ((pchErrorFormat[i] = (char *) XtMalloc (1+strlen(buffer))) == NULL)
	{
	    Warning ("Insufficient memory for error message initialization.");
	    ExitWM (1);
	}

	strcpy(pchErrorFormat[i], buffer);
    }

#endif /* DEBUG */

    XSetErrorHandler (WmXErrorHandler);
    XSetIOErrorHandler (WmXIOErrorHandler);

    XtSetWarningHandler (WmXtWarningHandler);
    XtSetErrorHandler (WmXtErrorHandler);

} /* END OF FUNCTION WmInitErrorHandler */


/*************************************<->*************************************
 *
 *  WmXErrorHandler (display, errorEvent)
 *
 *
 *  Description:
 *  -----------
 *  This function is the X error handler that is registered with X to
 *  handle X errors resulting from window management activities.
 *
 *
 *  Inputs:
 *  ------
 *  display = display on which X error occurred
 *
 *  errorEvent = pointer to a block of information describing the error
 *
 * 
 *  Outputs:
 *  -------
 *  wmGD.errorFlag = set to True
 *
 *  Return = 0
 *
 *************************************<->***********************************/

int
WmXErrorHandler (Display *display, XErrorEvent *errorEvent)
{
    ClientData *pCD;

#ifdef DEBUG
    char buffer[BUFSIZ];
    char message[BUFSIZ];

    XGetErrorText (display, errorEvent->error_code, buffer, BUFSIZ);
    Warning ("X error occurred during window management operation");
    fprintf (stderr, "Description = '%s'\n  ", buffer);

    fprintf (stderr, pchErrorFormat[E_MAJOR_CODE], errorEvent->request_code);
    sprintf(message, "%d", errorEvent->request_code);
    XGetErrorDatabaseText (display, "XRequest", message, 
	" ", buffer, BUFSIZ);
    fprintf (stderr, " (%s)\n  ", buffer);
    fprintf (stderr, pchErrorFormat[E_MINOR_CODE], errorEvent->minor_code);
    fprintf (stderr, "\n  ");
    fprintf (stderr, pchErrorFormat[E_RESOURCE_ID], errorEvent->resourceid);
    fprintf (stderr, "\n  ");
    fprintf (stderr, pchErrorFormat[E_ERROR_SERIAL], errorEvent->serial);
    fprintf (stderr, "\n  ");
    fprintf (stderr, pchErrorFormat[E_CURRENT_SERIAL], 
			LastKnownRequestProcessed(display));
    fprintf (stderr, "\n");
#endif /* DEBUG */

    /*
     * Check for a BadWindow error for a managed window.  If this error
     * is detected indicate in the client data that the window no longer
     * exists.
     */

    if ((errorEvent->error_code == BadWindow) &&
	!XFindContext (DISPLAY, errorEvent->resourceid, wmGD.windowContextType,
	     (caddr_t *)&pCD))
    {
	if (errorEvent->resourceid == pCD->client)
	{
	    pCD->clientFlags |= CLIENT_DESTROYED;
	}
    }

    wmGD.errorFlag = True;
    wmGD.errorResource = errorEvent->resourceid;
    wmGD.errorRequestCode = errorEvent->request_code;

    return (0);

} /* END OF FUNCTION WmXErrorHandler */



/*************************************<->*************************************
 *
 *  WmXIOErrorHandler (display)
 *
 *
 *  Description:
 *  -----------
 *  This function is the X IO error handler that is registered with X to
 *  handle X IO errors.  This function exits the window manager.
 *
 *
 *  Inputs:
 *  ------
 *  display = X display on which the X IO error occurred
 * 
 *************************************<->***********************************/

int
WmXIOErrorHandler (Display *display)
{
  char  err[100];
 
  sprintf (err, "%s: %s\n", "I/O error on display:", XDisplayString(display));
  Warning(err);

  ExitWM (WM_ERROR_EXIT_VALUE);

  /*NOTREACHED*/
  return 1;
} /* END OF FUNCTIONS WmXIOErrorHandler */



/*************************************<->*************************************
 *
 *  WmXtErrorHandler (message)
 *
 *
 *  Description:
 *  -----------
 *  This function is registered as the X Toolkit fatal error handler.
 *
 *
 *  Inputs:
 *  ------
 *  message = pointer to an error message
 *
 *************************************<->***********************************/

void
WmXtErrorHandler (char *message)
{

    Warning (message);
    ExitWM (WM_ERROR_EXIT_VALUE);

} /* END OF FUNCTION WmXtErrorHandler */



/*************************************<->*************************************
 *
 *  WmXtWarningHandler (message)
 *
 *
 *  Description:
 *  -----------
 *  This function is registered as an X Toolkit warning handler.
 *
 *
 *  Inputs:
 *  ------
 *  message = pointer to a warning message
 * 
 *************************************<->***********************************/

void
WmXtWarningHandler (char *message)
{

#ifdef DEBUG
    Warning (message);
#endif /* DEBUG */

} /* END OF FUNCTIONS WmXtWarningHandler */


/*************************************<->*************************************
 *
 *  Warning (message)
 *
 *
 *  Description:
 *  -----------
 *  This function lists a message to stderr.
 *
 *
 *  Inputs:
 *  ------
 *  message = pointer to a message string
 * 
 *************************************<->***********************************/

void
Warning (char *message)
{
#ifdef WSM
    char pch[MAXWMPATH+1];

    sprintf (pch, "%s: %s\n", 
	GETMESSAGE(20, 1, "Workspace Manager"), message);

    _DtSimpleError (wmGD.mwmName, DtIgnore, NULL, pch, NULL);
#else /* WSM */
    fprintf (stderr, "%s: %s\n", wmGD.mwmName, message);
    fflush (stderr);
#endif /* WSM */

} /* END OF FUNCTION Warning */

#ifdef WSM
#ifdef DEBUGGER

/******************************<->*************************************
 *
 *  PrintFormatted (format, message, message, ...)
 *
 *
 *  Description:
 *  -----------
 *  This function lists several messages to stderr using fprinf()
 *  formatting capabilities.
 *
 *  Inputs:
 *  ------
 *  s0-s9 = pointers to message strings
 * 
 *  Comments:
 *  ------
 *  Caller must provide his/her own argv[0] to this function.
 ******************************<->***********************************/

/*VARARGS1*/
void
PrintFormatted(char *f, char *s0, char *s1, char *s2, char *s3, char *s4, char *s5, char *s6, char *s7, char *s8, char *s9)
/* limit of ten args */
{
    fprintf( stderr, f, s0, s1, s2, s3, s4, s5, s6, s7, s8, s9);
    fflush (stderr);
} /* END OF FUNCTION PrintFormatted */

/************************    eof   **************************/
#endif /* DEBUGGER */
#endif /* WSM */
