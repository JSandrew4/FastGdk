/******************************************************************************/
/*                                                                            */
/*  GraphicsThread.cpp                                                        */
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

#include <Fast/GraphicsThread.hpp>
#include <Fast/GraphicsContextInterface.hpp>
#include <Fast/GraphicsIOCommand.hpp>
#include <Fast/GraphicsIOType.hpp>
#include <Fast/Conditional.hpp>
#include <Fast/Mutex.hpp>
#include <Fast/Model.hpp>

#include <stdio.h>

#include "OpenGL.hpp"

#include "Undefs.hpp"

namespace Fast
{
	ErrorType GraphicsGLErrorToFastErrorType(Int glError) {
		switch (glError)
		{
		case GL_NO_ERROR:
			return kErrorNone;
		case GL_INVALID_ENUM:
			return kErrorOpenGLInvalidEnum;
		case GL_INVALID_VALUE:
			return kErrorOpenGLInvalidValue;
		case GL_INVALID_OPERATION:
			return kErrorOpenGLInvalidOperation;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return kErrorOpenGLInvalidFramebufferOperation;
		case GL_OUT_OF_MEMORY:
			return kErrorOpenGLOutOfMemory;
		}
		return kErrorGeneric;
	}

	void GraphicsHandleIOCommand(GraphicsThreadArgs &gta) {
		if (*gta.mIsCommandWaiting) {
			gta.mCommandIssueFinishMutex->Lock();
			switch (gta.mGraphicsIOCommand->mType)
			{
			case kGraphicsIOGenerateNewOpenGLTexture2DID:
				*gta.mGraphicsIOCommand->mOpenGLTexture2DIDPtr =
					gta.mInterface->GenerateNewOpenGLTexture2DID();
				break;
			case kGraphicsIODeleteOpenGLTexture2DID:
				gta.mInterface->DeleteOpenGLTexture2DID(
					gta.mGraphicsIOCommand->mOpenGLTexture2DID);
				break;
			case kGraphicsIOStoreTexture2DData:
				gta.mInterface->StoreTexture2DData(
					gta.mGraphicsIOCommand->mOpenGLTexture2DID,
					*gta.mGraphicsIOCommand->mConstTexture2DDataPtr);
				break;
			case kGraphicsIOStoreAlphaTexture2D:
				gta.mInterface->StoreAlphaTexture2DData(
					gta.mGraphicsIOCommand->mOpenGLTexture2DID,
					*gta.mGraphicsIOCommand->mConstAlphaTexture2DDataPtr,
					gta.mGraphicsIOCommand->mOffsetX,
					gta.mGraphicsIOCommand->mOffsetY);
				break;
			case kGraphicsIOGenerateNewRenderSurfaceIDs:
				gta.mInterface->GenerateNewRenderSurfaceIDs(
					gta.mGraphicsIOCommand->mWidth,
					gta.mGraphicsIOCommand->mHeight,
					gta.mGraphicsIOCommand->mOpenGLTexture2DIDPtr,
					gta.mGraphicsIOCommand->mOpenGLFramebufferIDPtr,
					gta.mGraphicsIOCommand->mOpenGLRenderbufferIDPtr
					);
				break;
			case kGraphicsIODeleteRenderSurfaceIDs:
				gta.mInterface->DeleteRenderSurfaceIDs(
					*gta.mGraphicsIOCommand->mOpenGLFramebufferIDPtr,
					*gta.mGraphicsIOCommand->mOpenGLRenderbufferIDPtr
					);
				break;
			case kGraphicsIORetrieveTexture2DData:
				gta.mInterface->RetrieveTexture2DData(
					gta.mGraphicsIOCommand->mOpenGLTexture2DID,
					gta.mGraphicsIOCommand->mTexture2DDataPtr);
				break;
			case kGraphicsIORetrieveTexture2DProperties:
				gta.mInterface->RetrieveTexture2DProperties(
					gta.mGraphicsIOCommand->mOpenGLTexture2DID,
					gta.mGraphicsIOCommand->mTexture2DPropertiesPtr);
				break;
			case kGraphicsIOCreateOpenGLMesh:
				gta.mInterface->CreateOpenGLMesh(
					gta.mGraphicsIOCommand->mMeshResourcePtr,
					*gta.mGraphicsIOCommand->mConstMeshDataPtr,
					gta.mGraphicsIOCommand->mMeshUsage);
				break;
			case kGraphicsIODeleteOpenGLMesh:
				gta.mInterface->DeleteOpenGLMesh(
					gta.mGraphicsIOCommand->mMeshResourcePtr);
				break;
			default:
				break;
			};
			if (gta.mGraphicsIOCommand->mType) {
				gta.mGraphicsIOCommand->mType = kGraphicsIONone;
				*gta.mGLError = GraphicsGLErrorToFastErrorType(
					gta.mInterface->GetError());
			}
			*gta.mIsCommandWaiting = false;
			gta.mCommandIssueFinishMutex->Unlock();
			gta.mCommandIssueFinishConditional->Signal();
		}
	}

	void GraphicsThread::Main() {
		mArgs.mInterface->CreateContext();
		while (true) {
	    	Int i;
			if (*mArgs.mShouldRender) {
				mArgs.mRenderMutex->Lock();
				// TODO: Re-order draw calls in the most efficient manner
				for (i = 0; i < mArgs.mDepthChangeIndices->GetElementCount(); i++)
				{
					//for (j = mArgs.mDepthChangeIndices[0][i]; )
				}
				mArgs.mInterface->PushAttributes();
				for (i = 0; i < mArgs.mRenderItems->GetElementCount(); i++) {
					mArgs.mInterface->Draw(mArgs.mRenderItems[0][i]);
					GraphicsHandleIOCommand(mArgs);
	        	}
				mArgs.mInterface->PopAttributes();
				mArgs.mRenderItems->Clear();
				mArgs.mRenderMutex->Unlock();
	    	}
			GraphicsHandleIOCommand(mArgs);
			if (ShouldEnd())
				break;
		}
		mArgs.mInterface->DeleteContext();
	}

	GraphicsThread::GraphicsThread(const GraphicsThreadArgs &args) :
		Thread(),
		mArgs(args)
	{
		Run();
	}
}