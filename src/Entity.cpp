/******************************************************************************/
/*                                                                            */
/*  Entity.cpp                                                                */
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

#include <Fast/Entity.hpp>
#include <Fast/Scene.hpp>
#include <Fast/Renderable.hpp>
#include <Fast/PhysicsModel.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/NullEntity.hpp>
#include <Fast/Exception.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Entity::Entity(Scene *scene, const String &name) {
		mScene = scene;
		mName = name;
		mID = mScene->AddEntity(this);
		mIsSpawned = false;
		mHasParent = false;
		mParent = this;
	}

	Entity::~Entity() {
		if (mIsSpawned)
			Despawn();
		if (0 <= mID)
			mScene->RemoveEntity(mID);
		mScene = 0;
		mID = 0;
	}

	const String& Entity::GetName() const {
		return mName;
	}

	const Matrix& Entity::GetModelviewMatrix() const {
		return GetPhysicsModel().GetModelviewMatrix();
	}

	Scene* Entity::GetScene() {
		return mScene;
	}

	const Scene& Entity::GetScene() const {
		return *mScene;
	}

	Int Entity::GetID() const {
		return mID;
	}

	Bool Entity::IsSpawned() const {
		return mIsSpawned;
	}

	Bool Entity::HasParent() const {
		return mHasParent;
	}

	Entity* Entity::GetParent() {
		return mParent;
	}

	const Entity& Entity::GetParent() const {
		return *mParent;
	}

	Int Entity::GetNumChildren() const {
		return mChildren.GetElementCount();
	}

	Entity* Entity::GetChild(Int index) {
		if (0 > index || mChildren.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return mChildren[index];
	}

	const Entity& Entity::GetChild(Int index) const {
		if (0 > index || mChildren.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return *mChildren[index];
	}

	void Entity::SetName(const String &name) {
		mName = name;
	}

	void Entity::SetModelviewMatrix(const Matrix &modelviewMatrix) {
		GetPhysicsModel()->SetModelviewMatrix(modelviewMatrix);
	}

	void Entity::SetParent(Entity *entity) {
		if (!entity)
			return;
		if (mParent == entity)
			return;
		mParent = entity;
		mParent->mChildren.Append(this);
		mParent->OnChildAdd(this, mParent->mChildren.GetElementCount());
		OnParent();
	}

	void Entity::Unparent() {
		if (!mParent)
			return;
		Entity *parent = mParent;
		mParent = 0;
		for (Int i = 0; i < parent->mChildren.GetElementCount(); i++) {
			if (parent->mChildren[i] == this) {
				parent->mChildren.Erase(i);
			}
		}
		parent->OnChildRemove(this);
		OnUnparent(parent);
	}

	Int Entity::AddChild(Entity *entity) {
		if (!entity)
			return 0;
		// Check for existing entity
		for (Int i = 0; i < mChildren.GetElementCount(); i++)
			if (mChildren[i] == entity)
				return i;
		// Not existing, append entity
		mChildren.Append(entity);
		entity->mParent = this;
		entity->OnParent();
		OnChildAdd(entity, mChildren.GetElementCount());
		return mChildren.GetElementCount() - 1;
	}

	void Entity::RemoveChild(Entity *entity) {
		for (Int i = 0; i < mChildren.GetElementCount(); i++)
			if (mChildren[i] == entity)
				RemoveChild(i);
	}

	void Entity::RemoveChild(Int index) {
		if (0 > index || mChildren.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		Entity *childRemoved = mChildren[index];
		mChildren.Erase(index);
		childRemoved->mParent = 0;
		childRemoved->OnUnparent(this);
		OnChildRemove(childRemoved);
	}

	void Entity::Spawn() {
		if (!mIsSpawned) {
			mIsSpawned = true;
			OnSpawn();
		}
	}

	void Entity::Despawn() {
		if (mIsSpawned) {
			mIsSpawned = false;
			OnDespawn();
		}
	}

	void Entity::Update(Long deltaTimeMicroseconds) {
		if (mIsSpawned) {
			GetPhysicsModel()->Update(deltaTimeMicroseconds);
			OnUpdate(deltaTimeMicroseconds);
		}
	}

	void Entity::Draw() {
		if (mIsSpawned) {
			GetRenderable()->GetRenderPreferences()->SetModelviewMatrix(
				GetModelviewMatrix());
			// TODO: GetRenderable()->Draw(/* <frameBufferSurface> */);
			// NOTES: Maybe give every entity a list of FrameBufferSurface
			//	pointers. That way when we call Entity::Draw(), we let the
			//	render pipeline know all the different surfaces the entity
			//	needs to be visible on.
		}
	}

	void Entity::OnSpawn() {
		
	}

	void Entity::OnDespawn() {
		
	}

	void Entity::OnParent() {
		
	}

	void Entity::OnUnparent(Entity *oldParent) {
		
	}

	void Entity::OnChildAdd(Entity *entity, Int childIndex) {
		
	}

	void Entity::OnChildRemove(Entity *entity) {

	}
}
