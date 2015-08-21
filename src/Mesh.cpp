/******************************************************************************/
/*                                                                            */
/*  Mesh.cpp                                                                  */
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

#include <Fast/Mesh.hpp>
#include <Fast/Model.hpp>
#include <Fast/Matrix.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Mesh::Mesh() {
		mModel = 0;
		mIndex = 0;
	}

	Mesh::Mesh(Model *model, Int index, const MeshRenderPreferences &prefs) {
		mModel = model;
		mIndex = index;
		mRenderPreferences = prefs;
	}

	Mesh::Mesh(const Mesh &that) {
		*this = that;
	}

	Mesh::~Mesh() { }

	Model* Mesh::GetModel() {
		return mModel;
	}

	Int Mesh::GetIndex() const {
		return mIndex;
	}

	const Matrix& Mesh::GetMatrix() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[mIndex].mMatrix;
	}

	MeshRenderPreferences* Mesh::GetRenderPreferences() {
		return &mRenderPreferences;
	}

	const MeshRenderPreferences& Mesh::GetRenderPreferences() const {
		return mRenderPreferences;
	}

	const MeshRenderPreferences& Mesh::GetRenderPreferenceDefaults() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[
			mIndex].mRenderPreferenceDefaults;
	}

	Int Mesh::GetNumVertices() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[
			mIndex].mNumVertices;
	}

	Int Mesh::GetNumFaces() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[
			mIndex].mNumFaces;
	}

	UInt Mesh::GetOpenGLVertexBufferID() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[
			mIndex].mOpenGLVertexBufferID;
	}

	UInt Mesh::GetOpenGLIndexBufferID() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[
			mIndex].mOpenGLIndexBufferID;
	}

	UInt Mesh::GetOpenGLVertexArrayID() const {
		return mModel->GetCollection()->GetResource(
			mModel->GetID())->mMeshResources[
			mIndex].mOpenGLVertexArrayID;
	}

	void Mesh::Draw2D() {
		// TODO
	}

	void Mesh::Draw3D() {
		// TODO
	}

	Mesh& Mesh::operator= (const Mesh &that) {
		this->mModel = that.mModel;
		this->mIndex = that.mIndex;
		this->mRenderPreferences = that.mRenderPreferences;
		return *this;
	}

	Bool Mesh::operator==(const Mesh &that) const {
		if (this->mModel != that.mModel)
			return false;
		if (this->mIndex != that.mIndex)
			return false;
		if (this->mRenderPreferences != that.mRenderPreferences)
			return false;
		return true;
	}

	Bool Mesh::operator!=(const Mesh &that) const {
		if (this->mModel != that.mModel)
			return true;
		if (this->mIndex != that.mIndex)
			return true;
		if (this->mRenderPreferences != that.mRenderPreferences)
			return true;
		return false;
	}
}