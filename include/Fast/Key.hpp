/******************************************************************************/
/*                                                                            */
/*  Key.hpp                                                                   */
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

#ifndef FastKeyHppIncluded
#define FastKeyHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	enum FastApi Key
	{
		kKeyNone = 0,

		kKeyBackSpace,
		kKeyTab,
		kKeyEnter,
		kKeyEscape,
		kKeySpace,

		kKeyPageUp,
		kKeyPageDown,
		kKeyEnd,
		kKeyHome,
		kKeyPrtScrn,
		kKeyInsert,
		kKeyDelete,
		kKeyPause,
		kKeyScrollLock,
		kKeyBreak,

		kKeyRightSuper,
		kKeyLeftSuper,
		kKeyRightShift,
		kKeyLeftShift,
		kKeyRightControl,
		kKeyLeftControl,
		kKeyRightAlt,
		kKeyLeftAlt,

		kKeyLeft,
		kKeyUp,
		kKeyRight,
		kKeyDown,

		kKeyNumLock,
		kKeyNum0,
		kKeyNum1,
		kKeyNum2,
		kKeyNum3,
		kKeyNum4,
		kKeyNum5,
		kKeyNum6,
		kKeyNum7,
		kKeyNum8,
		kKeyNum9,
		kKeyMultiply,
		kKeyAdd,
		kKeySeparator,
		kKeySubtract,
		kKeyDecimal,
		kKeyDivide,

		kKeyF1,
		kKeyF2,
		kKeyF3,
		kKeyF4,
		kKeyF5,
		kKeyF6,
		kKeyF7,
		kKeyF8,
		kKeyF9,
		kKeyF10,
		kKeyF11,
		kKeyF12,

		kKeyColon,
		kKeyComma,
		kKeySlash,
		kKeyTilde,
		kKeyLeftBrace,
		kKeyRightBrace,
		kKeyBackSlash,
		kKeyQuote,
		kKeyMinus,
		kKeyPeriod,
		kKeyEquals,

		kKey0,
		kKey1,
		kKey2,
		kKey3,
		kKey4,
		kKey5,
		kKey6,
		kKey7,
		kKey8,
		kKey9,

		kKeyCapsLock,
		kKeyA,
		kKeyB,
		kKeyC,
		kKeyD,
		kKeyE,
		kKeyF,
		kKeyG,
		kKeyH,
		kKeyI,
		kKeyJ,
		kKeyK,
		kKeyL,
		kKeyM,
		kKeyN,
		kKeyO,
		kKeyP,
		kKeyQ,
		kKeyR,
		kKeyS,
		kKeyT,
		kKeyU,
		kKeyV,
		kKeyW,
		kKeyX,
		kKeyY,
		kKeyZ
	};
}

#endif // FastKeyHppIncluded
