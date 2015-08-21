/******************************************************************************/
/*                                                                            */
/*  GraphicsContext.hpp                                                       */
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

#ifndef FastGraphicsContextHppIncluded
#define FastGraphicsContextHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/Mutex.hpp>
#include <Fast/Conditional.hpp>
#include <Fast/GraphicsIOCommand.hpp>
#include <Fast/RenderPrimitive.hpp>
#include <Fast/PolygonFace.hpp>
#include <Fast/PolygonWindingDirection.hpp>
#include <Fast/PolygonMode.hpp>
#include <Fast/GraphicsContextInterface.hpp>
#include <Fast/GraphicsCapability.hpp>
#include <Fast/GraphicsThread.hpp>
#include <Fast/GraphicsBufferType.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/RenderItem.hpp>
#include <Fast/Texture2DCollection.hpp>
#include <Fast/FrameBufferCollection.hpp>
#include <Fast/FontCollection.hpp>

namespace Fast
{
	class Window;
	class Texture2DSurface;
	class Color;
	class Rectangle;
	class Texture2DData;
	class Texture2DProperties;
	class GraphicsCapabilities;
	class AlphaTexture2DData;
	class MeshResource;
	class MeshData;

	class FastApi GraphicsContext
	{
	private:
		Window						&mWindow;
		GraphicsContextInterface	mInterface;
		Int							mMultisampleCount;
		Bool						mShouldRender;
		Bool						mIsCommandWaiting;
		Bool						mIsCommandReady;
		Mutex						mCommandIssueMutex;
		Mutex						mCommandIssueFinishMutex;
		Conditional					mCommandIssueFinishConditional;
		Mutex						mRenderMutex;
		GraphicsIOCommand			mGraphicsIOCommand;
		ErrorType					mGLError;
		Array<Int>					mDepthChangeIndices;
		Array<RenderItem>			mRenderItems;
		GraphicsThread				mThread;
		Texture2DCollection			mDefaultTexture2DCollection;
		FrameBufferCollection		mDefaultFrameBufferCollection;
		FrameBufferSurface			mMainFrameBufferSurface;
		FontCollection				mDefaultFontCollection;
		// Private funcs
		void	IssueCommandStart();
		void	IssueCommandEnd();
		// Hide these functions. No copying contexts!
		GraphicsContext(const GraphicsContext &that) :
			mWindow(that.mWindow),
			mInterface(that.mWindow),
			mCommandIssueMutex("CommandIssueMutex"),
			mCommandIssueFinishMutex("CommandIssueFinishMutex"),
			mCommandIssueFinishConditional("CommandIssueFinishConditional"),
			mRenderMutex("RenderMutex"),
			mThread(GraphicsThreadArgs(NULL, NULL, NULL, NULL, NULL, NULL,
				NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)),
			mDefaultTexture2DCollection(this),
			mDefaultFrameBufferCollection(&mDefaultTexture2DCollection),
			mMainFrameBufferSurface(),
			mDefaultFontCollection(&mDefaultTexture2DCollection)
			{ }
		GraphicsContext& operator=(const GraphicsContext &that)
			{ return *this; }
	public:
		// (Con/De)structors
		GraphicsContext(Window *window,
			const Rectangle &targetContentRectangle, Int multisampleCount);
		~GraphicsContext();
		// Misc functions
		void	StartRender();
		void	FinishRender();
		void	QueueRenderItem(const RenderItem &renderItem);
		// Getters
		const GraphicsCapabilities&		GetCapabilities() const;
		Window*							GetWindow();
		const Window&					GetWindow() const;
		Int								GetDepthBits() const;
		Int								GetStencilBits() const;
		Int								GetMultisampleCount() const;
		Texture2DCollection*			GetDefaultTexture2DCollection();
		const Texture2DCollection&		GetDefaultTexture2DCollection() const;
		FrameBufferCollection*			GetDefaultFrameBufferCollection();
		const FrameBufferCollection&	GetDefaultFrameBufferCollection()
											const;
		FrameBufferSurface*				GetMainFrameBufferSurface();
		const FrameBufferSurface&		GetMainFrameBufferSurface() const;
		FontCollection*					GetDefaultFontCollection();
		const FontCollection&			GetDefaultFontCollection() const;
		// GraphicsContextState setters/modifiers
		UInt	GenerateNewOpenGLTexture2DID();
		void	DeleteOpenGLTexture2DID(UInt openGLTexture2DID);
		void	StoreTexture2DData(UInt openGLTexture2DID,
					const Texture2DData &texture2DData);
		void	GenerateNewRenderSurfaceIDs(Int width, Int height,
					UInt *openGLTexture2DID, UInt *openGLFramebufferID,
					UInt *openGLRenderbufferID);
		void	DeleteRenderSurfaceIDs(UInt openGLFramebufferID,
					UInt openGLRenderbufferID);
		void	CreateOpenGLMesh(MeshResource *resource,
					const MeshData &data, Int usage);
		void	DeleteOpenGLMesh(MeshResource *resource);
		void	StoreAlphaTexture2DData(UInt openGLAlphaTexture2DID,
					const AlphaTexture2DData &alphaTexture2D,
					Int offsetX, Int offsetY);
		// GraphicsContextState getters
		void		RetrieveTexture2DData(UInt openGLTexture2DID,
						Texture2DData *texture2DData);
		void		RetrieveTexture2DProperties(UInt openGLTexture2DID,
						Texture2DProperties *texture2DProperties);
		ErrorType	GetError();
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

#endif // FastGraphicsContextHppIncluded
