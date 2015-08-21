/******************************************************************************/
/*                                                                            */
/*  OpenGL.hpp                                                                */
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

#include <Fast/Types.hpp>

#if defined(FastOSWindows)
#	include <Windows.h>
#	include <windowsx.h>
#	include <gl/gl.h>
#	include <gl/glu.h>
#	include "glext.h"
#	include "wglext.h"
#elif defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/Xatom.h>
#	include <X11/Xutil.h>
#	include <X11/cursorfont.h>
#	include <X11/extensions/XInput2.h>
#	include <unistd.h>
#	include <GL/gl.h>
#	include <GL/glx.h>
#	include "glext.h"
#	include "glxext.h"
#elif defined(FastOSMacOSX)
#	include <OpenGL/gl.h>
#endif

#include "Undefs.hpp"

#ifndef FastOpenGLHppIncluded
#define FastOpenGLHppIncluded

namespace Fast
{
	// Context procs
	typedef Int  (StdCall *WGLSwapInterval)(Int);
	typedef Int  (StdCall *GLXSwapIntervalSGI)(Int);
	typedef void (StdCall *GLXSwapIntervalEXT)(CXDisplay*, CGLXDrawable, Int);
	typedef Int  (StdCall *GLXSwapIntervalMESA)(UInt);
	// Standard procs
	typedef void (StdCall *GLGenTextures)(Int, UInt*);
	// Extension procs
	typedef void (StdCall *GLGenBuffers)(Int, UInt*);
	typedef void (StdCall *GLBindBuffer)(UInt, UInt);
	typedef void (StdCall *GLBufferData)(UInt, Int, const Void*, UInt);
	typedef void (StdCall *GLVertexAttribPointer)(
		UInt, Int, UInt, UByte, Int, const Void*);
	typedef void (StdCall *GLDeleteBuffers)(Int, UInt*);
	typedef void (StdCall *GLEnableVertexAttribArray)(UInt);
	typedef void (StdCall *GLDisableVertexAttribArray)(UInt);
	typedef UInt (StdCall *GLCreateShader)(UInt);
	typedef void (StdCall *GLShaderSource)(
		UInt, Int, const Char *const *, const Int*);
	typedef void (StdCall *GLCompileShader)(UInt);
	typedef void (StdCall *GLDeleteShader)(UInt);
	typedef UInt (StdCall *GLCreateProgram)();
	typedef void (StdCall *GLDeleteProgram)(UInt);
	typedef void (StdCall *GLAttachShader)(UInt, UInt);
	typedef void (StdCall *GLLinkProgram)(UInt);
	typedef void (StdCall *GLUseProgram)(UInt);
	typedef void (StdCall *GLGetShaderiv)(UInt, UInt, Int*);
	typedef void (StdCall *GLGetProgramiv)(UInt, UInt, Int*);
	typedef void (StdCall *GLGetShaderInfoLog)(UInt, Int, Int*, Char*);
	typedef void (StdCall *GLGetProgramInfoLog)(UInt, Int, Int*, Char*);
	typedef void (StdCall *GLGenRenderbuffers)(Int, UInt*);
	typedef void (StdCall *GLDeleteRenderbuffers)(Int, const UInt*);
	typedef void (StdCall *GLBindRenderbuffer)(UInt, UInt);
	typedef void (StdCall *GLRenderbufferStorage)(UInt, UInt, Int, Int);
	typedef void (StdCall *GLGenFramebuffers)(Int, UInt*);
	typedef void (StdCall *GLDeleteFramebuffers)(Int, const UInt*);
	typedef void (StdCall *GLBindFramebuffer)(UInt, UInt);
	typedef void (StdCall *GLFramebufferTexture2D)(UInt, UInt, UInt, UInt, Int);
	typedef void (StdCall *GLFramebufferRenderbuffer)(UInt, UInt, UInt, UInt);
	typedef void (StdCall *GLBlendColor)(Float, Float, Float, Float);
	typedef void (StdCall *GLGenerateMipmap)(GLenum);
	typedef void (StdCall *GLGenVertexArrays)(Int, UInt*);
	typedef void (StdCall *GLBindVertexArray)(UInt);
	typedef void (StdCall *GLActiveTexture)(GLenum);

	namespace OpenGL
	{
		// Context procs
		extern GLXSwapIntervalSGI			glXSwapIntervalSGI;
		extern GLXSwapIntervalEXT			glXSwapIntervalEXT;
		extern GLXSwapIntervalMESA			glXSwapIntervalMESA;
		extern WGLSwapInterval				wglSwapInterval;
		// Extention procs
		extern GLGenBuffers					glGenBuffers;
		extern GLBindBuffer					glBindBuffer;
		extern GLBufferData					glBufferData;
		extern GLVertexAttribPointer		glVertexAttribPointer;
		extern GLDeleteBuffers				glDeleteBuffers;
		extern GLEnableVertexAttribArray	glEnableVertexAttribArray;
		extern GLDisableVertexAttribArray	glDisableVertexAttribArray;
		extern GLCreateShader				glCreateShader;
		extern GLShaderSource				glShaderSource;
		extern GLCompileShader				glCompileShader;
		extern GLDeleteShader				glDeleteShader;
		extern GLCreateProgram				glCreateProgram;
		extern GLDeleteProgram				glDeleteProgram;
		extern GLAttachShader				glAttachShader;
		extern GLLinkProgram				glLinkProgram;
		extern GLUseProgram					glUseProgram;
		extern GLGetShaderiv				glGetShaderiv;
		extern GLGetProgramiv				glGetProgramiv;
		extern GLGetShaderInfoLog			glGetShaderInfoLog;
		extern GLGetProgramInfoLog			glGetProgramInfoLog;
		extern GLGenRenderbuffers			glGenRenderbuffers;
		extern GLDeleteRenderbuffers		glDeleteRenderbuffers;
		extern GLBindRenderbuffer			glBindRenderbuffer;
		extern GLRenderbufferStorage		glRenderbufferStorage;
		extern GLGenFramebuffers			glGenFramebuffers;
		extern GLDeleteFramebuffers			glDeleteFramebuffers;
		extern GLBindFramebuffer			glBindFramebuffer;
		extern GLFramebufferTexture2D		glFramebufferTexture2D;
		extern GLFramebufferRenderbuffer	glFramebufferRenderbuffer;
		extern GLBlendColor					glBlendColor;
		extern GLGenerateMipmap				glGenerateMipmap;
		extern GLGenVertexArrays			glGenVertexArrays;
		extern GLBindVertexArray			glBindVertexArray;
		extern GLActiveTexture				glActiveTexture;
		// Wrappers
		void glXSwapInterval(CXDisplay *display,
			CGLXWindow drawable, Int interval);
		// Proc loaders
		void LoadContextProcs();
		void LoadExtensionProcs();
	}
}

#endif // FastOpenGLHppIncluded
