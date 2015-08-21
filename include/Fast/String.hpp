/******************************************************************************/
/*                                                                            */
/*  String.hpp                                                                */
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

#ifndef FastStringHppIncluded
#define FastStringHppIncluded

#include <Fast/Types.hpp>
#include <Fast/WString.hpp>
#include <Fast/AsciiString.hpp>

namespace Fast
{
	class FastApi String
	{
	private:
		Char	*mData;
		Int		mDataSize;
		Int		mDataCapacity;
		// Utf8 handling functions
		Int		GetByteIndex(Int charIndex) const;
		Int		GetCharLength(Int byteIndex) const;
		void	FromWCString(const WChar *wcString, Int wcStringSize);
	public:
		// (Con/De)Structors
		String();
		String(const String &that);
		String(const Char *cStringFormat, ...);
		String(const WString &wString);
		String(const WChar *wcString);
		~String();
		// Create From functions
		// TODO: Add extra optional parameters for formatting
		static String	FromByte(Byte x);
		static String	FromUByte(UByte x);
		static String	FromShort(Short x);
		static String	FromUShort(UShort x);
		static String	FromInt(Int x);
		static String	FromUInt(UInt x);
		static String	FromLong(Long x);
		static String	FromULong(ULong x);
		static String	FromFloat(Float x);
		static String	FromDouble(Double x);
		// Size functions
		void	Reserve(Int capacityInBytes);
		void	Resize(Int sizeInBytes);
		Int		GetTextLength() const;
		Int		GetCapacityInBytes() const;
		Int		GetSizeInBytes() const;
		Bool	IsEmpty() const;
		// Get functions
		String		GetSubString(Int charIndex, Int numChars) const;
		void		GetSubString(Int charIndex, Int numChars,
						String *result) const;
		String		GetCharacter(Int charIndex) const;
		void		GetCharacter(Int charIndex, String *result) const;
		Char*		GetData();
		AsciiString	GetAsciiString() const;
		void		GetAsciiString(AsciiString *result) const;
		const Char*	GetCString() const;
		WString		GetWString() const;
		void		GetWString(WString *result) const;
		Byte		GetByte() const;
		Short		GetShort() const;
		Int			GetInt() const;
		Long		GetLong() const;
		Float		GetFloat() const;
		Double		GetDouble() const;
		// Modify functions
		void	Assign(const String &string);
		void	Assign(const Char *cString);
		void	Assign(const WString &wString);
		void	Assign(const WChar *wcString);
		void	Append(const String &string);
		void	Append(const Char *cString);
		void	Append(const WString &wString);
		void	Append(const WChar *wcString);
		void	Prepend(const String &string);
		void	Prepend(const Char *cString);
		void	Prepend(const WString &wString);
		void	Prepend(const WChar *wcString);
		void	Insert(const String &string, Int charIndex);
		void	Insert(const Char *cString, Int charIndex);
		void	Insert(const WString &wString, Int charIndex);
		void	Insert(const WChar *wcString, Int charIndex);
		void	Erase(Int charIndex, Int numChars);
		void	Clear();
		void	MakeUppercase();
		void	MakeUppercase(Int charIndex, Int numChars = 0);
		void	MakeLowercase();
		void	MakeLowercase(Int charIndex, Int numChars = 0);
		void	MakeAscii();
		// Find functions
		Int	FindFirstOf(const String &string, Int startCharIndex = 0) const;
		Int	FindFirstOf(const Char *cString, Int startCharIndex = 0) const;
		Int	FindFirstOf(const WString &wString, Int startCharIndex = 0) const;
		Int	FindFirstOf(const WChar *wcString, Int startCharIndex = 0) const;
		Int	FindLastOf(const String &string, Int startCharIndex = 0) const;
		Int	FindLastOf(const Char *cString, Int startCharIndex = 0) const;
		Int	FindLastOf(const WString &wString, Int startCharIndex = 0) const;
		Int	FindLastOf(const WChar *wcString, Int startCharIndex = 0) const;
		// Assignment operators
		String&	operator= (const String			&that);
		String&	operator= (const Char			*that);
		String&	operator= (const WString		&that);
		String&	operator= (const WChar			*that);
		String&	operator+=(const String			&that);
		String&	operator+=(const Char			*that);
		String&	operator+=(const WString		&that);
		String&	operator+=(const WChar			*that);
		// Add operators
		String			operator+(const String	&that);
		String			operator+(const Char	*that);
		String			operator+(const WString	&that);
		String			operator+(const WChar	*that);
		const String	operator+(const String	&that) const;
		const String	operator+(const Char	*that) const;
		const String	operator+(const WString	&that) const;
		const String	operator+(const WChar	*that) const;
		// Compare operators
		Bool	operator==(const String		&that) const;
		Bool	operator==(const Char		*that) const;
		Bool	operator==(const WString	&that) const;
		Bool	operator==(const WChar		*that) const;
		Bool	operator!=(const String		&that) const;
		Bool	operator!=(const Char		*that) const;
		Bool	operator!=(const WString	&that) const;
		Bool	operator!=(const WChar		*that) const;
	};

	FastApi String	operator+ (const Char  *self, const String &that);
	FastApi Bool	operator==(const Char  *self, const String &that);
	FastApi Bool	operator!=(const Char  *self, const String &that);
	FastApi String	operator+ (const WChar *self, const String &that);
	FastApi Bool	operator==(const WChar *self, const String &that);
	FastApi Bool	operator!=(const WChar *self, const String &that);
}

#endif // FastStringHppIncluded
