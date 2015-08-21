/******************************************************************************/
/*                                                                            */
/*  SpriteData.cpp                                                            */
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

#include <Fast/SpriteData.hpp>
#include <Fast/Error.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/StreamWriter.hpp>
#include <Fast/FileReader.hpp>
#include <Fast/FileWriter.hpp>
#include <Fast/Exception.hpp>

#include "Undefs.hpp"

namespace Fast
{
	namespace SpriteDataVersion0_1
	{
		void Load(SpriteData *sd, StreamReader *f) {
			Int i, j;
			// Load Texture2DSurface Names
			Int numTexture2DNames = f->ReadInt();
			for (i = 0; i < numTexture2DNames; i++) {
				String texture2DName, spriteSheetName;
				f->ReadString(&texture2DName, f->ReadInt());
				f->ReadString(&spriteSheetName, f->ReadInt());
				sd->AddTexture2DAndSpriteSheetNames(
					texture2DName, spriteSheetName);
			}
			// Load Collision Models
			Int numCollisionModels = f->ReadInt();
			for (i = 0; i < numCollisionModels; i++) {
				SpriteCollisionModel scm;
				scm.SetName(f->ReadString(f->ReadInt()));
				// Load Triangles
				Int numTriangles = f->ReadInt();
				for (Int j = 0; j < numTriangles; j++) {
					SpriteCollisionTriangle sct;
					f->ReadVector2D(&sct.mComponentA);
					f->ReadVector2D(&sct.mComponentB);
					f->ReadVector2D(&sct.mComponentC);
					scm.AddTriangle(sct);
				}
				// Load Circles
				Int numCircles = f->ReadInt();
				for (Int k = 0; k < numCircles; k++) {
					Circle circle;
					f->ReadVector2D(&circle.mOrigin);
					circle.mRadius = f->ReadFloat();
					scm.AddCircle(circle);
				}
				sd->AddCollisionModel(scm);
			}
			// Load Frame Configs
			Int numFrameConfigs = f->ReadInt();
			for (i = 0; i < numFrameConfigs; i++) {
				SpriteFrameConfig sfc;
				sfc.SetName(f->ReadString(f->ReadInt()));
				sfc.SetTexture2DIndex(f->ReadInt());
				sfc.SetCollisionModelIndex(f->ReadInt());
				sfc.SetOffset(f->ReadVector2D());
				sfc.SetScale(f->ReadVector2D());
				sfc.SetRotationDegrees(f->ReadFloat());
				sfc.SetFlipX(f->ReadBool());
				sfc.SetFlipY(f->ReadBool());
				sd->AddFrameConfig(sfc);
			}
			// Load Actions
			Int numActions = f->ReadInt();
			for (i = 0; i < numActions; i++) {
				SpriteAction sa;
				sa.SetName(f->ReadString(f->ReadInt()));
				// Load Frames
				Int numFrames = f->ReadInt();
				for (j = 0; j < numFrames; j++) {
					SpriteFrame sf;
					sf.SetName(f->ReadString(f->ReadInt()));
					sf.SetFrameConfigIndex(f->ReadInt());
					sf.SetDelayMicroseconds(f->ReadLong());
					sf.SetInterpType(f->ReadInt());
					sa.AddFrame(sf);
				}
				sd->AddAction(sa);
			}
		}

