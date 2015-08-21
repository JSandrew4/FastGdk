/******************************************************************************/
/*                                                                            */
/*  SpriteMap.cpp                                                             */
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

#include <Fast/SpriteMap.hpp>
#include <Fast/SpriteMapLayer.hpp>
#include <Fast/String.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/StreamWriter.hpp>
#include <Fast/Scene.hpp>
#include <Fast/SpriteCollection.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/FileWriter.hpp>
#include <Fast/Box2D.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Error.hpp>
#include <Fast/Exception.hpp>
#include <Fast/Sprite.hpp>

#include "Undefs.hpp"

namespace Fast
{
	namespace SpriteMapVersion0_1
	{
		void Load(SpriteMap *sm, StreamReader *f) {
			// Read in TileTypes
			Short numTileTypes = f->ReadShort();
			for (Int i = 0; i < numTileTypes; i++) {
				String entityTypeName = f->ReadString(f->ReadInt());
				Int entityTypeID =
					sm->GetScene()->GetEntityTypeID(entityTypeName);
				String spriteName = f->ReadString(f->ReadInt());
				sm->AddTileType(SpriteMapTileType(entityTypeName, entityTypeID,
					Sprite(spriteName, sm->GetSpriteCollection())));
			}
			// Read in Layers
			Int numLayers = f->ReadInt();
			for (Int i = 0; i < numLayers; i++) {
				SpriteMapLayer *sml;
				String name;
				Int chunkWidth, chunkHeight;
				Box2D spawnBounds;
				name = f->ReadString(f->ReadInt());
				chunkWidth = f->ReadInt();
				chunkHeight = f->ReadInt();
				sml = new SpriteMapLayer(sm->GetScene(),
					sm->GetSpriteCollection(), name, chunkWidth, chunkHeight);
				sml->SetDrawLayer(f->ReadInt());
				sml->GetCamera()->SetStartingOrigin(f->ReadVector2D());
				sml->GetCamera()->SetStartingRotationDegrees(f->ReadFloat());
				sml->GetCamera()->SetStartingZoom(f->ReadFloat());
				sml->SetScrollMultiplier(f->ReadVector2D());
				spawnBounds.mOrigin.mX = f->ReadFloat();
				spawnBounds.mOrigin.mY = f->ReadFloat();
				spawnBounds.mSize.mX = f->ReadFloat();
				spawnBounds.mSize.mY = f->ReadFloat();
				sml->SetSpawnBounds(spawnBounds);
				// Read in chunks
				Int numChunks = f->ReadInt();
				for (Int j = 0; j < numChunks; j++) {
					SpriteMapChunk smc;
					Point tileOffset;
					Int compressedTilesLength;
					Array<Short> tiles;
					tileOffset.mX = f->ReadInt();
					tileOffset.mY = f->ReadInt();
					compressedTilesLength = f->ReadInt();
					tiles.SetElementCount(compressedTilesLength);
					f->Read((Byte*)&tiles[0], compressedTilesLength);
					smc = SpriteMapChunk(tileOffset,
						chunkWidth, chunkHeight, tiles);
					sml->AddChunk(smc);
				}
				sm->AddLayer(sml);
			}
		}

		void Save(SpriteMap *sm, StreamWriter *f) {
			// Write TileTypes
			f->WriteShort((Short)sm->GetNumTileTypes());
			for (Short i = 0; i < (Short)sm->GetNumTileTypes(); i++) {
				const SpriteMapTileType &smtt = sm->GetTileType(i);
				f->WriteInt(smtt.mEntityTypeName.GetSizeInBytes());
				f->WriteString(smtt.mEntityTypeName, false);
				f->WriteInt(smtt.mSpriteName.GetSizeInBytes());
				f->WriteString(smtt.mSpriteName, false);
			}
			// Write Layers
			f->WriteInt(sm->GetNumLayers());
			for (Int i = 0; i < sm->GetNumLayers(); i++) {
				SpriteMapLayer *sml = sm->GetLayer(i);
				f->WriteInt(sml->GetName().GetSizeInBytes());
				f->WriteString(sml->GetName(), false);
				f->WriteInt(sml->GetChunkWidth());
				f->WriteInt(sml->GetChunkHeight());
				f->WriteInt(sml->GetDrawLayer());
				f->WriteVector2D(sml->GetCamera()->GetStartingOrigin());
				f->WriteFloat(sml->GetCamera()->GetStartingRotationDegrees());
				f->WriteFloat(sml->GetCamera()->GetStartingZoom());
				f->WriteFloat(sml->GetScrollMultiplier().mX);
				f->WriteFloat(sml->GetScrollMultiplier().mY);
				f->WriteFloat(sml->GetSpawnBounds().mOrigin.mX);
				f->WriteFloat(sml->GetSpawnBounds().mOrigin.mY);
				f->WriteFloat(sml->GetSpawnBounds().mSize.mX);
				f->WriteFloat(sml->GetSpawnBounds().mSize.mX);
				// Write Chunks
				f->WriteInt(sml->GetNumChunks());
				for (Int j = 0; j < sml->GetNumChunks(); j++) {
					const SpriteMapChunk &c = sml->GetChunk(j);
					Array<Short> compressedTiles;
					f->WriteInt(c.GetTileOffset().mX);
					f->WriteInt(c.GetTileOffset().mY);
					c.GetCompressedTiles(compressedTiles);
					f->WriteInt(compressedTiles.GetElementCount());
					f->Write((Byte*)&compressedTiles[0],
						compressedTiles.GetElementCount());
				}
			}
		}
	}

