/******************************************************************************/
/*                                                                            */
/*  MeshData.hpp                                                              */
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

#ifndef FastMeshDataHppIncluded
#define FastMeshDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/Vertex.hpp>
#include <Fast/Triangle.hpp>
#include <Fast/VertexStruct.hpp>
#include <Fast/TriangleStruct.hpp>
#include <Fast/String.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/MeshRenderPreferences.hpp>

namespace Fast
{
	class FastApi MeshData
	{
	protected:
		String					mName;
		Matrix					mMatrix;
		Array<Vertex>			mVertices;
		Array<Triangle>			mFaces;
		MeshRenderPreferences	mRenderPreferenceDefaults;
	public:
		MeshData();
		// Modifiers
		void	SetName(const String &name);
		void	SetMatrix(const Matrix &matrix);
		void	AppendVertex(const Vertex &vertex);
		void	InsertVertex(const Vertex &vertex, Int index);
		void	ReplaceVertex(const Vertex &vertex, Int index);
		void	RemoveVertex(Int index, Int numVertices = 0);
		void	AppendVertices(const Array<Vertex> &vertices);
		void	InsertVertices(const Array<Vertex> &vertices, Int index);
		void	ReplaceVertices(const Array<Vertex> &vertices, Int index);
		void	AppendFace(const Triangle &face);
		void	InsertFace(const Triangle &face, Int index);
		void	ReplaceFace(const Triangle &face, Int index);
		void	RemoveFace(Int index, Int numFaces = 0);
		void	AppendFaces(const Array<Triangle> &faces);
		void	InsertFaces(const Array<Triangle> &faces, Int index);
		void	ReplaceFaces(const Array<Triangle> &faces, Int index);
		// Getters
		const String&					GetName() const;
		const Matrix&					GetMatrix() const;
		Int								GetNumVertices() const;
		Vertex*							GetVertex(Int index);
		const Vertex&					GetVertex(Int index) const;
		Array<VertexStruct>				GetVertexStructArray() const;
		Int								GetNumFaces() const;
		const Triangle&					GetFace(Int index) const;
		Triangle*						GetFace(Int index);
		Array<TriangleStruct>			GetTriangleStructArray() const;
		MeshRenderPreferences*			GetRenderPreferenceDefaults();
		const MeshRenderPreferences&	GetRenderPreferenceDefaults() const;
	};
}

#endif // FastMeshDataHppIncluded