		void Save(SpriteData *sd, StreamWriter *f) {
			Int i, j;
			// Write Texture2DSurface and SpriteSheet names
			f->WriteInt(sd->GetNumTexture2DAndSpriteSheetNames());
			for (i = 0; i < sd->GetNumTexture2DAndSpriteSheetNames(); i++) {
				f->WriteInt(sd->GetTexture2DName(i).GetSizeInBytes());
				f->WriteString(sd->GetTexture2DName(i), false);
				f->WriteInt(sd->GetSpriteSheetName(i).GetSizeInBytes());
				f->WriteString(sd->GetSpriteSheetName(i), false);
			}
			// Write CollisionModels
			f->WriteInt(sd->GetNumCollisionModels());
			for (i = 0; i < sd->GetNumCollisionModels(); i++) {
				f->WriteInt(
					sd->GetCollisionModel(i)->GetName().GetSizeInBytes());
				f->WriteString(sd->GetCollisionModel(i)->GetName(), false);
				// Write Triangles
				f->WriteInt(sd->GetCollisionModel(i)->GetNumTriangles());
				for (j = 0;
					j < sd->GetCollisionModel(i)->GetNumTriangles(); j++)
				{
					f->WriteVector2D(
						sd->GetCollisionModel(i)->GetTriangle(j)->mComponentA);
					f->WriteVector2D(
						sd->GetCollisionModel(i)->GetTriangle(j)->mComponentB);
					f->WriteVector2D(
						sd->GetCollisionModel(i)->GetTriangle(j)->mComponentC);
				}
				// Write Circles
				f->WriteInt(sd->GetCollisionModel(i)->GetNumCircles());
				for (j = 0; j < sd->GetCollisionModel(i)->GetNumCircles(); j++)
				{
					f->WriteVector2D(
						sd->GetCollisionModel(i)->GetCircle(j)->mOrigin);
					f->WriteFloat(
						sd->GetCollisionModel(i)->GetCircle(j)->mRadius);
				}
			}
			// Write FrameConfigs
			f->WriteInt(sd->GetNumFrameConfigs());
			for (i = 0; i < sd->GetNumFrameConfigs(); i++) {
				f->WriteInt(sd->GetFrameConfig(i)->GetName().GetSizeInBytes());
				f->WriteString(sd->GetFrameConfig(i)->GetName(), false);
				f->WriteInt(sd->GetFrameConfig(i)->GetTexture2DIndex());
				f->WriteInt(sd->GetFrameConfig(i)->GetCollisionModelIndex());
				f->WriteVector2D(sd->GetFrameConfig(i)->GetOffset());
				f->WriteVector2D(sd->GetFrameConfig(i)->GetScale());
				f->WriteFloat(sd->GetFrameConfig(i)->GetRotationDegrees());
				f->WriteBool(sd->GetFrameConfig(i)->IsXFlipped());
				f->WriteBool(sd->GetFrameConfig(i)->IsYFlipped());
			}
			// Write Actions
			f->WriteInt(sd->GetNumActions());
			for (i = 0; i < sd->GetNumActions(); i++) {
				f->WriteInt(sd->GetAction(i)->GetName().GetSizeInBytes());
				f->WriteString(sd->GetAction(i)->GetName(), false);
				// Write Frames
				f->WriteInt(sd->GetAction(i)->GetNumFrames());
				for (j = 0; j < sd->GetAction(i)->GetNumFrames(); j++) {
					f->WriteInt(sd->GetAction(i)->GetFrame(
						j)->GetName().GetSizeInBytes());
					f->WriteString(sd->GetAction(
						i)->GetFrame(j)->GetName(), false);
					f->WriteInt(sd->GetAction(
						i)->GetFrame(j)->GetFrameConfigIndex());
					f->WriteLong(sd->GetAction(
						i)->GetFrame(j)->GetDelayMicroseconds());
					f->WriteInt(sd->GetAction(
						i)->GetFrame(j)->GetInterpType());
				}
			}
		}
	}

	SpriteData::SpriteData() {
		Unload();
	}

	SpriteData::SpriteData(const SpriteData &that) {
		Unload();
		*this = that;
	}

	SpriteData::SpriteData(const String &fileName) {
		Unload();
		Load(fileName);
	}

	SpriteData::SpriteData(StreamReader *streamReader) {
		Unload();
		Load(streamReader);
	}

	SpriteData::~SpriteData() {
		Unload();
	}

	ErrorType SpriteData::Load(const String &fileName) {
		FileReader f(fileName);
		ErrorType error = f.GetError();
		if (error)
			return Error::Throw(error, String("[%s(\"%s\")]",
				FastFunctionName, fileName.GetCString()));
		return Load(&f);
	}

