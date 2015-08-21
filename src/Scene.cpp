/******************************************************************************/
/*                                                                            */
/*  Scene.cpp                                                                 */
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

#include <Fast/Scene.hpp>
#include <Fast/PhysicsContext.hpp>
#include <Fast/Entity.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/Exception.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Scene::Scene(GraphicsContext *graphicsContext) :
		mGraphicsContext(*graphicsContext)
	{
		mPhysicsContext = NULL;
		mNumActiveEntities = 0;
	}

	Scene::~Scene() {
		DeleteAllEntities();
		delete mPhysicsContext;
	}

	Int Scene::AddEntity(Entity *entity) {
		mNumActiveEntities++;
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

	void Scene::DeleteEntity(Int id) {
		if (mEntityEntries[id].mIsActive) {
			mEntityEntries[id].mIsActive = false;
			delete mEntityEntries[id].mEntity;
			mEntityEntries[id].mEntity = NULL;
			mNumActiveEntities--;
		}
	}

	void Scene::DeleteAllEntities() {
		for (Int i = 0; i < mEntityEntries.GetElementCount(); i++)
			DeleteEntity(i);
		mEntityEntries.Clear();
	}

	void Scene::RemoveEntity(Int id) {
		if (mEntityEntries[id].mIsActive) {
			mEntityEntries[id].mIsActive = false;
			mEntityEntries[id].mEntity = NULL;
			mNumActiveEntities--;
		}
	}

	Int Scene::GetNumEntities() const {
		return mNumActiveEntities;
	}

	Bool Scene::IsEntity(Int id) const {
		if (mEntityEntries.GetElementCount() <= id && 0 > id)
			if (mEntityEntries[id].mIsActive)
				return true;
		return false;
	}

	Entity* Scene::GetEntity(Int id) {
		if (!IsEntity(id))
			Exception::Throw(kExceptionInvalidValue, String("(%s: %d)",
				FastFunctionName, id));
		return mEntityEntries[id].mEntity;
	}

	const Entity& Scene::GetEntity(Int id) const {
		if (!IsEntity(id))
			Exception::Throw(kExceptionInvalidValue, String("(%s: %d)",
				FastFunctionName, id));
		return *mEntityEntries[id].mEntity;
	}

	PhysicsContext* Scene::GetPhysicsContext() {
		return mPhysicsContext;
	}

	const PhysicsContext& Scene::GetPhysicsContext() const {
		return *mPhysicsContext;
	}

	GraphicsContext* Scene::GetGraphicsContext() {
		return &mGraphicsContext;
	}

	const GraphicsContext& Scene::GetGraphicsContext() const {
		return mGraphicsContext;
	}

	void Scene::Update(Long deltaTimeMicroseconds) {
		for (Int i = 0; i < mEntityEntries.GetElementCount(); i++)
			if (mEntityEntries[i].mIsActive)
				mEntityEntries[i].mEntity->Update(deltaTimeMicroseconds);
	}

	void Scene::Draw() {
		for (Int i = 0; i < mEntityEntries.GetElementCount(); i++)
			if (mEntityEntries[i].mIsActive)
				mEntityEntries[i].mEntity->Draw();
	}
}
