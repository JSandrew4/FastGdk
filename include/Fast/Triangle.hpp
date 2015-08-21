/******************************************************************************/
/*                                                                            */
/*  Triangle.hpp                                                              */
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

#ifndef FastTriangleHppIncluded
#define FastTriangleHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/TriangleStruct.hpp>

namespace Fast
{
	class FastApi Triangle
	{
	private:
		TriangleStruct	mPlainOldData;
	public:
		// Constructors
		Triangle();
		Triangle(const Triangle &that);
		Triangle(Short vertexIndex0, Short vertexIndex1, Short vertexIndex2);
		Triangle(const TriangleStruct &that);
		// Setters
		void	FromPlainOldData(const TriangleStruct &that);
		void	SetVertexIndex(Int index, Short vertexIndex);
		// Getters
		const TriangleStruct&	GetPlainOldData() const;
		Short					GetVertexIndex(Int index) const;
		// Operators
		Triangle&	operator= (const Triangle &that);
		Bool		operator==(const Triangle &that) const;
		Bool		operator!=(const Triangle &that) const;
	};

	template class FastApi Array<Triangle>;
}

#endif // FastTriangleHppIncluded
