/******************************************************************************/
/*                                                                            */
/*  SkeletonAnimationData.cpp                                                 */
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

#include <Fast/SkeletonAnimationData.hpp>

namespace Fast
{
	SkeletonAnimationData::SkeletonAnimationData() {
		// TODO
	}

	SkeletonAnimationData::SkeletonAnimationData(
		const SkeletonAnimationData &that)
	{
		// TODO
	}

	SkeletonAnimationData::SkeletonAnimationData(const String &fileName) {
		// TODO
	}

	SkeletonAnimationData::SkeletonAnimationData(StreamReader *streamReader) {
		// TODO
	}

	SkeletonAnimationData::~SkeletonAnimationData() {
		// TODO
	}

	ErrorType SkeletonAnimationData::Load(const String &fileName) {
		// TODO
		return kErrorGeneric;
	}

	ErrorType SkeletonAnimationData::Load(StreamReader *streamReader) {
		// TODO
		return kErrorGeneric;
	}

	void SkeletonAnimationData::Unload() {
		// TODO
	}

	void SkeletonAnimationData::AddAction(const SkeletonAnimationAction &action)
	{
		// TODO
	}

	void SkeletonAnimationData::InsertAction(
		const SkeletonAnimationAction &action, Int index)
	{
		// TODO
	}

	void SkeletonAnimationData::ReplaceAction(
		const SkeletonAnimationAction &action, Int index)
	{
		// TODO
	}

	void SkeletonAnimationData::RemoveAction(Int index) {
		// TODO
	}

	SkeletonAnimationAction* SkeletonAnimationData::GetAction(Int index) {
		// TODO
		return NULL;
	}

	const SkeletonAnimationAction& SkeletonAnimationData::GetAction(
		Int index) const
	{
		// TODO
		static SkeletonAnimationAction null;
		return null;
	}

	SkeletonAnimationAction* SkeletonAnimationData::GetAction(
		const String &name)
	{
		// TODO
		return NULL;
	}

	const SkeletonAnimationAction& SkeletonAnimationData::GetAction(
		const String &name) const
	{
		// TODO
		static SkeletonAnimationAction null;
		return null;
	}

	Int SkeletonAnimationData::GetActionIndex(const String &name) const {
		// TODO
		return 0;
	}

	SkeletonAnimationData& SkeletonAnimationData::operator=(
		const SkeletonAnimationData &that)
	{
		// TODO
		return *this;
	}

	Bool SkeletonAnimationData::operator==(
		const SkeletonAnimationData &that) const
	{
		// TODO
		return false;
	}

	Bool SkeletonAnimationData::operator!=(
		const SkeletonAnimationData &That) const
	{
		// TODO
		return true;
	}
}