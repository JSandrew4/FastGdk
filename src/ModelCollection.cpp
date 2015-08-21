/******************************************************************************/
/*                                                                            */
/*  ModelCollection.cpp                                                       */
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

#include <Fast/ModelCollection.hpp>
#include <Fast/Model.hpp>
#include <Fast/ModelData.hpp>
#include <Fast/GraphicsContext.hpp>

#include "Undefs.hpp"

namespace Fast
{/* TODO: Remove
	void ModelCollection::BuildDefaultResource() {
		mResources.SetElementCount(1);
		ModelData md;
		md.SetName("DefaultModel");
		MeshData med;
		// TODO: Set render preferences? Maybe do this as quads instead?
		med.AppendVertex(Vertex(1.0f, 1.0f, 1.0f)); // Face 1
		med.AppendVertex(Vertex(1.0f, -1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(1.0f, -1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, -1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, -1.0f, 1.0f)); // Face 2
		med.AppendVertex(Vertex(-1.0f, -1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, -1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, -1.0f)); // Face 3
		med.AppendVertex(Vertex(1.0f, -1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, -1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, -1.0f, 1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, 1.0f)); // Face 4
		med.AppendVertex(Vertex(1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, -1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(1.0f, -1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, -1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f)); // Face 5
		med.AppendVertex(Vertex(-1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f)); // Face 6
		med.AppendVertex(Vertex(1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, -1.0f));
		med.AppendVertex(Vertex(-1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, 1.0f));
		med.AppendVertex(Vertex(1.0f, 1.0f, -1.0f));
		md.AddMeshData(med);
		Model m(md, this);
		SetResourceRetained(AddResource(m.GetResource(), &m), true);
	}
	*/
	ModelCollection::ModelCollection(GraphicsContext *graphicsContext) :
		mGraphicsContext(*graphicsContext)
	{ }

	ModelCollection::~ModelCollection() {
		UnloadAllResources();
	}

	ErrorType ModelCollection::LoadResource(const String &fileName)
	{
		Model model;
		ErrorType error = model.Load(fileName, this);
		if (!error)
			SetResourceRetained(model.GetID(), true);
		return error;
	}

	ErrorType ModelCollection::LoadResource(StreamReader *streamReader)
	{
		Model model;
		ErrorType error = model.Load(streamReader, this);
		if (!error)
			SetResourceRetained(model.GetID(), true);
		return error;
	}

	ErrorType ModelCollection::LoadResource(const AssetData &data)
	{
		Model model;
		ErrorType error = model.Load((ModelData&)data, this);
		if (!error)
			SetResourceRetained(model.GetID(), true);
		return error;
	}

	void ModelCollection::UnloadResource(Int id) {
		UnloadReferences(id);
		for (Int i = 0; i < mResources[id].mMeshResources.GetElementCount();
			i++)
		{
			mGraphicsContext.DeleteOpenGLMesh(&mResources[id].mMeshResources[i]);
		}
		mResources[id].SetActive(false);
	}

	GraphicsContext* ModelCollection::GetGraphicsContext() {
		return &mGraphicsContext;
	}

	const GraphicsContext& ModelCollection::GetGraphicsContext() const {
		return mGraphicsContext;
	}
}