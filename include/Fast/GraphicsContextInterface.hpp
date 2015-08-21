/******************************************************************************/
/*                                                                            */
/*  GraphicsContextInterface.hpp                                              */
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

#ifndef FastGraphicsContextInterfaceHppIncluded
#define FastGraphicsContextInterfaceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/OpenGLFramebufferState.hpp>
#include <Fast/GraphicsContextState.hpp>
#include <Fast/GraphicsCapability.hpp>
#include <Fast/GraphicsCapabilities.hpp>
#include <Fast/GraphicsBufferType.hpp>
#include <Fast/RenderPrimitive.hpp>
#include <Fast/PolygonFace.hpp>
#include <Fast/PolygonWindingDirection.hpp>
#include <Fast/PolygonMode.hpp>

namespace Fast
{
	class ImageData;
	class GraphicsCapabilities;
	class Window;
	class AlphaTexture2DData;
	class RenderItem;
	class Texture2DData;
	class Texture2DProperties;
	class MeshResource;
	class MeshData;

	class FastApi GraphicsContextInterface
	{
	private:
		Bool							mIsCreated;
		Array<OpenGLFramebufferState>	mOpenGLFramebufferStates;
		Array<GraphicsContextState>		mStack;
		Int								mStackIndex;
		Window							&mWindow;
		GraphicsCapabilities			mCapabilities;
		Int								mDepthBits;
		Int								mStencilBits;
		CHDC							mHdc;
		CHGLRC							mHglrc;
		CGLXContext						mGLXContext;
		CGLXWindow						mGLXWindow;
		CNSOpenGLContext				*mNSOpenGLContext;
		// Hide these functions. No copying contexts!
		GraphicsContextInterface(const GraphicsContextInterface &that);
		GraphicsContextInterface& operator=(
			const GraphicsContextInterface &that) { return *this; }
	public:
		// (Con/De)structors
		GraphicsContextInterface(Window &window);
		~GraphicsContextInterface();
		// Misc
		void	CreateContext();
		void	DeleteContext();
		void	MakeCurrent(Bool shouldMakeCurrent);
		void	Enable(GraphicsCapability capability);
		void	Disable(GraphicsCapability capability);
		void	Clear(GraphicsBufferType buffer);
		void	FlipBuffers();
		void	PushAttributes();
		void	PopAttributes();
		void	SetActiveTextureUnit(Int textureUnit);
		void	BindTexture2D(UInt openGLTextureID);
		void	BindTexture2D(UInt openGLTextureID, Int textureUnit);
		void	BindFramebuffer(UInt openGLFramebufferID);
		void	BindRenderbuffer(UInt openGLRenderbufferID);
		void	BindVertexArray(UInt openGLVertexArrayID);
		void	UseShaderProgram(UInt openGLShaderProgramID);
		void	Draw(const RenderItem &item);
		void	SetPointSize(Float size);
		void	SetLineWidth(Float width);
		void	SetCullFace(PolygonFace cullFace);
		void	SetPolygonWindingDirection(
					PolygonWindingDirection polygonWindingDirection);
		void	SetPolygonMode(PolygonFace face, PolygonMode mode);
		void	SetBlendColor(const Color &color);
		void	SetViewportRectangle(const Rectangle &rect);
		void	SetScissorRectangle(const Rectangle &rect);
		void	SetPolygonOffset(Float factor, Float units);
		UInt	GenerateNewOpenGLTexture2DID();
		UInt	GenerateNewOpenGLRenderbufferID();
		UInt	GenerateNewOpenGLFramebufferID();
		UInt	GenerateNewOpenGLBufferID();
		void	CreateOpenGLMesh(MeshResource *resource,
					const MeshData &data, Int usage);
		void	DeleteOpenGLTexture2DID(UInt openGLTexture2DID);
		void	DeleteOpenGLRenderbufferID(UInt openGLRenderbufferID);
		void	DeleteOpenGLFramebufferID(UInt openGLFramebufferID);
		void	DeleteOpenGLBufferID(UInt openGLBufferID);
		void	DeleteOpenGLMesh(MeshResource *resource);
		void	StoreTexture2DData(UInt openGLTexture2DID,
					const Texture2DData &texture2DData);
		void	StoreAlphaTexture2DData(UInt openGLAlphaTexture2DID,
					const AlphaTexture2DData &alphaTexture2D,
					Int offsetX, Int offsetY);
		void	GenerateNewRenderSurfaceIDs(Int width, Int height,
					UInt *openGLTexture2DID, UInt *openGLFramebufferID,
					UInt *openGLRenderbufferID);
		void	DeleteRenderSurfaceIDs(UInt openGLFramebufferID,
					UInt openGLRenderbufferID);
		void	SetFramebufferTexture2D(UInt openGLFramebufferID,
					UInt openGLTexture2DID);
		void	SetModelViewProjectionMatrix(const Matrix &matrix);
		// Getters
		Bool						IsCreated() const;
		Int							GetDepthBits() const;
		Int							GetStencilBits() const;
		const GraphicsCapabilities&	GetCapabilities() const;
		void						RetrieveTexture2DData(
										UInt openGLTexture2DID,
										Texture2DData *imageData);
		void						RetrieveTexture2DProperties(
										UInt openGLTexture2DID,
										Texture2DProperties
											*texture2DProperties);
		Int							GetError();
		// Win32
		CHDC			GetHDC();
		const CHDC		GetHDC() const;
		CHGLRC			GetHGLRC();
		const CHGLRC	GetHGLRC() const;
		// X11
		CGLXContext			GetGLXContext();
		const CGLXContext	GetGLXContext() const;
		CGLXWindow			GetGLXWindow();
		const CGLXWindow	GetGLXWindow() const;
		// Cocoa
		CNSOpenGLContext*		GetNSOpenGLContext();
		const CNSOpenGLContext*	GetNSOpenGLContext() const;
	};
}

#endif // FastGraphicsContextInterfaceHppIncluded