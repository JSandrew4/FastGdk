/******************************************************************************/
/*                                                                            */
/*  Vertex.hpp                                                                */
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

#ifndef FastVertexHppIncluded
#define FastVertexHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Color.hpp>
#include <Fast/VertexStruct.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi Vertex
	{
	protected:
		Vector3D		mPosition;
		Vector3D		mNormal;
		Vector2D		mTextureCoords;
		Color			mColor;
		VertexStruct	mPlainOldData;
	public:
		// (Con/De)structors
		Vertex();
		Vertex(const Vertex &that);
		Vertex(const Vector3D &position);
		Vertex(Float positionX, Float positionY, Float positionZ);
		Vertex(const Vector3D &position, const Vector2D &textureCoords);
		Vertex(Float positionX, Float positionY, Float positionZ,
			Float textureCoordS, Float textureCoordT);
		Vertex(const Vector3D &position, const Vector3D &normal,
			const Vector2D &textureCoords, const Color &color);
		Vertex(Float positionX, Float positionY, Float positionZ,
			Float normalX, Float normalY, Float normalZ,
			Float textureCoordS, Float textureCoordT,
			Float red, Float green, Float blue, Float alpha);
		Vertex(const VertexStruct &plainOldData);
		~Vertex();
		// Setters
		void	SetPosition(const Vector3D &position);
		void	SetPosition(Float x, Float y, Float z);
		void	SetNormal(const Vector3D &normal);
		void	SetNormal(Float x, Float y, Float z);
		void	SetTextureCoords(const Vector2D &textureCoords);
		void	SetTextureCoords(Float s, Float t);
		void	SetColor(const Color &color);
		void	SetColor(Float red, Float green, Float blue, Float alpha);
		// Getters
		const VertexStruct&	GetPlainOldData() const;
		const Vector3D&		GetPosition() const;
		const Vector3D&		GetNormal() const;
		const Vector2D&		GetTextureCoords() const;
		const Color&		GetColor() const;
		// Operators
		Vertex&	operator= (const Vertex &that);
		Bool	operator==(const Vertex &that) const;
		Bool	operator!=(const Vertex &that) const;
	};

	template class FastApi Array<Vertex>;
	/*
	class FastApi Vertex
	{
	protected:
		Vector3D		mPosition;
		Vector3D		mNormal;
		Vector2D		mTextureCoords;
		Color			mColor;
		VertexStruct	mPlainOldData;
	public:
		// (Con/De)structors
		Vertex();
		Vertex(const Vertex &that);
		Vertex(const Vector3D &position);
		Vertex(Float positionX, Float positionY, Float positionZ);
		Vertex(const Vector3D &position, const Vector2D &textureCoords);
		Vertex(Float positionX, Float positionY, Float positionZ,
			Float textureCoordS, Float textureCoordT);
		Vertex(const Vector3D &position, const Vector3D &normal,
			const Vector2D &textureCoords, const Color &color);
		Vertex(Float positionX, Float positionY, Float positionZ,
			Float normalX, Float normalY, Float normalZ,
			Float textureCoordS, Float textureCoordT,
			Float red, Float green, Float blue, Float alpha);
		Vertex(const VertexStruct &plainOldData);
		~Vertex();
		// Setters
		void	SetPosition(const Vector3D &position);
		void	SetPosition(Float x, Float y, Float z);
		void	SetNormal(const Vector3D &normal);
		void	SetNormal(Float x, Float y, Float z);
		void	SetTextureCoords(const Vector2D &textureCoords);
		void	SetTextureCoords(Float s, Float t);
		void	SetColor(const Color &color);
		void	SetColor(Float red, Float green, Float blue, Float alpha);
		// Getters
		const VertexStruct&	GetPlainOldData() const;
		const Vector3D&		GetPosition() const;
		const Vector3D&		GetNormal() const;
		const Vector2D&		GetTextureCoords() const;
		const Color&		GetColor() const;
		// Operators
		Vertex&	operator= (const Vertex &that);
		Bool	operator==(const Vertex &that) const;
		Bool	operator!=(const Vertex &that) const;
	};

	template class FastApi Array<Vertex>;*/
}

#endif // FastVertexHppIncluded
