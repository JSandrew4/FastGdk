/******************************************************************************/
/*                                                                            */
/*  Vertex.cpp                                                                */
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

#include <Fast/Vertex.hpp>
#include <Fast/Vector3D.hpp>

#include <string.h>

#include "Undefs.hpp"

namespace Fast
{
	Vertex::Vertex() {
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
	}

	Vertex::Vertex(const Vertex &that) {
		*this = that;
	}
	
	Vertex::Vertex(const Vector3D &position) {
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
		SetPosition(position);
	}

	Vertex::Vertex(Float positionX, Float positionY, Float positionZ) {
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
		SetPosition(positionX, positionY, positionZ);
	}
	
	Vertex::Vertex(const Vector3D &position, const Vector2D &textureCoords) {
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
		SetPosition(position);
		SetTextureCoords(textureCoords);
	}

	Vertex::Vertex(Float positionX, Float positionY, Float positionZ,
		Float textureCoordS, Float textureCoordT)
	{
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
		SetPosition(positionX, positionY, positionZ);
		SetTextureCoords(textureCoordS, textureCoordT);
	}
	
	Vertex::Vertex(const Vector3D &position, const Vector3D &normal,
		const Vector2D &textureCoords, const Color &color)
	{
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
		SetPosition(position);
		SetNormal(normal);
		SetTextureCoords(textureCoords);
		SetColor(color);
	}

	Vertex::Vertex(Float positionX, Float positionY, Float positionZ,
		Float normalX, Float normalY, Float normalZ,
		Float textureCoordS, Float textureCoordT,
		Float red, Float green, Float blue, Float alpha)
	{
		memset(&mPlainOldData, 0, sizeof(VertexStruct));
		SetPosition(positionX, positionY, positionZ);
		SetNormal(normalX, normalY, normalZ);
		SetTextureCoords(textureCoordS, textureCoordT);
		SetColor(red, green, blue, alpha);
	}

	Vertex::Vertex(const VertexStruct &plainOldData) {
		mPlainOldData = plainOldData;
		mPosition = Vector3D(plainOldData.mX, plainOldData.mY, plainOldData.mZ);
		mNormal = Vector3D(plainOldData.mNormalX,
			plainOldData.mNormalY, plainOldData.mNormalZ);
		mTextureCoords =
			Vector2D(plainOldData.mTextureU, plainOldData.mTextureV);
		mColor = Color(plainOldData.mRed, plainOldData.mGreen,
			plainOldData.mBlue, plainOldData.mAlpha);
	}

	Vertex::~Vertex() { }

	void Vertex::SetPosition(const Vector3D &position) {
		mPosition = position;
		mPlainOldData.mX = position.mX;
		mPlainOldData.mY = position.mY;
		mPlainOldData.mZ = position.mZ;
	}

	void Vertex::SetPosition(Float x, Float y, Float z) {
		mPosition.mX = x;
		mPosition.mY = y;
		mPosition.mZ = z;
		mPlainOldData.mX = x;
		mPlainOldData.mY = y;
		mPlainOldData.mZ = z;
	}

	void Vertex::SetNormal(const Vector3D &normal) {
		mNormal = normal;
		mPlainOldData.mNormalX = normal.mX;
		mPlainOldData.mNormalY = normal.mY;
		mPlainOldData.mNormalZ = normal.mZ;
	}

	void Vertex::SetNormal(Float x, Float y, Float z) {
		mNormal.mX = x;
		mNormal.mY = y;
		mNormal.mZ = z;
		mPlainOldData.mNormalX = x;
		mPlainOldData.mNormalY = y;
		mPlainOldData.mNormalZ = z;
	}

	void Vertex::SetTextureCoords(const Vector2D &textureCoords) {
		mTextureCoords = textureCoords;
		mPlainOldData.mTextureU = textureCoords.mX;
		mPlainOldData.mTextureV = textureCoords.mY;
	}

	void Vertex::SetTextureCoords(Float s, Float t) {
		mTextureCoords.mX = s;
		mTextureCoords.mY = t;
		mPlainOldData.mTextureU = s;
		mPlainOldData.mTextureV = t;
	}

	void Vertex::SetColor(const Color &color) {
		mColor = color;
		mPlainOldData.mRed = color.mRed;
		mPlainOldData.mGreen = color.mGreen;
		mPlainOldData.mBlue = color.mBlue;
		mPlainOldData.mAlpha = color.mAlpha;
	}

	void Vertex::SetColor(Float red, Float green, Float blue, Float alpha) {
		mColor.mRed = red;
		mColor.mGreen = green;
		mColor.mBlue = blue;
		mColor.mAlpha = alpha;
		mPlainOldData.mRed = red;
		mPlainOldData.mGreen = green;
		mPlainOldData.mBlue = blue;
		mPlainOldData.mAlpha = alpha;
	}

	const VertexStruct& Vertex::GetPlainOldData() const {
		return mPlainOldData;
	}

	const Vector3D& Vertex::GetPosition() const {
		return mPosition;
	}

	const Vector3D& Vertex::GetNormal() const {
		return mNormal;
	}

	const Vector2D& Vertex::GetTextureCoords() const {
		return mTextureCoords;
	}

	const Color& Vertex::GetColor() const {
		return mColor;
	}

	Vertex& Vertex::operator= (const Vertex &that) {
		this->mPlainOldData = that.mPlainOldData;
		this->mPosition = that.mPosition;
		this->mNormal = that.mNormal;
		this->mTextureCoords = that.mTextureCoords;
		this->mColor = that.mColor;
		return *this;
	}

	Bool Vertex::operator==(const Vertex &that) const {
		if (0 == memcmp(&this->mPlainOldData, 
			&that.mPlainOldData, sizeof(VertexStruct)))
		{
			return true;
		}
		return false;
	}

	Bool Vertex::operator!=(const Vertex &that) const {
		if (0 == memcmp(&this->mPlainOldData, 
			&that.mPlainOldData, sizeof(VertexStruct)))
		{
			return false;
		}
		return true;
	}
}