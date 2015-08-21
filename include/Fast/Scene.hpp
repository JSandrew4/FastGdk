/******************************************************************************/
/*                                                                            */
/*  Scene.hpp                                                                 */
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

#ifndef FastSceneHppIncluded
#define FastSceneHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/EntityEntry.hpp>

namespace Fast
{
	class PhysicsContext;
	class GraphicsContext;
	class Entity;

	class FastApi Scene
	{
	private:
		PhysicsContext		*mPhysicsContext;
		GraphicsContext		&mGraphicsContext;
		Array<EntityEntry>	mEntityEntries;
		Int					mNumActiveEntities;
		// Hide these functions. No copying collections!
		Scene(const Scene &that) : mPhysicsContext(that.mPhysicsContext),
			mGraphicsContext(that.mGraphicsContext)
			{ }
		Scene& operator=(const Scene &that)
			{ return *this; }
	public:
		// (Con/De)structors
		Scene(GraphicsContext *graphicsContext);
		~Scene();
		// Entity functions
		Int						AddEntity(Entity *entity);
		void					DeleteEntity(Int id);
		void					DeleteAllEntities();
		void					RemoveEntity(Int id);
		Int						GetNumEntities() const;
		Bool					IsEntity(Int entityID) const;
		Entity*					GetEntity(Int id);
		const Entity&			GetEntity(Int id) const;
		PhysicsContext*			GetPhysicsContext();
		const PhysicsContext&	GetPhysicsContext() const;
		GraphicsContext*		GetGraphicsContext();
		const GraphicsContext&	GetGraphicsContext() const;
		void					Update(Long deltaTimeMicroseconds);
		void					Draw();
		// Virtual functions
		virtual Entity*			CreateEntity(Int entityTypeID)				= 0;
		virtual Entity*			CreateEntity(const String &entityTypeName)	= 0;
		virtual Int				GetEntityTypeID(
									const String &entityTypeName) const		= 0;
		virtual const String&	GetEntityTypeName(Int entityTypeID) const	= 0;
	};
}

#endif // FastSceneHppIncluded
