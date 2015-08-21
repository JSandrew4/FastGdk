/******************************************************************************/
/*                                                                            */
/*  GraphicsJob.hpp                                                           */
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

#ifndef FastGraphicsJobHppIncluded
#define FastGraphicsJobHppIncluded

#include <Fast/Types.hpp>
#include <Fast/GraphicsJobType.hpp>
#include <Fast/GraphicsBufferType.hpp>
#include <Fast/GraphicsCapability.hpp>
#include <Fast/Texture2DSurface.hpp>
#include <Fast/RenderSurface.hpp>
#include <Fast/PolygonFace.hpp>
#include <Fast/PolygonWindingDirection.hpp>
#include <Fast/PolygonMode.hpp>
#include <Fast/Color.hpp>
#include <Fast/Rectangle.hpp>
#include <Fast/Matrix.hpp>

namespace Fast
{
	class Window;
	class ImageData;
	class ImageProperties;

	class FastApi GraphicsJob
	{
	public:
		GraphicsJobType			mType;
		Window					&mWindow;
		GraphicsBufferType		mBufferType;
		Int						mStencilBits;
		Int						mDepthBits;
		GraphicsCapability		mCapability;
		UInt					mOpenGLTexture2DID;
		UInt					mOpenGLFramebufferID;
		Int						mWidth;
		Int						mHeight;
		Int						mPointSize;
		Int						mLineWidth;
		PolygonFace				mCullFace;
		PolygonWindingDirection	mPolygonWindingDirection;
		PolygonMode				mPolygonMode;
		PolygonFace				mPolygonFace;
		Color					mBlendColor;
		Rectangle				mViewportRect;
		Rectangle				mScissorRect;
		Float					mPolygonOffsetFactor;
		Float					mPolygonOffsetUnits;
		Matrix					mMatrix;
		UInt					*mOpenGLTexture2DIDPtr;
		UInt					*mOpenGLFramebufferIDPtr;
		UInt					*mOpenGLRenderbufferIDPtr;
		ImageData				*mImageDataPtr;
		const ImageData			*mConstImageDataPtr;
		Int						*mGLErrorPtr;
		ImageProperties			*mImagePropertiesPtr;
	};

	template class FastApi Array<GraphicsJob>;
}

#endif // FastGraphicsJobHppIncluded