	ErrorType SpriteData::Load(StreamReader *streamReader) {
		ErrorType error;
		if (!streamReader->IsOpen()) {
			Unload();
			return Error::Throw(kErrorFileNotFound,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		streamReader->SeekTo(0);
		// Read magic number and version
		String magicNumber;
		Version version;
		streamReader->ReadString(&magicNumber, 4);
		if (magicNumber != "CSPA") {
			Unload();
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(%p): streamReaeder.mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		version.mMajor = streamReader->ReadInt();
		version.mMinor = streamReader->ReadInt();
		// Load in data by Version
		if (version == Version(0,1))
			SpriteDataVersion0_1::Load(this, streamReader);
		else {
			Unload();
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		// Check that everything went well and return
		error = streamReader->GetError();
		if (error) {
			Unload();
			return Error::Throw(error,
				String("[%s(%p): streamReader->mName=\"%s\"]",
				FastFunctionName, streamReader,
				streamReader->GetName().GetCString()));
		}
		return kErrorNone;
	}

	void SpriteData::Unload() {
		mTexture2DNames.Clear();
		mCollisionModels.Clear();
		mFrameConfigs.Clear();
		mActions.Clear();
	}

	void SpriteData::AddTexture2DAndSpriteSheetNames(
		const String &texture2DName, const String &spriteSheetName)
	{
		mTexture2DNames.Append(texture2DName);
		mSpriteSheetNames.Append(spriteSheetName);
	}

	void SpriteData::InsertTexture2DAndSpriteSheetNames(
		const String &texture2DName, const String &spriteSheetName, Int index)
	{
		if (0 > index || GetNumTexture2DAndSpriteSheetNames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(\"%s\", \"%s\", %d)]",
				FastFunctionName, texture2DName.GetCString(),
				spriteSheetName.GetCString(), index));
		mTexture2DNames.Insert(texture2DName, index);
		mSpriteSheetNames.Insert(spriteSheetName, index);
		for (Int i = 0; i < GetNumFrameConfigs(); i++)
			if (GetFrameConfig(i)->GetTexture2DIndex() >= index)
				GetFrameConfig(i)->SetTexture2DIndex(
					GetFrameConfig(i)->GetTexture2DIndex() + 1);
	}

	void SpriteData::ReplaceTexture2DAndSpriteSheetNames(
		const String &texture2DName, const String &spriteSheetName, Int index)
	{
		if (0 > index || GetNumTexture2DAndSpriteSheetNames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(\"%s\", \"%s\", %d)]",
				FastFunctionName, texture2DName.GetCString(),
				spriteSheetName.GetCString(), index));
		mTexture2DNames.Replace(texture2DName, index);
		mSpriteSheetNames.Replace(spriteSheetName, index);
		for (Int i = 0; i < GetNumFrameConfigs(); i++)
			if (GetFrameConfig(i)->GetTexture2DIndex() == index)
				GetFrameConfig(i)->SetTexture2DIndex(0);
	}

	void SpriteData::EraseTexture2DAndSpriteSheetNames(Int index) {
		if (0 > index || GetNumTexture2DAndSpriteSheetNames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		mTexture2DNames.Erase(index);
		mSpriteSheetNames.Erase(index);
		for (Int i = 0; i < GetNumFrameConfigs(); i++) {
			if (GetFrameConfig(i)->GetTexture2DIndex() == index)
				GetFrameConfig(i)->SetTexture2DIndex(0);
			if (GetFrameConfig(i)->GetTexture2DIndex() > index)
				GetFrameConfig(i)->SetTexture2DIndex(
					GetFrameConfig(i)->GetTexture2DIndex() - 1);
		}
	}

	void SpriteData::ClearTexture2DAndSpriteSheetNames() {
		for (Int i = GetNumTexture2DAndSpriteSheetNames() - 1; i >= 0; i--)
			EraseTexture2DAndSpriteSheetNames(i);
	}

	void SpriteData::AddCollisionModel(
		const SpriteCollisionModel &collisionModel)
	{
		mCollisionModels.Append(collisionModel);
	}

	void SpriteData::InsertCollisionModel(
		const SpriteCollisionModel &collisionModel, Int index)
	{
		if (0 > index || GetNumCollisionModels() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %d)]", FastFunctionName,
				&collisionModel, index));
		mCollisionModels.Insert(collisionModel, index);
		for (Int i = 0; i < GetNumFrameConfigs(); i++)
			if (GetFrameConfig(i)->GetCollisionModelIndex() >= index)
				GetFrameConfig(i)->SetCollisionModelIndex(
					GetFrameConfig(i)->GetCollisionModelIndex() + 1);
	}

	void SpriteData::ReplaceCollisionModel(
		const SpriteCollisionModel &collisionModel, Int index)
	{
		if (0 > index || GetNumCollisionModels() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %d)]", FastFunctionName,
				&collisionModel, index));
		mCollisionModels.Replace(collisionModel, index);
		for (Int i = 0; i < GetNumFrameConfigs(); i++)
			if (GetFrameConfig(i)->GetCollisionModelIndex() == index)
				GetFrameConfig(i)->SetCollisionModelIndex(0);
	}

	void SpriteData::EraseCollisionModel(Int index) {
		if (0 > index || GetNumCollisionModels() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%d)]", FastFunctionName, index));
		mCollisionModels.Erase(index);
		for (Int i = 0; i < GetNumFrameConfigs(); i++) {
			if (GetFrameConfig(i)->GetCollisionModelIndex() == index)
				GetFrameConfig(i)->SetCollisionModelIndex(0);
			if (GetFrameConfig(i)->GetCollisionModelIndex() > index)
				GetFrameConfig(i)->SetCollisionModelIndex(
					GetFrameConfig(i)->GetCollisionModelIndex() - 1);
		}
	}

	void SpriteData::ClearCollisionModels() {
		for (Int i = GetNumCollisionModels() - 1; i >= 0; i--)
			EraseCollisionModel(i);
	}

	void SpriteData::AddFrameConfig(const SpriteFrameConfig &frameConfig) {
		mFrameConfigs.Append(frameConfig);
	}

	void SpriteData::InsertFrameConfig(
		const SpriteFrameConfig &frameConfig, Int index)
	{
		if (0 > index || GetNumFrameConfigs() <= index)
			Exception::Throw(kExceptionOutOfRange,
				String("[%s(%p, %d)]", FastFunctionName,
				&frameConfig, index));
		mFrameConfigs.Insert(frameConfig, index);
		for (Int i = 0; i < GetNumActions(); i++)
			for (Int j = 0; j < GetAction(i)->GetNumFrames(); j++)
				if (GetAction(i)->GetFrame(j)->GetFrameConfigIndex() >= index)
					GetAction(i)->GetFrame(j)->SetFrameConfigIndex(
						GetAction(i)->GetFrame(j)->GetFrameConfigIndex() + 1);
	}

	void SpriteData::ReplaceFrameConfig(
		const SpriteFrameConfig &frameConfig, Int index)
	{
		if (0 > index || GetNumFrameConfigs() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%p, %d)]",
				FastFunctionName, &frameConfig, index));
		mFrameConfigs.Replace(frameConfig, index);
		for (Int i = 0; i < GetNumActions(); i++)
			for (Int j = 0; j < GetAction(i)->GetNumFrames(); j++)
				if (GetAction(i)->GetFrame(j)->GetFrameConfigIndex() == index)
					GetAction(i)->GetFrame(j)->SetFrameConfigIndex(0);
	}

	void SpriteData::EraseFrameConfig(Int index) {
		if (0 > index || GetNumFrameConfigs() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		mFrameConfigs.Erase(index);
		for (Int i = 0; i < GetNumActions(); i++) {
			for (Int j = 0; j < GetAction(i)->GetNumFrames(); j++) {
				if (GetAction(i)->GetFrame(j)->GetFrameConfigIndex() == index)
					GetAction(i)->GetFrame(j)->SetFrameConfigIndex(0);
				if (GetAction(i)->GetFrame(j)->GetFrameConfigIndex() > index)
					GetAction(i)->GetFrame(j)->SetFrameConfigIndex(
						GetAction(i)->GetFrame(j)->GetFrameConfigIndex() - 1);
			}
		}
	}

	void SpriteData::ClearFrameConfigs() {
		for (Int i = GetNumFrameConfigs() - 1; i >= 0; i--)
			EraseFrameConfig(i);
	}

	void SpriteData::AddAction(const SpriteAction &action) {
		mActions.Append(action);
	}

	void SpriteData::InsertAction(
		const SpriteAction &action, Int index)
	{
		if (0 > index || GetNumActions() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%p, %d)]",
				FastFunctionName, &action, index));
		mActions.Insert(action, index);
	}

	void SpriteData::ReplaceAction(
		const SpriteAction &action, Int index)
	{
		if (0 > index || GetNumActions() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%p, %d)]",
				FastFunctionName, &action, index));
		mActions.Replace(action, index);
	}

	void SpriteData::EraseAction(Int index) {
		if (0 > index || GetNumActions() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		mActions.Erase(index);
	}

	void SpriteData::ClearActions() {
		for (Int i = GetNumActions() - 1; i >= 0; i--)
			EraseAction(i);
	}

	Int SpriteData::GetNumTexture2DAndSpriteSheetNames() const {
		return mTexture2DNames.GetElementCount();
	}

	const String& SpriteData::GetTexture2DName(Int index) const {
		if (0 > index || GetNumTexture2DAndSpriteSheetNames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return mTexture2DNames[index];
	}

	Int SpriteData::GetTexture2DNameIndex(const String &name) const {
		for (Int i = 0; i < GetNumTexture2DAndSpriteSheetNames(); i++)
			if (GetTexture2DName(i) == name)
				return i;
		return -1;
	}

	const String& SpriteData::GetSpriteSheetName(Int index) const {
		if (0 > index || GetNumTexture2DAndSpriteSheetNames() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return mSpriteSheetNames[index];
	}

	Int SpriteData::GetSpriteSheetNameIndex(const String &name) const {
		for (Int i = 0; i < GetNumTexture2DAndSpriteSheetNames(); i++)
			if (GetSpriteSheetName(i) == name)
				return i;
		return -1;
	}

	Int SpriteData::GetNumCollisionModels() const {
		return mCollisionModels.GetElementCount();
	}

	SpriteCollisionModel* SpriteData::GetCollisionModel(Int index) {
		if (0 > index || GetNumCollisionModels() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return &mCollisionModels[index];
	}

	const SpriteCollisionModel& SpriteData::GetCollisionModel(Int index) const {
		if (0 > index || GetNumCollisionModels() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return mCollisionModels[index];
	}

	Int SpriteData::GetCollisionModelIndex(const String &name) const {
		for (Int i = 0; i < GetNumCollisionModels(); i++)
			if (GetCollisionModel(i).GetName() == name)
				return i;
		return -1;
	}

	Int SpriteData::GetNumFrameConfigs() const {
		return mFrameConfigs.GetElementCount();
	}

	SpriteFrameConfig* SpriteData::GetFrameConfig(Int index) {
		if (0 > index || GetNumFrameConfigs() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return &mFrameConfigs[index];
	}

	const SpriteFrameConfig& SpriteData::GetFrameConfig(Int index) const {
		if (0 > index || GetNumFrameConfigs() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return mFrameConfigs[index];
	}

	Int SpriteData::GetFrameConfigIndex(const String &name) const {
		for (Int i = 0; i < GetNumFrameConfigs(); i++)
			if (GetFrameConfig(i).GetName() == name)
				return i;
		return -1;
	}

	Int SpriteData::GetNumActions() const {
		return mActions.GetElementCount();
	}

	SpriteAction* SpriteData::GetAction(Int index) {
		if (0 > index || GetNumActions() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return &mActions[index];
	}

	const SpriteAction& SpriteData::GetAction(Int index) const {
		if (0 > index || GetNumActions() <= index)
			Exception::Throw(kExceptionOutOfRange, String("[%s(%d)]",
				FastFunctionName, index));
		return mActions[index];
	}

	Int SpriteData::GetActionIndex(const String &name) const {
		for (Int i = 0; i < GetNumActions(); i++)
			if (GetAction(i).GetName() == name)
				return i;
		return -1;
	}

	ErrorType SpriteData::SaveAs(const String &fileName, const Version &version)
	{
		FileWriter f(fileName);
		ErrorType error = f.GetError();
		if (error)
			return Error::Throw(error,
				String("[%s(\"%s\", %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		// Write magic number and version
		f.WriteString("CSPA", false);
		f.WriteInt(version.mMajor);
		f.WriteInt(version.mMinor);
		// Write data by version
		if (version == Version(0,1))
			SpriteDataVersion0_1::Save(this, &f);
		else
			return Error::Throw(kErrorFormatInvalid,
				String("[%s(\"%s\", %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		// Finish up and return
		error = f.GetError();
		if (error)
			return Error::Throw(error,
				String("[%s(\"%s\", %p): version=(%d, %d)]",
				FastFunctionName, fileName.GetCString(), &version,
				version.mMajor, version.mMinor));
		f.Close();
		return kErrorNone;
	}

	SpriteData& SpriteData::operator=(const SpriteData &that) {
		this->mTexture2DNames = that.mTexture2DNames;
		this->mCollisionModels = that.mCollisionModels;
		this->mFrameConfigs = that.mFrameConfigs;
		this->mActions = that.mActions;
		return *this;
	}

	Bool SpriteData::operator==(const SpriteData &that) const {
		if (this->mTexture2DNames.GetElementCount() !=
			that.mTexture2DNames.GetElementCount())
		{
			return false;
		}
		if (this->mCollisionModels.GetElementCount() !=
			that.mCollisionModels.GetElementCount())
		{
			return false;
		}
		if (this->mFrameConfigs.GetElementCount() !=
			that.mFrameConfigs.GetElementCount())
		{
			return false;
		}
		if (this->mActions.GetElementCount() != that.mActions.GetElementCount())
			return false;
		for (Int i = 0; i < this->mTexture2DNames.GetElementCount(); i++)
			if (this->mTexture2DNames[i] != that.mTexture2DNames[i])
				return false;
		for (Int i = 0; i < this->mCollisionModels.GetElementCount(); i++)
			if (this->mCollisionModels[i] != that.mCollisionModels[i])
				return false;
		for (Int i = 0; i < this->mFrameConfigs.GetElementCount(); i++)
			if (this->mFrameConfigs[i] != that.mFrameConfigs[i])
				return false;
		for (Int i = 0; i < this->mActions.GetElementCount(); i++)
			if (this->mActions[i] != that.mActions[i])
				return false;
		return true;
	}

	Bool SpriteData::operator!=(const SpriteData &that) const {
		if (this->mTexture2DNames.GetElementCount() !=
			that.mTexture2DNames.GetElementCount())
		{
			return false;
		}
		if (this->mCollisionModels.GetElementCount() !=
			that.mCollisionModels.GetElementCount())
		{
			return false;
		}
		if (this->mFrameConfigs.GetElementCount() !=
			that.mFrameConfigs.GetElementCount())
		{
			return false;
		}
		if (this->mActions.GetElementCount() != that.mActions.GetElementCount())
			return true;
		for (Int i = 0; i < this->mTexture2DNames.GetElementCount(); i++)
			if (this->mTexture2DNames[i] != that.mTexture2DNames[i])
				return true;
		for (Int i = 0; i < this->mCollisionModels.GetElementCount(); i++)
			if (this->mCollisionModels[i] != that.mCollisionModels[i])
				return true;
		for (Int i = 0; i < this->mFrameConfigs.GetElementCount(); i++)
			if (this->mFrameConfigs[i] != that.mFrameConfigs[i])
				return true;
		for (Int i = 0; i < this->mActions.GetElementCount(); i++)
			if (this->mActions[i] != that.mActions[i])
				return true;
		return false;
	}
}