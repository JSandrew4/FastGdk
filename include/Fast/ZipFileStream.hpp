/******************************************************************************/
/*                                                                            */
/*  ZipFileStream.hpp                                                         */
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

#ifndef FastZipFileStreamHppIncluded
#define FastZipFileStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ZipFileBase.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/StreamWriter.hpp>
#include <Fast/ByteStream.hpp>

namespace Fast
{
	class FastApi ZipFileStream : public ZipFileBase,
		public StreamReader, public StreamWriter
	{
	private:
		// Hide these functions. No copying streams!
		ZipFileStream(const ZipFileStream &that) { }
		ZipFileStream& operator=(const ZipFileStream &that)
			{ return *this; }
	protected:
		ByteStream	mBuffer;
		Bool		mMadeChange;
	public:
		// (Con/De)structors
		ZipFileStream();
		ZipFileStream(const String &fileName, ZipArchive *archive,
			Bool truncate = false);
		~ZipFileStream();
		// StreamBase implementation
		void		Close();
		void		Flush();
		Bool		IsOpen();
		Long		GetSize();
		ErrorType	GetError();
		void		SeekTo(Long readPosition);
		Long		GetSeekPosition();
		// StreamReader/Writer implementations
		void	Read(Byte *data, Long size);
		void	Write(const Byte *data, Long size);
		// Misc
		void Open(const String &fileName, ZipArchive *archive,
			Bool truncate = false);
	};
}

#endif // FastZipFileStreamHppIncluded