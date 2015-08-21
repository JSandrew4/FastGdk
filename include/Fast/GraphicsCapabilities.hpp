/******************************************************************************/
/*                                                                            */
/*  GraphicsCapabilities.hpp                                                  */
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

#ifndef FastGraphicsCapabilitiesHppIncluded
#define FastGraphicsCapabilitiesHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi GraphicsCapabilities
	{
	private:
		// Check for support
		Bool		mIsMultisamplingSupported;
		Bool		mIsAnisotropicFilteringSupported;
		Bool		mIsVerticalSyncSupported;
		// Get limits
		Int			mMaxRenderSurfaceSize;
		Int			mMaxRenderSurfaceSamples;
		Int			mMaxTexture2DSize;
		Int			mMaxTextureUnitsCount;
		Float		mPointSizeRange[2];
		Float		mPointSizeGranularity;
		Float		mLineWidthRange[4];
		Float		mSmoothLineWidthGranularity;  
		// Get supported values
		Array<Int>	mSupportedMultisampleSamples;
		Array<Int>	mSupportedAnisotropicFilteringSamples;
	public:
		// (Con/De)structors
		GraphicsCapabilities();
		~GraphicsCapabilities();
		// Misc
		void		Populate();
		// Check for support
		Bool		IsMultisamplingSupported() const;
		Bool		IsAnisotropicFilteringSupported() const;
		Bool		IsVerticalSyncSupported() const;
		// Get limits
		Int			GetMaxRenderSurfaceSize() const;
		Int			GetMaxRenderSurfaceSamples() const;
		Int			GetMaxTexture2DSize() const;
		Int			GetMaxTextureUnitsCount() const;
		Float		GetMaxPointSize() const;
		Float		GetMinPointSize() const;
		Float		GetPointSizeGranularity() const;
		Float		GetMaxAliasedLineWidth() const;
		Float		GetMinAliasedLineWidth() const;
		Float		GetMaxSmoothLineWidth() const;
		Float		GetMinSmoothLineWidth() const;
		Float		GetSmoothLineWidthGranularity() const;  
		// Get supported values
		Array<Int>	GetSupportedMultisampleSamples() const;
		Array<Int>	GetSupportedAnisotropicFilteringSamples() const;
	};
}

#endif // FastGraphicsCapabilitiesHppIncluded