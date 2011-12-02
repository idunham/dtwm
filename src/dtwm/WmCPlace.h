/* 
 * @OPENGROUP_COPYRIGHT@
 * COPYRIGHT NOTICE
 * Copyright (c) 1989, 1990, 1991, 1992, 1993 Open Software Foundation, Inc. 
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
 * Motif Release 1.2.2
*/ 
/*   $XConsortium: WmCPlace.h /main/4 1995/11/01 11:34:34 rswiston $ */
/*
 * (c) Copyright 1987, 1988, 1989, 1990 HEWLETT-PACKARD COMPANY */

extern void PlaceWindowInteractively (ClientData *pcd);
extern void DoPlacement (ClientData *pcd);
extern void SetupPlacement (ClientData *pcd);
extern void HandlePlacementKeyEvent (ClientData *pcd, XKeyEvent *pev);
extern void HandlePlacementButtonEvent (XButtonEvent *pev);
extern void HandlePlacementMotionEvent (ClientData *pcd, XMotionEvent *pev);
extern void StartInteractiveSizing (ClientData *pcd, Time time);
extern Bool IsRepeatedKeyEvent (Display *dpy, XEvent *pEvent, char *pOldEvent);
