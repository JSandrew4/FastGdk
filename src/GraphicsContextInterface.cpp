/******************************************************************************/
/*                                                                            */
/*  GraphicsContextInterface.cpp                                              */
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

#include <Fast/GraphicsContextInterface.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/Texture2DSurface.hpp>
#include <Fast/Window.hpp>
#include <Fast/Application.hpp>
#include <Fast/Display.hpp>
#include <Fast/VideoMode.hpp>
#include <Fast/Display.hpp>
#include <Fast/Monitor.hpp>
#include <Fast/Rectangle.hpp>
#include <Fast/Exception.hpp>
#include <Fast/Texture2DData.hpp>
#include <Fast/AlphaTexture2DData.hpp>
#include <Fast/GraphicsCapabilities.hpp>
#include <Fast/Texture2DProperties.hpp>
#include <Fast/SystemConsole.hpp>
#include <Fast/Color.hpp>
#include <Fast/RenderItem.hpp>
#include <Fast/MeshResource.hpp>
#include <Fast/MeshData.hpp>

#if defined(FastOSWindows)
#	include <WindowsX.h>
#	include <gl/GL.h>
#	include <gl/GLU.h>
#	include "glext.h"
#elif defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/Xatom.h>
#	include <X11/Xutil.h>
#	include <X11/cursorfont.h>
#	include <X11/extensions/XInput2.h>
#	include <unistd.h>
#endif

#include "OpenGL.hpp"
#include "NSInterface.hpp"
#include "X11Interface.hpp"
#include "W32Interface.hpp"

#include "Undefs.hpp"

namespace Fast
{
	using namespace OpenGL;

	GLenum GraphicsFastCapabilityToGLenum(GraphicsCapability capability) {
		static const GLenum capabilities[] = {
			GL_NONE,					// kGraphicsCapabilityNone
			GL_NONE,					// kGraphicsCapabilityVerticalSync
			GL_DEPTH_TEST,				// kGraphicsCapabilityDepth
			GL_POINT_SMOOTH,			// kGraphicsCapabilityPointSmoothing
			GL_LINE_SMOOTH,				// kGraphicsCapabilityLineSmoothing
			GL_CULL_FACE,				// kGraphicsCapabilityFaceCulling
			GL_MULTISAMPLE,				// kGraphicsCapabilityMultisampling
			GL_BLEND,					// kGraphicsCapabilityBlending
			GL_SCISSOR_TEST,			// kGraphicsCapabilityScissorRendering
			GL_TEXTURE_2D,				// kGraphicsCapabilityTexture2D
			GL_POLYGON_OFFSET_FILL,		// kGraphicsCapabilityPolygonOffsetFill
			GL_POLYGON_OFFSET_LINE,		// kGraphicsCapabilityPolygonOffsetLine
			GL_POLYGON_OFFSET_POINT		// kGraphicsCapabilityPolygonOffsetPoint
		};
		return capabilities[(Int)capability];
	}

	GLenum GraphicsFastTexture2DFilterTypeToGLenum(Texture2DFilterType type) {
		static const GLenum filterType[] = {
			GL_NONE,					// kTexture2DFilterNone
			GL_NEAREST,					// kTexture2DFilterNearest
			GL_LINEAR,					// kTexture2DFilterLinear
			GL_NEAREST_MIPMAP_NEAREST,	// kTexture2DFilterNearestMipmapNearest
			GL_LINEAR_MIPMAP_NEAREST,	// kTexture2DFilterLinearMipmapNearest
			GL_NEAREST_MIPMAP_LINEAR,	// kTexture2DFilterNearestMipmapLinear
			GL_LINEAR_MIPMAP_LINEAR		// kTexture2DFilterLinearMipmapLinear
		};
		return filterType[(Int)type];
	}

	GLenum GraphicsFastTexture2DWrapTypeToGLenum(Texture2DWrapType type) {
		static const GLenum wrapType[] = {
			GL_NONE,			// kTexture2DWrapNone
			GL_CLAMP_TO_EDGE,	// kTexture2DWrapClampToEdge
			GL_CLAMP_TO_BORDER,	// kTexture2DWrapClampToBorder
			GL_MIRRORED_REPEAT,	// kTexture2DWrapMirroredRepeat
			GL_REPEAT			// kTexture2DWrapRepeat
		};
		return wrapType[(Int)type];
	}

