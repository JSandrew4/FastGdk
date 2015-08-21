/******************************************************************************/
/*                                                                            */
/*  SpriteSheet.hpp                                                           */
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

#ifndef FastSpriteSheetHppIncluded
#define FastSpriteSheetHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/SubTexture2D.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Version.hpp>

namespace Fast
{
	class String;
	class StreamReader;

	template class FastApi Array<SubTexture2D>;

	class FastApi SpriteSheet
	{
	private:
		String				mName;
		Array<SubTexture2D>	mSubTexture2DArray;
	public:
		// (Con/De)structors
		SpriteSheet();
		SpriteSheet(const SpriteSheet &that);
		SpriteSheet(const String &fileName);
		SpriteSheet(StreamReader *streamReader);
		// Allocators
		ErrorType	Load(const String &fileName);
		ErrorType	Load(StreamReader *streamReader);
		void		Unload();
		// Getters
		const String&		GetName() const;
		Int					GetSubTexture2DCount() const;
		SubTexture2D*		GetSubTexture2D(Int index);
		const SubTexture2D&	GetSubTexture2D(Int index) const;
		Int					GetSubTexture2DIndex(const String &name) const;
		// Modifiers
		void	SetName(const String &name);
		void	AddSubTexture2D(const SubTexture2D &subTexture2D);
		void	InsertSubTexture2D(
					const SubTexture2D &subTexture2D, Int index);
		void	ReplaceSubTexture2D(
					const SubTexture2D &subTexture2D, Int index);
		void	EraseSubTexture2D(Int index);
		void	ClearSubTexture2DArray();
		// Misc
		ErrorType	SaveAs(const String &fileName,
						const Version &version = Version(0, 1));
		// Operators
		SpriteSheet&	operator= (const SpriteSheet &that);
		Bool			operator==(const SpriteSheet &that) const;
		Bool			operator!=(const SpriteSheet &that) const;
	};
}

#endif // FastSpriteSheetHppIncluded