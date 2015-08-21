/******************************************************************************/
/*                                                                            */
/*  ErrorType.hpp                                                             */
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

#ifndef FastErrorTypeHppIncluded
#define FastErrorTypeHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	enum FastApi ErrorType
	{
		kErrorNone								= 0,
		kErrorGeneric,
		kErrorEndOfStream,
		kErrorBadStream,
		kErrorOutOfMemory,
		kErrorInvalidValue,
		kErrorFormatInvalid,
		kErrorTimedOut,
		kErrorInProgress,

		kErrorFileCreationFailure				= 100,
		kErrorFileDeletionFailure,
		kErrorFileRenameFailure,
		kErrorFileNotFound,

		kErrorFolderCreationFailure				= 200,
		kErrorFolderDeletionFailure,

		kErrorSocketCreationFailure				= 300,
		kErrorSocketPortInvalid,

		kErrorClipboardDataInvalid				= 400,

		kErrorVideoModeSetFailure				= 500,

		kErrorOpenGLGenTexturesFailure			= 600,
		kErrorOpenGLFormatInvalid,
		kErrorOpenGLGenBuffersFailure,
		kErrorOpenGLInvalidEnum,
		kErrorOpenGLInvalidValue,
		kErrorOpenGLInvalidOperation,
		kErrorOpenGLOutOfMemory,
		kErrorOpenGLInvalidFramebufferOperation,

		kErrorImageFormatInvalid				= 700,
		
		kErrorPngCreationFailure				= 800,

		kErrorFontCreationFailure				= 900,
		kErrorFontInvalidEncoding,

		kErrorOpenALGenSourcesFailure			= 1000,
		kErrorOpenALFormatInvalid,
		kErrorOpenALGenBuffersFailure,
		kErrorOpenALNoBuffersAvailable,
		kErrorOpenALNoActiveSource,

		kErrorSoundFormatInvalid				= 1100,

		kErrorVorbisStackCorruption				= 1200,
		kErrorVorbisInvalidSetupRequest,
		kErrorVorbisUnimplementedMode,

		kErrorProcessCreationFailure			= 1300,

		kErrorModelFormatInvalid				= 1400,
	};
}

#endif // FastErrorTypeHppIncluded
