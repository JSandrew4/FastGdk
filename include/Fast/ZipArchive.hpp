/******************************************************************************/
/*                                                                            */
/*  ZipArchive.hpp                                                            */
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

#ifndef FastZipArchiveHppIncluded
#define FastZipArchiveHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi ZipArchive
	{
	protected:
		String	mName;
		Czip	*mZipHandle;
		// Hide these functions. No file stream copying!
		ZipArchive(const ZipArchive &that) { }
		ZipArchive& operator=(const ZipArchive &that)
			{ return *this; }
	public:
		// (Con/De)structors
		ZipArchive();
		ZipArchive(const String &fileName);
		~ZipArchive();
		// Getters
		const String&	GetName() const;
		Bool			IsOpen();
		Czip*			GetZipHandle();
		// Misc
		void			Open(const String &fileName);
		void			Close();
	};
}

#endif // FastZipArchiveHppIncluded