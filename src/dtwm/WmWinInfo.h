/* 
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1989, 1990, 1991, 1992 Open Software Foundation, Inc. 
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
 * Motif Release 1.2
*/ 
/*   $XConsortium: WmWinInfo.h /main/5 1995/12/27 17:24:50 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */


extern void FindClientPlacement (ClientData *pCD);
extern void FixWindowConfiguration (ClientData *pCD, unsigned int *pWidth, 
				    unsigned int *pHeight, 
				    unsigned int widthInc, 
				    unsigned int heightInc);
extern void FixWindowSize (ClientData *pCD, unsigned int *pWidth, 
			   unsigned int *pHeight, unsigned int widthInc, 
			   unsigned int heightInc);
extern ClientData *GetClientInfo (WmScreenData *pSD, Window clientWindow, 
				  long manageFlags);
extern ClientData *GetWmClientInfo (WmWorkspaceData *pWS, ClientData *pCD, 
				    long manageFlags);
extern void CalculateGravityOffset (ClientData *pCD, int *xoff, int *yoff);
extern Boolean InitClientPlacement (ClientData *pCD, long manageFlags);
extern void InitCColormapData (ClientData *pCD);
extern void MakeSystemMenu (ClientData *pCD);
extern void PlaceFrameOnScreen (ClientData *pCD, int *pX, int *pY, int w, 
				int h);
extern void PlaceIconOnScreen (ClientData *pCD, int *pX, int *pY);
extern void ProcessMwmHints (ClientData *pCD);
extern void ProcessWmClass (ClientData *pCD);
extern void ProcessWmHints (ClientData *pCD, Boolean firstTime);
extern void ProcessWmIconTitle (ClientData *pCD, Boolean firstTime);
extern void ProcessWmNormalHints (ClientData *pCD, Boolean firstTime, 
				  long manageFlags);
extern void ProcessWmTransientFor (ClientData *pCD);
extern void ProcessWmWindowTitle (ClientData *pCD, Boolean firstTime);
extern Boolean SetupClientIconWindow (ClientData *pCD, Window window);
extern Boolean WmGetWindowAttributes (Window window);
extern void ProcessSmClientID (ClientData *pCD);
extern void ProcessWmSaveHint (ClientData *pCD);
