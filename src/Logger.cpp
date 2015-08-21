/******************************************************************************/
/*                                                                            */
/*  Logger.cpp                                                                */
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

#include <Fast/Logger.hpp>
#include <Fast/String.hpp>
#include <Fast/FileWriter.hpp>

#include "Undefs.hpp"

namespace Fast
{
	void Logger::AppendLog(const String &log) {
		if (mLogArray.GetElementCount() >= mLogCountMax)
			mLogArray.Erase(0);
		mLogArray.Append(log);
	}

	Logger::Logger() {
		mDisplayLevel = kLoggerDisplayNone;
		mShouldWriteToConsole = false;
		SetLogCountMax(64);
	}

	Logger::~Logger() {
		mFile.Close();
	}

	LoggerDisplayLevel Logger::GetDisplayLevel() const {
		return mDisplayLevel;
	}

	const String& Logger::GetOutputFileName() const {
		return mOutputFileName;
	}

	Bool Logger::ShouldWriteToConsole() const {
		return mShouldWriteToConsole;
	}

	Int Logger::GetLogCountMax() const {
		return mLogCountMax;
	}

	Int Logger::GetLogCount() const {
		return mLogArray.GetElementCount();
	}

	const String& Logger::GetLog(Int id) const {
		return mLogArray[id];
	}

	void Logger::SetDisplayLevel(LoggerDisplayLevel level) {
		mDisplayLevel = level;
	}

	void Logger::SetOutputFileName(const String &fileName) {
		mFile.Close();
		mOutputFileName = fileName;
		if (!mOutputFileName.IsEmpty())
			mFile.Open(mOutputFileName);
	}

	void Logger::SetShouldWriteToConsole(Bool toConsole) {
		mShouldWriteToConsole = toConsole;
	}

	void Logger::SetLogCountMax(Int id) {
		mLogCountMax = id;
		mLogArray.SetElementCountCapacity(mLogCountMax);
	}

	void Logger::Log(const String &log) {
		if (mDisplayLevel == kLoggerDisplayAll) {
			if (mShouldWriteToConsole) {
				mSystemConsole.Print(log);
				mSystemConsole.Flush();
			}
			if (!mOutputFileName.IsEmpty())
				mFile.WriteLine(log);
			AppendLog(log);
		}
	}

	void Logger::LogError(const String &log) {
		if (mDisplayLevel == kLoggerDisplayAll ||
			mDisplayLevel == kLoggerDisplayErrorAndCritical)
		{
			if (mShouldWriteToConsole) {
				mSystemConsole.Print(log);
				mSystemConsole.Flush();
			}
			if (!mOutputFileName.IsEmpty())
				mFile.WriteLine(log);
			AppendLog(log);
		}
	}

	void Logger::LogCritical(const String &log) {
		if (mDisplayLevel == kLoggerDisplayAll ||
			mDisplayLevel == kLoggerDisplayErrorAndCritical ||
			mDisplayLevel == kLoggerDisplayCriticalOnly)
		{
			if (mShouldWriteToConsole) {
				mSystemConsole.Print(log);
				mSystemConsole.Flush();
			}
			if (!mOutputFileName.IsEmpty()) {
				mFile.WriteLine(log);
				mFile.Flush();
			}
			AppendLog(log);
		}
	}
}