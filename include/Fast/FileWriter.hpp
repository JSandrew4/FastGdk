/******************************************************************************/
/*                                                                            */
/*  FileWriter.hpp                                                            */
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

#ifndef FastFileWriterHppIncluded
#define FastFileWriterHppIncluded

#include <Fast/Types.hpp>
#include <Fast/FileBase.hpp>
#include <Fast/StreamWriter.hpp>

namespace Fast
{
	class String;

	class FastApi FileWriter : public FileBase, public StreamWriter
	{
	protected:
		// Hide these functions. No copying file streams!
		FileWriter(const FileWriter &that) { }
		FileWriter&	operator=(const FileWriter &that) { return *this; }
	public:
		// (Con/De)structors
		FileWriter();
		FileWriter(const String &fileName, Bool truncate = true);
		~FileWriter();
		// StreamBase implementation
		void		Close();
		void		Flush();
		Bool		IsOpen();
		Long		GetSize();
		ErrorType	GetError();
		void		SeekTo(Long seekPosition);
		Long		GetSeekPosition();
		// StreamWriter implementation
		void	Write(const Byte *data, Long size);
		// Misc functions
		void	Open(const String &fileName, Bool truncate = true);
	};
}

#endif // FastFileWriterHppIncluded
