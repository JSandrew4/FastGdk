/******************************************************************************/
/*                                                                            */
/*  StreamReader.cpp                                                          */
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

#include <Fast/StreamReader.hpp>
#include <Fast/System.hpp>
#include <Fast/Array.hpp>

#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	Bool StreamReader::ReadBool() {
		Bool var = false;
		Read((Byte*)&var, sizeof(var));
		return var;
	}

	UByte StreamReader::ReadUByte() {
		UByte var = 0;
		Read((Byte*)&var, sizeof(var));
		return var;
	}

	Byte StreamReader::ReadByte() {
		Byte var = 0;
		Read(&var, sizeof(var));
		return var;
	}

	UShort StreamReader::ReadUShort() {
		UShort var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	Short StreamReader::ReadShort() {
		Short var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	UInt StreamReader::ReadUInt() {
		UInt var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	Int StreamReader::ReadInt() {
		Int var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	ULong StreamReader::ReadULong() {
		ULong var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	Long StreamReader::ReadLong() {
		Long var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	Float StreamReader::ReadFloat() {
		Float var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	Double StreamReader::ReadDouble() {
		Double var = 0;
		Read((Byte*)&var, sizeof(var));
		return (mIsEndianAware && System::IsBigEndian()) ?
			System::SwapBytes(var) : var;
	}

	String StreamReader::ReadString(Int lengthInBytes) {
		String ret;
		ReadString(&ret, lengthInBytes);
		return ret;
	}

	void StreamReader::ReadString(String *result, Int lengthInBytes) {
		if (lengthInBytes) {
			Array<Char> chars;
			chars.SetElementCount(lengthInBytes);
			Read((Byte*)&chars[0], lengthInBytes);
			*result = &chars[0];
		}
	}

	String StreamReader::ReadString(const String &delimiter) {
		String ret;
		ReadString(&ret, delimiter);
		return ret;
	}

	void StreamReader::ReadString(String *result, const String &delimiter) {
		Array<Char> retString;
		Array<Char> delString;
		String strDelimiter = delimiter;
		Char c;
		if (strDelimiter.IsEmpty()) {
			strDelimiter.Resize(1);
			strDelimiter.Append("\0");
		}
		while (true) {
			c = ReadByte();
			if (this->GetError())
				break;
			if (c == strDelimiter.GetData()[0]) {
				delString.Clear();
				delString.Append(c);
				for (Int i = 1; i < strDelimiter.GetSizeInBytes(); i++) {
					c = ReadByte();
					if (this->GetError()) {
						for (Int j = 0; j < delString.GetElementCount(); j++)
							retString.Append(delString[j]);
						break;
					}
					delString.Append(c);
					if (c != strDelimiter.GetData()[i])
						break;
				}
				if (strDelimiter.GetSizeInBytes() > delString.GetElementCount())
					for (Int i = 0; i < delString.GetElementCount(); i++)
						retString.Append(delString[i]);
				else {
					if (memcmp(strDelimiter.GetData(),
						delString.GetData(), delString.GetElementCount()))
					{
						for (Int i = 0; i < delString.GetElementCount(); i++)
							retString.Append(delString[i]);
					}
					else
						break;
				}
			} else {
				retString.Append(c);
			}
		}
		result->Resize(retString.GetElementCount());
		memcpy((Char*)result->GetData(),
			retString.GetData(), retString.GetElementCount());
	}

	String StreamReader::ReadLine() {
		String ret;
		ReadString(&ret, "\n\r");
		return ret;
	}
	void StreamReader::ReadLine(String *result) {
		ReadString(result, "\n\r");
	}

	Vector2D StreamReader::ReadVector2D() {
		Vector2D var;
		var.mX = ReadFloat();
		var.mY = ReadFloat();
		return var;
	}

	void StreamReader::ReadVector2D(Vector2D *result) {
		result->mX = ReadFloat();
		result->mY = ReadFloat();
	}

	Vector3D StreamReader::ReadVector3D() {
		Vector3D var;
		var.mX = ReadFloat();
		var.mY = ReadFloat();
		var.mZ = ReadFloat();
		return var;
	}

	void StreamReader::ReadVector3D(Vector3D *result) {
		result->mX = ReadFloat();
		result->mY = ReadFloat();
		result->mZ = ReadFloat();
	}

	Vector4D StreamReader::ReadVector4D() {
		Vector4D var;
		var.mX = ReadFloat();
		var.mY = ReadFloat();
		var.mZ = ReadFloat();
		var.mW = ReadFloat();
		return var;
	}

	void StreamReader::ReadVector4D(Vector4D *result) {
		result->mX = ReadFloat();
		result->mY = ReadFloat();
		result->mZ = ReadFloat();
		result->mW = ReadFloat();
	}

	Matrix StreamReader::ReadMatrix() {
		Matrix var;
		for (Int i = 0; i < 16; i++)
			var.mElements[i] = ReadFloat();
		return var;
	}

	void StreamReader::ReadMatrix(Matrix *result) {
		for (Int i = 0; i < 16; i++)
			result->mElements[i] = ReadFloat();
	}

	Quaternion StreamReader::ReadQuaternion() {
		Quaternion var;
		var.mX = ReadFloat();
		var.mY = ReadFloat();
		var.mZ = ReadFloat();
		var.mW = ReadFloat();
		return var;
	}

	void StreamReader::ReadQuaternion(Quaternion *result) {
		result->mX = ReadFloat();
		result->mY = ReadFloat();
		result->mZ = ReadFloat();
		result->mW = ReadFloat();
	}

	Color StreamReader::ReadColor() {
		Color var;
		var.mRed = ReadFloat();
		var.mGreen = ReadFloat();
		var.mBlue = ReadFloat();
		var.mAlpha = ReadFloat();
		return var;
	}

	void StreamReader::ReadColor(Color *result) {
		result->mRed = ReadFloat();
		result->mGreen = ReadFloat();
		result->mBlue = ReadFloat();
		result->mAlpha = ReadFloat();
	}
}
