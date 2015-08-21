/******************************************************************************/
/*                                                                            */
/*  GraphicsCapabilities.cpp                                                  */
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

#include <Fast/GraphicsCapabilities.hpp>

#include "OpenGL.hpp"

#include "Undefs.hpp"

namespace Fast
{
	GraphicsCapabilities::GraphicsCapabilities() {
		mIsMultisamplingSupported			= false;
		mIsAnisotropicFilteringSupported	= false;
		mIsVerticalSyncSupported			= false;
		mMaxRenderSurfaceSize				= 0;
		mMaxRenderSurfaceSamples			= 0;
		mMaxTexture2DSize					= 0;
		mMaxTextureUnitsCount				= 0;
		mPointSizeRange[0]					= 0.0f;
		mPointSizeRange[1]					= 0.0f;
		mPointSizeGranularity				= 0.0f;
		mLineWidthRange[0]					= 0.0f;
		mLineWidthRange[1]					= 0.0f;
		mLineWidthRange[2]					= 0.0f;
		mLineWidthRange[3]					= 0.0f;
		mSmoothLineWidthGranularity			= 0.0f;
	}

	GraphicsCapabilities::~GraphicsCapabilities() { }

	void GraphicsCapabilities::Populate() {
		// TODO: Get capabilities
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mMaxTexture2DSize);
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &mMaxRenderSurfaceSize);
		if (0 == mMaxRenderSurfaceSize)
			mMaxRenderSurfaceSize = mMaxTexture2DSize;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &mMaxTextureUnitsCount);
		if (0 == mMaxTextureUnitsCount)
			mMaxTextureUnitsCount = 1;
		glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, &mLineWidthRange[0]);
		glGetFloatv(GL_SMOOTH_LINE_WIDTH_RANGE, &mLineWidthRange[2]);
		glGetFloatv(GL_SMOOTH_LINE_WIDTH_GRANULARITY,
			&mSmoothLineWidthGranularity);
		glGetFloatv(GL_POINT_SIZE_RANGE, &mPointSizeRange[0]);
		glGetFloatv(GL_POINT_SIZE_GRANULARITY, &mPointSizeGranularity);
	}

	Bool GraphicsCapabilities::IsMultisamplingSupported() const {
		return mIsMultisamplingSupported;
	}

	Bool GraphicsCapabilities::IsAnisotropicFilteringSupported() const {
		return mIsAnisotropicFilteringSupported;
	}

	Bool GraphicsCapabilities::IsVerticalSyncSupported() const {
		return mIsVerticalSyncSupported;
	}

	Int GraphicsCapabilities::GetMaxRenderSurfaceSize() const {
		return mMaxRenderSurfaceSize;
	}

	Int GraphicsCapabilities::GetMaxRenderSurfaceSamples() const {
		return mMaxRenderSurfaceSamples;
	}

	Int GraphicsCapabilities::GetMaxTexture2DSize() const {
		return mMaxTexture2DSize;
	}

	Int GraphicsCapabilities::GetMaxTextureUnitsCount() const {
		return mMaxTextureUnitsCount;
	}

	Float GraphicsCapabilities::GetMaxPointSize() const {
		return mPointSizeRange[1];
	}

	Float GraphicsCapabilities::GetMinPointSize() const {
		return mPointSizeRange[0];
	}

	Float GraphicsCapabilities::GetPointSizeGranularity() const {
		return mPointSizeGranularity;
	}

	Float GraphicsCapabilities::GetMaxAliasedLineWidth() const {
		return mLineWidthRange[1];
	}

	Float GraphicsCapabilities::GetMinAliasedLineWidth() const {
		return mLineWidthRange[0];
	}

	Float GraphicsCapabilities::GetMaxSmoothLineWidth() const {
		return mLineWidthRange[3];
	}

	Float GraphicsCapabilities::GetMinSmoothLineWidth() const {
		return mLineWidthRange[2];
	}

	Float GraphicsCapabilities::GetSmoothLineWidthGranularity() const {
		return mSmoothLineWidthGranularity;
	}

	Array<Int> GraphicsCapabilities::GetSupportedMultisampleSamples() const {
		return mSupportedMultisampleSamples;
	}

	Array<Int> GraphicsCapabilities::GetSupportedAnisotropicFilteringSamples()
		const
	{
		return mSupportedAnisotropicFilteringSamples;
	}
}