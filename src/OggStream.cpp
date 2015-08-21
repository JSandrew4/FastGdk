/******************************************************************************/
/*                                                                            */
/*  OggStream.cpp                                                             */
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

#include "OggStream.hpp"

#include "Undefs.hpp"

namespace Fast
{
	namespace OggStream
	{
		size_t Read(void *dst, size_t size1, size_t size2, void *stream) {
			StreamReader *streamReader = (StreamReader*)stream;
			size_t len = size1 * size2;
			if (streamReader->GetSize() < streamReader->GetSeekPosition() + (Long)len)
				len = (size_t)(streamReader->GetSize() - streamReader->GetSeekPosition());
			streamReader->Read((Byte*)dst, (Long)len);
			return len;
		}

		int Seek(void *stream, ogg_int64_t to, int type) {
			StreamReader *streamReader = (StreamReader*)stream;
			switch (type)
			{
			case SEEK_CUR:
				streamReader->SeekTo(streamReader->GetSeekPosition() + to);
				break;
			case SEEK_END:
				streamReader->SeekTo(streamReader->GetSize() - to);
				break;
			case SEEK_SET:
				streamReader->SeekTo(to);
				break;
			default:
				return -1;
			}
			if (streamReader->GetError())
				return -1;
			return 0;
		}

		int Close(void *stream) {
			return 0;
		}

		long Tell(void *stream) {
			StreamReader *streamReader = (StreamReader*)stream;
			return (long)streamReader->GetSeekPosition();
		}
	}
}
