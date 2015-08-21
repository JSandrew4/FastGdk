/******************************************************************************/
/*                                                                            */
/*  FrameBufferCollection.hpp                                                 */
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

#ifndef FastFrameBufferCollectionHppIncluded
#define FastFrameBufferCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollection.hpp>
#include <Fast/FrameBufferResource.hpp>

namespace Fast
{
	class GraphicsContext;
	class Texture2DCollection;

	class FastApi FrameBufferCollection :
		public AssetCollection<FrameBufferResource>
	{
	protected:
		Texture2DCollection	&mTexture2DCollection;
	public:
		// (Con/De)structors
		FrameBufferCollection(Texture2DCollection *texture2DCollection);
		~FrameBufferCollection();
		// Allocators
		void	UnloadResource(Int id);
		// Getters
		Texture2DCollection*		GetTexture2DCollection();
		const Texture2DCollection&	GetTexture2DCollection() const;
	};
}

#endif // FastFrameBufferCollectionHppIncluded