	GLenum GraphicsFastTextureUnitToGLenum(Int textureUnit) {
		static const GLenum unit[] = {
			GL_TEXTURE0,
			GL_TEXTURE1,
			GL_TEXTURE2,
			GL_TEXTURE3,
			GL_TEXTURE4,
			GL_TEXTURE5,
			GL_TEXTURE6,
			GL_TEXTURE7,
			GL_TEXTURE8,
			GL_TEXTURE9,
			GL_TEXTURE10,
			GL_TEXTURE11,
			GL_TEXTURE12,
			GL_TEXTURE13,
			GL_TEXTURE14,
			GL_TEXTURE15,
			GL_TEXTURE16,
			GL_TEXTURE17,
			GL_TEXTURE18,
			GL_TEXTURE19,
			GL_TEXTURE20,
			GL_TEXTURE21,
			GL_TEXTURE22,
			GL_TEXTURE23,
			GL_TEXTURE24,
			GL_TEXTURE25,
			GL_TEXTURE26,
			GL_TEXTURE27,
			GL_TEXTURE28,
			GL_TEXTURE29,
			GL_TEXTURE30,
			GL_TEXTURE31
		};
		return unit[(Int)textureUnit];
	}

	GLenum GraphicsFastPolygonFaceToGLenum(PolygonFace face) {
		static const GLenum faces[] = {
			GL_NONE,			// kPolygonFaceNone
			GL_BACK,			// kPolygonFaceBack
			GL_FRONT,			// kPolygonFaceFront
			GL_FRONT_AND_BACK	// kPolygonFaceFrontAndBack
		};
		return faces[(Int)face];
	}

	GLenum GraphicsFastRenderPrimitiveToGLenum(RenderPrimitive primitive) {
		static const GLenum primitives[] = {
			GL_NONE,			// kRenderPrimitiveNone
			GL_TRIANGLES,		// kRenderPrimitiveTriangles
			GL_TRIANGLE_STRIP,	// kRenderPrimitiveTriangleStrip
			GL_TRIANGLE_FAN,	// kRenderPrimitiveTriangleFan
			GL_POINTS,			// kRenderPrimitivePoints
			GL_LINES,			// kRenderPrimitiveLines
			GL_LINE_STRIP,		// kRenderPrimitiveLineStrip
			GL_LINE_LOOP		// kRenderPrimitiveLineLoop
		};
		return primitives[(Int)primitive];
	}

	GLenum GraphicsFastPolygonModeToGLenum(PolygonMode mode) {
		static const GLenum modes[] = {
			GL_NONE,	// kPolygonNone
			GL_FILL,	// kPolygonFill
			GL_LINE,	// kPolygonLine
			GL_POINT	// kPolygonPoint
		};
		return modes[(Int)mode];
	}

	GLenum GraphicsFastBufferToGLBufferBit(GraphicsBufferType bufferType) {
		static const GLenum buffers[] = {
			// kGraphicsBufferNone
			GL_NONE,
			// kGraphicsBufferColor
			GL_COLOR_BUFFER_BIT,
			// kGraphicsBufferDepth
			GL_DEPTH_BUFFER_BIT,
			// kGraphicsBufferStencil
			GL_STENCIL_BUFFER_BIT,
			// kGraphicsBufferColorAndDepth
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
			// kGraphicsBufferColorAndStencil
			GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
			// kGraphicsBufferDepthAndStencil
			GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
			// kGraphicsBufferAll
			GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
		};
		return buffers[(Int)bufferType];
	}

	GraphicsContextInterface::GraphicsContextInterface(Window &window) :
		mWindow(window)
	{
		mIsCreated = false;
		mDepthBits = 0;
		mStencilBits = 0;
		mHdc = NULL;
		mHglrc = NULL;
		mGLXContext = NULL;
		mGLXWindow = NULL;
		mNSOpenGLContext = NULL;
	}

	GraphicsContextInterface::~GraphicsContextInterface() { }

