/******************************************************************************/
/*                                                                            */
/*  FileSystem.cpp                                                            */
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

#include <Fast/FileSystem.hpp>
#include <Fast/FileStream.hpp>
#include <Fast/Error.hpp>

#include <cstdlib>
#include <cstdio>
#if defined(FastOSWindows)
#	include <wchar.h>
#elif defined(FastOSUnixLike)
#	include <unistd.h>
#	include <dirent.h>
#	include <sys/types.h>
#	include <sys/stat.h>
#endif
#if defined(FastOSMacOSX)
#	include <mach-o/dyld.h>
#endif

#include "Undefs.hpp"

namespace Fast
{
	void FileSystemAppendSlashIfNeeded(String *str) {
		if (str->IsEmpty())
			return;
		UInt textLength = str->GetTextLength();
		String endCharacter = str->GetCharacter(textLength-1);
		if (endCharacter == "\\" || endCharacter == "/")
			return;
	#if defined(FastOSWindows)
		str->Append("\\");
	#elif defined(FastOSUnixLike)
		str->Append("/");
	#endif
	}

	FileSystem::FileSystem() {
#if defined(FastOSWindows)
		WChar wcsPath[kFastMaxFileNameLength + 1];
		size_t wcsPathSize = kFastMaxFileNameLength;
		// Get AppData path
		memset(wcsPath, 0, (kFastMaxFileNameLength + 1) * sizeof(WChar));
		_wdupenv_s((WChar**)&wcsPath, &wcsPathSize, L"APPDATA");
		mAppDataPath = wcsPath;
		// Get CurrentWorking path
		memset(wcsPath, 0, (kFastMaxFileNameLength + 1) * sizeof(WChar));
		_wgetcwd(wcsPath, kFastMaxFileNameLength);
		mCurrentWorkingPath = wcsPath;
		// Get Application path
		memset(wcsPath, 0, (kFastMaxFileNameLength + 1) * sizeof(WChar));
		GetModuleFileName(0, wcsPath, kFastMaxFileNameLength);
		mApplicationPath = wcsPath;
		// Get Root path
		memset(wcsPath, 0, (kFastMaxFileNameLength + 1) * sizeof(WChar));
		_wdupenv_s((WChar**)&wcsPath, &wcsPathSize, L"HOMEDRIVE");
		mRootPath = wcsPath;
		// Get TempFolder path
		memset(wcsPath, 0, (kFastMaxFileNameLength + 1) * sizeof(WChar));
		_wdupenv_s((WChar**)&wcsPath, &wcsPathSize, L"TEMP");
		mTempFolderPath = wcsPath;
		// Get UserProfile path
		memset(wcsPath, 0, (kFastMaxFileNameLength + 1) * sizeof(WChar));
		_wdupenv_s((WChar**)&wcsPath, &wcsPathSize, L"USERPROFILE");
		mUserProfilePath = wcsPath;
#elif defined(FastOSUnixLike)
		Char buf[kFastMaxFileNameLength + 1];
		// Get AppData path
		mAppDataPath = std::getenv("HOME");
		// Get CurrentWorking path
		memset(buf, 0, kFastMaxFileNameLength + 1);
		getcwd(buf, kFastMaxFileNameLength);
		mCurrentWorkingPath = buf;
		// Get Application path
		memset(buf, 0, kFastMaxFileNameLength + 1);
#if defined(FastOSLinux)
		readlink("/proc/self/exe", buf, kFastMaxFileNameLength);
#elif defined(gdkOsMacOSX)
		Int size = kFastMaxFileNameLength;
		_NSGetExecutablePath(buf, &size);
#endif
		mApplicationPath = buf;
		// Get Root path
		mRootPath = "/";
		// Get TempFolder path
		mTempFolderPath = "/tmp/";
		// Get UserProfile path
		mUserProfilePath = std::getenv("HOME");
#endif
		FileSystemAppendSlashIfNeeded(&mAppDataPath);
		FileSystemAppendSlashIfNeeded(&mCurrentWorkingPath);
		FileSystemAppendSlashIfNeeded(&mApplicationPath);
		FileSystemAppendSlashIfNeeded(&mRootPath);
		FileSystemAppendSlashIfNeeded(&mTempFolderPath);
		FileSystemAppendSlashIfNeeded(&mUserProfilePath);
		// Remove executable name from ApplicationPath
		Char *tempPath = (Char*)mApplicationPath.GetData();
		UInt tempPathLength = mApplicationPath.GetSizeInBytes();
		UInt i;
		Char c;
		for (i = 1; i < tempPathLength + 1; i++) {
			c = tempPath[tempPathLength - i];
			if (c == '/' || c == '\\')
				break;
			else
				tempPath[tempPathLength - i] = '\0';
		}
		mApplicationPath.Resize(strlen(tempPath));
	}

