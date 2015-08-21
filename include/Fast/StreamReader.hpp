/******************************************************************************/
/*                                                                            */
/*  StreamReader.hpp                                                          */
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

#ifndef FastStreamReaderHppIncluded
#define FastStreamReaderHppIncluded

#include <Fast/Types.hpp>
#include <Fast/StreamBase.hpp>
#include <Fast/String.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Vector4D.hpp>
#include <Fast/Color.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Quaternion.hpp>

namespace Fast
{
	class FastApi StreamReader : public virtual StreamBase
	{
	public:
		virtual void	Read(Byte *data, Long size) = 0;
		// Read functions
		Bool		ReadBool();
		UByte		ReadUByte();
		Byte		ReadByte();
		UShort		ReadUShort();
		Short		ReadShort();
		UInt		ReadUInt();
		Int			ReadInt();
		ULong		ReadULong();
		Long		ReadLong();
		Float		ReadFloat();
		Double		ReadDouble();
		String		ReadString(Int lengthInBytes);
		void		ReadString(String *result, Int lengthInBytes);
		String		ReadString(const String &delimiter = "");
		void		ReadString(String *result, const String &delimiter = "");
		String		ReadLine();
		void		ReadLine(String *result);
		Vector2D	ReadVector2D();
		void		ReadVector2D(Vector2D *result);
		Vector3D	ReadVector3D();
		void		ReadVector3D(Vector3D *result);
		Vector4D	ReadVector4D();
		void		ReadVector4D(Vector4D *result);
		Matrix		ReadMatrix();
		void		ReadMatrix(Matrix *result);
		Quaternion	ReadQuaternion();
		void		ReadQuaternion(Quaternion *result);
		Color		ReadColor();
		void		ReadColor(Color *result);
	};
}

#endif // FastStreamReaderHppIncluded
