/******************************************************************************/
/*                                                                            */
/*  SoundBase.hpp                                                             */
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

#ifndef FastSoundBaseHppIncluded
#define FastSoundBaseHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SoundData.hpp>
#include <Fast/Vector3D.hpp>

namespace Fast
{
	class AudioContext;

	class FastApi SoundBase
	{
	protected:
		// Source properties
		UInt		mOpenALSourceID;
		Int			mImportance;
		Float		mVolume;
		Float		mPitch;
		Vector3D	mPosition;
		Bool		mIsRelativePosition;
		// State properties
		Bool	mIsPlaying;
		Bool	mIsPaused;
		Bool	mIsStopped;
		Bool	mIsFadingIn;
		Bool	mIsFadingOut;
		Int		mFadeTime;
		// Protected functions
		void	ResetBaseSourceProperties();
		void	ResetBaseStateProperties();
		void	HandleFading(Int elapsedMilliseconds);
	public:
		// Control functions
		virtual void	Play(Int fadeInTime = 0)		= 0;
		virtual void	Pause(Int fadeOutTime = 0)		= 0;
		virtual void	Stop(Int fadeOutTime = 0)		= 0;
		virtual void	Update(Int elapsedMilliseconds)	= 0;
		// Get source property functions
		virtual UInt			GetOpenALSourceID() const;
		virtual Int				GetImportance() const;
		virtual Float			GetVolume() const;
		virtual Float			GetPitch() const;
		virtual const Vector3D&	GetPosition() const;
		virtual Bool			IsRelativePosition() const;
		// Set source property functions
		virtual void	SetImportance(Int importance);
		virtual void	SetVolume(Float volume);
		virtual void	SetPitch(Float pitch);
		virtual void	SetPosition(const Vector3D &position);
		virtual void	SetRelativePosition(Bool isRelativePosition);
		// Get state functions
		virtual Bool	IsPlaying() const;
		virtual Bool	IsPaused() const;
		virtual Bool	IsStopped() const;
		virtual Bool	IsFadingIn() const;
		virtual Bool	IsFadingOut() const;
	};
}

#endif // FastSoundBaseHppIncluded