	Array<String> FileSystem::GetDirectoryListing(const String &directoryPath)
	{
		Array<String> files;
	#if defined(FastOSWindows)
		HANDLE dir;
		WIN32_FIND_DATA file_data;
		if ((dir = FindFirstFile((directoryPath + "/*").GetWString().mData,
			&file_data)) == INVALID_HANDLE_VALUE)
		{
			return files;
		}
		while (FindNextFile(dir, &file_data))
			files.Append(file_data.cFileName);
		FindClose(dir);
	#elif defined(FastOSUnixLike)
		DIR *dir;
		class dirent *ent;
		class stat st;
		dir = opendir(directoryPath.GetData());
		while ((ent = readdir(dir)) != NULL)
			files.Append(ent->d_name);
		closedir(dir);
	#endif
		return files;
	}

	Bool FileSystem::IsFile(const String &filePath) {
	#if defined(FastOSWindows)
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		BOOL succ = GetFileAttributesEx(filePath.GetWString().mData,
			GetFileExInfoStandard, &wfad);
		if (!succ)
			return false;
		if (0 != (wfad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			return false;
		else
			return true;
	#elif defined(FastOSUnixLike)
		int status;
		struct stat st_buf;
		status = stat(filePath.GetData(), &st_buf);
		if (status)
			return false;
		if (S_ISREG(st_buf.st_mode))
			return true;
		return false;
	#endif
	}

	Bool FileSystem::IsDirectory(const String &directoryPath) {
	#if defined(FastOSWindows)
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		BOOL succ = GetFileAttributesEx(directoryPath.GetWString().mData,
			GetFileExInfoStandard, &wfad);
		if (!succ)
			return false;
		if (0 != (wfad.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			return true;
		else
			return false;
	#elif defined(FastOSUnixLike)
		int status;
		struct stat st_buf;
		status = stat(directoryPath.GetData(), &st_buf);
		if (status)
			return false;
		if (S_ISDIR(st_buf.st_mode))
			return true;
		return false;
	#endif
	}

	const String& FileSystem::GetAppDataPath() {
		return mAppDataPath;
	}

	const String& FileSystem::GetCurrentWorkingPath() {
		return mCurrentWorkingPath;
	}

	const String& FileSystem::GetApplicationPath() {
		return mApplicationPath;
	}

	const String& FileSystem::GetRootPath() {
		return mRootPath;
	}

	const String& FileSystem::GetTempFolderPath() {
		return mTempFolderPath;
	}

	const String& FileSystem::GetUserProfilePath() {
		return mUserProfilePath;
	}

	ErrorType FileSystem::NewFile(const String &fileName) {
		FileStream f(fileName);
		if (!f.IsOpen())
			return Error::Throw(kErrorFileCreationFailure,
			String("[%s(\"%s\")]", FastFunctionName,
			fileName.GetCString()));
		f.Close();
		return kErrorNone;
	}

	ErrorType FileSystem::NewDirectory(const String &directoryName) {
	#if defined(FastOSWindows)
		if (0 == CreateDirectory(directoryName.GetWString().mData, 0))
	#elif defined(FastOSUnixLike)
		if (0 != mkdir(directoryName.GetData(), 0777))
	#endif
		{
			return Error::Throw(kErrorFolderCreationFailure,
				String("[%s(\"%s\")]", FastFunctionName,
				directoryName.GetCString()));
		}
		return kErrorNone;
	}

	ErrorType FileSystem::EraseFile(const String &fileName) {
	#if defined(FastOSWindows)
		if (0 != _wremove(fileName.GetWString().mData))
	#elif defined(FastOSUnixLike)
		if (0 != remove(fileName.GetData()))
	#endif
		{
			return Error::Throw(kErrorFileDeletionFailure,
				String("[%s(\"%s\")]", FastFunctionName,
				fileName.GetCString()));
		}
		return kErrorNone;
	}

	ErrorType FileSystem::EraseDirectory(const String &directoryName) {
	#if defined(FastOSWindows)
		if (0 == RemoveDirectory(directoryName.GetWString().mData))
	#elif defined(FastOSUnixLike)
		if (0 != rmdir(directoryName.GetData()))
	#endif
		{
			return Error::Throw(kErrorFolderDeletionFailure,
				String("[%s(\"%s\")]", FastFunctionName,
				directoryName.GetCString()));
		}
		return kErrorNone;
	}

	ErrorType FileSystem::Rename(const String &name, const String &newName) {
	#if defined(FastOSWindows)
		if (0 != _wrename(name.GetWString().mData,
			newName.GetWString().mData))
	#elif defined(FastOSUnixLike)
		if (0 != rename(name.GetData(), newName.GetData()))
	#endif
		{
			return Error::Throw(kErrorFileRenameFailure,
				String("[%s(\"%s\", \"%s\")]", FastFunctionName,
				name.GetCString(), newName.GetCString()));
		}
		return kErrorNone;
	}
}
