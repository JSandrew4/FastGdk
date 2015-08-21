/******************************************************************************/
/*                                                                            */
/*  Quaternion.hpp                                                            */
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

#ifndef FastQuaternionHppIncluded
#define FastQuaternionHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class Vector3D;

	class FastApi Quaternion
	{
	public:
		// Members
		Float	mX;
		Float	mY;
		Float	mZ;
		Float	mW;
		// (Con/De)structors
		Quaternion();
		Quaternion(const Quaternion &that);
		Quaternion(Float x, Float y, Float z, Float w);
		Quaternion(Float angle, const Vector3D &axis);
		~Quaternion();
		// Misc functions
		void	Reset();
		void	SetAxis();
		// Operators
		Quaternion&	operator= (const Quaternion &that);
		Bool		operator==(const Quaternion &that) const;
		Bool		operator!=(const Quaternion &that) const;
	};
}

#endif // FastQuaternionHppIncluded
