/******************************************************************************/
/*                                                                            */
/*  Point.hpp                                                                 */
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

#ifndef FastPointHppIncluded
#define FastPointHppIncluded

#include <Fast/Types.hpp>

#define kFastPointZero	Point(0, 0)

namespace Fast
{
	class Rectangle;

	class FastApi Point
	{
	public:
		// Members
		Int	mX;
		Int	mY;
		// (Con/De)structors
		Point();
		Point(Int x, Int y);
		Point(const Point &that);
		// Misc
		Bool	IsInside(const Rectangle &rect) const;
		// Assignment operator
		Point&	operator=(const Point &that);
		// Compare operators
		Bool	operator==(const Point &that) const;
		Bool	operator!=(const Point &that) const;
	};
}

#endif // FastPointHppIncluded