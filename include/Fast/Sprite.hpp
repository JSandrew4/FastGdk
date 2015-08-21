/******************************************************************************/
/*                                                                            */
/*  Sprite.hpp                                                                */
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

#ifndef FastSpriteHppIncluded
#define FastSpriteHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/SpriteCollection.hpp>
#include <Fast/Array.hpp>
#include <Fast/SpriteFrame.hpp>
#include <Fast/CustomRenderable2D.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Quaternion.hpp>
#include <Fast/Box2D.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SpriteCollection.hpp>
#include <Fast/SpriteResource.hpp>

namespace Fast
{
	class String;
	class SpriteData;
	class StreamReader;
	class FrameBufferSurface;

	class FastApi Sprite :
		public AssetImplementer<SpriteCollection, SpriteResource>,
		public CustomRenderable2D
	{
	private:
		// State
		Array<Int>	mActionQueue;
		Int			mCurrentActionIndex;
		Int			mCurrentFrameIndex;
		Float		mAnimationSpeed;
		Float		mDeltaTimeCumulative;
		Box2D		mBounds;
		// Private functions
		ErrorType	LoadResource(const String &name, const SpriteData &data,
						SpriteCollection *collection);
	public:
		// (Con/De)structors
		Sprite();
		Sprite(const Sprite &that);
		Sprite(const String &fileName, SpriteCollection *collection);
		Sprite(StreamReader *streamReader, SpriteCollection *collection);
		Sprite(const SpriteData &data, SpriteCollection *collection);
		~Sprite();
		// Allocators
		ErrorType	Load(const String &fileName,
						SpriteCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						SpriteCollection *collection);
		ErrorType	Load(const SpriteData &data,
						SpriteCollection *collection);
		void		Unbind();
		// Getters
		const Box2D&				GetBounds() const;
		Float						GetAnimationSpeed() const;
		Int							GetCurrentActionIndex() const;
		Int							GetCurrentFrameIndex() const;
		// SpriteData getters
		const String&				GetName() const;
		Int							GetNumTexture2Ds() const;
		const Texture2DSurface&		GetTexture2D(Int index) const;
		Int							GetTexture2DIndex(const String &name) const;
		Int							GetNumCollisionModels() const;
		const SpriteCollisionModel&	GetCollisionModel(Int index) const;
		Int							GetCollisionModelIndex(
										const String &name) const;
		Int							GetNumFrameConfigs() const;
		const SpriteFrameConfig&	GetFrameConfig(Int index) const;
		Int							GetFrameConfigIndex(
										const String &name) const;
		Int							GetNumActions() const;
		const SpriteAction&			GetAction(Int index) const;
		Int							GetActionIndex(const String &name) const;
		// Setters
		void	SetBounds(const Box2D &bounds);
		void	SetAnimationSpeed(Float animationSpeed);
		void	SetAction(Int actionIndex);
		void	SetFrame(Int index);
		void	QueueAction(Int actionIndex);
		void	ClearQueue();
		// Misc functions
		void	Update(Float deltaTime);
		void	Draw(FrameBufferSurface *surface);
		// Operators
		Sprite&	operator= (const Sprite &that);
		Bool	operator==(const Sprite &that) const;
		Bool	operator!=(const Sprite &that) const;
	};
}

#endif // FastSpriteHppIncluded
