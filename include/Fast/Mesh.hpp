/******************************************************************************/
/*                                                                            */
/*  Mesh.hpp                                                                  */
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

#ifndef FastMeshHppIncluded
#define FastMeshHppIncluded

#include <Fast/Types.hpp>
#include <Fast/MeshRenderPreferences.hpp>
#include <Fast/RenderPrimitive.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class Model;
	class Matrix;

	class FastApi Mesh
	{
	private:
		Model					*mModel;
		Int						mIndex;
		MeshRenderPreferences	mRenderPreferences;
	public:
		// (Con/De)structors
		Mesh();
		Mesh(Model *model, Int index, const MeshRenderPreferences &prefs);
		Mesh(const Mesh &that);
		~Mesh();
		// Getters
		Model*							GetModel();
		Int								GetIndex() const;
		const Matrix&					GetMatrix() const;
		MeshRenderPreferences*			GetRenderPreferences();
		const MeshRenderPreferences&	GetRenderPreferences() const;
		const MeshRenderPreferences&	GetRenderPreferenceDefaults() const;
		Int								GetNumVertices() const;
		Int								GetNumFaces() const;
		UInt							GetOpenGLVertexBufferID() const;
		UInt							GetOpenGLIndexBufferID() const;
		UInt							GetOpenGLVertexArrayID() const;
		// Draw functions
		void	Draw2D();
		void	Draw3D();
		// Operators
		Mesh&	operator= (const Mesh &that);
		Bool	operator==(const Mesh &that) const;
		Bool	operator!=(const Mesh &that) const;
	};

	template class FastApi Array<Mesh>;
}

#endif // FastMeshHppIncluded
