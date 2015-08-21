/******************************************************************************/
/*                                                                            */
/*  QZInterface.hpp                                                           */
/*                                                                            */
/*  Copyright (C) 2015, Joseph Andrew Staedelin IV                            */
/*                                                                            */
/*  This file is part of the FastGdk project.                                 */
/*                                                                            */
/*  The FastGdk is free software: you can redistribute it and/or modify       */
/*  it under the terms of the GNU Lesser General Public License as published  */
/*  by the Free Software Foundation, either version 3 of the License, or      */
/*  (at your option) any later version.                                       */
/*                                                                            */
/*  The FastGdk is distributed in the hope that it will be useful,            */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/*  GNU Lesser General Public License for more details.                       */
/*                                                                            */
/*  You should have received a copy of the GNU Lesser General Public License  */
/*  along with the FastGdk.  If not, see <http://www.gnu.org/licenses/>.      */
/*                                                                            */
/******************************************************************************/

#ifndef FastQZInterfaceHppIncluded
#define FastQZInterfaceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>

#define kFastMaxDisplays	10

namespace Fast
{
	class Rectangle;
	class VideoMode;

#if defined(FastOSMacOSX)
	
	extern void			QZRegisterDisplayChangeCallback(Display *display);
	extern void			QZUnregisterDisplayChangeCallback(Display *display);
	extern UInt			QZGetDisplayID(UInt chaosScreenID);
	extern void			QZGetVideoModes(UInt displayID,
							Array<VideoMode> *modes);
	extern void			QZGetCurrentVideoMode(UInt displayID, VideoMode *mode);
	extern ErrorType	QZSetVideoMode(UInt displayID, const VideoMode &vm);
	extern void			QZGetMonitorRect(UInt displayID, Rectangle *rect);

#endif
	
}

#endif // FastQZInterfaceHppIncluded