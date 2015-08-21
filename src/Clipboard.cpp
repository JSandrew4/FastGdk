/******************************************************************************/
/*                                                                            */
/*  Clipboard.cpp                                                             */
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

#include <Fast/Clipboard.hpp>
#include <Fast/Window.hpp>
#include <Fast/Error.hpp>

#include "Undefs.hpp"

namespace Fast
{
	Clipboard::Clipboard(Window *window) : mWindow(*window) { }

	Clipboard::~Clipboard() { }

	ErrorType Clipboard::StoreText(const String &text) {
		if (text.IsEmpty()) {
			Clear();
			return kErrorNone;
		}
	#if defined(FastOSWindows)
		OpenClipboard((HWND)mWindow.GetHWND());
		WString ws = text.GetWString();
		HGLOBAL hGlobal = GlobalAlloc(NULL, ws.mSize+1);
		if (hGlobal) {
			WCHAR *wd = (WCHAR*)GlobalLock(hGlobal);
			if (wd) {
				memcpy(wd, (WCHAR*)ws.mData, ws.mSize+1);
				GlobalUnlock(hGlobal);
				SetClipboardData(CF_UNICODETEXT, hGlobal);
			}
		} else {
			CloseClipboard();
			return kErrorGeneric; // TODO: Real error
		}
		CloseClipboard();
	#elif defined(FastOSLinux)
		// TODO
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
		return kErrorNone;
	}

	String Clipboard::GetStoredText() {
		String text;
	#if defined(FastOSWindows)
		HANDLE hText = NULL;
		if (OpenClipboard((HWND)mWindow.GetHWND())) {
			if (hText = GetClipboardData(CF_UNICODETEXT)) {
				text = (WChar*)GlobalLock(hText);
				GlobalUnlock(hText);
			}
			CloseClipboard();
		}
	#elif defined(FastOSLinux)
		// TODO
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
		return text;
	}

	void Clipboard::Clear() {
	#if defined(FastOSWindows)
		OpenClipboard((HWND)mWindow.GetHWND());
		EmptyClipboard();
		CloseClipboard();
	#elif defined(FastOSLinux)
		// TODO
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
	}
}
