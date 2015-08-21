/******************************************************************************/
/*                                                                            */
/*  PngStream.cpp                                                             */
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

#include "PngStream.hpp"

#include "Undefs.hpp"

namespace Fast
{
	namespace PngStream
	{
		void Read(png_structp png, png_bytep outBytes, png_size_t bytesToRead) {
			if (png_get_io_ptr(png) == 0)
				return;
			PngBuffer *pngBuffer = (PngBuffer*)png_get_io_ptr(png);
			if (bytesToRead > (pngBuffer->mSize - pngBuffer->mIndex)) {
				// TODO: PNG buffer error handler
				return;
			}
			memcpy(outBytes, pngBuffer->mData + pngBuffer->mIndex, bytesToRead);
			pngBuffer->mIndex += bytesToRead;
		}
	}
}