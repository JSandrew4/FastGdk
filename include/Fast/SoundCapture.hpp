/******************************************************************************/
/*                                                                            */
/*  SoundCapture.hpp                                                          */
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

#ifndef FastSoundCaptureHppIncluded
#define FastSoundCaptureHppIncluded

#include <Fast/Types.hpp>
#include <Fast/SoundProperties.hpp>
#include <Fast/String.hpp>
#include <Fast/SoundData.hpp>

namespace Fast
{
	class FastApi SoundCapture
	{
	private:
		// Private data
		CALCdevice		*mALCdevice;
		String			mDeviceName;
		SoundProperties	mProperties;
		Int				mNumSampleFrames;
		// Private functions
		void	Initialize(const String &deviceName,
					const SoundProperties &properties, Int numSampleFrames);
		// Hide these functions. No copying sound captures!
		SoundCapture(const SoundCapture &that) {}
		SoundCapture& operator=(const SoundCapture &that) { return *this; }
	public:
		// Static functions
		Array<String>	GetAvailableDevices();
		void			GetAvailableDevices(Array<String> &devices);
		// (Con/De)structors
		SoundCapture();
		SoundCapture(const String &deviceName);
		SoundCapture(const SoundProperties &properties,
			Int numSampleFrames, const String &deviceName = "");
		~SoundCapture();
		// Control functions
		void	StartCapturing();
		void	StopCapturing();
		// Get functions
		const String&			GetDeviceName() const;
		Int						GetNumBuffersToBeRead();
		void					GetBufferData(SoundData *data);
		SoundData				GetBufferData();
		const SoundProperties&	GetProperties() const;
	};
}

#endif // FastSoundCaptureHppIncluded
