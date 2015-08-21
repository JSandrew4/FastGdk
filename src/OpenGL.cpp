/******************************************************************************/
/*                                                                            */
/*  OpenGL.cpp                                                                */
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

#include <Fast/Exception.hpp>
#include <Fast/ExceptionType.hpp>

#include "OpenGL.hpp"

////////////////////////
#include <cstdio>
//////////////////

#if defined(FastOSWindows)
#	define FastOpenGLGetProcAddress(ext)	wglGetProcAddress((const char*)ext)
#elif defined(FastOSLinux)
#	define FastOpenGLGetProcAddress(ext)	glXGetProcAddress((const GLubyte*)ext)
#endif

#define FastOpenGLTryProc(proc, procClass, procString) \
	if (0 == proc) proc = (procClass)FastOpenGLGetProcAddress(procString);

#define FastOpenGLTryProcSuffix(procBase, procSuffix) \
	FastOpenGLTryProc(gl##procBase, GL ## procBase, "gl" ## #procBase ## procSuffix);

#define FastOpenGLLoadProc(procBase) \
	FastOpenGLTryProcSuffix(procBase, ""); \
	FastOpenGLTryProcSuffix(procBase, "EXT"); \
	FastOpenGLTryProcSuffix(procBase, "ARB"); \
	FastOpenGLTryProcSuffix(procBase, "MESA"); \
	FastOpenGLTryProcSuffix(procBase, "SGI");

#define FastOpenGLIsProcLoaded(proc) \
	if (0 == proc) \
		Exception::Throw(kExceptionOpenGLContextCreationFailure, \
			String("[%s(): %s]", FastFunctionName, #proc));

namespace Fast
{
	namespace OpenGL
	{
		// Context procs
		GLXSwapIntervalSGI			glXSwapIntervalSGI			= 0;
		GLXSwapIntervalEXT			glXSwapIntervalEXT			= 0;
		GLXSwapIntervalMESA			glXSwapIntervalMESA			= 0;
		WGLSwapInterval				wglSwapInterval				= 0;
		// Extension procs
		GLGenBuffers				glGenBuffers				= 0;
		GLBindBuffer				glBindBuffer				= 0;
		GLBufferData				glBufferData				= 0;
		GLVertexAttribPointer		glVertexAttribPointer		= 0;
		GLDeleteBuffers				glDeleteBuffers				= 0;
		GLEnableVertexAttribArray	glEnableVertexAttribArray	= 0;
		GLDisableVertexAttribArray	glDisableVertexAttribArray	= 0;
		GLCreateShader				glCreateShader				= 0;
		GLShaderSource				glShaderSource				= 0;
		GLCompileShader				glCompileShader				= 0;
		GLDeleteShader				glDeleteShader				= 0;
		GLCreateProgram				glCreateProgram				= 0;
		GLDeleteProgram				glDeleteProgram				= 0;
		GLAttachShader				glAttachShader				= 0;
		GLLinkProgram				glLinkProgram				= 0;
		GLUseProgram				glUseProgram				= 0;
		GLGetShaderiv				glGetShaderiv				= 0;
		GLGetProgramiv				glGetProgramiv				= 0;
		GLGetShaderInfoLog			glGetShaderInfoLog			= 0;
		GLGetProgramInfoLog			glGetProgramInfoLog			= 0;
		GLGenRenderbuffers			glGenRenderbuffers			= 0;
		GLDeleteRenderbuffers		glDeleteRenderbuffers		= 0;
		GLBindRenderbuffer			glBindRenderbuffer			= 0;
		GLRenderbufferStorage		glRenderbufferStorage		= 0;
		GLGenFramebuffers			glGenFramebuffers			= 0;
		GLDeleteFramebuffers		glDeleteFramebuffers		= 0;
		GLBindFramebuffer			glBindFramebuffer			= 0;
		GLFramebufferTexture2D		glFramebufferTexture2D		= 0;
		GLFramebufferRenderbuffer	glFramebufferRenderbuffer	= 0;
		GLBlendColor				glBlendColor				= 0;
		GLGenerateMipmap			glGenerateMipmap			= 0;
		GLGenVertexArrays			glGenVertexArrays			= 0;
		GLBindVertexArray			glBindVertexArray			= 0;
		GLActiveTexture				glActiveTexture				= 0;

	#if defined(FastOSWindows)
		LRESULT APIENTRY WndProc(HWND hWnd, UINT message,
			WPARAM wParam, LPARAM lParam)
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	#endif

		void OpenGL::LoadContextProcs() {
		#if defined(FastOSWindows)
			// Create temporary window to get context extensions
			WNDCLASS wndClass;
			HWND hwnd;
			MSG msg;
			HDC hdc;
			HGLRC hglrc;
			memset(&wndClass, 0, sizeof(WNDCLASS));
			wndClass.hInstance = GetModuleHandle(0);
			wndClass.lpszClassName = L"WndClass";
			wndClass.lpfnWndProc = WndProc;
			RegisterClass(&wndClass);
			hwnd = CreateWindow(L"WndClass", L"Name",
				0, 0, 0, 0, 0, 0, 0, GetModuleHandle(0), 0);
			UpdateWindow(hwnd);
			hdc = GetDC(hwnd);
			if (!hdc)
				Exception::Throw(kExceptionOpenGLContextCreationFailure,
					String("[%s()]", FastFunctionName));
			wglMakeCurrent(hdc, NULL);
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW |
				PFD_SUPPORT_OPENGL |
				PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				16,
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				0,
				0,
				0,
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};
			Int pixelFormat = ChoosePixelFormat(hdc, &pfd);
			SetPixelFormat(hdc, pixelFormat, &pfd);
			hglrc = wglCreateContext(hdc);
			if (!hglrc)
				Exception::Throw(kExceptionOpenGLContextCreationFailure,
					String("[%s()]", FastFunctionName));
			wglMakeCurrent(hdc, hglrc);
			// Load context extensions
			wglSwapInterval = (WGLSwapInterval)
				FastOpenGLGetProcAddress("wglSwapIntervalEXT");
			if (!wglSwapInterval)
				Exception::Throw(kExceptionOpenGLContextCreationFailure,
				String("[%s(): %s]", FastFunctionName, "WGLSwapInterval"));
			// Load GL extensions
			FastOpenGLLoadProc(GenBuffers);
			FastOpenGLLoadProc(BindBuffer);
			FastOpenGLLoadProc(BufferData);
			FastOpenGLLoadProc(VertexAttribPointer);
			FastOpenGLLoadProc(DeleteBuffers);
			FastOpenGLLoadProc(EnableVertexAttribArray);
			FastOpenGLLoadProc(DisableVertexAttribArray);
			FastOpenGLLoadProc(CreateShader);
			FastOpenGLLoadProc(ShaderSource);
			FastOpenGLLoadProc(CompileShader);
			FastOpenGLLoadProc(DeleteShader);
			FastOpenGLLoadProc(CreateProgram);
			FastOpenGLLoadProc(DeleteProgram);
			FastOpenGLLoadProc(AttachShader);
			FastOpenGLLoadProc(LinkProgram);
			FastOpenGLLoadProc(UseProgram);
			FastOpenGLLoadProc(GetShaderiv);
			FastOpenGLLoadProc(GetProgramiv);
			FastOpenGLLoadProc(GetShaderInfoLog);
			FastOpenGLLoadProc(GetProgramInfoLog);
			FastOpenGLLoadProc(GenRenderbuffers);
			FastOpenGLLoadProc(DeleteRenderbuffers);
			FastOpenGLLoadProc(BindRenderbuffer);
			FastOpenGLLoadProc(RenderbufferStorage);
			FastOpenGLLoadProc(GenFramebuffers);
			FastOpenGLLoadProc(DeleteFramebuffers);
			FastOpenGLLoadProc(BindFramebuffer);
			FastOpenGLLoadProc(FramebufferTexture2D);
			FastOpenGLLoadProc(FramebufferRenderbuffer);
			FastOpenGLLoadProc(BlendColor);
			FastOpenGLLoadProc(GenerateMipmap);
			FastOpenGLLoadProc(GenVertexArrays);
			FastOpenGLLoadProc(BindVertexArray);
			FastOpenGLLoadProc(ActiveTexture);
			// Check 'em
			FastOpenGLIsProcLoaded(glGenBuffers);
			FastOpenGLIsProcLoaded(glBindBuffer);
			FastOpenGLIsProcLoaded(glBufferData);
			FastOpenGLIsProcLoaded(glVertexAttribPointer);
			FastOpenGLIsProcLoaded(glDeleteBuffers);
			FastOpenGLIsProcLoaded(glEnableVertexAttribArray);
			FastOpenGLIsProcLoaded(glDisableVertexAttribArray);
			FastOpenGLIsProcLoaded(glCreateShader);
			FastOpenGLIsProcLoaded(glShaderSource);
			FastOpenGLIsProcLoaded(glCompileShader);
			FastOpenGLIsProcLoaded(glDeleteShader);
			FastOpenGLIsProcLoaded(glCreateProgram);
			FastOpenGLIsProcLoaded(glDeleteProgram);
			FastOpenGLIsProcLoaded(glAttachShader);
			FastOpenGLIsProcLoaded(glLinkProgram);
			FastOpenGLIsProcLoaded(glUseProgram);
			FastOpenGLIsProcLoaded(glGetShaderiv);
			FastOpenGLIsProcLoaded(glGetProgramiv);
			FastOpenGLIsProcLoaded(glGetShaderInfoLog);
			FastOpenGLIsProcLoaded(glGetProgramInfoLog);
			FastOpenGLIsProcLoaded(glGenRenderbuffers);
			FastOpenGLIsProcLoaded(glDeleteRenderbuffers);
			FastOpenGLIsProcLoaded(glBindRenderbuffer);
			FastOpenGLIsProcLoaded(glRenderbufferStorage);
			FastOpenGLIsProcLoaded(glGenFramebuffers);
			FastOpenGLIsProcLoaded(glDeleteFramebuffers);
			FastOpenGLIsProcLoaded(glBindFramebuffer);
			FastOpenGLIsProcLoaded(glFramebufferTexture2D);
			FastOpenGLIsProcLoaded(glFramebufferRenderbuffer);
			FastOpenGLIsProcLoaded(glBlendColor);
			FastOpenGLIsProcLoaded(glGenerateMipmap);
			FastOpenGLIsProcLoaded(glGenVertexArrays);
			FastOpenGLIsProcLoaded(glBindVertexArray);
			FastOpenGLIsProcLoaded(glActiveTexture);
			// Delete temporary window
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hglrc);
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);
		#elif defined(FastOSLinux)
			glXSwapIntervalSGI = (GLXSwapIntervalSGI)
				FastOpenGLGetProcAddress("glXSwapIntervalSGI");
			glXSwapIntervalEXT = (GLXSwapIntervalEXT)
				FastOpenGLGetProcAddress("glXSwapIntervalEXT");
			glXSwapIntervalMESA = (GLXSwapIntervalMESA)
				FastOpenGLGetProcAddress("glXSwapIntervalMESA");
			if (!glXSwapIntervalSGI && !glXSwapIntervalEXT &&
				!glXSwapIntervalMESA)
			{
				Exception::Throw(kExceptionOpenGLContextCreationFailure,
					String("[%s(): %s]", FastFunctionName, "GLXSwapInterval"));
			}
		#endif
		}

		void OpenGL::LoadExtensionProcs() {
		#if defined(FastOSWindows)
			/* // Create temporary window to get context extensions
			WNDCLASS wndClass;
			HWND hwnd;
			MSG msg;
			HDC hdc;
			HGLRC hglrc;
			memset(&wndClass, 0, sizeof(WNDCLASS));
			wndClass.hInstance = GetModuleHandle(0);
			wndClass.lpszClassName = L"WndClass";
			wndClass.lpfnWndProc = WndProc;
			RegisterClass(&wndClass);
			hwnd = CreateWindow(L"WndClass", L"Name",
				0, 0, 0, 0, 0, 0, 0, GetModuleHandle(0), 0);
			UpdateWindow(hwnd);
			hdc = GetDC(hwnd);
			if (!hdc)
				Exception::Throw(kExceptionOpenGLContextCreationFailure,
					String("[%s()]", FastFunctionName));
			wglMakeCurrent(hdc, NULL);
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW |
				PFD_SUPPORT_OPENGL |
				PFD_DOUBLEBUFFER,
				PFD_TYPE_RGBA,
				16,
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				0,
				0,
				0,
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
			};
			Int pixelFormat = ChoosePixelFormat(hdc, &pfd);
			SetPixelFormat(hdc, pixelFormat, &pfd);
			hglrc = wglCreateContext(hdc);
			if (!hglrc)
				Exception::Throw(kExceptionOpenGLContextCreationFailure,
					String("[%s()]", FastFunctionName));
			wglMakeCurrent(hdc, hglrc);*/
		#elif defined(FastOSLinux)
			// TODO
		#endif
		#if defined(FastOSWindows) || defined(FastOSLinux)
			// Load 'em
			FastOpenGLLoadProc(GenBuffers);
			FastOpenGLLoadProc(BindBuffer);
			FastOpenGLLoadProc(BufferData);
			FastOpenGLLoadProc(VertexAttribPointer);
			FastOpenGLLoadProc(DeleteBuffers);
			FastOpenGLLoadProc(EnableVertexAttribArray);
			FastOpenGLLoadProc(DisableVertexAttribArray);
			FastOpenGLLoadProc(CreateShader);
			FastOpenGLLoadProc(ShaderSource);
			FastOpenGLLoadProc(CompileShader);
			FastOpenGLLoadProc(DeleteShader);
			FastOpenGLLoadProc(CreateProgram);
			FastOpenGLLoadProc(DeleteProgram);
			FastOpenGLLoadProc(AttachShader);
			FastOpenGLLoadProc(LinkProgram);
			FastOpenGLLoadProc(UseProgram);
			FastOpenGLLoadProc(GetShaderiv);
			FastOpenGLLoadProc(GetProgramiv);
			FastOpenGLLoadProc(GetShaderInfoLog);
			FastOpenGLLoadProc(GetProgramInfoLog);
			FastOpenGLLoadProc(GenRenderbuffers);
			FastOpenGLLoadProc(DeleteRenderbuffers);
			FastOpenGLLoadProc(BindRenderbuffer);
			FastOpenGLLoadProc(RenderbufferStorage);
			FastOpenGLLoadProc(GenFramebuffers);
			FastOpenGLLoadProc(DeleteFramebuffers);
			FastOpenGLLoadProc(BindFramebuffer);
			FastOpenGLLoadProc(FramebufferTexture2D);
			FastOpenGLLoadProc(FramebufferRenderbuffer);
			FastOpenGLLoadProc(BlendColor);
			FastOpenGLLoadProc(GenerateMipmap);
			FastOpenGLLoadProc(GenVertexArrays);
			FastOpenGLLoadProc(BindVertexArray);
			FastOpenGLLoadProc(ActiveTexture);
			// Check 'em
			FastOpenGLIsProcLoaded(glGenBuffers);
			FastOpenGLIsProcLoaded(glBindBuffer);
			FastOpenGLIsProcLoaded(glBufferData);
			FastOpenGLIsProcLoaded(glVertexAttribPointer);
			FastOpenGLIsProcLoaded(glDeleteBuffers);
			FastOpenGLIsProcLoaded(glEnableVertexAttribArray);
			FastOpenGLIsProcLoaded(glDisableVertexAttribArray);
			FastOpenGLIsProcLoaded(glCreateShader);
			FastOpenGLIsProcLoaded(glShaderSource);
			FastOpenGLIsProcLoaded(glCompileShader);
			FastOpenGLIsProcLoaded(glDeleteShader);
			FastOpenGLIsProcLoaded(glCreateProgram);
			FastOpenGLIsProcLoaded(glDeleteProgram);
			FastOpenGLIsProcLoaded(glAttachShader);
			FastOpenGLIsProcLoaded(glLinkProgram);
			FastOpenGLIsProcLoaded(glUseProgram);
			FastOpenGLIsProcLoaded(glGetShaderiv);
			FastOpenGLIsProcLoaded(glGetProgramiv);
			FastOpenGLIsProcLoaded(glGetShaderInfoLog);
			FastOpenGLIsProcLoaded(glGetProgramInfoLog);
			FastOpenGLIsProcLoaded(glGenRenderbuffers);
			FastOpenGLIsProcLoaded(glDeleteRenderbuffers);
			FastOpenGLIsProcLoaded(glBindRenderbuffer);
			FastOpenGLIsProcLoaded(glRenderbufferStorage);
			FastOpenGLIsProcLoaded(glGenFramebuffers);
			FastOpenGLIsProcLoaded(glDeleteFramebuffers);
			FastOpenGLIsProcLoaded(glBindFramebuffer);
			FastOpenGLIsProcLoaded(glFramebufferTexture2D);
			FastOpenGLIsProcLoaded(glFramebufferRenderbuffer);
			FastOpenGLIsProcLoaded(glBlendColor);
			FastOpenGLIsProcLoaded(glGenerateMipmap);
			FastOpenGLIsProcLoaded(glGenVertexArrays);
			FastOpenGLIsProcLoaded(glBindVertexArray);
			FastOpenGLIsProcLoaded(glActiveTexture);
		#endif
		#if defined(FastOSWindows)
			/* // Delete temporary window
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(hglrc);
			ReleaseDC(hwnd, hdc);
			DestroyWindow(hwnd);*/
		#elif defined(FastOSLinux)
			// TODO
		#endif
		}

		void glXSwapInterval(CXDisplay *display,
			CGLXWindow drawable, Int interval)
		{
		#if defined(FastOSLinux)
			if (interval <= 0 ) {
				if (glXSwapIntervalExt)
					glXSwapIntervalExt((::Display*)display,
						(GLXDrawable)drawable, interval);
				else if (glXSwapIntervalMesa)
					glXSwapIntervalMesa((UInt)interval);
			} else if (interval > 0) {
				if (glXSwapIntervalSgi)
					glXSwapIntervalSgi(interval);
				else if (glXSwapIntervalExt)
					glXSwapIntervalExt((::Display*)display,
						(GLXDrawable)drawable, interval);
				else if (glXSwapIntervalMesa)
					glXSwapIntervalMesa((UInt)interval);
			}
		#endif
		}
	}
}
