/******************************************************************************/
/*                                                                            */
/*  NullEntity.cpp                                                            */
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

#include <Fast/NullEntity.hpp>
#include <Fast/Renderable.hpp>
#include <Fast/PhysicsModel.hpp>
#include <Fast/FrameBufferCollection.hpp>

#include "Undefs.hpp"

namespace Fast
{
	NullEntity::NullEntity(Scene *scene) :
		Entity(scene, "NullEntity"),
		mRenderable()
	{ }

	Renderable* NullEntity::GetRenderable() {
		return &mRenderable;
	}

	const Renderable& NullEntity::GetRenderable() const {
		return mRenderable;
	}

	PhysicsModel* NullEntity::GetPhysicsModel() {
		return &mPhysicsModel;
	}

	const PhysicsModel& NullEntity::GetPhysicsModel() const {
		return mPhysicsModel;
	}

	void NullEntity::OnUpdate(Long deltaTimeMicroseconds) {
		// Nothing
	}

	void NullEntity::OnCollision(Entity *entity) {
		// Nothing
	}
}