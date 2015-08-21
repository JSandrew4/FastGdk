/******************************************************************************/
/*                                                                            */
/*  KeyTranslator.cpp                                                         */
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

#include <Fast/KeyTranslator.hpp>

#if defined(FastOSWindows)
#	include <Windows.h>
#elif defined(FastOSLinux)
#	include <X11/Xlib.h>
#	include <X11/Xutil.h>
#elif defined(FastOSMacOSX)
// We only need HIToolbox/Events.h from Carbon but can't include directly...
#	include <Carbon/Carbon.h>
#endif
#include <cstring>

#include "Undefs.hpp"

namespace Fast
{
	KeyTranslator::KeyTranslator() {
		memset(mKeyMap, 0, 0xff);

	#if defined(FastOSWindows)

		mKeyMap[VK_BACK]				= "backspace";
		mKeyMap[VK_TAB]					= "tab";
		mKeyMap[VK_RETURN]				= "enter";
		mKeyMap[VK_ESCAPE]				= "escape";
		mKeyMap[VK_SPACE]				= "space";

		mKeyMap[VK_PRIOR]				= "pageup";
		mKeyMap[VK_NEXT]				= "pagedown";
		mKeyMap[VK_END]					= "end";
		mKeyMap[VK_HOME]				= "home";
		mKeyMap[VK_SNAPSHOT]			= "printscreen";
		mKeyMap[VK_INSERT]				= "insert";
		mKeyMap[VK_DELETE]				= "delete";
		mKeyMap[VK_PAUSE]				= "pause";
		mKeyMap[VK_CANCEL]				= "break";

		mKeyMap[VK_LWIN]				= "super";
		mKeyMap[VK_RWIN]				= "super";
		mKeyMap[VK_LSHIFT]				= "shift";
		mKeyMap[VK_RSHIFT]				= "shift";
		mKeyMap[VK_RCONTROL]			= "control";
		mKeyMap[VK_RCONTROL]			= "control";
		mKeyMap[VK_LMENU]				= "alt";
		mKeyMap[VK_RMENU]				= "alt";
		mKeyMap[VK_SCROLL]				= "scrolllock";
		mKeyMap[VK_CAPITAL]				= "capslock";
		mKeyMap[VK_NUMLOCK]				= "numlock";

		mKeyMap[VK_LEFT]				= "left";
		mKeyMap[VK_UP]					= "up";
		mKeyMap[VK_RIGHT]				= "right";
		mKeyMap[VK_DOWN]				= "down";

		mKeyMap[VK_F1]					= "f1";
		mKeyMap[VK_F2]					= "f2";
		mKeyMap[VK_F3]					= "f3";
		mKeyMap[VK_F4]					= "f4";
		mKeyMap[VK_F5]					= "f5";
		mKeyMap[VK_F6]					= "f6";
		mKeyMap[VK_F7]					= "f7";
		mKeyMap[VK_F8]					= "f8";
		mKeyMap[VK_F9]					= "f9";
		mKeyMap[VK_F10]					= "f10";
		mKeyMap[VK_F11]					= "f11";
		mKeyMap[VK_F12]					= "f12";
		/*
		mKeyMap[VK_NUMPAD0]				= kKeyNum0;
		mKeyMap[VK_NUMPAD1]				= kKeyNum1;
		mKeyMap[VK_NUMPAD2]				= kKeyNum2;
		mKeyMap[VK_NUMPAD3]				= kKeyNum3;
		mKeyMap[VK_NUMPAD4]				= kKeyNum4;
		mKeyMap[VK_NUMPAD5]				= kKeyNum5;
		mKeyMap[VK_NUMPAD6]				= kKeyNum6;
		mKeyMap[VK_NUMPAD7]				= kKeyNum7;
		mKeyMap[VK_NUMPAD8]				= kKeyNum8;
		mKeyMap[VK_NUMPAD9]				= kKeyNum9;
		mKeyMap[VK_MULTIPLY]			= kKeyMultiply;
		mKeyMap[VK_ADD]					= kKeyAdd;
		mKeyMap[VK_SUBTRACT]			= kKeySubtract;
		mKeyMap[VK_DECIMAL]				= kKeyDecimal;
		mKeyMap[VK_DIVIDE]				= kKeyDivide;

		mKeyMap[VK_OEM_1]				= kKeyColon;
		mKeyMap[VK_OEM_COMMA]			= kKeyComma;
		mKeyMap[VK_OEM_2]				= kKeySlash;
		mKeyMap[VK_OEM_3]				= kKeyTilde;
		mKeyMap[VK_OEM_4]				= kKeyLeftBrace;
		mKeyMap[VK_OEM_5]				= kKeyRightBrace;
		mKeyMap[VK_OEM_6]				= kKeyBackSlash;
		mKeyMap[VK_OEM_7]				= kKeyQuote;
		mKeyMap[VK_OEM_MINUS]			= kKeyMinus;
		mKeyMap[VK_OEM_PERIOD]			= kKeyPeriod;
		mKeyMap[VK_OEM_PLUS]			= kKeyEquals;

		mKeyMap['0']					= kKey0;
		mKeyMap['1']					= kKey1;
		mKeyMap['2']					= kKey2;
		mKeyMap['3']					= kKey3;
		mKeyMap['4']					= kKey4;
		mKeyMap['5']					= kKey5;
		mKeyMap['6']					= kKey6;
		mKeyMap['7']					= kKey7;
		mKeyMap['8']					= kKey8;
		mKeyMap['9']					= kKey9;

		mKeyMap['A']					= kKeyA;
		mKeyMap['B']					= kKeyB;
		mKeyMap['C']					= kKeyC;
		mKeyMap['D']					= kKeyD;
		mKeyMap['E']					= kKeyE;
		mKeyMap['F']					= kKeyF;
		mKeyMap['G']					= kKeyG;
		mKeyMap['H']					= kKeyH;
		mKeyMap['I']					= kKeyI;
		mKeyMap['J']					= kKeyJ;
		mKeyMap['K']					= kKeyK;
		mKeyMap['L']					= kKeyL;
		mKeyMap['M']					= kKeyM;
		mKeyMap['N']					= kKeyN;
		mKeyMap['O']					= kKeyO;
		mKeyMap['P']					= kKeyP;
		mKeyMap['Q']					= kKeyQ;
		mKeyMap['R']					= kKeyR;
		mKeyMap['S']					= kKeyS;
		mKeyMap['T']					= kKeyT;
		mKeyMap['U']					= kKeyU;
		mKeyMap['V']					= kKeyV;
		mKeyMap['W']					= kKeyW;
		mKeyMap['X']					= kKeyX;
		mKeyMap['Y']					= kKeyY;
		mKeyMap['Z']					= kKeyZ;
		*/
	#elif defined(FastOSLinux)

		mKeyMap[XK_BackSpace & 0xff]	= "backspace";
		mKeyMap[XK_Tab & 0xff]			= "tab";
		mKeyMap[XK_Linefeed & 0xff]		= "enter";
		mKeyMap[XK_Escape & 0xff]		= "escape";
		mKeyMap[XK_KP_Space & 0xff]		= "space";

		mKeyMap[XK_Page_Up & 0xff]		= "pageup";
		mKeyMap[XK_Page_Down & 0xff]	= "pagedown";
		mKeyMap[XK_End & 0xff]			= "end";
		mKeyMap[XK_Home & 0xff]			= "home";
		mKeyMap[XK_Sys_Req & 0xff]		= "printscreen";
		mKeyMap[XK_Insert & 0xff]		= "insert";
		mKeyMap[XK_Delete & 0xff]		= "delete";
		mKeyMap[XK_Pause & 0xff]		= "pause";
		mKeyMap[XK_Break & 0xff]		= "break";

		mKeyMap[XK_Super_L & 0xff]		= "super";
		mKeyMap[XK_Super_R & 0xff]		= "super";
		mKeyMap[XK_Shift_L & 0xff]		= "shift";
		mKeyMap[XK_Shift_R & 0xff]		= "shift";
		mKeyMap[XK_Control_L & 0xff]	= "control";
		mKeyMap[XK_Control_R & 0xff]	= "control";
		mKeyMap[XK_Alt_L & 0xff]		= "alt";
		mKeyMap[XK_Alt_R & 0xff]		= "alt";
		mKeyMap[XK_Scroll_Lock & 0xff]	= "scrolllock";
		mKeyMap[XK_Caps_Lock & 0xff]	= "capslock";
		mKeyMap[XK_Num_Lock & 0xff]		= "numlock";

		mKeyMap[XK_Left & 0xff]			= "left";
		mKeyMap[XK_Up & 0xff]			= "up";
		mKeyMap[XK_Right & 0xff]		= "right";
		mKeyMap[XK_Down & 0xff]			= "down";

		mKeyMap[XK_F1 & 0xff]			= "f1";
		mKeyMap[XK_F2 & 0xff]			= "f2";
		mKeyMap[XK_F3 & 0xff]			= "f3";
		mKeyMap[XK_F4 & 0xff]			= "f4";
		mKeyMap[XK_F5 & 0xff]			= "f5";
		mKeyMap[XK_F6 & 0xff]			= "f6";
		mKeyMap[XK_F7 & 0xff]			= "f7";
		mKeyMap[XK_F8 & 0xff]			= "f8";
		mKeyMap[XK_F9 & 0xff]			= "f9";
		mKeyMap[XK_F10 & 0xff]			= "f10";
		mKeyMap[XK_F11 & 0xff]			= "f11";
		mKeyMap[XK_F12 & 0xff]			= "f12";
		/*
		mKeyMap[XK_KP_0 & 0xff]			= kKeyNum0;
		mKeyMap[XK_KP_1 & 0xff]			= kKeyNum1;
		mKeyMap[XK_KP_2 & 0xff]			= kKeyNum2;
		mKeyMap[XK_KP_3 & 0xff]			= kKeyNum3;
		mKeyMap[XK_KP_4 & 0xff]			= kKeyNum4;
		mKeyMap[XK_KP_5 & 0xff]			= kKeyNum5;
		mKeyMap[XK_KP_6 & 0xff]			= kKeyNum6;
		mKeyMap[XK_KP_7 & 0xff]			= kKeyNum7;
		mKeyMap[XK_KP_8 & 0xff]			= kKeyNum8;
		mKeyMap[XK_KP_9 & 0xff]			= kKeyNum9;
		mKeyMap[XK_KP_Multiply & 0xff]	= kKeyMultiply;
		mKeyMap[XK_KP_Add & 0xff]		= kKeyAdd;
		mKeyMap[XK_KP_Subtract & 0xff]	= kKeySubtract;
		mKeyMap[XK_KP_Decimal & 0xff]	= kKeyDecimal;
		mKeyMap[XK_KP_Divide & 0xff]	= kKeyDivide;

		mKeyMap[';']					= kKeyColon;
		mKeyMap[',']					= kKeyComma;
		mKeyMap['/']					= kKeySlash;
		mKeyMap['`']					= kKeyTilde;
		mKeyMap['[']					= kKeyLeftBrace;
		mKeyMap[']']					= kKeyRightBrace;
		mKeyMap['\\']					= kKeyBackSlash;
		mKeyMap['\'']					= kKeyQuote;
		mKeyMap['-']					= kKeyMinus;
		mKeyMap['.']					= kKeyPeriod;
		mKeyMap['=']					= kKeyEquals;

		mKeyMap['0']					= kKey0;
		mKeyMap['1']					= kKey1;
		mKeyMap['2']					= kKey2;
		mKeyMap['3']					= kKey3;
		mKeyMap['4']					= kKey4;
		mKeyMap['5']					= kKey5;
		mKeyMap['6']					= kKey6;
		mKeyMap['7']					= kKey7;
		mKeyMap['8']					= kKey8;
		mKeyMap['9']					= kKey9;

		mKeyMap['a']					= kKeyA;
		mKeyMap['b']					= kKeyB;
		mKeyMap['c']					= kKeyC;
		mKeyMap['d']					= kKeyD;
		mKeyMap['e']					= kKeyE;
		mKeyMap['f']					= kKeyF;
		mKeyMap['g']					= kKeyG;
		mKeyMap['h']					= kKeyH;
		mKeyMap['i']					= kKeyI;
		mKeyMap['j']					= kKeyJ;
		mKeyMap['k']					= kKeyK;
		mKeyMap['l']					= kKeyL;
		mKeyMap['m']					= kKeyM;
		mKeyMap['n']					= kKeyN;
		mKeyMap['o']					= kKeyO;
		mKeyMap['p']					= kKeyP;
		mKeyMap['q']					= kKeyQ;
		mKeyMap['r']					= kKeyR;
		mKeyMap['s']					= kKeyS;
		mKeyMap['t']					= kKeyT;
		mKeyMap['u']					= kKeyU;
		mKeyMap['v']					= kKeyV;
		mKeyMap['w']					= kKeyW;
		mKeyMap['x']					= kKeyX;
		mKeyMap['y']					= kKeyY;
		mKeyMap['z']					= kKeyZ;
		*/
	#elif defined(FastOSMacOSX)

		mKeyMap[kVK_Delete]				= "backspace";
		mKeyMap[kVK_Tab]				= "tab";
		mKeyMap[kVK_Return]				= "enter";
		mKeyMap[kVK_Escape]				= "escape";
		mKeyMap[kVK_Space]				= "space";

		mKeyMap[kVK_PageUp]				= "pageup";
		mKeyMap[kVK_PageDown]			= "pagedown";
		mKeyMap[kVK_End]				= "end";
		mKeyMap[kVK_Home]				= "home";
		mKeyMap[kVK_F13]				= "printscreen";
		mKeyMap[kVK_Help]				= "insert";
		mKeyMap[kVK_ForwardDelete]		= "delete";
		mKeyMap[kVK_F15]				= "pause";
		//mKeyMap[VK_CANCEL]			= "break";

		mKeyMap[kVK_Command]			= "super";
		mKeyMap[0x36]					= "super";
		mKeyMap[kVK_Shift]				= "shift";
		mKeyMap[kVK_RightShift]			= "shift";
		mKeyMap[kVK_Control]			= "control";
		mKeyMap[kVK_RightControl]		= "control";
		mKeyMap[kVK_Option]				= "alt";
		mKeyMap[kVK_RightOption]		= "alt";
		mKeyMap[kVK_F14]				= "scrolllock";
		mKeyMap[kVK_CapsLock]			= "capslock";
		//mKeyMap[VK_NUMLOCK]			= "numlock";

		mKeyMap[kVK_LeftArrow]			= "left";
		mKeyMap[kVK_UpArrow]			= "up";
		mKeyMap[kVK_RightArrow]			= "right";
		mKeyMap[kVK_DownArrow]			= "down";

		mKeyMap[kVK_F1]					= "f1";
		mKeyMap[kVK_F2]					= "f2";
		mKeyMap[kVK_F3]					= "f3";
		mKeyMap[kVK_F4]					= "f4";
		mKeyMap[kVK_F5]					= "f5";
		mKeyMap[kVK_F6]					= "f6";
		mKeyMap[kVK_F7]					= "f7";
		mKeyMap[kVK_F8]					= "f8";
		mKeyMap[kVK_F9]					= "f9";
		mKeyMap[kVK_F10]				= "f10";
		mKeyMap[kVK_F11]				= "f11";
		mKeyMap[kVK_F12]				= "f12";
		/*
		mKeyMap[kVK_ANSI_Keypad0]		= kKeyNum0;
		mKeyMap[kVK_ANSI_Keypad1]		= kKeyNum1;
		mKeyMap[kVK_ANSI_Keypad2]		= kKeyNum2;
		mKeyMap[kVK_ANSI_Keypad3]		= kKeyNum3;
		mKeyMap[kVK_ANSI_Keypad4]		= kKeyNum4;
		mKeyMap[kVK_ANSI_Keypad5]		= kKeyNum5;
		mKeyMap[kVK_ANSI_Keypad6]		= kKeyNum6;
		mKeyMap[kVK_ANSI_Keypad7]		= kKeyNum7;
		mKeyMap[kVK_ANSI_Keypad8]		= kKeyNum8;
		mKeyMap[kVK_ANSI_Keypad9]		= kKeyNum9;
		mKeyMap[kVK_ANSI_KeypadMultiply]= kKeyMultiply;
		mKeyMap[kVK_ANSI_KeypadPlus]	= kKeyAdd;
		mKeyMap[kVK_ANSI_KeypadMinus]	= kKeySubtract;
		mKeyMap[kVK_ANSI_KeypadDecimal]	= kKeyDecimal;
		mKeyMap[kVK_ANSI_KeypadDivide]	= kKeyDivide;

		mKeyMap[kVK_ANSI_Semicolon]		= kKeyColon;
		mKeyMap[kVK_ANSI_Comma]			= kKeyComma;
		mKeyMap[kVK_ANSI_Slash]			= kKeySlash;
		mKeyMap[kVK_ANSI_Grave]			= kKeyTilde;
		mKeyMap[kVK_ANSI_LeftBracket]	= kKeyLeftBrace;
		mKeyMap[kVK_ANSI_RightBracket]	= kKeyRightBrace;
		mKeyMap[kVK_ANSI_Backslash]		= kKeyBackSlash;
		mKeyMap[kVK_ANSI_Quote]			= kKeyQuote;
		mKeyMap[kVK_ANSI_Minus]			= kKeyMinus;
		mKeyMap[kVK_ANSI_Period]		= kKeyPeriod;
		mKeyMap[kVK_ANSI_Equal]			= kKeyEquals;

		mKeyMap[kVK_ANSI_0]				= kKey0;
		mKeyMap[kVK_ANSI_1]				= kKey1;
		mKeyMap[kVK_ANSI_2]				= kKey2;
		mKeyMap[kVK_ANSI_3]				= kKey3;
		mKeyMap[kVK_ANSI_4]				= kKey4;
		mKeyMap[kVK_ANSI_5]				= kKey5;
		mKeyMap[kVK_ANSI_6]				= kKey6;
		mKeyMap[kVK_ANSI_7]				= kKey7;
		mKeyMap[kVK_ANSI_8]				= kKey8;
		mKeyMap[kVK_ANSI_9]				= kKey9;

		mKeyMap[kVK_ANSI_A]				= kKeyA;
		mKeyMap[kVK_ANSI_B]				= kKeyB;
		mKeyMap[kVK_ANSI_C]				= kKeyC;
		mKeyMap[kVK_ANSI_D]				= kKeyD;
		mKeyMap[kVK_ANSI_E]				= kKeyE;
		mKeyMap[kVK_ANSI_F]				= kKeyF;
		mKeyMap[kVK_ANSI_G]				= kKeyG;
		mKeyMap[kVK_ANSI_H]				= kKeyH;
		mKeyMap[kVK_ANSI_I]				= kKeyI;
		mKeyMap[kVK_ANSI_J]				= kKeyJ;
		mKeyMap[kVK_ANSI_K]				= kKeyK;
		mKeyMap[kVK_ANSI_L]				= kKeyL;
		mKeyMap[kVK_ANSI_M]				= kKeyM;
		mKeyMap[kVK_ANSI_N]				= kKeyN;
		mKeyMap[kVK_ANSI_O]				= kKeyO;
		mKeyMap[kVK_ANSI_P]				= kKeyP;
		mKeyMap[kVK_ANSI_Q]				= kKeyQ;
		mKeyMap[kVK_ANSI_R]				= kKeyR;
		mKeyMap[kVK_ANSI_S]				= kKeyS;
		mKeyMap[kVK_ANSI_T]				= kKeyT;
		mKeyMap[kVK_ANSI_U]				= kKeyU;
		mKeyMap[kVK_ANSI_V]				= kKeyV;
		mKeyMap[kVK_ANSI_W]				= kKeyW;
		mKeyMap[kVK_ANSI_X]				= kKeyX;
		mKeyMap[kVK_ANSI_Y]				= kKeyY;
		mKeyMap[kVK_ANSI_Z]				= kKeyZ;
		*/
	#endif
	}

	const Char* KeyTranslator::GetKey(Int keyCode) {
		if (keyCode < 0xff && keyCode >= 0)
			return mKeyMap[keyCode];
		return 0;
	}
}