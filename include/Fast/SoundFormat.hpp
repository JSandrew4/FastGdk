/******************************************************************************/
/*                                                                            */
/*  SoundFormat.hpp                                                           */
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

#ifndef FastSoundFormatHppIncluded
#define FastSoundFormatHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	enum FastApi SoundFormat
	{
		kSoundFormatNone = 0,
		kSoundFormatMono8 = 0x1100,		// AL_FORMAT_MONO8
		kSoundFormatMono16 = 0x1101,	// AL_FORMAT_MONO16
		kSoundFormatStereo8 = 0x1102,	// AL_FORMAT_STEREO8
		kSoundFormatStereo16 = 0x1103	// AL_FORMAT_STEREO16
	};
}

#endif // FastSoundFormatHppIncluded
