/******************************************************************************/
/*                                                                            */
/*  MeshRenderPreferences.cpp                                                 */
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

#include <Fast/MeshRenderPreferences.hpp>

#include "Undefs.hpp"

namespace Fast
{
	MeshRenderPreferences::MeshRenderPreferences() {
		// FIXME: Find out real defaults
		mPrimitive					= kRenderPrimitiveTriangles;
		mMaterial					= Material();
		mPointSize					= 1.0f;
		mIsPointSmoothingEnabled	= false;
		mLineWidth					= 1.0f;
		mIsLineSmoothingEnabled		= false;
		mCullFace					= kPolygonFaceNone;
		mIsFaceCullingEnabled		= false;
		mPolygonWindingDirection	= kPolygonWindingClockwise;
		mFrontFacePolygonMode		= kPolygonFill;
		mBackFacePolygonMode		= kPolygonFill;
        mSourceBlendFunction		= kBlendFunctionOneMinusSourceColor;
        mDestinationBlendFunction	= kBlendFunctionOneMinusDestinationColor;
        mBlendEquation				= kBlendEquationAdd;
    	mBlendColor					= Color(1.0f, 1.0f, 1.0f, 1.0f);
    	mPolygonOffsetFactor		= 1.0f;
    	mPolygonOffsetUnits			= 1.0f;
    	mPolygonOffsetType			= kPolygonOffsetFill;
	}

	MeshRenderPreferences::MeshRenderPreferences(
		const MeshRenderPreferences &that)
	{
		*this = that;
	}

	MeshRenderPreferences::~MeshRenderPreferences() { }

	RenderPrimitive MeshRenderPreferences::GetPrimitive() const {
		return mPrimitive;
	}

	const Material& MeshRenderPreferences::GetMaterial() const {
		return mMaterial;
	}

	Float MeshRenderPreferences::GetPointSize() const {
		return mPointSize;
	}

	Bool MeshRenderPreferences::IsPointSmoothingEnabled() const {
		return mIsPointSmoothingEnabled;
	}

	Float MeshRenderPreferences::GetLineWidth() const {
		return mLineWidth;
	}

	Bool MeshRenderPreferences::IsLineSmoothingEnabled() const {
		return mIsLineSmoothingEnabled;
	}

	PolygonFace MeshRenderPreferences::GetCullFace() const {
		return mCullFace;
	}

	Bool MeshRenderPreferences::IsFaceCullingEnabled() const {
		return mIsFaceCullingEnabled;
	}

	PolygonWindingDirection MeshRenderPreferences::GetPolygonWindingDirection()
		const
	{
		return mPolygonWindingDirection;
	}

	PolygonMode MeshRenderPreferences::GetFrontFacePolygonMode() const {
		return mFrontFacePolygonMode;
	}

	PolygonMode MeshRenderPreferences::GetBackFacePolygonMode() const {
		return mBackFacePolygonMode;
	}

	BlendFunction MeshRenderPreferences::GetSourceBlendFunction() const {
		return mSourceBlendFunction;
	}

	BlendFunction MeshRenderPreferences::GetDestinationBlendFunction() const {
		return mDestinationBlendFunction;
	}

	BlendEquation MeshRenderPreferences::GetBlendEquation() const {
		return mBlendEquation;
	}

	const Color& MeshRenderPreferences::GetBlendColor() const {
		return mBlendColor;
	}

	Float MeshRenderPreferences::GetPolygonOffsetFactor() const {
		return mPolygonOffsetFactor;
	}

	Float MeshRenderPreferences::GetPolygonOffsetUnits() const {
		return mPolygonOffsetUnits;
	}

	PolygonOffsetType MeshRenderPreferences::GetPolygonOffsetType() const {
		return mPolygonOffsetType;
	}

	void MeshRenderPreferences::SetPrimitive(RenderPrimitive primitive) {
		mPrimitive = primitive;
	}

	void MeshRenderPreferences::SetMaterial(const Material &material) {
		mMaterial = material;
	}

	void MeshRenderPreferences::SetPointSize(Float size) {
		mPointSize = size;
	}

	void MeshRenderPreferences::SetPointSmoothingEnabled(Bool enabled) {
		mIsPointSmoothingEnabled = enabled;
	}

	void MeshRenderPreferences::SetLineWidth(Float width) {
		mLineWidth = width;
	}

	void MeshRenderPreferences::SetLineSmoothingEnabled(Bool enabled) {
		mIsLineSmoothingEnabled = enabled;
	}

	void MeshRenderPreferences::SetCullFace(PolygonFace cullFace) {
		mCullFace = cullFace;
	}

	void MeshRenderPreferences::SetFaceCullingEnabled(Bool enabled) {
		mIsFaceCullingEnabled = enabled;
	}

	void MeshRenderPreferences::SetPolygonWindingDirection(
		PolygonWindingDirection pwd)
	{
		mPolygonWindingDirection = pwd;
	}

	void MeshRenderPreferences::SetFrontFacePolygonMode(PolygonMode polygonMode)
	{
		mFrontFacePolygonMode = polygonMode;
	}

	void MeshRenderPreferences::SetBackFacePolygonMode(PolygonMode polygonMode)
	{
		mBackFacePolygonMode = polygonMode;
	}

	void MeshRenderPreferences::SetSourceBlendFunction(BlendFunction blendFunc)
	{
		mSourceBlendFunction = blendFunc;
	}

	void MeshRenderPreferences::SetDestinationBlendFunction(
		BlendFunction blendFunc)
	{
		mDestinationBlendFunction = blendFunc;
	}

	void MeshRenderPreferences::SetBlendEquation(BlendEquation blendEq) {
		mBlendEquation = blendEq;
	}

	void MeshRenderPreferences::SetBlendColor(const Color &blendColor) {
		mBlendColor = blendColor;
	}

	void MeshRenderPreferences::SetPolygonOffsetFactor(Float offsetFactor) {
		mPolygonOffsetFactor = offsetFactor;
	}

	void MeshRenderPreferences::SetPolygonOffsetUnits(Float offsetUnits) {
		mPolygonOffsetUnits = offsetUnits;
	}

	void MeshRenderPreferences::SetPolygonOffsetType(
		PolygonOffsetType offsetType)
	{
		mPolygonOffsetType = offsetType;
	}

	MeshRenderPreferences& MeshRenderPreferences::operator=(
		const MeshRenderPreferences &that)
	{
		// TODO
		return *this;
	}

	Bool MeshRenderPreferences::operator==(
		const MeshRenderPreferences &that) const
	{
		// TODO
		return false;
	}

	Bool MeshRenderPreferences::operator!=(
		const MeshRenderPreferences &that) const
	{
		// TODO
		return true;
	}
}