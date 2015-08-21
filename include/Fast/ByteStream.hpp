/******************************************************************************/
/*                                                                            */
/*  ByteStream.hpp                                                            */
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

#ifndef FastByteStreamHppIncluded
#define FastByteStreamHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/ExceptionType.hpp>
#include <Fast/Array.hpp>
#include <Fast/StreamReader.hpp>
#include <Fast/StreamWriter.hpp>

namespace Fast
{
	class String;

	class FastApi ByteStream : virtual public StreamReader,
		virtual public StreamWriter
	{
	protected:
		Array<Byte>	mData;
		Long		mSeekPosition;
		ErrorType	mError;
	public:
		// (Con/De)structors
		ByteStream();
		ByteStream(const ByteStream &that);
		~ByteStream();
		// Read/write functions
		void	Read(Byte *data, Long size);
		void	Write(const Byte *data, Long size);
		// Seek functions
		void	SeekTo(Long seekPosition);
		Long	GetSeekPosition();
		// Misc functions
		void		Close();
		void		Flush();
		Bool		IsOpen();
		void		Clear();
		Long		GetSize();
		Long		GetSize() const;
		ErrorType	GetError();
		Byte*		GetData();
		const Byte*	GetData() const;
		void		SetName(const String &name);
		// Operators
		ByteStream&	operator= (const ByteStream &that);
		Bool		operator==(const ByteStream &that) const;
		Bool		operator!=(const ByteStream &that) const;
	};
}

#endif // FastByteStreamHppIncluded
