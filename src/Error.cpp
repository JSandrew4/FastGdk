/******************************************************************************/
/*                                                                            */
/*  Error.cpp                                                                 */
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

#include <Fast/Error.hpp>
#include <Fast/Debug.hpp>
#include <Fast/Logger.hpp>
#include <Fast/Application.hpp>

#include <cstdio>

#include "Undefs.hpp"

namespace Fast
{
	namespace Error
	{
		void (*gErrorCallback)(ErrorType, const String&, void*);

		String GetString(ErrorType error) {
			switch (error)
			{
			case kErrorNone:
				return "No error";
			case kErrorGeneric:
				return "An error occurred";
			case kErrorEndOfStream:
				return "End of stream";
			case kErrorBadStream:
				return "Bad stream";
			case kErrorOutOfMemory:
				return "Out of memory";
			case kErrorInvalidValue:
				return "Invalid value";
			case kErrorFormatInvalid:
				return "Format invalid";
			case kErrorFileCreationFailure:
				return "File creation failure";
			case kErrorFileDeletionFailure:
				return "File deletion failure";
			case kErrorFileRenameFailure:
				return "File rename failure";
			case kErrorFileNotFound:
				return "File not found";
			case kErrorFolderCreationFailure:
				return "Folder creation failure";
			case kErrorFolderDeletionFailure:
				return "Folder deletion failure";
			case kErrorSocketCreationFailure:
				return "Socket creation failure";
			case kErrorSocketPortInvalid:
				return "Socket port invalid";
			case kErrorClipboardDataInvalid:
				return "Clipboard data invalid";
			case kErrorVideoModeSetFailure:
				return "Video mode set failure";
			case kErrorOpenGLGenTexturesFailure:
				return "OpenGL texture generation failure";
			case kErrorOpenGLFormatInvalid:
				return "OpenGL format invalid";
			case kErrorOpenGLGenBuffersFailure:
				return "OpenGL buffer generation failure";
			case kErrorImageFormatInvalid:
				return "Image format invalid";
			case kErrorPngCreationFailure:
				return "Png creation failure";
			case kErrorFontCreationFailure:
				return "Font creation failure";
			case kErrorFontInvalidEncoding:
				return "Font invalid encoding";
			case kErrorOpenALGenSourcesFailure:
				return "OpenAL source generation failure";
			case kErrorOpenALFormatInvalid:
				return "OpenAL format invalid";
			case kErrorOpenALGenBuffersFailure:
				return "OpenAL buffer generation failure";
			case kErrorOpenALNoBuffersAvailable:
				return "No OpenAL buffers available";
			case kErrorOpenALNoActiveSource:
				return "No OpenAL active source";
			case kErrorSoundFormatInvalid:
				return "Sound format invalid";
			case kErrorVorbisStackCorruption:
				return "Vorbis stack corruption";
			case kErrorVorbisInvalidSetupRequest:
				return "Vorbis invalid setup request";
			case kErrorVorbisUnimplementedMode:
				return "Unimplemented Vorbis mode";
			case kErrorProcessCreationFailure:
				return "Process creation failure";
			case kErrorModelFormatInvalid:
				return "Model format invalid";
			default:
				return "Invalid error code";
			};
		}

		void DefaultCallback(ErrorType error,
			const String &moreInfo, void *args)
		{
			Application::GetCurrent()->GetLogger()->LogError(
				String("Error %d: %s. %s\n", (Int)error,
					GetString(error).GetCString(), moreInfo.GetCString()));
		}

		void SetCallback(void (*callback)(ErrorType,const String&,void*)) {
			gErrorCallback = callback;
		}

		ErrorType Throw(ErrorType error, const String &moreInfo, void *args) {
			(*gErrorCallback)(error, moreInfo, args);
			return error;
		}

		ErrorType GetOSError() {
		#if defined(FastOSWindows)
			switch (GetLastError()) {
			case WSAETIMEDOUT:		return kErrorTimedOut;
			case WSAEWOULDBLOCK:	return kErrorInProgress;
			default:				return kErrorGeneric;
			}
		#elif defined(FastOSUnixLike)
			switch (errno) {
			case ETIMEDOUT:		return kErrorTimedOut;
			case EINPROGRESS:	return kErrorInProgress;
			default:			return kErrorGeneric;
			}
		#endif
		}
	}
}
