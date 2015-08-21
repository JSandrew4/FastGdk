/******************************************************************************/
/*                                                                            */
/*  GraphicsContextState.cpp                                                  */
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

#include <Fast/GraphicsContextState.hpp>
#include <Fast/GraphicsContextInterface.hpp>

namespace Fast
{
	GraphicsContextState::GraphicsContextState(GraphicsContextInterface *gci) {
		mInterface = gci;
		mCapabilitiesEnabled.SetElementCount(32);
		mActiveTextureUnit = 0;
		mBoundOpenGLTexture2DIDArray.SetElementCount(
			gci->GetCapabilities().GetMaxTextureUnitsCount());
		mBoundOpenGLFramebufferID = 0;
		mBoundOpenGLRenderbufferID = 0;
		mBoundOpenGLVertexArrayID = 0;
		mOpenGLShaderProgramIDInUse = 0;
		mPointSize = 1.0f;
		mLineWidth = 1.0f;
		mCullFace = kPolygonFaceBack;
		mPolygonWindingDirection = kPolygonWindingClockwise;
		mFrontFacePolygonMode = kPolygonFill;
		mBackFacePolygonMode = kPolygonFill;
		// TODO: Blend defaults
		mBlendColor = Color::Black;
		mViewportRectangle = Rectangle(0, 0, 100, 100);
		mScissorRectangle = Rectangle(0, 0, 100, 100);
		mPolygonOffsetFactor = 0.0f;
		mPolygonOffsetUnits = 0.0f;
	}

	void GraphicsContextState::Apply() {
		GraphicsContextInterface *gci = mInterface;
		for (Int i = 1; i < 32; i++) {
			if (mCapabilitiesEnabled[i])
				gci->Enable((GraphicsCapability)i);
			else
				gci->Disable((GraphicsCapability)i);
		}
		mBoundOpenGLTexture2DIDArray.SetElementCount(
			gci->GetCapabilities().GetMaxTextureUnitsCount());
		for (Int i = 0; i < mBoundOpenGLTexture2DIDArray.GetElementCount(); i++)
			gci->BindTexture2D(mBoundOpenGLTexture2DIDArray[i], i);
		gci->SetActiveTextureUnit(mActiveTextureUnit);
		gci->BindFramebuffer(mBoundOpenGLFramebufferID);
		gci->BindRenderbuffer(mBoundOpenGLRenderbufferID);
		gci->SetPointSize(mPointSize);
		gci->SetLineWidth(mLineWidth);
		gci->SetCullFace(mCullFace);
		gci->SetPolygonWindingDirection(mPolygonWindingDirection);
		gci->SetPolygonMode(kPolygonFaceFront, mFrontFacePolygonMode);
		gci->SetPolygonMode(kPolygonFaceBack, mBackFacePolygonMode);
		// TODO: Blending
		gci->SetBlendColor(mBlendColor);
		gci->SetViewportRectangle(mViewportRectangle);
		gci->SetScissorRectangle(mScissorRectangle);
		gci->SetPolygonOffset(mPolygonOffsetFactor, mPolygonOffsetUnits);
		gci->SetModelViewProjectionMatrix(mModelViewProjectionMatrix);
	}
}