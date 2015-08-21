/******************************************************************************/
/*                                                                            */
/*  Material.hpp                                                              */
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

#ifndef FastMaterialHppIncluded
#define FastMaterialHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class FastApi Material
	{
	public:
		Float	mAmbient[3];
		Float	mDiffuse[3];
		Float	mSpecular[3];
		Float	mEmissive[3];
		Float	mShininess;
		UInt	mOpenGLTextureID;
		// Constructors
		Material();
		Material(const Material &that);
		Material(Float ambient0, Float ambient1, Float ambient2,
			Float diffuse0, Float diffuse1, Float diffuse2,
			Float specular0, Float specular1, Float specular2,
			Float emissive0, Float emissive1, Float emissive2,
			Float shininess, UInt openGLTextureID);
		// Operators
		Material&	operator= (const Material &that);
		Bool		operator==(const Material &that) const;
		Bool		operator!=(const Material &that) const;
	};
}

#endif // FastMaterialHppIncluded
