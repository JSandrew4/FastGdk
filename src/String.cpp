/******************************************************************************/
/*                                                                            */
/*  String.cpp                                                                */
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

#include <Fast/String.hpp>

#if defined(FastOSWindows)
#	include <Windows.h>
#elif defined(FastOSUnixLike)
#	include <iconv.h>
#	include <wctype.h>
#endif

#include <cwchar>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>

#include "Undefs.hpp"

namespace Fast
{
	Int WCStringLength(const WChar *wcString) {
		if (!wcString)
			return 0;
		return wcslen(wcString);
	}

	Int StringLength(const Char *cString) {
		if (!cString)
			return 0;
		return strlen(cString);
	}

	Int StringCompare(const Char *cString1, const Char *cString2) {
		if (!cString1 && !cString2)
			return 0;
		if (!cString1 || !cString2)
			return 1;
		return strcmp(cString1, cString2);
	}

	Int String::GetByteIndex(Int charIndex) const {
		Int byteIndex = 0;
		while (byteIndex < mDataSize || charIndex > 0) {
			byteIndex += GetCharLength(byteIndex);
			charIndex--;
		}
		if (charIndex > 0)
			return 0;
		else
			return byteIndex;
	}

	Int String::GetCharLength(Int byteIndex) const {
		if (mData[byteIndex] > 0)
			return 1;
		switch (0xF0 & mData[byteIndex])
		{
		case 0xE0:
			return 3;
		case 0xF0:
			return 4;
		default:
			return 2;
		};
	}

	void String::FromWCString(const WChar *wcString, Int wcStringSize) {
		if (!wcString || 0 >= wcStringSize)
			return;
	#if defined(FastOSWindows)
		Resize(WideCharToMultiByte(CP_UTF8, 0, wcString,
			wcStringSize, 0, 0, 0, 0));
		WideCharToMultiByte(CP_UTF8, 0, wcString,
			wcStringSize, mData, mDataSize, 0, 0);
	#elif defined(FastOSUnixLike)
		Int tempStrSize = wcStringSize * 4;
		Char *tempStr = (Char*)calloc(tempStrSize + 1, sizeof(Char));
		Char *sIn = (Char*)wcString;
		Char *sOut = tempStr;
		size_t lIn = (size_t)tempStrSize;
		size_t lOut = (size_t)tempStrSize;
		iconv_t conv = iconv_open("UTF-8", "WCHAR_T");
		iconv(conv, &sIn, &lIn, &sOut, &lOut);
		iconv_close(conv);
		Resize(StringLength(tempStr));
		memcpy(mData, tempStr, mDataSize);
		free(tempStr);
	#endif
	}

	String::String() {
		mData = 0;
		mDataSize = 0;
		mDataCapacity = 0;
	}

	String::String(const String &that) {
		mData = 0;
		mDataSize = 0;
		mDataCapacity = 0;
		Assign(that);
	}

	String::String(const Char *cStringFormat, ...) {
		mData = 0;
		mDataSize = 0;
		mDataCapacity = 0;
		Int newCStringSize = 0;
		va_list vl;
		va_start(vl, cStringFormat);
	#if defined(FastOSWindows)
		newCStringSize = _vscprintf(cStringFormat, vl);
	#elif defined(FastOSUnixLike)
		newCStringSize = vsnprintf(0, 0, that.GetData(), vl);
	#endif
		va_end(vl);
		if (0 < newCStringSize) {
			Resize(newCStringSize);
			va_start(vl, cStringFormat);
		#if defined(FastOSWindows)
			newCStringSize = _vsnprintf_s(mData, newCStringSize + 1,
				_TRUNCATE, cStringFormat, vl);
		#elif defined(FastOSUnixLike)
			newCStringSize = vsnprintf(mData, newCStringSize,
				cStringFormat, vl);
		#endif
			va_end(vl);
			Resize(newCStringSize);
		}
	}

	String::String(const WString &wString) {
		mData = 0;
		mDataSize = 0;
		mDataCapacity = 0;
		Assign(wString);
	}

	String::String(const WChar *wcString) {
		mData = 0;
		mDataSize = 0;
		mDataCapacity = 0;
		Assign(wcString);
	}

	String::~String() {
		free(mData);
	}

	String String::FromByte(Byte x) {
		return String("%hhd", x);
	}

	String String::FromUByte(UByte x) {
		return String("%hhu", x);
	}

	String String::FromShort(Short x) {
		return String("%hd", x);
	}

	String String::FromUShort(UShort x) {
		return String("%hu", x);
	}

	String String::FromInt(Int x) {
		return String("%d", x);
	}

	String String::FromUInt(UInt x) {
		return String("%u", x);
	}

	String String::FromLong(Long x) {
		return String("%lld", x);
	}

