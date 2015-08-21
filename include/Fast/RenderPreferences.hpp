/******************************************************************************/
/*                                                                            */
/*  RenderPreferences.hpp                                                     */
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

#ifndef FastRenderPreferencesHppIncluded
#define FastRenderPreferencesHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/RenderPrimitive.hpp>
#include <Fast/FrameBufferSurface.hpp>
#include <Fast/Matrix.hpp>
#include <Fast/Material.hpp>
#include <Fast/PolygonFace.hpp>
#include <Fast/PolygonWindingDirection.hpp>
#include <Fast/PolygonMode.hpp>
#include <Fast/BlendFunction.hpp>
#include <Fast/BlendEquation.hpp>
#include <Fast/Color.hpp>
#include <Fast/PolygonOffsetType.hpp>
#include <Fast/GraphicsCapability.hpp>

namespace Fast
{
	class FastApi RenderPreferences
	{
	protected:
		Array<Bool>				mCapabilitiesEnabled;
		Bool					mIsVisible;
		Matrix					mModelviewMatrix;
		RenderPrimitive			mPrimitive;
		Int						mDrawLayer;
		Material				mMaterial;
		Float					mPointSize;
		Bool					mIsPointSmoothingEnabled;
		Float					mLineWidth;
		Bool					mIsLineSmoothingEnabled;
		PolygonFace				mCullFace;
		Bool					mIsFaceCullingEnabled;
		PolygonWindingDirection	mPolygonWindingDirection;
		PolygonMode				mFrontFacePolygonMode;
		PolygonMode				mBackFacePolygonMode;
        BlendFunction			mSourceBlendFunction;
        BlendFunction			mDestinationBlendFunction;
        BlendEquation			mBlendEquation;
    	Color					mBlendColor;
    	Float					mPolygonOffsetFactor;
    	Float					mPolygonOffsetUnits;
    	PolygonOffsetType		mPolygonOffsetType;
	public:
    	// (Con/De)structors
		RenderPreferences();
    	RenderPreferences(const RenderPreferences &that);
    	~RenderPreferences();
    	// Getters
    	Bool						IsCapabilityEnabled(
    									GraphicsCapability capacility) const;
		Bool						IsVisible() const;
		const Matrix&				GetModelviewMatrix() const;
		RenderPrimitive				GetPrimitive() const;
		Int							GetDrawLayer() const;
		const Material&				GetMaterial() const;
		Float						GetPointSize() const;
		Bool						IsPointSmoothingEnabled() const;
		Float						GetLineWidth() const;
		Bool						IsLineSmoothingEnabled() const;
		PolygonFace					GetCullFace() const;
		Bool						IsFaceCullingEnabled() const;
		PolygonWindingDirection		GetPolygonWindingDirection() const;
		PolygonMode					GetFrontFacePolygonMode() const;
		PolygonMode					GetBackFacePolygonMode() const;
		BlendFunction				GetSourceBlendFunction() const;
		BlendFunction				GetDestinationBlendFunction() const;
		BlendEquation				GetBlendEquation() const;
		const Color&				GetBlendColor() const;
		Float						GetPolygonOffsetFactor() const;
		Float						GetPolygonOffsetUnits() const;
		PolygonOffsetType			GetPolygonOffsetType() const;
    	// Setters
		void	SetVisible(Bool isVisible);
		void	SetModelviewMatrix(const Matrix &modelviewMatrix);
		void	SetPrimitive(RenderPrimitive primitive);
		void	SetDrawLayer(Int depthLayer);
		void	SetMaterial(const Material &material);
		void	SetPointSize(Float size);
		void	SetPointSmoothingEnabled(Bool enabled);
		void	SetLineWidth(Float width);
		void	SetLineSmoothingEnabled(Bool enabled);
		void	SetCullFace(PolygonFace cullFace);
		void	SetFaceCullingEnabled(Bool enabled);
		void	SetPolygonWindingDirection(PolygonWindingDirection pwd);
		void	SetFrontFacePolygonMode(PolygonMode polygonMode);
		void	SetBackFacePolygonMode(PolygonMode polygonMode);
		void	SetSourceBlendFunction(BlendFunction blendFunc);
		void	SetDestinationBlendFunction(BlendFunction blendFunc);
		void	SetBlendEquation(BlendEquation blendEq);
		void	SetBlendColor(const Color &blendColor);
		void	SetPolygonOffsetFactor(Float offsetFactor);
		void	SetPolygonOffsetUnits(Float offsetUnits);
		void	SetPolygonOffsetType(PolygonOffsetType offsetType);
    	// Operators
		RenderPreferences&	operator= (const RenderPreferences &that);
		Bool				operator==(const RenderPreferences &that) const;
		Bool				operator!=(const RenderPreferences &that) const;
	};
}

#endif // FastRenderPreferencesHppIncluded