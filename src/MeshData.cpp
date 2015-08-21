/******************************************************************************/
/*                                                                            */
/*  MeshData.cpp                                                              */
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

#include <Fast/MeshData.hpp>

#include "Undefs.hpp"

namespace Fast
{
	MeshData::MeshData() { }

	void MeshData::SetName(const String &name) {
		mName = name;
	}

	void MeshData::SetMatrix(const Matrix &matrix) {
		mMatrix = matrix;
	}

	void MeshData::AppendVertex(const Vertex &vertex) {
		mVertices.Append(vertex);
	}

	void MeshData::InsertVertex(const Vertex &vertex, Int index) {
		mVertices.Insert(vertex, index);
	}

	void MeshData::ReplaceVertex(const Vertex &vertex, Int index) {
		mVertices.Replace(vertex, index);
	}

	void MeshData::RemoveVertex(Int index, Int numVertices) {
		mVertices.Erase(index, numVertices);
	}

	void MeshData::AppendVertices(const Array<Vertex> &vertices) {
		mVertices.Append(vertices);
	}

	void MeshData::InsertVertices(const Array<Vertex> &vertices, Int index) {
		mVertices.Insert(vertices, index);
	}

	void MeshData::ReplaceVertices(const Array<Vertex> &vertices, Int index) {
		mVertices.Replace(vertices, index);
	}

	void MeshData::AppendFace(const Triangle &face) {
		mFaces.Append(face);
	}

	void MeshData::InsertFace(const Triangle &face, Int index) {
		mFaces.Insert(face, index);
	}

	void MeshData::ReplaceFace(const Triangle &face, Int index) {
		mFaces.Replace(face, index);
	}

	void MeshData::RemoveFace(Int index, Int numFaces) {
		mFaces.Erase(index, numFaces);
	}

	void MeshData::AppendFaces(const Array<Triangle> &faces) {
		mFaces.Append(faces);
	}

	void MeshData::InsertFaces(const Array<Triangle> &faces, Int index) {
		mFaces.Insert(faces, index);
	}

	void MeshData::ReplaceFaces(const Array<Triangle> &faces, Int index) {
		mFaces.Replace(faces, index);
	}

	const String& MeshData::GetName() const {
		return mName;
	}

	const Matrix& MeshData::GetMatrix() const {
		return mMatrix;
	}

	Int MeshData::GetNumVertices() const {
		return mVertices.GetElementCount();
	}

	const Vertex& MeshData::GetVertex(Int index) const {
		return mVertices[index];
	}

	Vertex* MeshData::GetVertex(Int index) {
		return &mVertices[index];
	}

	Array<VertexStruct> MeshData::GetVertexStructArray() const {
		Array<VertexStruct> vsa;
		for (Int i = 0; i < mVertices.GetElementCount(); i++)
			vsa.Append(mVertices[i].GetPlainOldData());
		return vsa;
	}

	Int MeshData::GetNumFaces() const {
		return mFaces.GetElementCount();
	}

	const Triangle& MeshData::GetFace(Int index) const {
		return mFaces[index];
	}

	Triangle* MeshData::GetFace(Int index) {
		return &mFaces[index];
	}

	Array<TriangleStruct> MeshData::GetTriangleStructArray() const {
		Array<TriangleStruct> tsa;
		for (Int i = 0; i < mFaces.GetElementCount(); i++)
			tsa.Append(mFaces[i].GetPlainOldData());
		return tsa;
	}

	const MeshRenderPreferences& MeshData::GetRenderPreferenceDefaults() const {
		return mRenderPreferenceDefaults;
	}

	MeshRenderPreferences* MeshData::GetRenderPreferenceDefaults() {
		return &mRenderPreferenceDefaults;
	}
}