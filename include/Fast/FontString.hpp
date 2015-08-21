/******************************************************************************/
/*                                                                            */
/*  FontString.hpp                                                            */
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

#ifndef FastFontStringHppIncluded
#define FastFontStringHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Alignment.hpp>

namespace Fast
{
	class FontBase;
	class String;
	class Vector2D;
	class Vector3D;
	class Matrix;
	class Quaternion;

	class FastApi FontString
	{
	public:
		// (Con/De)structors
		FontString();
		FontString(const FontBase &font, const String &text, Float scale);
		~FontString();
		// Setters
		void SetFont(const FontBase &font);
		void SetText(const String &text);
		// Getters
		const FontBase& GetFont() const;
		const String&   GetText() const;
		// Draw functions
		void	Draw2D(Alignment alignment, const Vector2D &origin,
					const Vector2D &scale, Float rotationAngle);
		void	Draw2D(Alignment alignment, const Matrix &matrix);
		void	Draw3D(Alignment alignment, const Vector3D &origin,
					const Vector3D &scale, const Quaternion &rotation);
		void	Draw3D(Alignment alignment, const Matrix &matrix);
		// Operators
		FontString& operator= (const FontString &that);
		Bool        operator==(const FontString &that);
		Bool        operator!=(const FontString &that);
	};
}

#endif // FastFontStringHppIncluded
