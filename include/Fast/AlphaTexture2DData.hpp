/******************************************************************************/
/*                                                                            */
/*  AlphaTexture2DData.hpp                                                    */
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

#ifndef FastAlphaTexture2DDataHppIncluded
#define FastAlphaTexture2DDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi AlphaTexture2DData
	{
	private:
		// Members
		Array<Byte>	mPixels;
		Int			mWidth;
		Int			mHeight;
	public:
		// (Con/De)structors
		AlphaTexture2DData();
		AlphaTexture2DData(Int width, Int height);
		AlphaTexture2DData(Int width, Int height, const Array<Byte> &pixels);
		AlphaTexture2DData(const AlphaTexture2DData &that);
		~AlphaTexture2DData();
		// Getters
		Int					GetWidth() const;
		Int					GetHeight() const;
		const Array<Byte>&	GetPixels() const;
		// Operators
		AlphaTexture2DData&	operator= (const AlphaTexture2DData &that);
		Bool				operator==(const AlphaTexture2DData &that) const;
		Bool				operator!=(const AlphaTexture2DData &that) const;
	};
}

#endif // FastAlphaTexture2DDataHppIncluded
