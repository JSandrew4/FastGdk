/******************************************************************************/
/*                                                                            */
/*  GraphicsIOCommand.hpp                                                     */
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

#ifndef FastGraphicsIOCommandHppIncluded
#define FastGraphicsIOCommandHppIncluded

#include <Fast/Types.hpp>
#include <Fast/GraphicsIOType.hpp>

namespace Fast
{
	class Texture2DData;
	class Texture2DProperties;
	class AlphaTexture2DData;
	class MeshResource;
	class MeshData;

	class FastApi GraphicsIOCommand
	{
	public:
		GraphicsIOType				mType;
		UInt						*mOpenGLTexture2DIDPtr;
		UInt						mOpenGLTexture2DID;
		const Texture2DData			*mConstTexture2DDataPtr;
		Int							mWidth;
		Int							mHeight;
		const AlphaTexture2DData	*mConstAlphaTexture2DDataPtr;
		Int							mOffsetX;
		Int							mOffsetY;
		UInt						*mOpenGLFramebufferIDPtr;
		UInt						*mOpenGLRenderbufferIDPtr;
		Texture2DData				*mTexture2DDataPtr;
		Texture2DProperties			*mTexture2DPropertiesPtr;
		MeshResource				*mMeshResourcePtr;
		const MeshData				*mConstMeshDataPtr;
		Int							mMeshUsage;
		// (Con/De)structors
		GraphicsIOCommand();
	};
}

#endif // FastGraphicsIOCommandHppIncluded