	String String::FromULong(ULong x) {
		return String("%llu", x);
	}

	String String::FromFloat(Float x) {
		return String("%F", x);
	}

	String String::FromDouble(Double x) {
		return String("%F", x);
	}

	void String::Reserve(Int capacityInBytes) {
		if (capacityInBytes == 0 || capacityInBytes < mDataCapacity)
			return;
		capacityInBytes++;
		if (mDataCapacity == 0)
			mData = (Char*)calloc(capacityInBytes, sizeof(Char));
		else {
			Char *tempData = (Char*)calloc(capacityInBytes, sizeof(Char));
			memcpy(tempData, mData, mDataCapacity);
			free(mData);
			mData = tempData;
		}
		mDataCapacity = capacityInBytes;
	}

	void String::Resize(Int sizeInBytes) {
		if (sizeInBytes == mDataSize)
			return;
		if (sizeInBytes >= mDataCapacity) {
			Int newCapacity = (mDataCapacity < 2) ? 2 : mDataCapacity;
			while (sizeInBytes > newCapacity)
				newCapacity *= 2;
			Reserve(newCapacity);
		}
		for (Int i = mDataSize; i < sizeInBytes; i++)
			mData[i] = 0;
		mDataSize = sizeInBytes;
		mData[mDataSize] = 0;
	}

	Int String::GetTextLength() const {
		Int textLength = 0;
		for (Int i = 0, iBefore = 0; i < mDataSize;) {
			if (mData[i] > 0) {
				iBefore = i;
				while (mData[i] > 0)
					i++;
				textLength += i - iBefore;
				continue;
			}
			switch (0xF0 & mData[i])
			{
			case 0xE0:
				i += 3;
				break;
			case 0xF0:
				i += 4;
				break;
			default:
				i += 2;
				break;
			};
			textLength++;
		}
		return textLength;
	}

	Int String::GetCapacityInBytes() const {
		return mDataCapacity - 1; // Trim terminator byte
	}

	Int String::GetSizeInBytes() const {
		return mDataSize;
	}

	Bool String::IsEmpty() const {
		return mDataSize == 0;
	}

	String String::GetSubString(Int charIndex, Int numChars) const {
		String subString;
		GetSubString(charIndex, numChars, &subString);
		return subString;
	}

	void String::GetSubString(Int charIndex, Int numChars, String *result) const {
		Int startByteIndex = GetByteIndex(charIndex);
		Int endByteIndex = GetByteIndex(charIndex + numChars);
		Int numBytes = startByteIndex + GetCharLength(endByteIndex);
		result->Resize(numBytes);
		memcpy(result->mData, &mData[startByteIndex], numBytes);
	}

	String String::GetCharacter(Int charIndex) const {
		String subString;
		GetCharacter(charIndex, &subString);
		return subString;
	}

	void String::GetCharacter(Int charIndex, String *result) const {
		GetSubString(charIndex, 1, result);
	}

	Char* String::GetData() {
		return mData;
	}

	AsciiString String::GetAsciiString() const {
		AsciiString asciiString;
		GetAsciiString(&asciiString);
		return asciiString;
	}

	void String::GetAsciiString(AsciiString *result) const {
		free(result->mData);
		result->mData = 0;
		result->mSize = GetTextLength();
		result->mData = (Char*)calloc(result->mSize + 1, sizeof(Char));
		for (Int i = 0, j = 0; i < mDataSize || j < result->mSize; j++) {
			if (mData[i] > 0) {
				result->mData[j] = mData[i];
				i++;
			} else {
				result->mData[j] = '?';
				switch (0xF0 & mData[i]) {
				case 0xE0:
					i += 3;
					break;
				case 0xF0:
					i += 4;
					break;
				default:
					i += 2;
					break;
				}
			}
		}
	}

	const Char* String::GetCString() const {
		return mData;
	}

	WString String::GetWString() const {
		WString wString;
		GetWString(&wString);
		return wString;
	}

	void String::GetWString(WString *result) const {
		free(result->mData);
		result->mData = 0;
		result->mSize = 0;
		if (!mData || 0 >= mDataSize)
			return;
	#if defined(FastOSWindows)
		result->mSize = MultiByteToWideChar(CP_UTF8, 0, mData, -1, 0, 0) - 1;
		if (0 >= result->mSize) {
			result->mSize = 0;
			return;
		}
		result->mData = (WChar*)calloc(result->mSize + 1, sizeof(WChar));
		MultiByteToWideChar(CP_UTF8, 0, mData, -1,
			result->mData, result->mSize);
	#elif defined(FastOSUnixLike)
		Int tempWStrSize = mDataSize;
		WChar *tempWStr = (WChar*)calloc(tempWStrSize + 1, sizeof(WChar));
		Char *sIn = mData;
		Char *sOut = (Char*)tempWStr;
		size_t lIn = (size_t)mDataSize;
		size_t lOut = (size_t)(tempWStrSize * sizeof(WChar));
		iconv_t conv = iconv_open("WCHAR_T", "UTF-8");
		iconv(conv, &sIn, &lIn, &sOut, &lOut);
		iconv_close(conv);
		result->mSize = WCStringLength(tempWStr);
		result->mData = (WChar*)calloc(result->mSize + 1, sizeof(WChar));
		memcpy(result->mData, tempWStr, result->mSize * sizeof(WChar));
		free(tempWStr);
	#endif
	}

