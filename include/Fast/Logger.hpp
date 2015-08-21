/******************************************************************************/
/*                                                                            */
/*  Logger.hpp                                                                */
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

#ifndef FastLoggerHppIncluded
#define FastLoggerHppIncluded

#include <Fast/Types.hpp>
#include <Fast/LoggerDisplayLevel.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/FileWriter.hpp>
#include <Fast/SystemConsole.hpp>

#undef GetMessage

namespace Fast
{
	class String;

	class FastApi Logger
	{
	private:
		String				mOutputFileName;
		LoggerDisplayLevel	mDisplayLevel;
		Bool				mShouldWriteToConsole;
		SystemConsole		mSystemConsole;
		FileWriter			mFile;
		Int					mLogCountMax;
		Array<String>		mLogArray;
		// Hide these functions. No reason to copy logs
		Logger(const Logger &that) { }
		Logger& operator=(const Logger &that) { return *this; }
		// Misc hidden functions
		void	AppendLog(const String &log);
	public:
		// (Con/De)structors
		Logger();
		~Logger();
		// Get functions
		LoggerDisplayLevel	GetDisplayLevel() const;
		const String&		GetOutputFileName() const;
		Bool				ShouldWriteToConsole() const;
		Int					GetLogCountMax() const;
		Int					GetLogCount() const;
		const String&		GetLog(Int id) const;
		// Set functions
		void	SetDisplayLevel(LoggerDisplayLevel level);
		void	SetOutputFileName(const String &fileName);
		void	SetShouldWriteToConsole(Bool toConsole);
		void	SetLogCountMax(Int max);
		// Log functions
		void	Log(const String &log);
		void	LogError(const String &log);
		void	LogCritical(const String &log);
	};
}

#endif // FastLoggerHppIncluded