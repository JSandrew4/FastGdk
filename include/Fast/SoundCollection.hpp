/******************************************************************************/
/*                                                                            */
/*  SoundCollection.hpp                                                       */
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

#ifndef FastSoundCollectionHppIncluded
#define FastSoundCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollectionVerifiable.hpp>
#include <Fast/SoundResource.hpp>

namespace Fast
{
	class AudioContext;
	class StreamReader;

	template class FastApi AssetCollectionVerifiable<SoundResource>;

	class FastApi SoundCollection : public AssetCollectionVerifiable<SoundResource>
	{
	private:
		AudioContext	&mAudioContext;
		// Hide these functions. No copying collections!
		SoundCollection(const SoundCollection &that) :
			mAudioContext(that.mAudioContext)
			{ }
		SoundCollection& operator=(const SoundCollection &that)
			{ return *this; }
	public:
		// (Con/De)structor
		SoundCollection(AudioContext *audioContext);
		~SoundCollection();
		// Allocators
		ErrorType		LoadResource(const String &fileName);
		ErrorType		LoadResource(StreamReader *streamReader);
		ErrorType		LoadResource(const AssetData &assetData);
		void			UnloadResource(Int id);
		// Getters
		AudioContext*		GetAudioContext();
		const AudioContext&	GetAudioContext() const;
	};
}

#endif // FastSoundCollectionHppIncluded
