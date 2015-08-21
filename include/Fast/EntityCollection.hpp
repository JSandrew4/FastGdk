/******************************************************************************/
/*                                                                            */
/*  EntityCollection.hpp                                                      */
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

#ifndef FastEntityCollectionHppIncluded
#define FastEntityCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/EntityEntry.hpp>

namespace Fast
{
	class GraphicsContext;
	class PhysicsScene;
	class Entity;
	template class FastApi Array<EntityEntry>;

	class FastApi EntityCollection
	{
	private:
		PhysicsScene		&mPhysicsScene;
		Array<EntityEntry>	mEntityEntries;
		// Hide these functions. No copying collections!
		EntityCollection(const EntityCollection &that)
		:	mPhysicsScene(that.mPhysicsScene)
		{}
		EntityCollection& operator=(const EntityCollection &that)
			{ return *this; }
	public:
		// (Con/De)structors
		EntityCollection(PhysicsScene *physicsScene);
		~EntityCollection();
		// Entity functions
		Int					AddEntity(Entity *entity);
		void				RemoveEntity(Int id);
		void				RemoveAllEntities();
		Entity*				GetEntity(Int id);
		const Entity&		GetEntity(Int id) const;
		PhysicsScene*		GetPhysicsScene();
		const PhysicsScene&	GetPhysicsScene() const;
		void				Update(Long deltaTimeMicroseconds);
		void				Draw();
	};
}

#endif // FastEntityCollectionHppIncluded
