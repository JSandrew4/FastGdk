/******************************************************************************/
/*                                                                            */
/*  SpriteCollisionTriangle.cpp                                               */
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

#include <Fast/SpriteCollisionTriangle.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SpriteCollisionTriangle::SpriteCollisionTriangle() { }

	SpriteCollisionTriangle::SpriteCollisionTriangle(
		const SpriteCollisionTriangle &that)
	{
		*this = that;
	}

	SpriteCollisionTriangle::SpriteCollisionTriangle(
		const Vector2D &componentA, const Vector2D &componentB,
		const Vector2D &componentC)
	{
		mComponentA = componentA;
		mComponentB = componentB;
		mComponentC = componentC;
	}

	SpriteCollisionTriangle& SpriteCollisionTriangle::operator=(
		const SpriteCollisionTriangle &that)
	{
		this->mComponentA = that.mComponentA;
		this->mComponentB = that.mComponentB;
		this->mComponentC = that.mComponentC;
		return *this;
	}

	Bool SpriteCollisionTriangle::operator==(
		const SpriteCollisionTriangle &that) const
	{
		if (this->mComponentA != that.mComponentA)
			return false;
		if (this->mComponentB != that.mComponentB)
			return false;
		if (this->mComponentC != that.mComponentC)
			return false;
		return true;
	}

	Bool SpriteCollisionTriangle::operator!=(
		const SpriteCollisionTriangle &that) const
	{
		if (this->mComponentA != that.mComponentA)
			return true;
		if (this->mComponentB != that.mComponentB)
			return true;
		if (this->mComponentC != that.mComponentC)
			return true;
		return false;
	}
}