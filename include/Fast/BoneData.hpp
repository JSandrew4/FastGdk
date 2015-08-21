/******************************************************************************/
/*                                                                            */
/*  BoneData.hpp                                                              */
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

#ifndef FastBoneDataHppIncluded
#define FastBoneDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi BoneData
	{
	protected:
		String		mName;
		Float		mLength;
		Int			mParentBoneID;
		Array<Int>	mChildBoneIDArray;
	public:
		// (Con/De)structors
		BoneData();
		BoneData(const BoneData &that);
		~BoneData();
		// Getters
		const String&		GetName() const;
		Float				GetLength() const;
		Int					GetParentBoneID() const;
		Array<Int>*			GetChildBoneIDArray();
		const Array<Int>&	GetChildBoneIDArray() const;
		// Setters
		void	SetName(const String &name);
		void	SetLength(Float length);
		void	SetParentBoneID(Int parentBoneID);
		// Operators
		BoneData&	operator= (const BoneData &that);
		Bool		operator==(const BoneData &that) const;
		Bool		operator!=(const BoneData &that) const;
	};

	template class FastApi Array<BoneData>;
}

#endif // FastBoneDataHppIncluded