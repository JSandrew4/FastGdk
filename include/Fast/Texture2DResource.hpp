/******************************************************************************/
/*                                                                            */
/*  Texture2DResource.hpp                                                     */
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

#ifndef FastTexture2DResourceHppIncluded
#define FastTexture2DResourceHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetResourceBase.hpp>
#include <Fast/Texture2DProperties.hpp>
#include <Fast/AssetResourceVerifiableBase.hpp>

namespace Fast
{
	class FastApi Texture2DResource :
		public AssetResourceBase<Texture2DProperties>,
		public AssetResourceVerifiableBase
	{
	protected:
		UInt	mOpenGLID;
	public:
		// (Con/De)structors
		Texture2DResource();
		// Getters
		UInt	GetOpenGLID() const;
		// Setters
		void	SetOpenGLID(UInt openGLID);
	};
}

#endif // FastTexture2DResourceHppIncluded
