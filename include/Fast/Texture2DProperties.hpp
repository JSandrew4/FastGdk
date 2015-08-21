/******************************************************************************/
/*                                                                            */
/*  Texture2DProperties.hpp                                                   */
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

#ifndef FastTexture2DPropertiesHppIncluded
#define FastTexture2DPropertiesHppIncluded

#include <Fast/Types.hpp>
#include <Fast/SpriteSheet.hpp>
#include <Fast/Texture2DFilterType.hpp>
#include <Fast/Texture2DWrapType.hpp>
#include <Fast/Color.hpp>

namespace Fast
{

	class FastApi Texture2DProperties
	{
	protected:
		Int					mWidth;
		Int					mHeight;
		Int					mBitsPerPixel;
		SpriteSheet			mSpriteSheet;
		Texture2DWrapType	mWrapTypeS;
		Texture2DWrapType	mWrapTypeT;
		Texture2DFilterType	mMinifyFilterType;
		Texture2DFilterType	mMagnifyFilterType;
		Color				mBorderColor;
	public:
		// Constructors
		Texture2DProperties();
		Texture2DProperties(Int width, Int height, Int bitsPerPixel);
		// Getters
		Int					GetWidth() const;
		Int					GetHeight() const;
		Int					GetBitsPerPixel() const;
		const SpriteSheet&	GetSpriteSheet() const;
		SpriteSheet*		GetSpriteSheet();
		Texture2DWrapType	GetWrapTypeS() const;
		Texture2DWrapType	GetWrapTypeT() const;
		Texture2DFilterType	GetMinifyFilterType() const;
		Texture2DFilterType	GetMagnifyFilterType() const;
		const Color&		GetBorderColor() const;
		// Setters
		void	SetSize(Int width, Int height);
		void	SetWidth(Int width);
		void	SetHeight(Int height);
		void	SetBitsPerPixel(Int bitsPerPixel);
		void	SetSpriteSheet(const SpriteSheet &spriteSheet);
		void	SetWrapTypeS(Texture2DWrapType type);
		void	SetWrapTypeT(Texture2DWrapType type);
		void	SetMinifyFilterType(Texture2DFilterType type);
		void	SetMagnifyFilterType(Texture2DFilterType type);
		void	SetBorderColor(const Color &borderColor);
		// Operators
		Bool	operator==(const Texture2DProperties &that) const;
		Bool	operator!=(const Texture2DProperties &that) const;
	};
}

#endif // FastTexture2DPropertiesHppIncluded
