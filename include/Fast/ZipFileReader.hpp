/******************************************************************************/
/*                                                                            */
/*  ZipFileReader.hpp                                                         */
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

#ifndef FastZipFileReaderHppIncluded
#define FastZipFileReaderHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/StreamReader.hpp>

namespace Fast
{
	class String;
	class ZipArchive;

	class FastApi ZipFileReader : public StreamReader
	{
	private:
		// Hide these functions. No copying file streams!
		ZipFileReader(const ZipFileReader &that) { }
		ZipFileReader& operator=(const ZipFileReader &that)
			{ return *this; }
	protected:
		ZipArchive	*mArchive;
		Czip_file	*mFile;
		Long		mSeekPosition;
	public:
		// (Con/De)structors
		ZipFileReader();
		ZipFileReader(const String &fileName, ZipArchive *archive);
		~ZipFileReader();
		// StreamBase functions
		void		Close();
		void		Flush();
		Bool		IsOpen();
		Long		GetSize();
		ErrorType	GetError();
		void		SeekTo(Long seekPosition);
		Long		GetSeekPosition();
		// StreamReader implementation
		void		Read(Byte *data, Long size);
		// Misc
		void		Open(const String &fileName, ZipArchive *archive);
	};
}

#endif // FastZipFileReaderHppIncluded