/******************************************************************************/
/*                                                                            */
/*  SpriteMapLayer.hpp                                                        */
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

#ifndef FastSpriteMapLayerHppIncluded
#define FastSpriteMapLayerHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Entity.hpp>
#include <Fast/SpriteMapCamera.hpp>
#include <Fast/Box2D.hpp>
#include <Fast/Array.hpp>
#include <Fast/SpriteMapChunk.hpp>
#include <Fast/NullRenderable.hpp>
#include <Fast/NullPhysicsModel.hpp>

#define kFastSpriteMapChunkDefaultWidth	128
#define kFastSpriteMapChunkDefaultHeight	128

namespace Fast
{
	class SpriteCollection;
	class String;

	class FastApi SpriteMapLayer : public Entity
	{
	private:
		SpriteCollection		*mSpriteCollection;
		Int						mChunkWidth;
		Int						mChunkHeight;
		Int						mDrawLayer;
		SpriteMapCamera			mCamera;
		Vector2D				mScrollMultiplier;
		Box2D					mSpawnBounds;
		Array<SpriteMapChunk>	mChunks;
		NullRenderable			mRenderable;
		NullPhysicsModel		mPhysicsModel;
		// Private functions
		Int	GetChunkIndexEnclosing(Int x, Int y);
		Int	GetChunkIndexEnclosing(Int x, Int y) const;
		// Hide these functions. No copying entities!
		SpriteMapLayer&	operator=(const SpriteMapLayer &that) { return *this; }
	public:
		// (Con/De)structors
		SpriteMapLayer(Scene *scene, SpriteCollection *spriteCollection,
			const String &name, Int chunkWidth, Int chunkHeight);
		~SpriteMapLayer();
		// Setters
		void	SetTile(Int x, Int y, Short tileType);
		void	SetDrawLayer(Int renderLayer);
		void	SetScrollMultiplier(const Vector2D &scrollMultiplier);
		void	SetSpawnBounds(const Box2D &bounds);
		void	ReplaceAllTilesOfType(Short oldType, Short newType);
		void	AddChunk(const SpriteMapChunk &chunk);
		void	ClearChunks();
		// Getters
		Short					GetTile(Int x, Int y) const;
		Int						GetChunkWidth() const;
		Int						GetChunkHeight() const;
		Int						GetDrawLayer() const;
		const Vector2D&			GetScrollMultiplier() const;
		const Box2D&			GetSpawnBounds() const;
		Int						GetNumChunks() const;
		const SpriteMapChunk&	GetChunk(Int index) const;
		SpriteCollection*		GetSpriteCollection();
		const SpriteCollection&	GetSpriteCollection() const;
		SpriteMapCamera*		GetCamera();
		const SpriteMapCamera&	GetCamera() const;
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

#endif // FastSpriteMapLayerHppIncluded