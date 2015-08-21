/******************************************************************************/
/*                                                                            */
/*  FrameBufferSurface.cpp                                                    */
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

#include <Fast/FrameBufferSurface.hpp>
#include <Fast/Texture2DSurface.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/Error.hpp>

namespace Fast
{
	FrameBufferSurface::FrameBufferSurface()
	:	AssetImplementer<FrameBufferCollection, FrameBufferResource>()
	{
		Unbind();
	}

	FrameBufferSurface::FrameBufferSurface(Int width, Int height,
		Int bitsPerPixel, FrameBufferCollection *collection)
	:	AssetImplementer<FrameBufferCollection, FrameBufferResource>()
	{
		Create(width, height, bitsPerPixel, collection);
	}

	FrameBufferSurface::FrameBufferSurface(const FrameBufferSurface &that)
	:	AssetImplementer<FrameBufferCollection, FrameBufferResource>()
	{
		*this = that;
	}

	FrameBufferSurface::~FrameBufferSurface() {
		Unbind();
	}

	ErrorType FrameBufferSurface::Create(Int width, Int height,
		Int bitsPerPixel, FrameBufferCollection *collection)
	{
		Unbind();
		GraphicsContext *gc =
			collection->GetTexture2DCollection()->GetGraphicsContext();
		FrameBufferResource fbr(collection->GetTexture2DCollection());
		UInt newOpenGLTextureID = 0;
		gc->GenerateNewRenderSurfaceIDs(width, height, &newOpenGLTextureID,
			&fbr.mOpenGLFramebufferID, &fbr.mOpenGLRenderbufferID);
		if (0 == newOpenGLTextureID || 0 == fbr.mOpenGLFramebufferID ||
			0 == fbr.mOpenGLRenderbufferID)
		{
			return Error::Throw(gc->GetError(),
				String("[%s(%d, %d, %d, %p)]", FastFunctionName, width,
					height, bitsPerPixel, (void*)collection));
		}
		fbr.mTexture2DSurface.Load(newOpenGLTextureID,
			collection->GetTexture2DCollection());
		mID = collection->AddResource(fbr, this);
		mCollection = collection;
		return kErrorNone;
	}

	void FrameBufferSurface::Unbind() {
		Bind(NULL, -1);
	}

	void FrameBufferSurface::Resize(Int width, Int height) {
		// TODO: Delete and recreate?
	}

	FrameBufferCollection* FrameBufferSurface::GetCollection() {
		return mCollection;
	}

	const FrameBufferCollection& FrameBufferSurface::GetCollection() const {
		return *mCollection;
	}

	UInt FrameBufferSurface::GetOpenGLFramebufferID() const {
		return GetCollection().GetResource(mID).mOpenGLFramebufferID;
	}

	UInt FrameBufferSurface::GetOpenGLRenderbufferID() const {
		return GetCollection().GetResource(mID).mOpenGLRenderbufferID;
	}

	Texture2DSurface* FrameBufferSurface::GetTexture2D() {
		return &GetCollection()->GetResource(mID)->mTexture2DSurface;
	}

	const Texture2DSurface& FrameBufferSurface::GetTexture2D() const {
		return GetCollection().GetResource(mID).mTexture2DSurface;
	}

	Int FrameBufferSurface::GetWidth() const {
		return GetCollection().GetResource(mID).mTexture2DSurface.GetResource(
			).GetProperties().GetWidth();
	}

	Int FrameBufferSurface::GetHeight() const {
		return GetCollection().GetResource(mID).mTexture2DSurface.GetResource(
			).GetProperties().GetHeight();
	}

	Int FrameBufferSurface::GetBitsPerPixel() const {
		return GetCollection().GetResource(mID).mTexture2DSurface.GetResource(
			).GetProperties().GetBitsPerPixel();
	}

	FrameBufferSurface& FrameBufferSurface::operator=(const FrameBufferSurface &that) {
		this->Bind(that.mCollection, that.mID);
		return *this;
	}

	Bool FrameBufferSurface::operator==(const FrameBufferSurface &that) const {
		if (this->mCollection != that.mCollection)
			return false;
		if (this->mID != that.mID)
			return false;
		return true;
	}

	Bool FrameBufferSurface::operator!=(const FrameBufferSurface &that) const {
		if (this->mCollection != that.mCollection)
			return true;
		if (this->mID != that.mID)
			return true;
		return false;
	}
}