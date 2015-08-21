/******************************************************************************/
/*                                                                            */
/*  FontResource.hpp                                                          */
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

#ifndef FastFontResourceHppIncluded
#define FastFontResourceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetResourceBase.hpp>
#include <Fast/AssetResourceVerifiableBase.hpp>
#include <Fast/FontProperties.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	template class FastApi AssetResourceBase<FontProperties>;

	class FastApi FontResource : public AssetResourceBase<FontProperties>,
		public AssetResourceVerifiableBase
	{
	protected:
		// TODO: Array<Texture2DFontGlyph>	mTexture2DFontGlyphArray;
		// TODO: Other kinds of glyph arrays
		CFTFont	*mFTFont;
	public:
		FontResource();
		// Getters
		CFTFont*		GetFTFont();
		const CFTFont*	GetFTFont() const;
	};
}

#endif // FastFontResourceHppIncluded
