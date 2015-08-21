/******************************************************************************/
/*                                                                            */
/*  ModelCollection.hpp                                                       */
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

#ifndef FastModelCollectionHppIncluded
#define FastModelCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollectionVerifiable.hpp>
#include <Fast/ModelResource.hpp>

namespace Fast
{
	class GraphicsContext;
	class StreamReader;
	class FrameBufferCollection;
	class ModelData;

	template class FastApi AssetCollectionVerifiable<ModelResource>;

	class FastApi ModelCollection : public AssetCollectionVerifiable<ModelResource>
	{
	private:
		// Hide these functions. No copying collections!
		ModelCollection(const ModelCollection &that) :
			mGraphicsContext(that.mGraphicsContext)
			{ }
		ModelCollection& operator=(const ModelCollection &that)
			{ return *this; }
	protected:
		GraphicsContext	&mGraphicsContext;
	public:
		// (Con/De)structors
		ModelCollection(GraphicsContext *graphicsContext);
		~ModelCollection();
		// Allocators
		ErrorType	LoadResource(const String &fileName);
		ErrorType	LoadResource(StreamReader *streamReader);
		ErrorType	LoadResource(const AssetData &data);
		void		UnloadResource(Int id);
		// Getters
		GraphicsContext*		GetGraphicsContext();
		const GraphicsContext&	GetGraphicsContext() const;
	};
}

#endif // FastModelCollectionHppIncluded
