/******************************************************************************/
/*                                                                            */
/*  System.cpp                                                                */
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

#include <Fast/System.hpp>

#include <cstdlib>
#include <ctime>
#include <cstring>
#if defined(FastOSUnixLike)
#	include <unistd.h>
#	include <sys/time.h>
#endif

#include "Undefs.hpp"

namespace Fast
{
	namespace System
	{
		Platform GetPlatform() {
		#if defined(FastOSWindows)
			return kPlatformWindows;
		#elif defined(FastOSLinux)
			return kPlatformLinux;
		#elif defined(FastOSMacOSX)
			return kPlatformMacOSX;
		#endif
		}

		Clock GetTimeAndDate() {
			Clock clock;
		#if defined(FastOSWindows)
			SYSTEMTIME st;
			GetLocalTime(&st);
			clock.mSecond				= st.wSecond;
			clock.mMinute				= st.wMinute;
			clock.mHour					= st.wHour;
			clock.mWeekday				= (Weekday)st.wDayOfWeek;
			clock.mDay					= st.wDay;
			clock.mMonth				= (Month)st.wMonth;
			clock.mYear					= st.wYear;
			clock.mTotalMicroseconds	= (Long)timeGetTime();
		#elif defined(FastOSUnixLike)
			struct timeval now;
			time_t t = time(0);
			tm *localTime = localtime(&t);
			gettimeofday(&now, NULL);
			clock.seconds				= localTime->tm_sec;
			clock.minutes				= localTime->tm_min;
			clock.hours					= localTime->tm_hour;
			clock.weekday				= (Weekday)localTime->tm_wday;
			clock.day					= localTime->tm_mday;
			clock.month					= (Month)localTime->tm_mon;
			clock.year					= 1900 + localTime->tm_year;
			clock.mTotalMicroseconds	= ((Long)now.tv_sec * 1000000L) + now.tv_usec;
		#endif
			return clock;
		}

		String GetCurrentUserName() {
		#if defined(FastOSWindows)
			WChar uname[100];
			DWORD dwSize = sizeof(uname);
			GetUserName(uname, &dwSize);
			return uname;
		#elif defined(FastOSUnixLike)
			return getlogin();
		#endif
		}

		String GetPCName() {
		#if defined(FastOSWindows)
			WChar pcname[kFastMaxPCNameLength+1];
			memset(pcname, 0, (kFastMaxPCNameLength+1) * sizeof(WChar));
			DWORD dwSize = sizeof(kFastMaxPCNameLength);
			GetComputerName(pcname, &dwSize);
			return pcname;
		#elif defined(FastOSUnixLike)
			Char pcname[kFastMaxPCNameLength+1];
			memset(pcname, 0, kFastMaxPCNameLength+1);
			gethostname(pcname, kFastMaxPCNameLength);
			return pcname;
		#endif
		}
		
		Bool IsBigEndian() {
			Int num = 1;
			Bool isBigEndian = !(*(Byte*)&num==1);
			return isBigEndian;
		}

		Bool IsLittleEndian() {
			Int num = 1;
			Bool isBigEndian = !(*(Byte*)&num==1);
			return !isBigEndian;
		}

		Short SwapBytes(Short var) {
			Byte temp[2], swap;
			memcpy(&temp, &var, sizeof(var));
			swap = temp[0];
			temp[0] = temp[1];
			temp[1] = swap;
			memcpy(&var, &temp, sizeof(var));
			return var;
		}

		UShort SwapBytes(UShort var) {
			UByte temp[2], swap;
			memcpy(&temp, &var, sizeof(var));
			swap = temp[0];
			temp[0] = temp[1];
			temp[1] = swap;
			memcpy(&var, &temp, sizeof(var));
			return var;
		}

		Int SwapBytes(Int var) {
			Byte temp[4], swap;
			UByte size = sizeof(var);
			memcpy(&temp[0], &var, size);
			for (int i = 0; i < (size / 2); i++) {
				swap = temp[i];
				temp[i] = temp[(size-1)-i];
				temp[(size-1)-i] = swap;
			}
			memcpy(&var, &temp[0], size);
			return var;
		}

		UInt SwapBytes(UInt var) {
			UByte temp[4], swap;
			UByte size = sizeof(var);
			memcpy(&temp[0], &var, size);
			for (int i = 0; i < (size / 2); i++) {
				swap = temp[i];
				temp[i] = temp[(size-1)-i];
				temp[(size-1)-i] = swap;
			}
			memcpy(&var, &temp[0], size);
			return var;
		}

		Long SwapBytes(Long var) {
			Byte temp[8], swap;
			UByte size = sizeof(var);
			memcpy(&temp[0], &var, size);
			for (int i = 0; i < (size / 2); i++) {
				swap = temp[i];
				temp[i] = temp[(size-1)-i];
				temp[(size-1)-i] = swap;
			}
			memcpy(&var, &temp[0], size);
			return var;
		}

		ULong SwapBytes(ULong var) {
			UByte temp[8], swap;
			UByte size = sizeof(var);
			memcpy(&temp[0], &var, size);
			for (int i = 0; i < (size / 2); i++) {
				swap = temp[i];
				temp[i] = temp[(size-1)-i];
				temp[(size-1)-i] = swap;
			}
			memcpy(&var, &temp[0], size);
			return var;
		}

		Float SwapBytes(Float var) {
			union
			{
				Byte b[4];
				Float f;
			} in, out;
			in.f = var;
			out.b[0] = in.b[3];
			out.b[1] = in.b[2];
			out.b[2] = in.b[1];
			out.b[3] = in.b[0];
			return out.f;
		}

		Double SwapBytes(Double var) {
			union
			{
				Byte b[8];
				Double d;
			} in, out;
			in.d = var;
			out.b[0] = in.b[7];
			out.b[1] = in.b[6];
			out.b[2] = in.b[5];
			out.b[3] = in.b[4];
			out.b[4] = in.b[3];
			out.b[5] = in.b[2];
			out.b[6] = in.b[1];
			out.b[7] = in.b[0];
			return out.d;
		}
	}
}