	void SpriteMap::Load(StreamReader *streamReader) {
		String magicNumber;
		Version version;
		ErrorType error;
		if (!streamReader->IsOpen()) {
			Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader.mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
			return;
		}
		streamReader->SeekTo(0);
		streamReader->ReadString(&magicNumber, 4);
		if (magicNumber != "CSPM") {
			Error::Throw(kErrorFormatInvalid,
				String("[%s(%p): streamReader.mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
			return;
		}
		version.mMajor = streamReader->ReadInt();
		version.mMinor = streamReader->ReadInt();
		// Read in data by version
		if (version == Version(0,1))
			SpriteMapVersion0_1::Load(this, streamReader);
		else {
			Error::Throw(kErrorFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\" version=(%d, %d)]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString(),
				version.mMajor, version.mMinor));
				return;
		}
		// Check that everything went well
		error = streamReader->GetError();
		if (error)
			Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\" version=(%d, %d)]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString(),
				version.mMajor, version.mMinor));
	}

	SpriteMap::SpriteMap(Scene *scene, SpriteCollection *spriteCollection) :
		Entity(scene, "SpriteMapEntity"),
		mSpriteCollection(*spriteCollection),
		mRenderable()
	{ }

	SpriteMap::SpriteMap(const String &fileName,
		Scene *scene, SpriteCollection *spriteCollection) :
		Entity(scene, "SpriteMapEntity"),
		mSpriteCollection(*spriteCollection),
		mRenderable()
	{
		FileReader f(fileName);
		Load(&f);
	}

	SpriteMap::SpriteMap(StreamReader *streamReader,
		Scene *scene, SpriteCollection *spriteCollection) :
		Entity(scene, "SpriteMapEntity"),
		mSpriteCollection(*spriteCollection),
		mRenderable()
	{
		Load(streamReader);
	}

	SpriteMap::~SpriteMap() { }

	void SpriteMap::AddTileType(
		const SpriteMapTileType &tileType)
	{
		mTileTypes.Append(tileType);
		Int newSize = mTileTypes.GetElementCount() - 1;
		mTileTypes[newSize].mSprite.Load(
			mTileTypes[newSize].mSpriteName, &mSpriteCollection);
	}

	void SpriteMap::InsertTileType(
		const SpriteMapTileType &tileType, Short index)
	{
		if (0 > index || mTileTypes.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %hd): mTileTypes.mSize=%d]",
				FastFunctionName, &tileType, index,
				mTileTypes.GetElementCount()));
		for (Short i = mTileTypes.GetElementCount() - 1; i >= index; i--)
			for (Int j = 0; j < mLayers.GetElementCount(); j++)
				mLayers[j]->ReplaceAllTilesOfType(i, i + 1);
		mTileTypes.Insert(tileType, (Int)index);
		mTileTypes[(Int)index].mSprite.Load(
			mTileTypes[(Int)index].mSpriteName, &mSpriteCollection);
	}

	void SpriteMap::ReplaceTileType(
		const SpriteMapTileType &tileType, Short index)
	{
		if (0 > index || mTileTypes.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %hd): mTileTypes.mSize=%d]",
				FastFunctionName, &tileType, index,
				mTileTypes.GetElementCount()));
		mTileTypes.Replace(tileType, (Int)index);
		for (Int i = 0; i < mLayers.GetElementCount(); i++)
			mLayers[i]->ReplaceAllTilesOfType(index, 0);
		mTileTypes[(Int)index].mSprite.Load(
			mTileTypes[(Int)index].mSpriteName, &mSpriteCollection);
	}

	void SpriteMap::RemoveTileType(Short index) {
		if (0 > index || mTileTypes.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%hd): mTileTypes.mSize=%d]",
				FastFunctionName, index, mTileTypes.GetElementCount()));
		mTileTypes.Erase((Int)index);
		for (Int i = 0; i < mLayers.GetElementCount(); i++)
			mLayers[i]->ReplaceAllTilesOfType(index, 0);
		for (Short j = index+1; j <= (Short)mTileTypes.GetElementCount(); j++)
			for (Int k = 0; k < mLayers.GetElementCount(); k++)
				mLayers[k]->ReplaceAllTilesOfType(j, j - 1);
	}

	void SpriteMap::ClearTileTypes() {
		for (Int i = GetNumTileTypes() - 1; i >= 0; i--)
			RemoveTileType(i);
	}

	void SpriteMap::AddLayer(SpriteMapLayer *layer) {
		mLayers.Append(layer);
		layer->SetParent(this);
		layer->Spawn();
	}

	void SpriteMap::InsertLayer(SpriteMapLayer *layer, Int index) {
		if (0 > index || mLayers.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %d): mLayers.mSize=%d]",
				FastFunctionName, layer, index, mLayers.GetElementCount()));
		mLayers.Insert(layer, index);
		layer->SetParent(this);
		layer->Spawn();
	}

	void SpriteMap::ReplaceLayer(SpriteMapLayer *layer, Int index) {
		if (0 > index || mLayers.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %d): mLayers.mSize=%d]", FastFunctionName,
					layer, index, mLayers.GetElementCount()));
		mLayers[index]->Despawn();
		delete mLayers[index];
		mLayers.Replace(layer, index);
		layer->SetParent(this);
		layer->Spawn();
	}

	void SpriteMap::RemoveLayer(Int index) {
		if (0 > index || mLayers.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): mLayers.mSize=%d]", FastFunctionName,
				index, mLayers.GetElementCount()));
		mLayers.Erase(index);
	}

	void SpriteMap::ClearLayers() {
		for (Int i = GetNumLayers() - 1; i >= 0; i--)
			RemoveLayer(i);
	}

	SpriteCollection* SpriteMap::GetSpriteCollection() {
		return &mSpriteCollection;
	}

	const SpriteCollection& SpriteMap::GetSpriteCollection() const {
		return mSpriteCollection;
	}

	Int SpriteMap::GetNumLayers() const {
		return mLayers.GetElementCount();
	}

	SpriteMapLayer* SpriteMap::GetLayer(Int index) {
		if (0 > index || mLayers.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): mLayers.mSize=%d]", FastFunctionName,
				index, mLayers.GetElementCount()));
		return mLayers[index];
	}

	const SpriteMapLayer& SpriteMap::GetLayer(Int index) const {
		if (0 > index || mLayers.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): mLayers.mSize=%d]",
				FastFunctionName, index, mLayers.GetElementCount()));
		return *mLayers[index];
	}

	Int SpriteMap::GetLayerIndex(const String &name) const {
		for (Int i = 0; i < mLayers.GetElementCount(); i++)
			if (mLayers[i]->GetName() == name)
				return i;
		return -1;
	}

	Int SpriteMap::GetNumTileTypes() const {
		return mTileTypes.GetElementCount();
	}

	const SpriteMapTileType& SpriteMap::GetTileType(Short index) const {
		if (0 > index || mTileTypes.GetElementCount() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%hd): mTileTypes.mSize=%d]",
				FastFunctionName, index, mTileTypes.GetElementCount()));
		return mTileTypes[index];
	}

	Short SpriteMap::GetTileTypeIndexByEntityTypeName(
		const String &entityTypeName) const
	{
		for (Int i = 0; i < mTileTypes.GetElementCount(); i++)
			if (mTileTypes[i].mEntityTypeName == entityTypeName)
				return i;
		return -1;
	}

	Short SpriteMap::GetTileTypeIndexByEntityTypeID(Int entityTypeID) const {
		for (Int i = 0; i < mTileTypes.GetElementCount(); i++)
			if (mTileTypes[i].mEntityTypeID == entityTypeID)
				return i;
		return -1;
	}

	Short SpriteMap::GetTileTypeIndexBySpriteName(
		const String &spriteName) const
	{
		for (Int i = 0; i < mTileTypes.GetElementCount(); i++)
			if (mTileTypes[i].mSprite.GetName() == spriteName)
				return i;
		return -1;
	}

	ErrorType SpriteMap::SaveAs(const String &fileName, const Version &version)
	{
		FileWriter f(fileName);
		ErrorType error = f.GetError();
		if (error)
			return Error::Throw(error, String("[%s(%s, %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		// Write magic number and version
		f.WriteString("CSPM", false);
		f.WriteInt(version.mMajor);
		f.WriteInt(version.mMinor);
		// Write out data by version
		if (version == Version(0,1))
			SpriteMapVersion0_1::Save(this, &f);
		else
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(%s, %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		// Finish up and return
		error = f.GetError();
		if (error)
			return Error::Throw(error, String("[%s(%s, %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		f.Close();
		return kErrorNone;
	}

	Renderable* SpriteMap::GetRenderable() {
		return &mRenderable;
	}

	const Renderable& SpriteMap::GetRenderable() const {
		return mRenderable;
	}

	PhysicsModel* SpriteMap::GetPhysicsModel() {
		return &mPhysicsModel;
	}

	const PhysicsModel& SpriteMap::GetPhysicsModel() const {
		return mPhysicsModel;
	}

	void SpriteMap::OnUpdate(Long deltaTimeMicroseconds) {
		
	}

	void SpriteMap::OnCollision(Entity *entity) {
		
	}

	void SpriteMap::OnSpawn() {
		
	}

	void SpriteMap::OnDespawn() {
		
	}

	void SpriteMap::OnParent() {
		
	}

	void SpriteMap::OnUnparent(Entity *oldParent) {
		
	}

	void SpriteMap::OnChildAdd(Entity *entity, Int childIndex) {
		
	}

	void SpriteMap::OnChildRemove(Entity *entity) {

	}
}