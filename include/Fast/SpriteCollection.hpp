/******************************************************************************/
/*                                                                            */
/*  SpriteCollection.hpp                                                      */
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

#ifndef FastSpriteCollectionHppIncluded
#define FastSpriteCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/AssetCollectionVerifiable.hpp>
#include <Fast/SpriteResource.hpp>
#include <Fast/Model.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class Texture2DCollection;
	class ModelCollection;
	class ShaderProgramCollection;
	class String;
	class StreamReader;
	class AssetData;
	class GraphicsContext;

	template class FastApi AssetCollectionVerifiable<SpriteResource>;

	class FastApi SpriteCollection :
		public AssetCollectionVerifiable<SpriteResource>
	{
	protected:
		Texture2DCollection		&mTexture2DCollection;
		ModelCollection			&mModelCollection;
		ShaderProgramCollection	&mShaderProgramCollection;
		Model					mSurfaceQuad;
		void	BuildDefaultResource();
	public:
		// (Con/De)structors
		SpriteCollection(Texture2DCollection *texture2DCollection,
			ModelCollection *modelCollection,
			ShaderProgramCollection *shaderProgramCollection);
		~SpriteCollection();
		// Allocators
		ErrorType	LoadResource(const String &fileName);
		ErrorType	LoadResource(StreamReader *streamReader);
		ErrorType	LoadResource(const AssetData &assetData);
		void		UnloadResource(Int id);
		// Getters
		GraphicsContext*				GetGraphicsContext();
		const GraphicsContext&			GetGraphicsContext() const;
		Texture2DCollection*			GetTexture2DCollection();
		const Texture2DCollection&		GetTexture2DCollection() const;
		ModelCollection*				GetModelCollection();
		const ModelCollection&			GetModelCollection() const;
		ShaderProgramCollection*		GetShaderProgramCollection();
		const ShaderProgramCollection&	GetShaderProgramCollection() const;
		const Model&					GetSurfaceQuad() const;
	};
}

#endif // FastSpriteCollectionHppIncluded
