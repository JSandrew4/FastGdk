/******************************************************************************/
/*                                                                            */
/*  GraphicsContext.cpp                                                       */
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
#include <Fast/Thread.hpp>
#include <Fast/GraphicsCapabilities.hpp>
#include <Fast/SystemConsole.hpp>
#include <Fast/Thread.hpp>
#include <Fast/GraphicsThreadArgs.hpp>
#include <Fast/AlphaTexture2DData.hpp>

#if defined(FastOSWindows)
#	include <WindowsX.h>
#elif defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/Xatom.h>
#	include <X11/Xutil.h>
#	include <X11/cursorfont.h>
#	include <X11/extensions/XInput2.h>
#	include <unistd.h>
#endif

#include <stdio.h>

#include "OpenGL.hpp"
#include "NSInterface.hpp"
#include "X11Interface.hpp"
#include "W32Interface.hpp"

#include "Undefs.hpp"

namespace Fast
{
	using namespace OpenGL;

	void GraphicsContext::IssueCommandStart() {
		mCommandIssueMutex.Lock();
		mCommandIssueFinishMutex.Lock();
		mIsCommandWaiting = true;
		printf("GC::IsCommandWaiting(true)\n");
	}

	void GraphicsContext::IssueCommandEnd() {
		mCommandIssueFinishMutex.Unlock();
		mCommandIssueFinishConditional.Wait(&mCommandIssueFinishMutex);
		mCommandIssueMutex.Unlock();
	}

	GraphicsContext::GraphicsContext(Window *window,
		const Rectangle &targetContentRectangle, Int multisampleCount) :
		mWindow(*window),
		mInterface(*window),
		mMultisampleCount(multisampleCount),
		mShouldRender(false),
		mIsCommandWaiting(false),
		mIsCommandReady(false),
		mCommandIssueMutex("CommandIssueMutex"),
		mCommandIssueFinishMutex("CommandIssueFinishMutex"),
		mCommandIssueFinishConditional("CommandIssueFinishConditional"),
		mRenderMutex("RenderMutex"),
		mGLError(kErrorNone),
		mThread(GraphicsThreadArgs(this, &mWindow, &mMultisampleCount,
			&mInterface, &mShouldRender, &mIsCommandWaiting, &mIsCommandReady,
			&mDepthChangeIndices, &mRenderItems, &mRenderMutex,
			&mCommandIssueMutex, &mCommandIssueFinishMutex,
			&mCommandIssueFinishConditional, &mGraphicsIOCommand, &mGLError)),
		mDefaultTexture2DCollection(this),
		mDefaultFrameBufferCollection(&mDefaultTexture2DCollection),
		mMainFrameBufferSurface(targetContentRectangle.mWidth,
			targetContentRectangle.mHeight, 32,
			&mDefaultFrameBufferCollection),
		mDefaultFontCollection(&mDefaultTexture2DCollection)
	{ }

	GraphicsContext::~GraphicsContext() { }

	void GraphicsContext::StartRender() {
		mRenderMutex.Lock();
	}

	void GraphicsContext::FinishRender() {
		mShouldRender = true;
		mRenderMutex.Unlock();
	}

	void GraphicsContext::QueueRenderItem(const RenderItem &renderItem) {
		// NOTE: When queuing a RenderItem, we need to make sure to keep track
		//	of any changes made to the depth buffer as this means, more than
		//	likely, that the ordering of those draw calls was purposeful.
		if (mRenderItems.GetElementCount() > 0) {
			if (mRenderItems[mRenderItems.GetElementCount()-1
				].mRenderPreferences.IsCapabilityEnabled(
				kGraphicsCapabilityDepth) !=
				renderItem.mRenderPreferences.IsCapabilityEnabled(
				kGraphicsCapabilityDepth))
			{
				mDepthChangeIndices.Append(mRenderItems.GetElementCount());
			}
		}
		mRenderItems.Append(renderItem);
	}

	const GraphicsCapabilities& GraphicsContext::GetCapabilities() const {
		return mInterface.GetCapabilities();
	}

	const Window& GraphicsContext::GetWindow() const {
		return mWindow;
	}

	Window* GraphicsContext::GetWindow() {
		return &mWindow;
	}

	Int GraphicsContext::GetMultisampleCount() const {
		return mMultisampleCount;
	}

	Int GraphicsContext::GetDepthBits() const {
		return mInterface.GetDepthBits();
	}

	Int GraphicsContext::GetStencilBits() const {
		return mInterface.GetStencilBits();
	}

	Texture2DCollection* GraphicsContext::GetDefaultTexture2DCollection() {
		return &mDefaultTexture2DCollection;
	}

	const Texture2DCollection& GraphicsContext::GetDefaultTexture2DCollection()
		const
	{
		return mDefaultTexture2DCollection;
	}

	FrameBufferCollection* GraphicsContext::GetDefaultFrameBufferCollection() {
		return &mDefaultFrameBufferCollection;
	}

	const FrameBufferCollection&
		GraphicsContext::GetDefaultFrameBufferCollection() const
	{
		return mDefaultFrameBufferCollection;
	}

	FrameBufferSurface* GraphicsContext::GetMainFrameBufferSurface() {
		return &mMainFrameBufferSurface;
	}

	const FrameBufferSurface& GraphicsContext::GetMainFrameBufferSurface()
		const
	{
		return mMainFrameBufferSurface;
	}

	FontCollection* GraphicsContext::GetDefaultFontCollection() {
		return &mDefaultFontCollection;
	}

	const FontCollection& GraphicsContext::GetDefaultFontCollection() const {
		return mDefaultFontCollection;
	}

