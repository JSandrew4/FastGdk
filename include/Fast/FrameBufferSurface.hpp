/******************************************************************************/
/*                                                                            */
/*  FrameBufferSurface.hpp                                                    */
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

#ifndef FastFrameBufferSurfaceHppIncluded
#define FastFrameBufferSurfaceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/FrameBufferCollection.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class Texture2DSurface;

	class FastApi FrameBufferSurface :
		public AssetImplementer<FrameBufferCollection, FrameBufferResource>
	{
	public:
		// (Con/De)structors
		FrameBufferSurface();
		FrameBufferSurface(Int width, Int height, Int bitsPerPixel,
			FrameBufferCollection *collection);
		FrameBufferSurface(const FrameBufferSurface &that);
		~FrameBufferSurface();
		// Allocators
		ErrorType	Create(Int width, Int height, Int bitsPerPixel,
						FrameBufferCollection *collection);
		void		Unbind();
		// Misc
		void	Resize(Int width, Int height);
		// Getters
		FrameBufferCollection*			GetCollection();
		const FrameBufferCollection&	GetCollection() const;
		UInt							GetOpenGLFramebufferID() const;
		UInt							GetOpenGLRenderbufferID() const;
		Texture2DSurface*				GetTexture2D();
		const Texture2DSurface&			GetTexture2D() const;
		Int								GetWidth() const;
		Int								GetHeight() const;
		Int								GetBitsPerPixel() const;
		// Operators
		FrameBufferSurface&	operator= (const FrameBufferSurface &that);
		Bool				operator==(const FrameBufferSurface &that) const;
		Bool				operator!=(const FrameBufferSurface &that) const;
	};
}

#endif // FastRenderSurfaceHppIncluded