	Byte String::GetByte() const {
		return (Byte)atoi(mData);
	}

	Short String::GetShort() const {
		return (Short)atoi(mData);
	}

	Int String::GetInt() const {
		return atoi(mData);
	}

	Long String::GetLong() const {
	#if defined(FastOSWindows)
		return (Long)_strtoi64(mData, 0, 10);
	#elif defined(FastOSUnixLike)
		return (Long)strtoll(mData, 0, 10);
	#endif
	}

	Float String::GetFloat() const {
		return (Float)atof(mData);
	}

	Double String::GetDouble() const {
		return atof(mData);
	}

	void String::Assign(const String &string) {
		Resize(string.mDataSize);
		memcpy(mData, string.mData, mDataSize);
	}

	void String::Assign(const Char *cString) {
		if (!cString)
			return;
		Resize(StringLength(cString));
		memcpy(mData, cString, mDataSize);
	}

	void String::Assign(const WString &wString) {
		FromWCString(wString.mData, wString.mSize);
	}

	void String::Assign(const WChar *wcString) {
		if (!wcString)
			return;
		FromWCString(wcString, WCStringLength(wcString));
	}

	void String::Append(const String &string) {
		Resize(mDataSize + string.mDataSize);
		memcpy(&mData[mDataSize-string.mDataSize],
			string.mData, string.mDataSize);
	}

	void String::Append(const Char *cString) {
		Int cstrSize = StringLength(cString);
		Resize(mDataSize + cstrSize);
		memcpy(&mData[mDataSize-cstrSize], cString, cstrSize);
	}

	void String::Append(const WString &wString) {
		Append(String(wString));
	}

	void String::Append(const WChar *wcString) {
		Append(String(wcString));
	}

	void String::Prepend(const String &string) {
		String endString(*this);
		Clear();
		Append(string);
		Append(endString);
	}

	void String::Prepend(const Char *cString) {
		String endString(*this);
		Clear();
		Append(cString);
		Append(endString);
	}

	void String::Prepend(const WString &wString) {
		Prepend(String(wString));
	}

	void String::Prepend(const WChar *wcString) {
		Prepend(String(wcString));
	}

	void String::Insert(const String &string, Int charIndex) {
		if (charIndex == 0) {
			Prepend(string);
		} else {
			String sub1 = GetSubString(0, charIndex - 1);
			String sub2 = GetSubString(charIndex, GetTextLength() - 1);
			Clear();
			Append(sub1);
			Append(string);
			Append(sub2);
		}
	}

	void String::Insert(const Char *cString, Int charIndex) {
		if (charIndex == 0) {
			Prepend(cString);
		} else {
			Int textLength = GetTextLength();
			String sub1 = GetSubString(0, charIndex - 1);
			String sub2 = GetSubString(charIndex, textLength - charIndex);
			Clear();
			Append(sub1);
			Append(cString);
			Append(sub2);
		}
	}

	void String::Insert(const WString &wString, Int charIndex) {
		Insert(String(wString), charIndex);
	}

	void String::Insert(const WChar *wcString, Int charIndex) {
		Insert(String(wcString), charIndex);
	}

	void String::Erase(Int charIndex, Int numChars) {
		if (numChars == 0)
			return;
		Int textLength = GetTextLength();
		if (charIndex == 0 && numChars == textLength) {
			Clear();
		} else if (charIndex == 0) {
			Assign(GetSubString(numChars + 1, textLength - 1));
		} else if ((charIndex + numChars) == textLength) {
			Assign(GetSubString(0, charIndex - 1));
		} else {
			String startSubString = GetSubString(0, charIndex - 1);
			String endSubString = GetSubString(charIndex + numChars,
				textLength - (charIndex + numChars));
			Clear();
			Append(startSubString);
			Append(endSubString);
		}
	}

	void String::Clear() {
		Resize(0);
	}

	void String::MakeUppercase() {
		WString wString = GetWString();
		for (Int i = 0; i < wString.mSize; i++)
			towupper(wString.mData[i]);
		Assign(wString);
	}

