/******************************************************************************/
/*                                                                            */
/*  SoundProperties.hpp                                                       */
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

#ifndef FastSoundPropertiesHppIncluded
#define FastSoundPropertiesHppIncluded

#include <Fast/Types.hpp>
#include <Fast/SoundFormat.hpp>

namespace Fast
{
	class FastApi SoundProperties
	{
	protected:
		SoundFormat	mFormat;
		Int			mFrequency;
		Int			mChannelCount;
		Int			mSamplesByteCount;
		Int			mSampleCount;
	public:
		// Constructors
		SoundProperties();
		SoundProperties(SoundFormat format, Int frequency, Int sampleCount);
		// Getters
		SoundFormat	GetFormat() const;
		Int			GetFrequency() const;
		Int			GetChannelCount() const;
		Int			GetSamplesByteCount() const;
		Int			GetSampleCount() const;
		// Setters
		void	SetFormat(SoundFormat format);
		void	SetFrequency(Int frequency);
		void	SetSampleCount(Int sampleCount);
		// Operators
		Bool	operator==(const SoundProperties &that) const;
		Bool	operator!=(const SoundProperties &that) const;
	};
}

#endif // FastSoundPropertiesHppIncluded
