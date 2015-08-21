/******************************************************************************/
/*                                                                            */
/*  Box3D.hpp                                                                 */
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

#ifndef FastBox3DHppIncluded
#define FastBox3DHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector3D.hpp>

namespace Fast
{
	class FastApi Box3D
	{
	public:
		// Members
		Vector3D	mOrigin;
		Vector3D	mSize;
		// (Con/De)structors
		Box3D();
		Box3D(const Box3D &that);
		Box3D(const Vector3D &origin, const Vector3D &size);
		Box3D(Float originX, Float originY, Float originZ,
			Float sizeX, Float sizeY, Float sizeZ);
		~Box3D();
		// Operators
		Box3D&	operator= (const Box3D &that);
		Bool	operator==(const Box3D &that) const;
		Bool	operator!=(const Box3D &that) const;
	};
}

#endif // FastBox3DHppIncluded