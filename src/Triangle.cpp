/******************************************************************************/
/*                                                                            */
/*  Triangle.cpp                                                              */
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

#include <Fast/Triangle.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	Triangle::Triangle() {
		memset(mPlainOldData.mIndices, 0, sizeof(Short)*3);
	}

	Triangle::Triangle(const Triangle &that) {
		*this = that;
	}

	Triangle::Triangle(Short vertexIndex0,
		Short vertexIndex1, Short vertexIndex2)
	{
		mPlainOldData.mIndices[0] = vertexIndex0;
		mPlainOldData.mIndices[1] = vertexIndex1;
		mPlainOldData.mIndices[2] = vertexIndex2;
	}

	Triangle::Triangle(const TriangleStruct &plainOldData) {
		FromPlainOldData(plainOldData);
	}

	void Triangle::FromPlainOldData(const TriangleStruct &that) {
		mPlainOldData = that;		
	}

	void Triangle::SetVertexIndex(Int index, Short vertexIndex) {
		mPlainOldData.mIndices[index] = vertexIndex;
	}

	const TriangleStruct& Triangle::GetPlainOldData() const {
		return mPlainOldData;
	}

	Short Triangle::GetVertexIndex(Int index) const {
		return mPlainOldData.mIndices[index];
	}

	Triangle& Triangle::operator=(const Triangle &that) {
		memcpy(this->mPlainOldData.mIndices,
			that.mPlainOldData.mIndices, sizeof(Short)*3);
		return *this;
	}

	Bool Triangle::operator==(const Triangle &that) const {
		if (0 == memcmp(this->mPlainOldData.mIndices,
			that.mPlainOldData.mIndices, sizeof(Short)*3))
		{
			return true;
		}
		return false;
	}

	Bool Triangle::operator!=(const Triangle &that) const {
		if (0 == memcmp(this->mPlainOldData.mIndices,
			that.mPlainOldData.mIndices, sizeof(Short)*3))
		{
			return false;
		}
		return true;
	}
}