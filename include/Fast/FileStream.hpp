/******************************************************************************/
/*                                                                            */
/*  FileStream.hpp                                                            */
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

#ifndef FastFileStreamHppIncluded
#define FastFileStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/FileBase.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/StreamWriter.hpp>

namespace Fast
{
	class String;

	class FastApi FileStream : public FileBase,
		public StreamWriter, public StreamReader
	{
	protected:
		Bool	mMadeChange;
		// Hide these functions. No copying file streams!
		FileStream(const FileStream &that) { }
		FileStream&	operator=(const FileStream &that) { return *this; }
	public:
		// (Con/De)structors
		FileStream();
		FileStream(const String &fileName, Bool truncate = false);
		~FileStream();
		// StreamBase implementation
		void		Close();
		void		Flush();
		Bool		IsOpen();
		Long		GetSize();
		ErrorType	GetError();
		void		SeekTo(Long seekPosition);
		Long		GetSeekPosition();
		// StreamReader/Writer implementation
		void	Read(Byte *data, Long size);
		void	Write(const Byte *data, Long size);
		// Misc functions
		void	Open(const String &fileName, Bool truncate = false);
	};
}

#endif // FastFileStreamHppIncluded
