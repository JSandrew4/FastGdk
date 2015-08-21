/******************************************************************************/
/*                                                                            */
/*  Material.cpp                                                              */
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

#include <Fast/Material.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	Material::Material() {
		// TODO: Find out real default values
		memset(this, 0, sizeof(Material));
	}

	Material::Material(const Material &that) {
		*this = that;
	}

	Material::Material(Float ambient0, Float ambient1, Float ambient2,
		Float diffuse0, Float diffuse1, Float diffuse2,
		Float specular0, Float specular1, Float specular2,
		Float emissive0, Float emissive1, Float emissive2,
		Float shininess, UInt openGLTextureID)
	{
		mAmbient[0]			= ambient0;
		mAmbient[1]			= ambient1;
		mAmbient[2]			= ambient2;
		mDiffuse[0]			= diffuse0;
		mDiffuse[1]			= diffuse1;
		mDiffuse[2]			= diffuse2;
		mSpecular[0]		= specular0;
		mSpecular[1]		= specular1;
		mSpecular[2]		= specular2;
		mEmissive[0]		= emissive0;
		mEmissive[1]		= emissive1;
		mEmissive[2]		= emissive2;
		mShininess			= shininess;
		mOpenGLTextureID	= openGLTextureID;
	}

	Material& Material::operator=(const Material &that) {
		memcpy(this, &that, sizeof(Material));
		return *this;
	}

	Bool Material::operator==(const Material &that) const {
		if (0 == memcmp(this, &that, sizeof(Material)))
			return true;
		return false;
	}

	Bool Material::operator!=(const Material &that) const {
		if (0 == memcmp(this, &that, sizeof(Material)))
			return false;
		return true;
	}
}