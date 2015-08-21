/******************************************************************************/
/*                                                                            */
/*  Socket.hpp                                                                */
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

#ifndef FastSocketHppIncluded
#define FastSocketHppIncluded

#include <Fast/Types.hpp>
#include <Fast/IPAddress.hpp>
#include <Fast/Array.hpp>
#include <Fast/SocketThreadOperation.hpp>

namespace Fast
{
	class SocketCollection;

	class FastApi Socket
	{
	private:
		Int	mType;
		Int	mProtocol;
		// Hide these functions. No copying sockets!
		Socket(const Socket &that) { }
		Socket& operator=(const Socket &that)
			{ return *this; }
	protected:
		Array<SocketThreadOperation>	mSocketThreadOperations;
		IPAddress						mLocalIPAddress;
		Int								mHandle;
		// Virtuals
		virtual ErrorType	OnOpen()	= 0;
		virtual void		OnClose()	= 0;
	public:
		Socket(Int type, Int protocol);
		~Socket();
		ErrorType	Open(UShort localPort);
		void		Close();
		UShort		GetLocalPort();
		Int			GetHandle();
		void		StopOperation(Int opID);
	};
}

#endif // FastSocketHppIncluded
