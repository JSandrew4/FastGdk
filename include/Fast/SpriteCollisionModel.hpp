/******************************************************************************/
/*                                                                            */
/*  SpriteCollisionModel.hpp                                                  */
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

#ifndef FastSpriteCollisionModelHppIncluded
#define FastSpriteCollisionModelHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>
#include <Fast/SpriteCollisionTriangle.hpp>
#include <Fast/Circle.hpp>

namespace Fast
{
	class FastApi SpriteCollisionModel
	{
	private:
		String							mName;
		Array<SpriteCollisionTriangle>	mTriangles;
		Array<Circle>					mCircles;
	public:
		// Constructors
		SpriteCollisionModel();
		SpriteCollisionModel(const SpriteCollisionModel &that);
		// Getters
		const String&					GetName() const;
		Int								GetNumTriangles() const;
		SpriteCollisionTriangle*		GetTriangle(Int index);
		const SpriteCollisionTriangle&	GetTriangle(Int index) const;
		Int								GetNumCircles() const;
		Circle*							GetCircle(Int index);
		const Circle&					GetCircle(Int index) const;
		// Setters
		void	SetName(const String &name);
		void	AddTriangle(const SpriteCollisionTriangle &triangle);
		void	InsertTriangle(const SpriteCollisionTriangle &triangle,
					Int index);
		void	ReplaceTriangle(const SpriteCollisionTriangle &triangle,
					Int index);
		void	EraseTriangle(Int index);
		void	ClearTriangles();
		void	AddCircle(const Circle &circle);
		void	InsertCircle(const Circle &circle, Int index);
		void	ReplaceCircle(const Circle &circle, Int index);
		void	EraseCircle(Int index);
		void	ClearCircles();
		// Operators
		SpriteCollisionModel&	operator= (const SpriteCollisionModel &that);
		Bool					operator==(const SpriteCollisionModel &that)
									const;
		Bool					operator!=(const SpriteCollisionModel &that)
									const;
	};

	template class FastApi Array<SpriteCollisionModel>;
}

#endif // FastSpriteCollisionModelHppIncluded