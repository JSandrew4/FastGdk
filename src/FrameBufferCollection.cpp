/******************************************************************************/
/*                                                                            */
/*  FrameBufferCollection.cpp                                                 */
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

#include <Fast/FrameBufferCollection.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/FrameBufferSurface.hpp>

#include "Undefs.hpp"

namespace Fast
{/* TODO: Remove
	void FrameBufferCollection::BuildDefaultResource() {
		mResources.SetElementCount(1,
			FrameBufferResource(GetTexture2DCollection()));
		FrameBufferSurface fbs(8, 8, 24, this);
		FrameBufferResource fbr(GetTexture2DCollection());
		SetResourceRetained(AddResource(fbr, &fbs), true);
	}
	*/
	FrameBufferCollection::FrameBufferCollection(
		Texture2DCollection *texture2DCollection) :
		mTexture2DCollection(*texture2DCollection)
	{ }
	
	FrameBufferCollection::~FrameBufferCollection() {
		UnloadAllResources();
	}

	void FrameBufferCollection::UnloadResource(Int id) {
		UnloadReferences(id);
		mTexture2DCollection.GetGraphicsContext()->DeleteRenderSurfaceIDs(
			mResources[id].mOpenGLFramebufferID,
			mResources[id].mOpenGLRenderbufferID);
		mResources[id].mTexture2DSurface.Unbind();
		mResources[id].SetActive(false);
	}

	Texture2DCollection* FrameBufferCollection::GetTexture2DCollection() {
		return &mTexture2DCollection;
	}

	const Texture2DCollection& FrameBufferCollection::GetTexture2DCollection()
		const
	{
		return mTexture2DCollection;
	}
}