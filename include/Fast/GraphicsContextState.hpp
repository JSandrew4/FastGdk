/******************************************************************************/
/*                                                                            */
/*  GraphicsContextState.hpp                                                  */
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

#ifndef FastGraphicsContextStateHppIncluded
#define FastGraphicsContextStateHppIncluded

#include <Fast/Types.hpp>
#include <Fast/GraphicsCapability.hpp>
#include <Fast/PolygonFace.hpp>
#include <Fast/PolygonWindingDirection.hpp>
#include <Fast/PolygonMode.hpp>
#include <Fast/BlendFunction.hpp>
#include <Fast/BlendEquation.hpp>
#include <Fast/Color.hpp>
#include <Fast/Rectangle.hpp>
#include <Fast/Vertex.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class GraphicsContextInterface;

	class FastApi GraphicsContextState
	{
	public:
		GraphicsContextInterface	*mInterface;
		Array<Bool>					mCapabilitiesEnabled;
		Array<UInt>					mBoundOpenGLTexture2DIDArray;
		Int							mActiveTextureUnit;
		UInt						mBoundOpenGLFramebufferID;
		UInt						mBoundOpenGLRenderbufferID;
		UInt						mBoundOpenGLVertexArrayID;
		UInt						mOpenGLShaderProgramIDInUse;
		Float						mPointSize;
		Float						mLineWidth;
		PolygonFace					mCullFace;
		PolygonWindingDirection		mPolygonWindingDirection;
		PolygonMode					mFrontFacePolygonMode;
		PolygonMode					mBackFacePolygonMode;
        BlendFunction				mSourceBlendFunction;
        BlendFunction				mDestinationBlendFunction;
        BlendEquation				mBlendEquation;
    	Color						mBlendColor;
    	Rectangle					mViewportRectangle;
    	Rectangle					mScissorRectangle;
    	Float						mPolygonOffsetFactor;
    	Float						mPolygonOffsetUnits;
		Matrix						mModelViewProjectionMatrix;
		GraphicsContextState(GraphicsContextInterface *gci);
		void	Apply();
	};

	template class FastApi Array<GraphicsContextState>;
}

#endif // FastGraphicsContextStateHppIncluded