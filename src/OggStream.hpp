/******************************************************************************/
/*                                                                            */
/*  OggStream.hpp                                                             */
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

#ifndef FastOggStreamHppIncluded
#define FastOggStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/StreamReader.hpp>

#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <ogg/ogg.h>

namespace Fast
{
	namespace OggStream
	{
		size_t	Read(void *dst, size_t size1, size_t size2, void *stream);
		int		Seek(void *stream, ogg_int64_t to, int type);
		int		Close(void *stream);
		long	Tell(void *stream);
	}
}

#endif // FastOggStreamHppIncluded
