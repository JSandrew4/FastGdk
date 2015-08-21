/******************************************************************************/
/*                                                                            */
/*  Entity.hpp                                                                */
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

#ifndef FastEntityHppIncluded
#define FastEntityHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class Scene;
	class Renderable;
	class PhysicsModel;
	class Vector2D;
	class Vector3D;
	class Quaternion;
	class Matrix;

	class FastApi Entity
	{
	private:
		// Hide these functions. No copying entities!
		Entity(const Entity &that) {}
		Entity& operator=(const Entity &that)
			{ return *this; }
	private:
		String			mName;
		Scene			*mScene;
		Int				mID;
		Bool			mIsSpawned;
		Bool			mHasParent;
		Entity			*mParent;
		Array<Entity*>	mChildren;
	public:
		// (Con/De)structors
		Entity(Scene *scene, const String &name = "GenericEntity");
		~Entity();
		// Getters
		const String&		GetName() const;
		const Matrix&		GetModelviewMatrix() const;
		Scene*				GetScene();
		const Scene&		GetScene() const;
		Int					GetID() const;
		Bool				IsSpawned() const;
		Bool				HasParent() const;
		Entity*				GetParent();
		const Entity&		GetParent() const;
		Int					GetNumChildren() const;
		Entity*				GetChild(Int index);
		const Entity&		GetChild(Int index) const;
		// Setters
		void	SetName(const String &name);
		void	SetModelviewMatrix(const Matrix &modelviewMatrix);
		void	SetParent(Entity *entity);
		void	Unparent();
		Int		AddChild(Entity *entity);
		void	RemoveChild(Entity *entity);
		void	RemoveChild(Int index);
		// Misc
		void	Spawn();
		void	Despawn();
		void	Update(Long deltaTimeMicroseconds);
		void	Draw();
		// Virtual functions
		virtual Renderable*			GetRenderable()							= 0;
		virtual const Renderable&	GetRenderable() const					= 0;
		virtual PhysicsModel*		GetPhysicsModel()						= 0;
		virtual const PhysicsModel&	GetPhysicsModel() const					= 0;
		virtual void				OnUpdate(Long deltaTimeMicroseconds)	= 0;
		virtual void				OnCollision(Entity *entity)				= 0;
		virtual void				OnSpawn();
		virtual void				OnDespawn();
		virtual void				OnParent();
		virtual void				OnUnparent(Entity *oldParent);
		virtual void				OnChildAdd(Entity *entity, Int childIndex);
		virtual void				OnChildRemove(Entity *entity);
	};
}

#endif // FastEntityHppIncluded