	void String::MakeUppercase(Int charIndex, Int numChars) {
		String ucSubString = GetSubString(charIndex, numChars);
		Erase(charIndex, numChars);
		ucSubString.MakeLowercase();
		Insert(ucSubString, charIndex);
	}

	void String::MakeLowercase() {
		WString wString = GetWString();
		for (Int i = 0; i < wString.mSize; i++)
			towlower(wString.mData[i]);
		Assign(wString);
	}

	void String::MakeLowercase(Int charIndex, Int numChars) {
		String lcSubString = GetSubString(charIndex, numChars);
		Erase(charIndex, numChars);
		lcSubString.MakeLowercase();
		Insert(lcSubString, charIndex);
	}

	void String::MakeAscii() {
		String asciiString;
		asciiString.Resize(GetTextLength());
		for (Int i = 0, j = 0; i < mDataSize || j >= asciiString.mDataSize; j++) {
			if (mData[i] > 0) {
				asciiString.mData[j] = mData[i];
				i++;
			} else {
				asciiString.mData[j] = '?';
				switch (0xF0 & mData[i]) {
				case 0xE0:
					i += 3;
					break;
				case 0xF0:
					i += 4;
					break;
				default:
					i += 2;
					break;
				}
			}
		}
		Assign(asciiString);
	}

	Int String::FindFirstOf(const String &string, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindFirstOf(const Char *cString, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindFirstOf(const WString &wString, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindFirstOf(const WChar *wcString, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindLastOf(const String &string, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindLastOf(const Char *cString, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindLastOf(const WString &wString, Int startCharIndex) const {
		// TODO
		return -1;
	}

	Int String::FindLastOf(const WChar *wcString, Int startCharIndex) const {
		// TODO
		return -1;
	}

	String& String::operator=(const String &that) {
		this->Assign(that);
		return *this;
	}

	String& String::operator=(const Char *that) {
		this->Assign(that);
		return *this;
	}

	String& String::operator=(const WString &that) {
		this->Assign(that);
		return *this;
	}

	String& String::operator=(const WChar *that) {
		this->Assign(that);
		return *this;
	}

	String& String::operator+=(const String &that) {
		this->Append(that);
		return *this;
	}

	String& String::operator+=(const Char *that) {
		this->Append(that);
		return *this;
	}

	String& String::operator+=(const WString &that) {
		this->Append(that);
		return *this;
	}

	String& String::operator+=(const WChar *that) {
		this->Append(that);
		return *this;
	}

	String String::operator+(const String &that) {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	String String::operator+(const Char *that) {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	String String::operator+(const WString &that) {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	String String::operator+(const WChar *that) {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	const String String::operator+(const String &that) const {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	const String String::operator+(const Char *that) const {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	const String String::operator+(const WString &that) const {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	const String String::operator+(const WChar *that) const {
		String newString(*this);
		newString.Append(that);
		return newString;
	}

	Bool String::operator==(const String &that) const {
		if (this->mDataSize != that.mDataSize)
			return false;
		return StringCompare(this->mData, that.mData) ? false : true;
	}

	Bool String::operator==(const Char *that) const {
		if (this->mDataSize != StringLength(that))
			return false;
		return StringCompare(this->mData, that) ? false : true;
	}

	Bool String::operator==(const WString &that) const {
		return *this == String(that);
	}

	Bool String::operator==(const WChar *that) const {
		return *this == String(that);
	}

	Bool String::operator!=(const String &that) const {
		if (this->mDataSize != that.mDataSize)
			return true;
		return StringCompare(this->mData, that.mData) ? true : false;
	}

	Bool String::operator!=(const Char *that) const {
		if (this->mDataSize != StringLength(that))
			return true;
		return StringCompare(this->mData, that) ? true : false;
	}

	Bool String::operator!=(const WString &that) const {
		return *this != String(that);
	}

	Bool String::operator!=(const WChar *that) const {
		return *this != String(that);
	}

	String operator+(const Char *self, const String &that) {
		return String(self) + that;
	}

	Bool operator==(const Char *self, const String &that) {
		if (StringLength(self) != that.GetSizeInBytes())
			return false;
		if (StringCompare(self, that.GetCString()))
			return false;
		return true;
	}

	Bool operator!=(const Char *self, const String &that) {
		if (StringLength(self) != that.GetSizeInBytes())
			return true;
		if (StringCompare(self, that.GetCString()))
			return true;
		return false;
	}

	String operator+(const WChar *self, const String &that) {
		return String(self) + that;
	}

	Bool operator==(const WChar *self, const String &that) {
		if (String(self) != that)
			return false;
		return true;
	}

	Bool operator!=(const WChar *self, const String &that) {
		if (String(self) != that)
			return true;
		return false;
	}
}
