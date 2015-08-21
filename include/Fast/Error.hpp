/******************************************************************************/
/*                                                                            */
/*  Error.hpp                                                                 */
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

#ifndef FastErrorHppIncluded
#define FastErrorHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/String.hpp>

namespace Fast
{
	namespace Error
	{
		extern FastApi String		GetString(ErrorType error);
		extern FastApi void		GetString(ErrorType error, String *result);
		extern FastApi void		DefaultCallback(ErrorType error,
										const String &moreInfo, void *args);
		extern FastApi void		SetCallback(
										void (*callback)(ErrorType,
											const String&,void*));
		extern FastApi ErrorType	Throw(ErrorType error,
										const String &moreInfo = String(),
										void *args = 0);
		extern FastApi ErrorType	GetOSError();
	}
}

#endif // FastErrorHppIncluded