	UInt GraphicsContext::GenerateNewOpenGLTexture2DID() {
		UInt newOpenGLTexture2DID = 0;
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIOGenerateNewOpenGLTexture2DID;
		mGraphicsIOCommand.mOpenGLTexture2DIDPtr = &newOpenGLTexture2DID;
		IssueCommandEnd();
		return newOpenGLTexture2DID;
	}

	void GraphicsContext::DeleteOpenGLTexture2DID(UInt openGLTexture2DID) {
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIODeleteOpenGLTexture2DID;
		mGraphicsIOCommand.mOpenGLTexture2DID = openGLTexture2DID;
		IssueCommandEnd();
	}

	void GraphicsContext::StoreTexture2DData(
		UInt openGLTexture2DID, const Texture2DData &texture2DData)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIOStoreTexture2DData;
		mGraphicsIOCommand.mOpenGLTexture2DID = openGLTexture2DID;
		mGraphicsIOCommand.mConstTexture2DDataPtr = &texture2DData;
		IssueCommandEnd();
	}

	void GraphicsContext::StoreAlphaTexture2DData(UInt openGLAlphaTexture2DID,
		const AlphaTexture2DData &alphaTexture2D, Int offsetX, Int offsetY)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIOStoreAlphaTexture2D;
		mGraphicsIOCommand.mOpenGLTexture2DID = openGLAlphaTexture2DID;
		mGraphicsIOCommand.mConstAlphaTexture2DDataPtr = &alphaTexture2D;
		mGraphicsIOCommand.mOffsetX = offsetX;
		mGraphicsIOCommand.mOffsetY = offsetY;
		IssueCommandEnd();
	}

	void GraphicsContext::GenerateNewRenderSurfaceIDs(Int width, Int height,
		UInt *openGLTexture2DID, UInt *openGLFramebufferID,
		UInt *openGLRenderbufferID)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIOGenerateNewRenderSurfaceIDs;
		mGraphicsIOCommand.mWidth = width;
		mGraphicsIOCommand.mHeight = height;
		mGraphicsIOCommand.mOpenGLTexture2DIDPtr = openGLTexture2DID;
		mGraphicsIOCommand.mOpenGLFramebufferIDPtr = openGLFramebufferID;
		mGraphicsIOCommand.mOpenGLRenderbufferIDPtr = openGLRenderbufferID;
		IssueCommandEnd();
	}

	void GraphicsContext::DeleteRenderSurfaceIDs(
		UInt openGLFramebufferID, UInt openGLRenderbufferID)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIODeleteRenderSurfaceIDs;
		mGraphicsIOCommand.mOpenGLFramebufferIDPtr = &openGLFramebufferID;
		mGraphicsIOCommand.mOpenGLRenderbufferIDPtr = &openGLRenderbufferID;
		IssueCommandEnd();
	}

	void GraphicsContext::CreateOpenGLMesh(
		MeshResource *resource, const MeshData &data, Int usage)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIOCreateOpenGLMesh;
		mGraphicsIOCommand.mMeshResourcePtr = resource;
		mGraphicsIOCommand.mConstMeshDataPtr = &data;
		mGraphicsIOCommand.mMeshUsage = usage;
		IssueCommandEnd();
	}

	void GraphicsContext::DeleteOpenGLMesh(MeshResource *resource) {
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIODeleteOpenGLMesh;
		mGraphicsIOCommand.mMeshResourcePtr = resource;
		IssueCommandEnd();
	}

	void GraphicsContext::RetrieveTexture2DData(
		UInt openGLTexture2DID, Texture2DData *texture2DData)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIORetrieveTexture2DData;
		mGraphicsIOCommand.mOpenGLTexture2DID = openGLTexture2DID;
		mGraphicsIOCommand.mTexture2DDataPtr = texture2DData;
		IssueCommandEnd();
	}

	void GraphicsContext::RetrieveTexture2DProperties(UInt openGLTexture2DID,
		Texture2DProperties *texture2DProperties)
	{
		IssueCommandStart();
		mGraphicsIOCommand.mType = kGraphicsIORetrieveTexture2DProperties;
		mGraphicsIOCommand.mOpenGLTexture2DID = openGLTexture2DID;
		mGraphicsIOCommand.mTexture2DPropertiesPtr = texture2DProperties;
		IssueCommandEnd();
	}

	ErrorType GraphicsContext::GetError() {
		ErrorType errorReturn = mGLError;
		mGLError = kErrorNone;
		return errorReturn;
	}

	CHDC GraphicsContext::GetHDC() {
		return mInterface.GetHDC();
	}

	const CHDC GraphicsContext::GetHDC() const {
		return mInterface.GetHDC();
	}

	CHGLRC GraphicsContext::GetHGLRC() {
		return mInterface.GetHGLRC();
	}

	const CHGLRC GraphicsContext::GetHGLRC() const {
		return mInterface.GetHGLRC();
	}

	CGLXContext GraphicsContext::GetGLXContext() {
		return mInterface.GetGLXContext();
	}

	const CGLXContext GraphicsContext::GetGLXContext() const {
		return mInterface.GetGLXContext();
	}

	CGLXWindow GraphicsContext::GetGLXWindow() {
		return mInterface.GetGLXWindow();
	}

	const CGLXWindow GraphicsContext::GetGLXWindow() const {
		return mInterface.GetGLXWindow();
	}

	CNSOpenGLContext* GraphicsContext::GetNSOpenGLContext() {
		return mInterface.GetNSOpenGLContext();
	}

	const CNSOpenGLContext* GraphicsContext::GetNSOpenGLContext() const {
		return mInterface.GetNSOpenGLContext();
	}
}
