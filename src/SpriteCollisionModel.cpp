/******************************************************************************/
/*                                                                            */
/*  SpriteCollisionModel.cpp                                                  */
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

#include <Fast/SpriteCollisionModel.hpp>
#include <Fast/Exception.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteCollisionModel::SpriteCollisionModel() { }

	SpriteCollisionModel::SpriteCollisionModel(const SpriteCollisionModel &that)
	{
		*this = that;
	}

	const String& SpriteCollisionModel::GetName() const {
		return mName;
	}

	Int SpriteCollisionModel::GetNumTriangles() const {
		return mTriangles.GetElementCount();
	}

	SpriteCollisionTriangle* SpriteCollisionModel::GetTriangle(Int index) {
		if (0 > index || GetNumTriangles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return &mTriangles[index];
	}

	const SpriteCollisionTriangle& SpriteCollisionModel::GetTriangle(
		Int index) const
	{
		if (0 > index || GetNumTriangles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return mTriangles[index];
	}

	Int SpriteCollisionModel::GetNumCircles() const {
		return mCircles.GetElementCount();
	}

	Circle* SpriteCollisionModel::GetCircle(Int index) {
		if (0 > index || GetNumCircles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return &mCircles[index];
	}

	const Circle& SpriteCollisionModel::GetCircle(Int index) const {
		if (0 > index || GetNumCircles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return mCircles[index];
	}

	void SpriteCollisionModel::SetName(const String &name) {
		mName = name;
	}

	void SpriteCollisionModel::AddTriangle(
		const SpriteCollisionTriangle &triangle)
	{
		mTriangles.Append(triangle);
	}

	void SpriteCollisionModel::InsertTriangle(
		const SpriteCollisionTriangle &triangle, Int index)
	{
		if (0 > index || GetNumTriangles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mTriangles.Insert(triangle, index);
	}

	void SpriteCollisionModel::ReplaceTriangle(
		const SpriteCollisionTriangle &triangle, Int index)
	{
		if (0 > index || GetNumTriangles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mTriangles.Replace(triangle, index);
	}

	void SpriteCollisionModel::EraseTriangle(Int index) {
		if (0 > index || GetNumTriangles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mTriangles.Erase(index);
	}

	void SpriteCollisionModel::ClearTriangles() {
		for (Int i = GetNumTriangles() - 1; i >= 0; i--)
			EraseTriangle(i);
	}

	void SpriteCollisionModel::AddCircle(const Circle &circle) {
		mCircles.Append(circle);
	}

	void SpriteCollisionModel::InsertCircle(const Circle &circle, Int index) {
		if (0 > index || GetNumCircles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mCircles.Insert(circle, index);
	}

	void SpriteCollisionModel::ReplaceCircle(const Circle &circle, Int index) {
		if (0 > index || GetNumCircles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mCircles.Replace(circle, index);
	}

	void SpriteCollisionModel::EraseCircle(Int index) {
		if (0 > index || GetNumCircles() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		mCircles.Erase(index);
	}

	void SpriteCollisionModel::ClearCircles() {
		for (Int i = GetNumCircles() - 1; i >= 0; i--)
			EraseCircle(i);
	}

	SpriteCollisionModel& SpriteCollisionModel::operator=(
		const SpriteCollisionModel &that)
	{
		this->mName = that.mName;
		this->mTriangles = that.mTriangles;
		this->mCircles = that.mCircles;
		return *this;
	}

	Bool SpriteCollisionModel::operator==(
		const SpriteCollisionModel &that) const
	{
		if (this->mName != that.mName)
			return false;
		if (this->mTriangles.GetElementCount() !=
			this->mTriangles.GetElementCount())
		{
			return false;
		}
		for (Int i = 0; i < this->mTriangles.GetElementCount(); i++)
			if (this->mTriangles[i] != that.mTriangles[i])
				return false;
		if (this->mCircles.GetElementCount() !=
			this->mCircles.GetElementCount())
		{
			return false;
		}
		for (Int i = 0; i < this->mCircles.GetElementCount(); i++)
			if (this->mCircles[i] != that.mCircles[i])
				return false;
		return true;
	}

	Bool SpriteCollisionModel::operator!=(
		const SpriteCollisionModel &that) const
	{
		if (this->mName != that.mName)
			return true;
		if (this->mTriangles.GetElementCount() !=
			this->mTriangles.GetElementCount())
		{
			return true;
		}
		for (Int i = 0; i < this->mTriangles.GetElementCount(); i++)
			if (this->mTriangles[i] != that.mTriangles[i])
				return true;
		if (this->mCircles.GetElementCount() !=
			this->mCircles.GetElementCount())
		{
			return true;
		}
		for (Int i = 0; i < this->mCircles.GetElementCount(); i++)
			if (this->mCircles[i] != that.mCircles[i])
				return true;
		return false;
	}
}