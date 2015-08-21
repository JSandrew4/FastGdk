/******************************************************************************/
/*                                                                            */
/*  SoundCapture.cpp                                                          */
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

#include <Fast/SoundCapture.hpp>
#include <Fast/Exception.hpp>

#include "OpenAL.hpp"
#include "Undefs.hpp"

namespace Fast
{
	Array<String> SoundCapture::GetAvailableDevices() {
		Array<String> devices;
		GetAvailableDevices(devices);
		return devices;
	}

	void SoundCapture::GetAvailableDevices(Array<String> &devices) {
		devices.Clear();
		const ALchar *alcDevices =
			alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
		while (*alcDevices) {
			devices.Append(alcDevices);
			alcDevices += strlen(alcDevices) + 1;
		}
	}

	SoundCapture::SoundCapture() {
		SoundCapture(SoundProperties(), 2048, "");
	}

	SoundCapture::SoundCapture(const String &deviceName) {
		SoundCapture(SoundProperties(), 2048, deviceName);
	}

	SoundCapture::SoundCapture(const SoundProperties &properties,
		Int numSampleFrames, const String &deviceName)
	{
		mALCdevice = 0;
		mDeviceName = deviceName;
		mProperties = properties;
		mNumSampleFrames = numSampleFrames;
		if (kSoundFormatNone == mProperties.GetFormat())
			Exception::Throw(kExceptionOpenALFormatInvalid,
				String("(%s)", FastFunctionName));
		alGetError();
		mALCdevice = (CALCdevice*)alcCaptureOpenDevice(
			mDeviceName.IsEmpty() ? 0 : mDeviceName.GetData(),
			mProperties.GetFrequency(),
			(ALint)mProperties.GetFormat(), mNumSampleFrames);
		if (!mALCdevice)
			Exception::Throw(kExceptionOpenALDeviceCreationFailure,
				String("(%s)", FastFunctionName));
	}

	SoundCapture::~SoundCapture() {
		StopCapturing();
		alcCaptureCloseDevice((ALCdevice*)mALCdevice);
	}

	void SoundCapture::StartCapturing() {
		alcCaptureStart((ALCdevice*)mALCdevice);
	}

	void SoundCapture::StopCapturing() {
		alcCaptureStop((ALCdevice*)mALCdevice);
	}

	const String& SoundCapture::GetDeviceName() const {
		return mDeviceName;
	}

	Int SoundCapture::GetNumBuffersToBeRead() {
		ALint capturedSamples;
		alcGetIntegerv((ALCdevice*)mALCdevice, ALC_CAPTURE_SAMPLES,
			(ALCsizei)sizeof(ALint), &capturedSamples);
		return ((Int)capturedSamples / mNumSampleFrames);
	}

	void SoundCapture::GetBufferData(SoundData *data) {
		((Array<Byte>)data->GetSamples()).SetElementCount(mNumSampleFrames *
			mProperties.GetChannelCount() *
			mProperties.GetSamplesByteCount());
		alcCaptureSamples((ALCdevice*)mALCdevice,
			(ALCvoid*)data->GetSamples().GetData(), mNumSampleFrames);
	}

	SoundData SoundCapture::GetBufferData() {
		SoundData soundData;
		GetBufferData(&soundData);
		return soundData;
	}

	const SoundProperties& SoundCapture::GetProperties() const {
		return mProperties;
	}
}
