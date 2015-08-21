/******************************************************************************/
/*                                                                            */
/*  StreamWriter.hpp                                                          */
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

#ifndef FastStreamWriterHppIncluded
#define FastStreamWriterHppIncluded

#include <Fast/Types.hpp>
#include <Fast/StreamBase.hpp>

namespace Fast
{
	class String;
	class Vector2D;
	class Vector3D;
	class Vector4D;
	class Quaternion;
	class Matrix;
	class Color;

	class FastApi StreamWriter : public virtual StreamBase
	{
	public:
		virtual void	Write(const Byte *data, Long size) = 0;
		// Write functions
		void	WriteBool(Bool var);
		void	WriteUByte(UByte var);
		void	WriteByte(Byte var);
		void	WriteUShort(UShort var);
		void	WriteShort(Short var);
		void	WriteUInt(UInt var);
		void	WriteInt(Int var);
		void	WriteULong(ULong var);
		void	WriteLong(Long var);
		void	WriteFloat(Float var);
		void	WriteDouble(Double var);
		void	WriteString(const String &var, Bool writeNullTerminator = true);
		void	WriteLine(const String &var);
		void	WriteVector2D(const Vector2D &var);
		void	WriteVector3D(const Vector3D &var);
		void	WriteVector4D(const Vector4D &var);
		void	WriteMatrix(const Matrix &var);
		void	WriteQuaternion(const Quaternion &var);
		void	WriteColor(const Color &var);
	};
}

#endif // FastStreamWriterHppIncluded
