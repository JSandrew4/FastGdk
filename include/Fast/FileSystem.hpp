/******************************************************************************/
/*                                                                            */
/*  FileSystem.hpp                                                            */
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

#ifndef FastFileSystemHppIncluded
#define FastFileSystemHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/ErrorType.hpp>

#define kFastMaxFileNameLength	1024

namespace Fast
{
	class FastApi FileSystem
	{
	private:
		String	mAppDataPath;
		String	mCurrentWorkingPath;
		String	mApplicationPath;
		String	mRootPath;
		String	mTempFolderPath;
		String	mUserProfilePath;
		// Hide these functions. No copying FileSystem objects!
		FileSystem(const FileSystem &that) { }
		FileSystem& operator=(const FileSystem &that) { return *this; }
	public:
		// (Con/De)structors
		FileSystem();
		// Get functions
		Array<String>	GetDirectoryListing(const String &directoryPath);
		Bool			IsFile(const String &filePath);
		Bool			IsDirectory(const String &directoryPath);
		const String&	GetAppDataPath();
		const String&	GetCurrentWorkingPath();
		const String&	GetApplicationPath();
		const String&	GetRootPath();
		const String&	GetTempFolderPath();
		const String&	GetUserProfilePath();
		// Modify functions
		ErrorType	NewFile(const String &fileName);
		ErrorType	NewDirectory(const String &directoryName);
		ErrorType	EraseFile(const String &fileName);
		ErrorType	EraseDirectory(const String &directoryName);
		ErrorType	Rename(const String &name, const String &newName);
	};
}

#endif // FastFileSystemHppIncluded
