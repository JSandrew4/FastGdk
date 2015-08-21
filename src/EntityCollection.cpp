/******************************************************************************/
/*                                                                            */
/*  EntityCollection.cpp                                                      */
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

#include <Fast/EntityCollection.hpp>
#include <Fast/PhysicsScene.hpp>
#include <Fast/Entity.hpp>
#include <Fast/GraphicsContext.hpp>

#include "Undefs.hpp"

namespace Fast
{
	EntityCollection::EntityCollection(PhysicsScene *physicsScene) :
		mPhysicsScene(*physicsScene)
	{ }

	EntityCollection::~EntityCollection() {
		RemoveAllEntities();
	}

	Int EntityCollection::AddEntity(Entity *entity) {
		for (Int i = 0; i < mEntityEntries.GetElementCount(); i++) {
			if (!mEntityEntries[i].mIsActive) {
				mEntityEntries[i].mEntity = entity;
				mEntityEntries[i].mIsActive = true;
				return i;
			}
		}
		EntityEntry e;
		e.mEntity = entity;
		e.mIsActive = true;
		mEntityEntries.Append(e);
		return mEntityEntries.GetElementCount() - 1;
	}

	void EntityCollection::RemoveEntity(Int id) {
		mEntityEntries[id].mIsActive = false;
	}

	void EntityCollection::RemoveAllEntities() {
		mEntityEntries.Clear();
	}

	Entity* EntityCollection::GetEntity(Int id) {
		return mEntityEntries[id].mEntity;
	}

	const Entity& EntityCollection::GetEntity(Int id) const {
		return *mEntityEntries[id].mEntity;
	}

	PhysicsScene* EntityCollection::GetPhysicsScene() {
		return &mPhysicsScene;
	}

	const PhysicsScene& EntityCollection::GetPhysicsScene() const {
		return mPhysicsScene;
	}

	void EntityCollection::Update(Long deltaTimeMicroseconds) {
		for (Int i = 0; i < mEntityEntries.GetElementCount(); i++)
			if (mEntityEntries[i].mIsActive)
				mEntityEntries[i].mEntity->Update(deltaTimeMicroseconds);
	}

	void EntityCollection::Draw() {
		for (Int i = 0; i < mEntityEntries.GetElementCount(); i++)
			if (mEntityEntries[i].mIsActive)
				mEntityEntries[i].mEntity->Draw();
	}
}
