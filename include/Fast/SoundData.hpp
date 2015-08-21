/******************************************************************************/
/*                                                                            */
/*  SoundData.hpp                                                             */
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

#ifndef FastSoundDataHppIncluded
#define FastSoundDataHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/SoundDataBase.hpp>
#include <Fast/AssetData.hpp>

#define kFastSoundBufferSize	4096

namespace Fast
{
	class String;
	class StreamReader;

	class FastApi SoundData : public SoundDataBase, public AssetData
	{
	private:
		// Specific format load functions
		ErrorType	LoadOgg(const String &fileName);
		ErrorType	LoadOgg(StreamReader *streamReader);
		ErrorType	LoadWav(const String &fileName);
		ErrorType	LoadWav(StreamReader *streamReader);
	public:
		// (Con/De)structors
		SoundData();
		SoundData(const SoundProperties &properties);
		SoundData(const SoundProperties &properties,
			const Array<Byte> &samples);
		SoundData(const SoundData &that);
		SoundData(const String &fileName);
		SoundData(StreamReader *streamReader);
		~SoundData();
		// Allocate functions
		ErrorType	Load(const String &fileName);
		ErrorType	Load(StreamReader *streamReader);
		void		Unload();
		// Save functions
		ErrorType	SaveAsOgg(const String &fileName,
						Int kbitRate, Float vbrQuality = 0.1f);
		ErrorType	SaveAsWav(const String &fileName);
		// Assignment operator
		SoundData&	operator=(const SoundData &that);
		// Compare operators
		Bool	operator==(const SoundData &that) const;
		Bool	operator!=(const SoundData &that) const;
	};
}

#endif // FastSoundDataHppIncluded