	void GraphicsContextInterface::CreateContext()
	{
		// TODO: Initialize mStack members
		// Initialize members
		mStackIndex = 0;
		mHdc = 0;
		mHglrc = 0;
		mGLXContext = 0;
		mGLXWindow = 0;
		mNSOpenGLContext = 0;
		// Setup contexts
		OpenGL::LoadContextProcs();
	#if defined(FastOSWindows)
		HDC hdc = NULL;
		HGLRC hglrc = NULL;
		HWND hwnd = NULL;
		Int pixelFormat = 0;
		hwnd = (HWND)mWindow.GetHWND();
		hdc = GetDC(hwnd);
		if (!hdc)
			Exception::Throw(kExceptionOpenGLContextCreationFailure,
				String("[%s()]", FastFunctionName));
		pixelFormat = W32FindBestPixelFormat((CHDC)hdc);
		if (!pixelFormat)
			Exception::Throw(kExceptionOpenGLNoValidPixelFormats,
				String("[%s()]", FastFunctionName));
		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(pfd));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		DescribePixelFormat(hdc, pixelFormat, pfd.nSize, &pfd);
		mDepthBits = pfd.cDepthBits;
		mStencilBits = pfd.cStencilBits;
		SetPixelFormat(hdc, pixelFormat, &pfd);
		hglrc = wglCreateContext(hdc);
		if (!hglrc)
			Exception::Throw(kExceptionOpenGLContextCreationFailure,
				String("[%s()]", FastFunctionName));
		mHdc = (CHDC)hdc;
		mHglrc = (CHGLRC)hglrc;
	#elif defined(FastOSLinux)
		::Display *xdisplay = (::Display*)mWindow->GetDisplay()->GetXDisplay();
		::Window xwindow = (::Window)mWindow->GetXWindow();
		GLXFBConfig glxFBConfig = (GLXFBConfig)mWindow->GetGLXFBConfig();
		mGLXContext = (CGLXContext)glXCreateNewContext(xdisplay,
			glxFBConfig, GLX_RGBA_TYPE, 0, True);
		if (!mGLXContext)
			Exception::Throw(kExceptionOpenGLContextCreationFailure,
				String("[GraphicsContextInterface::CreateContext(%p, %d, %d)]",
					(void*)window, depthBits, stencilBits));
		mGLXWindow = (CGLXWindow)glXCreateWindow(
			xdisplay, glxFBConfig, xwindow, 0);
		if (!mGLXWindow)
			Exception::Throw(kExceptionWindowCreationFailure,
				String("[GraphicsContextInterface::CreateContext(%p, %d, %d)]",
					(void*)window, depthBits, stencilBits));
	#elif defined(FastOSMacOSX)
		mNSOpenGLContext = NSCreateOpenGLContext(
			window->GetNSWindow(), depthBits, stencilBits);
		if (!mNSOpenGLContext)
			Exception::Throw(kExceptionOpenGLContextCreationFailure,
				String("[GraphicsContextInterface::CreateContext(%p, %d, %d)]",
					(void*)window, depthBits, stencilBits));
	#endif
		MakeCurrent(true);
		mCapabilities.Populate();
		mStack.Append(GraphicsContextState(this));
		// OpenGL won't be managing our matrices so set GL_MODELVIEW and forget
		//	about it
		glMatrixMode(GL_MODELVIEW);
		mIsCreated = true;
	}

	void GraphicsContextInterface::DeleteContext() {
		MakeCurrent(false);
	#if defined(FastOSWindows)
		wglDeleteContext((HGLRC)mHglrc);
	#elif defined(FastOSLinux)
		glXDestroyContext((::Display*)mWindow->GetDisplay()->GetXDisplay(),
			(GLXContext)mGLXContext);
	#elif defined(FastOSMacOSX)
		NSDestroyOpenGLContext(mNSOpenGLContext);
	#endif
		mIsCreated = false;
	}

	void GraphicsContextInterface::MakeCurrent(Bool shouldMakeCurrent) {
	#if defined(FastOSWindows)
		if (shouldMakeCurrent)
			wglMakeCurrent((HDC)mHdc, (HGLRC)mHglrc);
		else
			wglMakeCurrent((HDC)mHdc, 0);
	#elif defined(FastOSLinux)
		if (shouldMakeCurrent)
			glXMakeContextCurrent(
				(::Display*)mWindow->GetDisplay()->GetXDisplay(),
				(GLXWindow)mGLXWindow, (GLXWindow)mGLXWindow,
				(GLXContext)mGLXContext);
		else
			glXMakeContextCurrent(
				(::Display*)mWindow->GetDisplay()->GetXDisplay(), 0, 0, 0);
	#elif defined(FastOSMacOSX)
		NSMakeContextCurrent(shouldMakeCurrent ? mNSOpenGLContext : false);
	#endif
	}

	void GraphicsContextInterface::Enable(GraphicsCapability capability) {
		if (true == mStack[mStackIndex].mCapabilitiesEnabled[(Int)capability])
			return;
		mStack[mStackIndex].mCapabilitiesEnabled[(Int)capability] = true;
		if (kGraphicsCapabilityVerticalSync == capability) {
		#if defined(FastOSWindows)
			wglSwapInterval(1);
		#elif defined(FastOSLinux)
			glXSwapInterval(mWindows->GetDisplay()->GetXDisplay(),
				mGLXWindow, 1);
		#elif defined(FastOSMacOSX)
			//mCocoaGLContext->EnableVSync(true);
		#endif
			return;
		}
		glEnable(GraphicsFastCapabilityToGLenum(capability));
	}

	void GraphicsContextInterface::Disable(GraphicsCapability capability) {
		if (false == mStack[mStackIndex].mCapabilitiesEnabled[(Int)capability])
			return;
		mStack[mStackIndex].mCapabilitiesEnabled[(Int)capability] = false;
		if (kGraphicsCapabilityVerticalSync == capability) {
		#if defined(FastOSWindows)
			wglSwapInterval(0);
		#elif defined(FastOSLinux)
			glXSwapInterval(mWindow->GetDisplay()->GetXDisplay(),
				mGLXWindow, 0);
		#elif defined(FastOSMacOSX)
			//mCocoaGLContext->EnableVSync(false);
		#endif
			return;
		}
		glDisable(GraphicsFastCapabilityToGLenum(capability));
	}

	void GraphicsContextInterface::Clear(GraphicsBufferType bufferType) {
		glClear(GraphicsFastBufferToGLBufferBit(bufferType));
	}

	void GraphicsContextInterface::FlipBuffers() {
	#if defined(FastOSWindows)
		SwapBuffers((HDC)mHdc);
	#elif defined(FastOSLinux)
		glXSwapBuffers((::Display*)mWindow->GetDisplay()->GetXDisplay(),
			(GLXWindow)mGLXWindow);
	#elif defined(FastOSMacOSX)
		//mCocoaWindow->SwapGraphicsBuffers();
	#endif
	}

	void GraphicsContextInterface::PushAttributes() {
		mStackIndex++;
		if (mStack.GetElementCount() <= mStackIndex)
			mStack.SetElementCount(mStack.GetElementCount() * 2,
				GraphicsContextState(this));
		mStack[mStackIndex] = mStack[mStackIndex-1];
	}

	void GraphicsContextInterface::PopAttributes() {
		if (0 == mStackIndex)
			return;
		Int index = mStackIndex - 1;
		// mCapabilitiesEnabled
		for (Int i = 1; i < 32; i++)
			mStack[index].mCapabilitiesEnabled[i] ?
				Enable((GraphicsCapability)i) : Disable((GraphicsCapability)i);
		// mBoundTexture2D
		for (Int i = 0; i < mCapabilities.GetMaxTextureUnitsCount(); i++)
			BindTexture2D(mStack[index].mBoundOpenGLTexture2DIDArray[i], i);
		SetActiveTextureUnit(mStack[mStackIndex].mActiveTextureUnit);
		// mBoundRenderSurface
		if (mStack[index].mBoundOpenGLFramebufferID)
			BindFramebuffer(mStack[index].mBoundOpenGLFramebufferID);
		else
			BindFramebuffer(0);
		// mPointSize
		SetPointSize(mStack[index].mPointSize);
		// mLineWidth
		SetLineWidth(mStack[index].mLineWidth);
		// mCullFace
		SetCullFace(mStack[index].mCullFace);
		// mPolygonWindingDirection
		SetPolygonWindingDirection(mStack[index].mPolygonWindingDirection);
		// mFrontFacePolygonMode
		SetPolygonMode(kPolygonFaceFront,
			mStack[index].mFrontFacePolygonMode);
		// mBackFacePolygonMode
		SetPolygonMode(kPolygonFaceBack,
			mStack[index].mBackFacePolygonMode);
		// TODO: Blend equations
		// mViewportRectangle
		SetViewportRectangle(mStack[index].mViewportRectangle);
		// mScissorRectangle
		SetScissorRectangle(mStack[index].mScissorRectangle);
		// mPolygonOffsetFactor, mPolygonOffsetUnits
		SetPolygonOffset(mStack[index].mPolygonOffsetFactor,
			mStack[index].mPolygonOffsetUnits);
		// mModelViewProjectionMatrix
		SetModelViewProjectionMatrix(
			mStack[index].mModelViewProjectionMatrix);
	}

	void GraphicsContextInterface::SetActiveTextureUnit(Int textureUnit) {
		Enable(kGraphicsCapabilityTexture2D);
		if (textureUnit != mStack[mStackIndex].mActiveTextureUnit &&
			0 <= textureUnit &&
			mCapabilities.GetMaxTextureUnitsCount() > textureUnit)
		{
			mStack[mStackIndex].mActiveTextureUnit = textureUnit;
			glActiveTexture(GraphicsFastTextureUnitToGLenum(textureUnit));
		}
	}

	void GraphicsContextInterface::BindTexture2D(UInt openGLTexture2DID) {
		Enable(kGraphicsCapabilityTexture2D);
		if (openGLTexture2DID !=
			mStack[mStackIndex].mBoundOpenGLTexture2DIDArray[
				mStack[mStackIndex].mActiveTextureUnit])
		{
			mStack[mStackIndex].mBoundOpenGLTexture2DIDArray[
				mStack[mStackIndex].mActiveTextureUnit] = openGLTexture2DID;
			glBindTexture(GL_TEXTURE_2D, openGLTexture2DID);
		}
	}

	void GraphicsContextInterface::BindTexture2D(
		UInt openGLTexture2DID, Int textureUnit)
	{
		Enable(kGraphicsCapabilityTexture2D);
		if (textureUnit != mStack[mStackIndex].mActiveTextureUnit) {
			if (0 > textureUnit ||
				mCapabilities.GetMaxTextureUnitsCount() <= textureUnit)
			{
				return;
			}
			mStack[mStackIndex].mActiveTextureUnit = textureUnit;
			glActiveTexture(GraphicsFastTextureUnitToGLenum(textureUnit));
		}
		if (openGLTexture2DID !=
			mStack[mStackIndex].mBoundOpenGLTexture2DIDArray[textureUnit])
		{
			mStack[mStackIndex].mBoundOpenGLTexture2DIDArray[textureUnit] =
				openGLTexture2DID;
			glBindTexture(GL_TEXTURE_2D, openGLTexture2DID);
		}
	}

	void GraphicsContextInterface::BindFramebuffer(UInt openGLFramebufferID) {
		if (openGLFramebufferID !=
			mStack[mStackIndex].mBoundOpenGLFramebufferID)
		{
			mStack[mStackIndex].mBoundOpenGLFramebufferID = openGLFramebufferID;
			glBindFramebuffer(GL_FRAMEBUFFER, openGLFramebufferID);
			// Binding the framebuffer also binds the associated renderbuffer
			for (Int i = 0; mOpenGLFramebufferStates.GetElementCount(); i++) {
				if (openGLFramebufferID ==
					mOpenGLFramebufferStates[i].mOpenGLID)
				{
					mStack[mStackIndex].mBoundOpenGLRenderbufferID =
						mOpenGLFramebufferStates[i].mRenderbufferID;
				}
			}
		}
	}

	void GraphicsContextInterface::BindRenderbuffer(UInt openGLRenderbufferID) {
		if (openGLRenderbufferID !=
			mStack[mStackIndex].mBoundOpenGLRenderbufferID)
		{
			mStack[mStackIndex].mBoundOpenGLRenderbufferID = openGLRenderbufferID;
			glBindRenderbuffer(GL_RENDERBUFFER, openGLRenderbufferID);
		}
	}

	void GraphicsContextInterface::BindVertexArray(UInt openGLVertexArrayID) {
		if (openGLVertexArrayID !=
			mStack[mStackIndex].mBoundOpenGLVertexArrayID)
		{
			mStack[mStackIndex].mBoundOpenGLVertexArrayID = openGLVertexArrayID;
			glBindVertexArray(openGLVertexArrayID);
		}
	}

	void GraphicsContextInterface::UseShaderProgram(UInt openGLShaderProgramID)
	{
		if (openGLShaderProgramID !=
			mStack[mStackIndex].mOpenGLShaderProgramIDInUse)
		{
			mStack[mStackIndex].mOpenGLShaderProgramIDInUse = openGLShaderProgramID;
			glUseProgram(openGLShaderProgramID);
		}
	}

	void GraphicsContextInterface::Draw(const RenderItem &item) {
		const RenderPreferences *rp = &item.mRenderPreferences;
		PushAttributes();
			Enable(kGraphicsCapabilityTexture2D);
			UseShaderProgram(item.mOpenGLShaderProgramID);
			BindTexture2D(item.mOpenGLTexture2DID);
			BindVertexArray(item.mOpenGLVertexArrayID);
			glDrawArrays(GraphicsFastRenderPrimitiveToGLenum(rp->GetPrimitive()),
				item.mFirstElement, item.mElementCount);
		PopAttributes();
	}

	void GraphicsContextInterface::SetPointSize(Float size) {
		if (size == mStack[mStackIndex].mPointSize)
			return;
		mStack[mStackIndex].mPointSize = size;
		glPointSize(size);
	}

	void GraphicsContextInterface::SetLineWidth(Float width) {
		if (width == mStack[mStackIndex].mLineWidth)
			return;
		mStack[mStackIndex].mLineWidth = width;
		glLineWidth(width);
	}

	void GraphicsContextInterface::SetCullFace(PolygonFace cullFace) {
		if (cullFace == mStack[mStackIndex].mCullFace)
			return;
		mStack[mStackIndex].mCullFace = cullFace;
		glCullFace(GraphicsFastPolygonFaceToGLenum(cullFace));
	}

	void GraphicsContextInterface::SetPolygonWindingDirection(
		PolygonWindingDirection polygonWindingDirection)
	{
		if (polygonWindingDirection ==
			mStack[mStackIndex].mPolygonWindingDirection)
		{
			return;
		}
		mStack[mStackIndex].mPolygonWindingDirection = polygonWindingDirection;
		glFrontFace(kPolygonWindingCounterClockwise == polygonWindingDirection
			? GL_CCW : GL_CW);
	}

	void GraphicsContextInterface::SetPolygonMode(
		PolygonFace face, PolygonMode polygonMode)
	{
		switch (face)
		{
		case kPolygonFaceFront:
			if (polygonMode == mStack[mStackIndex].mFrontFacePolygonMode)
				return;
			mStack[mStackIndex].mFrontFacePolygonMode = polygonMode;
			break;
		case kPolygonFaceBack:
			if (polygonMode == mStack[mStackIndex].mBackFacePolygonMode)
				return;
			mStack[mStackIndex].mBackFacePolygonMode = polygonMode;
			break;
		case kPolygonFaceFrontAndBack:
			if (polygonMode == mStack[mStackIndex].mFrontFacePolygonMode &&
				polygonMode == mStack[mStackIndex].mBackFacePolygonMode)
			{
				return;
			}
			mStack[mStackIndex].mFrontFacePolygonMode = polygonMode;
			mStack[mStackIndex].mBackFacePolygonMode = polygonMode;
			break;
		};
		glPolygonMode(GraphicsFastPolygonFaceToGLenum(face),
			GraphicsFastPolygonModeToGLenum(polygonMode));
	}

	void GraphicsContextInterface::SetBlendColor(const Color &color) {
		if (color == mStack[mStackIndex].mBlendColor)
			return;
		mStack[mStackIndex].mBlendColor = color;
		glBlendColor(color.mRed, color.mGreen, color.mBlue, color.mAlpha);
	}

	void GraphicsContextInterface::SetViewportRectangle(const Rectangle &rect) {
		if (rect == mStack[mStackIndex].mViewportRectangle)
			return;
		mStack[mStackIndex].mViewportRectangle = rect;
		glViewport(rect.mX, rect.mY, rect.mWidth, rect.mHeight);
	}

	void GraphicsContextInterface::SetScissorRectangle(const Rectangle &rect) {
		if (rect == mStack[mStackIndex].mScissorRectangle)
			return;
		mStack[mStackIndex].mScissorRectangle = rect;
		glScissor(rect.mX, rect.mY, rect.mWidth, rect.mHeight);
	}

	void GraphicsContextInterface::SetPolygonOffset(Float factor, Float units) {
		if (factor == mStack[mStackIndex].mPolygonOffsetFactor &&
			units == mStack[mStackIndex].mPolygonOffsetUnits)
		{
			return;
		}
		mStack[mStackIndex].mPolygonOffsetFactor = factor;
		mStack[mStackIndex].mPolygonOffsetUnits = units;
		glPolygonOffset(factor, units);
	}

	UInt GraphicsContextInterface::GenerateNewOpenGLTexture2DID() {
		UInt openGLTexture2DID = 0;
		Enable(kGraphicsCapabilityTexture2D);
		glGenTextures(1, (GLuint*)&openGLTexture2DID);
		return openGLTexture2DID;
	}

	UInt GraphicsContextInterface::GenerateNewOpenGLRenderbufferID() {
		UInt openGLRenderbufferID = 0;
		glGenRenderbuffers(1, (GLuint*)&openGLRenderbufferID);
		return openGLRenderbufferID;
	}

	UInt GraphicsContextInterface::GenerateNewOpenGLFramebufferID() {
		UInt openGLFramebufferID = 0;
		glGenFramebuffers(1, (GLuint*)&openGLFramebufferID);
		return openGLFramebufferID;
	}

	UInt GraphicsContextInterface::GenerateNewOpenGLBufferID() {
		UInt openGLBufferID = 0;
		glGenBuffers(1, (GLuint*)&openGLBufferID);
		return openGLBufferID;
	}

	void GraphicsContextInterface::CreateOpenGLMesh(
		MeshResource *resource, const MeshData &data, Int usage)
	{
		Array<VertexStruct> varray;
		Array<TriangleStruct> iarray;
		// Load vertices into OpenGL
		resource->mOpenGLVertexBufferID = GenerateNewOpenGLBufferID();
		glBindBuffer(GL_ARRAY_BUFFER, resource->mOpenGLVertexBufferID);
		varray = data.GetVertexStructArray();
		glBufferData(GL_ARRAY_BUFFER, varray.GetElementCount() *
			sizeof(VertexStruct), &varray[0], usage);
		// Load indices into OpenGL
		if (0 >= data.GetNumFaces())
			return;
		resource->mOpenGLIndexBufferID = GenerateNewOpenGLBufferID();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resource->mOpenGLIndexBufferID);
		iarray = data.GetTriangleStructArray();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iarray.GetElementCount() *
			sizeof(TriangleStruct), &iarray[0], usage);
	}

	void GraphicsContextInterface::DeleteOpenGLTexture2DID(
		UInt openGLTexture2DID)
	{
		Enable(kGraphicsCapabilityTexture2D);
		for (Int i = 0; i < mOpenGLFramebufferStates.GetElementCount(); i++)
			if (openGLTexture2DID == mOpenGLFramebufferStates[i].mTexture2DID)
				mOpenGLFramebufferStates[i].mTexture2DID = 0;
		glDeleteTextures(1, (GLuint*)&openGLTexture2DID);
	}

	void GraphicsContextInterface::DeleteOpenGLRenderbufferID(
		UInt openGLRenderbufferID)
	{
		for (Int i = 0; i < mOpenGLFramebufferStates.GetElementCount(); i++) {
			if (openGLRenderbufferID ==
				mOpenGLFramebufferStates[i].mRenderbufferID)
			{
				mOpenGLFramebufferStates[i].mRenderbufferID = 0;
			}
		}
		glDeleteRenderbuffers(1, &openGLRenderbufferID);
	}

	void GraphicsContextInterface::DeleteOpenGLFramebufferID(
		UInt openGLFramebufferID)
	{
		glDeleteFramebuffers(1, &openGLFramebufferID);
	}

	void GraphicsContextInterface::DeleteOpenGLBufferID(
		UInt openGLBufferID)
	{
		glDeleteBuffers(1, &openGLBufferID);
	}

	void GraphicsContextInterface::DeleteOpenGLMesh(MeshResource *resource) {
		glDeleteBuffers(1, &resource->mOpenGLVertexBufferID);
		glDeleteBuffers(1, &resource->mOpenGLIndexBufferID);
	}

	void GraphicsContextInterface::StoreTexture2DData(
		UInt openGLTexture2DID, const Texture2DData &texture2DData)
	{
		PushAttributes();
			Enable(kGraphicsCapabilityTexture2D);
			// TODO: Make these properties changeable somehow
			BindTexture2D(openGLTexture2DID);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				GraphicsFastTexture2DWrapTypeToGLenum(
					texture2DData.GetProperties().GetWrapTypeS()));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				GraphicsFastTexture2DWrapTypeToGLenum(
					texture2DData.GetProperties().GetWrapTypeT()));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
				GraphicsFastTexture2DFilterTypeToGLenum(
					texture2DData.GetProperties().GetMagnifyFilterType()));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GraphicsFastTexture2DFilterTypeToGLenum(
					texture2DData.GetProperties().GetMinifyFilterType()));
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			const Color &color = texture2DData.GetProperties().GetBorderColor();
			GLfloat c[] = { color.mRed, color.mGreen, color.mBlue, color.mAlpha };
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, c);
			if (texture2DData.GetBitsPerPixel() == 32)
				glTexImage2D(GL_TEXTURE_2D, 0,
					(Int)texture2DData.GetBitsPerPixel() / 8,
					texture2DData.GetWidth(), texture2DData.GetHeight(),
					0, GL_RGBA, GL_UNSIGNED_BYTE,
					texture2DData.GetPixels().GetData());
			else if (texture2DData.GetBitsPerPixel() == 24)
				glTexImage2D(GL_TEXTURE_2D, 0,
					(Int)texture2DData.GetBitsPerPixel() / 8,
					texture2DData.GetWidth(), texture2DData.GetHeight(),
					0, GL_RGB, GL_UNSIGNED_BYTE,
					texture2DData.GetPixels().GetData());
			if (texture2DData.GetProperties().GetMagnifyFilterType() >
				kTexture2DFilterLinear ||
				texture2DData.GetProperties().GetMinifyFilterType() >
				kTexture2DFilterLinear)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
			}
		PopAttributes();
	}

	void GraphicsContextInterface::StoreAlphaTexture2DData(
		UInt openGLAlphaTexture2DID, const AlphaTexture2DData &alphaTexture2D,
		Int offsetX, Int offsetY)
	{
		PushAttributes();
			Enable(kGraphicsCapabilityTexture2D);
			// TODO: Make these properties changeable somehow
			BindTexture2D(openGLAlphaTexture2DID);
			glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
			glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
			glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexSubImage2D(GL_TEXTURE_2D, 0, offsetX, offsetY,
				alphaTexture2D.GetWidth(), alphaTexture2D.GetHeight(), GL_ALPHA,
				GL_UNSIGNED_BYTE, &alphaTexture2D.GetPixels()[0]);
		PopAttributes();
	}

	void GraphicsContextInterface::GenerateNewRenderSurfaceIDs(Int width,
		Int height, UInt *openGLTexture2DID, UInt *openGLFramebufferID,
		UInt *openGLRenderbufferID)
	{
		PushAttributes();
			Enable(kGraphicsCapabilityTexture2D);
			*openGLTexture2DID = GenerateNewOpenGLTexture2DID();
			if (!openGLTexture2DID) {
				PopAttributes();
				return;
			}
			*openGLRenderbufferID = GenerateNewOpenGLRenderbufferID();
			if (!openGLRenderbufferID) {
				DeleteOpenGLTexture2DID(*openGLTexture2DID);
				PopAttributes();
				return;
			}
			*openGLFramebufferID = GenerateNewOpenGLFramebufferID();
			if (!openGLFramebufferID) {
				DeleteOpenGLTexture2DID(*openGLTexture2DID);
				DeleteOpenGLRenderbufferID(*openGLRenderbufferID);
				PopAttributes();
				return;
			}
			// Set up Framebuffer Texture2DSurface
			BindTexture2D(*openGLTexture2DID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
				height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			// Set up Renderbuffer
			BindRenderbuffer(*openGLRenderbufferID);
			glRenderbufferStorage(GL_RENDERBUFFER,
				GL_DEPTH_COMPONENT16, width, height);
			// Set up Framebuffer
			BindFramebuffer(*openGLFramebufferID);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_2D, (GLuint)openGLTexture2DID, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				GL_RENDERBUFFER, (GLuint)openGLRenderbufferID);
		PopAttributes();
	}

	void GraphicsContextInterface::DeleteRenderSurfaceIDs(
		UInt openGLFramebufferID, UInt openGLRenderbufferID)
	{
		glDeleteFramebuffers(1, (GLuint*)&openGLFramebufferID);
		glDeleteRenderbuffers(1, (GLuint*)&openGLRenderbufferID);
	}

	void GraphicsContextInterface::SetModelViewProjectionMatrix(
		const Matrix &matrix)
	{
		// TODO: Deprecated
		glLoadMatrixf(matrix.mElements);
	}

	Bool GraphicsContextInterface::IsCreated() const {
		return mIsCreated;
	}

	Int GraphicsContextInterface::GetDepthBits() const {
		return mDepthBits;
	}

	Int GraphicsContextInterface::GetStencilBits() const {
		return mStencilBits;
	}

	const GraphicsCapabilities& GraphicsContextInterface::GetCapabilities()
		const
	{
		return mCapabilities;
	}

	void GraphicsContextInterface::RetrieveTexture2DData(
		UInt openGLTexture2DID, Texture2DData *texture2DData)
	{
		Texture2DProperties texture2DProperties;
		RetrieveTexture2DProperties(openGLTexture2DID, &texture2DProperties);
		if (0 == texture2DProperties.GetWidth())
			return;
		PushAttributes();
			Enable(kGraphicsCapabilityTexture2D);
			BindTexture2D(openGLTexture2DID);
			*texture2DData = Texture2DData(texture2DProperties);
			if (texture2DData->GetBitsPerPixel() == 32)
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA,
					GL_UNSIGNED_BYTE,
					(GLubyte*)texture2DData->GetPixels().GetData());
			else if (texture2DData->GetBitsPerPixel() == 24)
				glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB,
					GL_UNSIGNED_BYTE,
					(GLubyte*)texture2DData->GetPixels().GetData());
		PopAttributes();
	}

	void GraphicsContextInterface::RetrieveTexture2DProperties(
		UInt openGLTexture2DID, Texture2DProperties *texture2DProperties)
	{
		GLint format;
		PushAttributes();
			Enable(kGraphicsCapabilityTexture2D);
			BindTexture2D(openGLTexture2DID);
			// Get ImageProperties
			Int width = texture2DProperties->GetWidth();
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0,
				GL_TEXTURE_WIDTH, &width);
			if (0 == texture2DProperties->GetWidth()) {
				*texture2DProperties = Texture2DProperties();
				PopAttributes();
				return;
			}
			Int height = texture2DProperties->GetHeight();
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0,
				GL_TEXTURE_HEIGHT, &height);
			if (0 == texture2DProperties->GetHeight()) {
				*texture2DProperties = Texture2DProperties();
				PopAttributes();
				return;
			}
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0,
				GL_TEXTURE_INTERNAL_FORMAT, &format);
			if (format == GL_RGBA)
				texture2DProperties->SetBitsPerPixel(32);
			else if (format == GL_RGB)
				texture2DProperties->SetBitsPerPixel(24);
			else {
				*texture2DProperties = Texture2DProperties();
				PopAttributes();
				return;
			}
		PopAttributes();
	}

	Int GraphicsContextInterface::GetError() {
		return glGetError();
	}

	CHDC GraphicsContextInterface::GetHDC() {
		return mHdc;
	}

	const CHDC GraphicsContextInterface::GetHDC() const {
		return mHdc;
	}

	CHGLRC GraphicsContextInterface::GetHGLRC() {
		return mHglrc;
	}

	const CHGLRC GraphicsContextInterface::GetHGLRC() const {
		return mHglrc;
	}

	CGLXContext GraphicsContextInterface::GetGLXContext() {
		return mGLXContext;
	}

	const CGLXContext GraphicsContextInterface::GetGLXContext() const {
		return mGLXContext;
	}

	CGLXWindow GraphicsContextInterface::GetGLXWindow() {
		return mGLXWindow;
	}

	const CGLXWindow GraphicsContextInterface::GetGLXWindow() const {
		return mGLXWindow;
	}

	CNSOpenGLContext* GraphicsContextInterface::GetNSOpenGLContext() {
		return mNSOpenGLContext;
	}

	const CNSOpenGLContext* GraphicsContextInterface::GetNSOpenGLContext() const
	{
		return mNSOpenGLContext;
	}
	/*
	void GraphicsContextInterface::DrawTexturedSquare() {
		glBegin(GL_QUADS);
			glColor3f(1.f, 1.f, 1.f);
			glTexCoord2f(0.0f,  1.0f);
			glVertex2f(	-1.0f,  1.0f);
			glTexCoord2f(1.0f,  1.0f);
			glVertex2f(  1.0f,  1.0f);
			glTexCoord2f(1.0f,  0.0f);
			glVertex2f(  1.0f, -1.0f);
			glTexCoord2f(0.0f,  0.0f);
			glVertex2f(	-1.0f, -1.0f);
		glEnd();
	}*/
}
