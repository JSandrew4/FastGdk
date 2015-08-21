/******************************************************************************/
/*                                                                            */
/*  ZipFileWriter.hpp                                                         */
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

#ifndef FastZipFileWriterHppIncluded
#define FastZipFileWriterHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/StreamWriter.hpp>
#include <Fast/ByteStream.hpp>
#include <Fast/ZipFileBase.hpp>

namespace Fast
{
	class String;
	class ZipArchive;

	class FastApi ZipFileWriter : public ZipFileBase, public StreamWriter
	{
	private:
		// Hide these functions. No copying file streams!
		ZipFileWriter(const ZipFileWriter &that) { }
		ZipFileWriter& operator=(const ZipFileWriter &that)
			{ return *this; }
	protected:
		ByteStream	mBuffer;
		Bool		mMadeChange;
	public:
		// (Con/De)structors
		ZipFileWriter();
		ZipFileWriter(const String &fileName,
			ZipArchive *archive, Bool truncate = false);
		~ZipFileWriter();
		// StreamBase implementation
		void		Close();
		void		Flush();
		Bool		IsOpen();
		Long		GetSize();
		ErrorType	GetError();
		void		SeekTo(Long writePosition);
		Long		GetSeekPosition();
		// StreamWriter implementation
		void		Write(Byte *data, Long size);
		// Misc
		void Open(const String &fileName,
			ZipArchive *archive, Bool truncate = false);
	};
}

#endif // FastZipFileWriterHppIncluded