/******************************************************************************/
/*                                                                            */
/*  RenderItem.hpp                                                            */
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

#ifndef FastRenderItemHppIncluded
#define FastRenderItemHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ArrayMinimumCapacity.hpp>
#include <Fast/ShaderUniform.hpp>
#include <Fast/RenderPreferences.hpp>

namespace Fast
{
	template class FastApi ArrayMinimumCapacity
		<ShaderUniform, ShaderUniform[16]>;
	typedef ArrayMinimumCapacity<ShaderUniform, ShaderUniform[16]>
		ArrayShaderUniform16;

	class FastApi RenderItem
	{
	public:
		FrameBufferSurface		&mFrameBufferSurface;
		RenderPreferences		mRenderPreferences;
		ArrayShaderUniform16	mUniforms;
		UInt					mOpenGLTexture2DID;
		UInt					mOpenGLVertexArrayID;
		UInt					mOpenGLShaderProgramID;
		Int						mFirstElement;
		Int						mElementCount;
		// (Con/De)structors
		RenderItem(FrameBufferSurface *frameBufferSurface);
	};
}

#endif // FastRenderItemHppIncluded