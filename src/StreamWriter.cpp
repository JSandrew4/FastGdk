/******************************************************************************/
/*                                                                            */
/*  StreamWriter.cpp                                                          */
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

#include <Fast/StreamWriter.hpp>
#include <Fast/String.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Vector4D.hpp>
#include <Fast/Color.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/System.hpp>

#include "Undefs.hpp"

namespace Fast
{
	void StreamWriter::WriteBool(Bool var) {
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteUByte(UByte var) {
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteByte(Byte var) {
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteUShort(UShort var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteShort(Short var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteUInt(UInt var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteInt(Int var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteULong(ULong var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteLong(Long var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteFloat(Float var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteDouble(Double var) {
		if (mIsEndianAware && System::IsBigEndian())
			var = System::SwapBytes(var);
		Write((Byte*)&var, sizeof(var));
	}

	void StreamWriter::WriteString(const String &var, Bool writeNullTerminator)
	{
		Write(var.GetCString(), var.GetSizeInBytes());
		if (writeNullTerminator)
			Write("\0", 1);
	}

	void StreamWriter::WriteLine(const String &var) {
		String toWrite = var;
		for (Int i = 0; i < toWrite.GetSizeInBytes(); i++)
			if (toWrite.GetCharacter(i) == "\n")
				toWrite.Insert("\r", ++i);
		Write((Byte*)toWrite.GetCString(), toWrite.GetSizeInBytes());
		Write("\n\r", 2);
	}

	void StreamWriter::WriteVector2D(const Vector2D &var) {
		WriteFloat(var.mX);
		WriteFloat(var.mY);
	}

	void StreamWriter::WriteVector3D(const Vector3D &var) {
		WriteFloat(var.mX);
		WriteFloat(var.mY);
		WriteFloat(var.mZ);
	}

	void StreamWriter::WriteVector4D(const Vector4D &var) {
		WriteFloat(var.mX);
		WriteFloat(var.mY);
		WriteFloat(var.mZ);
		WriteFloat(var.mW);
	}

	void StreamWriter::WriteMatrix(const Matrix &var) {
		for (Int i = 0; i < 16; i++)
			WriteFloat(var.mElements[i]);
	}

	void StreamWriter::WriteQuaternion(const Quaternion &var) {
		WriteFloat(var.mX);
		WriteFloat(var.mY);
		WriteFloat(var.mZ);
		WriteFloat(var.mW);
	}

	void StreamWriter::WriteColor(const Color &var) {
		WriteFloat(var.mRed);
		WriteFloat(var.mGreen);
		WriteFloat(var.mBlue);
		WriteFloat(var.mAlpha);
	}
}
