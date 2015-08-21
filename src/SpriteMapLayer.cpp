/******************************************************************************/
/*                                                                            */
/*  SpriteMapLayer.cpp                                                        */
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

#include <Fast/SpriteMapLayer.hpp>
#include <Fast/SpriteCollection.hpp>
#include <Fast/Exception.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Int SpriteMapLayer::GetChunkIndexEnclosing(Int x, Int y) {
		for (Int i = 0; i < mChunks.GetElementCount(); i++)
			if (mChunks[i].Encloses(x, y))
				return i;
		// If no chunk exists for this point, make a new one
		SpriteMapChunk newChunk = SpriteMapChunk(Point(
			x - (x % mChunkWidth),
			y - (y % mChunkHeight)), mChunkWidth, mChunkHeight);
		mChunks.Append(newChunk);
		return mChunks.GetElementCount() - 1;
	}

	Int SpriteMapLayer::GetChunkIndexEnclosing(Int x, Int y) const {
		for (Int i = 0; i < mChunks.GetElementCount(); i++)
			if (mChunks[i].Encloses(x, y))
				return i;
		return -1;
	}

	SpriteMapLayer::SpriteMapLayer(Scene *scene,
		SpriteCollection *spriteCollection, const String &name,
		Int chunkWidth, Int chunkHeight) :
		Entity(scene, name),
		mRenderable()
	{
		mSpriteCollection = spriteCollection;
		mChunkWidth = chunkWidth;
		mChunkHeight = chunkHeight;
		mScrollMultiplier = 1.0f;
		mDrawLayer = 0;
	}

	SpriteMapLayer::~SpriteMapLayer() { }

	void SpriteMapLayer::SetTile(Int x, Int y, Short tileType) {
		mChunks[GetChunkIndexEnclosing(x, y)].SetTile(x, y, tileType);
	}

	void SpriteMapLayer::SetDrawLayer(Int drawLayer) {
		mDrawLayer = drawLayer;
		for (Int i = 0; i < GetNumChildren(); i++)
			GetChild(i)->GetRenderable()->GetRenderPreferences()->SetDrawLayer(
				mDrawLayer);
	}

	void SpriteMapLayer::SetScrollMultiplier(const Vector2D &scrollMultiplier) {
		mScrollMultiplier = scrollMultiplier;
	}

	void SpriteMapLayer::SetSpawnBounds(const Box2D &bounds) {
		mSpawnBounds = bounds;
	}

	void SpriteMapLayer::ReplaceAllTilesOfType(Short oldType, Short newType) {
		for (Int i = 0; i < mChunks.GetElementCount(); i++)
			mChunks[i].ReplaceAllTilesOfType(oldType, newType);
	}

	void SpriteMapLayer::AddChunk(const SpriteMapChunk &chunk) {
		if (chunk.GetWidth() != mChunkWidth ||
			chunk.GetHeight() != mChunkHeight)
		{
			return;
		}
		for (Int i = 0; i < mChunks.GetElementCount(); i++) {
			if (mChunks[i].GetTileOffset() == chunk.GetTileOffset()) {
				mChunks[i] = chunk;
				return;
			}
		}
		mChunks.Append(chunk);
	}

	void SpriteMapLayer::ClearChunks() {
		mChunks.Clear();
	}

	Short SpriteMapLayer::GetTile(Int x, Int y) const {
		Int chunkIndex = GetChunkIndexEnclosing(x, y);
		if (0 > chunkIndex)
			return 0;
		return mChunks[chunkIndex].GetTile(x, y);
	}

	Int SpriteMapLayer::GetChunkWidth() const {
		return mChunkWidth;
	}

	Int SpriteMapLayer::GetChunkHeight() const {
		return mChunkHeight;
	}

	Int SpriteMapLayer::GetDrawLayer() const {
		return mDrawLayer;
	}

	const Vector2D& SpriteMapLayer::GetScrollMultiplier() const {
		return mScrollMultiplier;
	}

	const Box2D& SpriteMapLayer::GetSpawnBounds() const {
		return mSpawnBounds;
	}

	Int SpriteMapLayer::GetNumChunks() const {
		return mChunks.GetElementCount();
	}

	const SpriteMapChunk& SpriteMapLayer::GetChunk(Int index) const {
		if (0 > index || mChunks.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange, String("(%s: %d)",
				FastFunctionName, index));
		return mChunks[index];
	}

	SpriteCollection* SpriteMapLayer::GetSpriteCollection() {
		return mSpriteCollection;
	}

	const SpriteCollection& SpriteMapLayer::GetSpriteCollection() const {
		return *mSpriteCollection;
	}

	SpriteMapCamera* SpriteMapLayer::GetCamera() {
		return &mCamera;
	}

	const SpriteMapCamera& SpriteMapLayer::GetCamera() const {
		return mCamera;
	}

	Renderable* SpriteMapLayer::GetRenderable() {
		return &mRenderable;
	}

	const Renderable& SpriteMapLayer::GetRenderable() const {
		return mRenderable;
	}

	PhysicsModel* SpriteMapLayer::GetPhysicsModel() {
		return &mPhysicsModel;
	}

	const PhysicsModel& SpriteMapLayer::GetPhysicsModel() const {
		return mPhysicsModel;
	}

	void SpriteMapLayer::OnUpdate(Long deltaTimeMicroseconds) {
		// TODO: Spawn tile entities as they enter spawn area.
		//	We need a way to track which tiles have already been spawned.
	}

	void SpriteMapLayer::OnCollision(Entity *entity) {
		
	}

	void SpriteMapLayer::OnSpawn() {
		
	}

	void SpriteMapLayer::OnDespawn() {
		
	}

	void SpriteMapLayer::OnParent() {
		
	}

	void SpriteMapLayer::OnUnparent(Entity *oldParent) {
		
	}

	void SpriteMapLayer::OnChildAdd(Entity *entity, Int childIndex) {
		
	}

	void SpriteMapLayer::OnChildRemove(Entity *entity) {

	}
}