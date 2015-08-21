/******************************************************************************/
/*                                                                            */
/*  SpriteMap.hpp                                                             */
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

#ifndef FastSpriteMapHppIncluded
#define FastSpriteMapHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Array.hpp>
#include <Fast/SpriteMapTileType.hpp>
#include <Fast/Entity.hpp>
#include <Fast/NullRenderable.hpp>
#include <Fast/NullPhysicsModel.hpp>
#include <Fast/Version.hpp>

namespace Fast
{
	class String;
	class StreamReader;
	class Scene;
	class SpriteCollection;
	class SpriteMapLayer;

	class FastApi SpriteMap : public Entity
	{
	private:
		SpriteCollection			&mSpriteCollection;
		Array<SpriteMapTileType>	mTileTypes;
		Array<SpriteMapLayer*>		mLayers;
		NullRenderable				mRenderable;
		NullPhysicsModel			mPhysicsModel;
		// Private functions
		void	Load(StreamReader *streamReader);
		// Hide these functions. No copying entities!
		SpriteMap&	operator=(const SpriteMap &that) { return *this; }
	public:
		// (Con/De)structors
		SpriteMap(Scene *scene, SpriteCollection *spriteCollection);
		SpriteMap(const String &fileName, Scene *scene,
			SpriteCollection *spriteCollection);
		SpriteMap(StreamReader *streamReader, Scene *scene,
			SpriteCollection *spriteCollection);
		~SpriteMap();
		// Modify functions
		void	AddTileType(const SpriteMapTileType &tileType);
		void	InsertTileType(const SpriteMapTileType &tileType, Short index);
		void	ReplaceTileType(const SpriteMapTileType &tileType, Short index);
		void	RemoveTileType(Short index);
		void	ClearTileTypes();
		void	AddLayer(SpriteMapLayer *layer);
		void	InsertLayer(SpriteMapLayer *layer, Int index);
		void	ReplaceLayer(SpriteMapLayer *layer, Int index);
		void	RemoveLayer(Int index);
		void	ClearLayers();
		// Getters
		SpriteCollection*			GetSpriteCollection();
		const SpriteCollection&		GetSpriteCollection() const;
		Int							GetNumLayers() const;
		SpriteMapLayer*				GetLayer(Int index);
		const SpriteMapLayer&		GetLayer(Int index) const;
		Int							GetLayerIndex(const String &name) const;
		Int							GetNumTileTypes() const;
		const SpriteMapTileType&	GetTileType(Short index) const;
		Short						GetTileTypeIndexByEntityTypeName(
										const String &entityTypeName) const;
		Short						GetTileTypeIndexByEntityTypeID(
										Int entityTypeID) const;
		Short						GetTileTypeIndexBySpriteName(
										const String &spriteName) const;
		// Misc
		ErrorType	SaveAs(const String &fileName,
						const Version &version = Version(0, 1));
		// Entity overrides
		Renderable*			GetRenderable();
		const Renderable&	GetRenderable() const;
		PhysicsModel*		GetPhysicsModel();
		const PhysicsModel&	GetPhysicsModel() const;
		void				OnUpdate(Long deltaTimeMicroseconds);
		void				OnCollision(Entity *entity);
		void				OnSpawn();
		void				OnDespawn();
		void				OnParent();
		void				OnUnparent(Entity *oldParent);
		void				OnChildAdd(Entity *entity, Int childIndex);
		void				OnChildRemove(Entity *entity);
	};
}

#endif // FastSpriteMapHppIncluded