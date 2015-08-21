/******************************************************************************/
/*                                                                            */
/*  RenderPreferences.cpp                                                     */
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

#include <Fast/RenderPreferences.hpp>

#include "Undefs.hpp"

namespace Fast
{
	RenderPreferences::RenderPreferences() {
		// FIXME: Find out real defaults
		mCapabilitiesEnabled.SetElementCount(32);
		mIsVisible					= true;
		mPrimitive					= kRenderPrimitiveTriangles;
		mDrawLayer					= 0;
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

	RenderPreferences::RenderPreferences(const RenderPreferences &that) {
		*this = that;
	}

	RenderPreferences::~RenderPreferences() { }

	Bool RenderPreferences::IsCapabilityEnabled(
		GraphicsCapability capability) const
	{
		return mCapabilitiesEnabled[(Int)capability];
	}

	Bool RenderPreferences::IsVisible() const {
		return mIsVisible;
	}

	const Matrix& RenderPreferences::GetModelviewMatrix() const {
		return mModelviewMatrix;
	}

	RenderPrimitive RenderPreferences::GetPrimitive() const {
		return mPrimitive;
	}

	Int RenderPreferences::GetDrawLayer() const {
		return mDrawLayer;
	}

	const Material& RenderPreferences::GetMaterial() const {
		return mMaterial;
	}

	Float RenderPreferences::GetPointSize() const {
		return mPointSize;
	}

	Bool RenderPreferences::IsPointSmoothingEnabled() const {
		return mIsPointSmoothingEnabled;
	}

	Float RenderPreferences::GetLineWidth() const {
		return mLineWidth;
	}

	Bool RenderPreferences::IsLineSmoothingEnabled() const {
		return mIsLineSmoothingEnabled;
	}

	PolygonFace RenderPreferences::GetCullFace() const {
		return mCullFace;
	}

	Bool RenderPreferences::IsFaceCullingEnabled() const {
		return mIsFaceCullingEnabled;
	}

	PolygonWindingDirection RenderPreferences::GetPolygonWindingDirection()
		const
	{
		return mPolygonWindingDirection;
	}

	PolygonMode RenderPreferences::GetFrontFacePolygonMode() const {
		return mFrontFacePolygonMode;
	}

	PolygonMode RenderPreferences::GetBackFacePolygonMode() const {
		return mBackFacePolygonMode;
	}

	BlendFunction RenderPreferences::GetSourceBlendFunction() const {
		return mSourceBlendFunction;
	}

	BlendFunction RenderPreferences::GetDestinationBlendFunction() const {
		return mDestinationBlendFunction;
	}

	BlendEquation RenderPreferences::GetBlendEquation() const {
		return mBlendEquation;
	}

	const Color& RenderPreferences::GetBlendColor() const {
		return mBlendColor;
	}

	Float RenderPreferences::GetPolygonOffsetFactor() const {
		return mPolygonOffsetFactor;
	}

	Float RenderPreferences::GetPolygonOffsetUnits() const {
		return mPolygonOffsetUnits;
	}

	PolygonOffsetType RenderPreferences::GetPolygonOffsetType() const {
		return mPolygonOffsetType;
	}

	void RenderPreferences::SetVisible(Bool isVisible) {
		mIsVisible = isVisible;
	}

	void RenderPreferences::SetModelviewMatrix(const Matrix &modelviewMatrix) {
		mModelviewMatrix = modelviewMatrix;
	}

	void RenderPreferences::SetPrimitive(RenderPrimitive primitive) {
		mPrimitive = primitive;
	}

	void RenderPreferences::SetDrawLayer(Int drawLayer) {
		mDrawLayer = drawLayer;
	}

	void RenderPreferences::SetMaterial(const Material &material) {
		mMaterial = material;
	}

	void RenderPreferences::SetPointSize(Float size) {
		mPointSize = size;
	}

	void RenderPreferences::SetPointSmoothingEnabled(Bool enabled) {
		mIsPointSmoothingEnabled = enabled;
	}

	void RenderPreferences::SetLineWidth(Float width) {
		mLineWidth = width;
	}

	void RenderPreferences::SetLineSmoothingEnabled(Bool enabled) {
		mIsLineSmoothingEnabled = enabled;
	}

	void RenderPreferences::SetCullFace(PolygonFace cullFace) {
		mCullFace = cullFace;
	}

	void RenderPreferences::SetFaceCullingEnabled(Bool enabled) {
		mIsFaceCullingEnabled = enabled;
	}

	void RenderPreferences::SetPolygonWindingDirection(
		PolygonWindingDirection pwd)
	{
		mPolygonWindingDirection = pwd;
	}

	void RenderPreferences::SetFrontFacePolygonMode(PolygonMode polygonMode)
	{
		mFrontFacePolygonMode = polygonMode;
	}

	void RenderPreferences::SetBackFacePolygonMode(PolygonMode polygonMode)
	{
		mBackFacePolygonMode = polygonMode;
	}

	void RenderPreferences::SetSourceBlendFunction(BlendFunction blendFunc)
	{
		mSourceBlendFunction = blendFunc;
	}

	void RenderPreferences::SetDestinationBlendFunction(BlendFunction blendFunc)
	{
		mDestinationBlendFunction = blendFunc;
	}

	void RenderPreferences::SetBlendEquation(BlendEquation blendEq) {
		mBlendEquation = blendEq;
	}

	void RenderPreferences::SetBlendColor(const Color &blendColor) {
		mBlendColor = blendColor;
	}

	void RenderPreferences::SetPolygonOffsetFactor(Float offsetFactor) {
		mPolygonOffsetFactor = offsetFactor;
	}

	void RenderPreferences::SetPolygonOffsetUnits(Float offsetUnits) {
		mPolygonOffsetUnits = offsetUnits;
	}

	void RenderPreferences::SetPolygonOffsetType(PolygonOffsetType offsetType) {
		mPolygonOffsetType = offsetType;
	}

	RenderPreferences& RenderPreferences::operator=(
		const RenderPreferences &that)
	{
		// TODO
		return *this;
	}

	Bool RenderPreferences::operator==(
		const RenderPreferences &that) const
	{
		// TODO
		return false;
	}

	Bool RenderPreferences::operator!=(
		const RenderPreferences &that) const
	{
		// TODO
		return true;
	}
}