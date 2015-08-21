/******************************************************************************/
/*                                                                            */
/*  GraphicsIOCommand.cpp                                                     */
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

#include <Fast/GraphicsIOCommand.hpp>

#include "Undefs.hpp"

namespace Fast
{
	GraphicsIOCommand::GraphicsIOCommand() {
		mType						= kGraphicsIONone;
		mOpenGLTexture2DIDPtr		= NULL;
		mOpenGLTexture2DID			= 0;
		mConstTexture2DDataPtr		= NULL;
		mWidth						= 0;
		mHeight						= 0;
		mOpenGLFramebufferIDPtr		= NULL;
		mOpenGLRenderbufferIDPtr	= NULL;
		mTexture2DDataPtr			= NULL;
		mTexture2DPropertiesPtr		= NULL;
	}
}