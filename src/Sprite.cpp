/******************************************************************************/
/*                                                                            */
/*  Sprite.cpp                                                                */
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

#include <Fast/Sprite.hpp>
#include <Fast/String.hpp>
#include <Fast/SpriteData.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/Texture2DCollection.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/RenderItem.hpp>
#include <Fast/Error.hpp>
#include <Fast/Exception.hpp>
#include <Fast/Texture2DSurface.hpp>
#include <Fast/SpriteCollection.hpp>

#include "OpenGL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	const SpriteData& SpriteGetData(Int id, SpriteCollection *collection) {
		return *collection->GetResource(id)->GetData();
	}

	ErrorType Sprite::LoadResource(const String &name,
		const SpriteData &data, SpriteCollection *collection)
	{
		SpriteResource res;
		//	Cache currently used textures before Unload() call, in case there is
		//		any texture overlap with the new sprite (we don't want to waste
		//		time unloading and reloading textures)
		Array<Texture2DSurface> mBackupTexture2Ds;
		if (-1 < mID && GetCollection())
			mBackupTexture2Ds =
				*GetCollection()->GetResource(mID)->GetTexture2DSurfaceArray();
		Unbind();
		res.SetName(name);
		res.SetActive(true);
		res.SetRetained(false);
		*res.GetData() = data;
		for (Int i = 0; i < data.GetNumTexture2DAndSpriteSheetNames(); i++)
			res.GetTexture2DSurfaceArray()->Append(
				Texture2DSurface(data.GetTexture2DName(i),
				collection->GetTexture2DCollection()));
		mID = collection->AddResource(res, this);
		mCollection = collection;
		return kErrorNone;
	}

	Sprite::Sprite()
	:	AssetImplementer(),
		CustomRenderable2D()
	{
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mAnimationSpeed = 1.0f;
		mDeltaTimeCumulative = 0.0f;
		mBounds = Box2D(0.0f, 0.0f, 1.0f, 1.0f);
		Unbind();
	}

	Sprite::Sprite(const Sprite &that)
	:	AssetImplementer(),
		CustomRenderable2D()
	{
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mAnimationSpeed = 1.0f;
		mDeltaTimeCumulative = 0.0f;
		mBounds = Box2D(0.0f, 0.0f, 1.0f, 1.0f);
		*this = that;
	}

	Sprite::Sprite(const String &fileName, SpriteCollection *collection)
	:	AssetImplementer(),
		CustomRenderable2D()
	{
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mAnimationSpeed = 1.0f;
		mDeltaTimeCumulative = 0.0f;
		mBounds = Box2D(0.0f, 0.0f, 1.0f, 1.0f);
		Load(fileName, collection);
	}

	Sprite::Sprite(StreamReader *streamReader, SpriteCollection *collection)
	:	AssetImplementer(),
		CustomRenderable2D()
	{
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mAnimationSpeed = 1.0f;
		mDeltaTimeCumulative = 0.0f;
		mBounds = Box2D(0.0f, 0.0f, 1.0f, 1.0f);
		Load(streamReader, collection);
	}

	Sprite::Sprite(const SpriteData &data, SpriteCollection *collection)
	:	AssetImplementer(),
		CustomRenderable2D()
	{
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mAnimationSpeed = 1.0f;
		mDeltaTimeCumulative = 0.0f;
		mBounds = Box2D(0.0f, 0.0f, 1.0f, 1.0f);
		Load(data, collection);
	}

	Sprite::~Sprite() {
		Unbind();
	}

	ErrorType Sprite::Load(const String &fileName, SpriteCollection *collection)
	{
		Bind(collection, collection->GetIDByName(fileName));
		if (-1 < mID)
			return kErrorNone;
		// No sprite was found, load the sprite animation data
		SpriteData spriteData;
		ErrorType error = spriteData.Load(fileName);
		if (error)
			return Error::Throw(error,
				String("[%s(\"%s\", %p): spriteData.mName=\"%s\"]",
				FastFunctionName, fileName.GetCString(), collection,
				spriteData.GetName().GetCString()));
		return LoadResource(fileName, spriteData, collection);
	}

	ErrorType Sprite::Load(StreamReader *streamReader,
		SpriteCollection *collection)
	{
		String spriteName = streamReader->GetName();
		Bind(collection, collection->GetIDByName(spriteName));
		// Check for existing sprite animation by this name
		if (-1 < mID)
			return kErrorNone;
		// If no match, load the sprite animation data
		SpriteData spriteData;
		ErrorType error = spriteData.Load(streamReader);
		if (error)
			return Error::Throw(error, String(
				"[%s(%p, %p): streamReader->mName=\"%s\" spriteData.mName=\"%s\"]",
				FastFunctionName, streamReader, collection,
				streamReader->GetName().GetCString(),
				spriteName.GetCString()));
		return LoadResource(spriteName, spriteData, collection);
	}

	ErrorType Sprite::Load(const SpriteData &data, SpriteCollection *collection)
	{
		String spriteName = data.GetName();
		Bind(collection, collection->GetIDByName(spriteName));
		// Check for existing sprite animation by this name
		if (-1 < mID)
			return kErrorNone;
		// If no match, load the sprite animation data
		return LoadResource(spriteName, data, collection);
	}

	void Sprite::Unbind() {
		Bind(NULL, -1);
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mAnimationSpeed = 1.0f;
		mDeltaTimeCumulative = 0.0f;
		mBounds = Box2D(0.0f, 0.0f, 1.0f, 1.0f);
	}

	const Box2D& Sprite::GetBounds() const {
		return mBounds;
	}

	Float Sprite::GetAnimationSpeed() const {
		return mAnimationSpeed;
	}

	Int Sprite::GetCurrentActionIndex() const {
		return mCurrentActionIndex;
	}

	Int Sprite::GetCurrentFrameIndex() const {
		return mCurrentFrameIndex;
	}

	const String& Sprite::GetName() const {
		return SpriteGetData(mID, mCollection).GetName();
	}

	Int Sprite::GetNumTexture2Ds() const {
		return mCollection->GetResource(mID
			)->GetTexture2DSurfaceArray()->GetElementCount();
	}

	const Texture2DSurface& Sprite::GetTexture2D(Int index) const {
		SpriteResource *sres = mCollection->GetResource(mID);
		if (0 > index || sres->GetTexture2DSurfaceArray()->GetElementCount() <=
			index)
		{
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): spriteResource.mTexture2Ds.mSize=%d]",
				FastFunctionName, index,
				sres->GetTexture2DSurfaceArray()->GetElementCount()));
		}
		return mCollection->GetResource(mID
			)->GetTexture2DSurfaceArray()->GetElement(index);
	}

	Int Sprite::GetTexture2DIndex(const String &name) const {
		if (0 > mID)
			return -1;
		for (Int i = 0; i < GetNumTexture2Ds(); i++)
			if (GetTexture2D(i).GetResource().GetName() == name)
				return i;
		return -1;
	}

	Int Sprite::GetNumCollisionModels() const {
		return SpriteGetData(mID, mCollection).GetNumCollisionModels();
	}

	const SpriteCollisionModel& Sprite::GetCollisionModel(Int index) const {
		if (0 > index ||
			SpriteGetData(mID, mCollection).GetNumCollisionModels() <= index)
		{
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): spriteData.mNumCollisionModels=%d]",
				FastFunctionName, index,
				SpriteGetData(mID, mCollection).GetNumCollisionModels()));
		}
		return SpriteGetData(mID, mCollection).GetCollisionModel(index);
	}

	Int Sprite::GetCollisionModelIndex(const String &name) const {
		return SpriteGetData(mID, mCollection).GetCollisionModelIndex(name);
	}

	Int Sprite::GetNumFrameConfigs() const {
		return SpriteGetData(mID, mCollection).GetNumFrameConfigs();
	}

	const SpriteFrameConfig& Sprite::GetFrameConfig(Int index) const {
		if (0 > index ||
			SpriteGetData(mID, mCollection).GetNumFrameConfigs() <= index)
		{
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): spriteData.mNumFrameConfigs=%d]",
				FastFunctionName, index,
				SpriteGetData(mID, mCollection).GetNumFrameConfigs()));
		}
		return SpriteGetData(mID, mCollection).GetFrameConfig(index);
	}

	Int Sprite::GetFrameConfigIndex(const String &name) const {
		return SpriteGetData(mID, mCollection).GetFrameConfigIndex(name);
	}

	Int Sprite::GetNumActions() const {
		return SpriteGetData(mID, mCollection).GetNumActions();
	}

	const SpriteAction& Sprite::GetAction(Int index) const {
		if (0 > index ||
			SpriteGetData(mID, mCollection).GetNumActions() <= index)
		{
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d): spriteData.mNumActions=%d]",
				FastFunctionName, index,
				SpriteGetData(mID, mCollection).GetNumActions()));
		}
		return SpriteGetData(mID, mCollection).GetAction(index);
	}

	Int Sprite::GetActionIndex(const String &name) const {
		return SpriteGetData(mID, mCollection).GetActionIndex(name);
	}

	void Sprite::SetBounds(const Box2D &bounds) {
		mBounds = bounds;
	}

	void Sprite::SetAnimationSpeed(Float animationSpeed) {
		mAnimationSpeed = animationSpeed;
	}

	void Sprite::SetAction(Int actionIndex) {
		if (0 > mID)
			return;
		mCurrentActionIndex = actionIndex;
		mCurrentFrameIndex = 0;
		mDeltaTimeCumulative = 0.0f;
	}

	void Sprite::SetFrame(Int index) {
		mCurrentFrameIndex = index;
		mDeltaTimeCumulative = 0.0f;
	}

	void Sprite::QueueAction(Int actionIndex) {
		if (0 > mID)
			return;
		mCurrentFrameIndex = 0;
		if (mActionQueue.IsEmpty())
			mCurrentActionIndex = actionIndex;
		else
			mActionQueue.Append(actionIndex);
	}

	void Sprite::ClearQueue() {
		mActionQueue.Clear();
		mCurrentActionIndex = 0;
		mCurrentFrameIndex = 0;
		mDeltaTimeCumulative = 0.0f;
	}

	void Sprite::Update(Float deltaTime) {
		if (0 > mID || 0 == mCurrentActionIndex) {
			mDeltaTimeCumulative = 0.0f;
			return;
		}
		// TODO: Interpolate frames if needed (frame.matrix->nextFrame.matrix)
		// Is it time to move to the next frame yet?
		mDeltaTimeCumulative += deltaTime * mAnimationSpeed;
		Float currentFrameDelay = (Float)GetAction(
			mCurrentActionIndex).GetFrame(
			mCurrentFrameIndex).GetDelayMicroseconds();
		if (mDeltaTimeCumulative > currentFrameDelay) {
			mDeltaTimeCumulative -= currentFrameDelay;
			mCurrentFrameIndex++;
			// Is the action over yet?
			if (mCurrentFrameIndex >=
				GetAction(mCurrentActionIndex).GetNumFrames())
			{	// If another action is queued, pop current. Else loop action.
				if (1 < mActionQueue.GetElementCount()) {
					mCurrentActionIndex = mActionQueue[0];
					mActionQueue.Erase(0);
				}
				mCurrentFrameIndex = 0;
			}
		}
	}

	void Sprite::Draw(FrameBufferSurface *surface) {
		if (0 == mCurrentActionIndex)
			return;
		GraphicsContext *gc = GetCollection()->GetGraphicsContext();
		RenderItem ri(surface);
		/* TODO:
		SpriteResource *sr = GetCollection()->GetResource(mID);
		ri.mRenderPreferences = mRenderPreferences;
		ri.mModelviewProjectionMatrix = mModelviewProjectionMatrix;*/
		gc->QueueRenderItem(ri);
		/* FIXME: Old code. We'll hang onto it for a bit longer.
		GraphicsContext *gc =
			mCollection->GetTexture2DCollection()->GetGraphicsContext();
		gc->BindTexture2D(GetCurrentFrameTexture2D());
		glPushMatrix();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			Matrix m = Matrix::CreateTranslation(mPosition3D) *
				Matrix::CreateFromQuaternion(mOrientation) *
				Matrix::CreateScale(mScale3D);
			glMultMatrixf(m.mElements);
			glBegin(GL_TRIANGLES);
				glTexCoord2f(0.0f, 1.0f);
				glVertex2f(mBounds.mOrigin.mX, mBounds.mOrigin.mY);
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(mBounds.mOrigin.mX + mBounds.mSize.mX,
					mBounds.mOrigin.mY);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(mBounds.mOrigin.mX,
					mBounds.mOrigin.mY - mBounds.mSize.mY);
				glTexCoord2f(1.0f, 1.0f);
				glVertex2f(mBounds.mOrigin.mX + mBounds.mSize.mX,
					mBounds.mOrigin.mY);
				glTexCoord2f(1.0f, 0.0f);
				glVertex2f(mBounds.mOrigin.mX + mBounds.mSize.mX,
					mBounds.mOrigin.mY = mBounds.mSize.mY);
				glTexCoord2f(0.0f, 0.0f);
				glVertex2f(mBounds.mOrigin.mX,
					mBounds.mOrigin.mY - mBounds.mSize.mY);
			glEnd();
		glPopMatrix();*/
	}

	Sprite& Sprite::operator=(const Sprite &that) {
		this->Bind(that.mCollection, that.mID);
		return *this;
	}

	Bool Sprite::operator==(const Sprite &that) const {
		if (this->mCollection != that.mCollection)
			return false;
		if (this->mID != that.mID)
			return false;
		return true;
	}

	Bool Sprite::operator!=(const Sprite &that) const {
		if (this->mCollection != that.mCollection)
			return true;
		if (this->mID != that.mID)
			return true;
		return false;
	}
}