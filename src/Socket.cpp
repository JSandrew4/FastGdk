/******************************************************************************/
/*                                                                            */
/*  Socket.cpp                                                                */
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

#include <Fast/Socket.hpp>
#include <Fast/Error.hpp>
#include <Fast/Thread.hpp>

#include "Network.hpp"

#include "Undefs.hpp"

namespace Fast
{
	Socket::Socket(Int type, Int protocol) {
		mType = type;
		mProtocol = protocol;
		mHandle = -1;
	}

	Socket::~Socket() {
		Close();
	}

	ErrorType Socket::Open(UShort localPort) {
		mHandle = NetworkSocketOpen(mType, mProtocol);
		if (0 > mHandle)
			return Error::Throw(Error::GetOSError(),
				String("[%s(%d)]", FastFunctionName, (Int)localPort));
		if (0 > NetworkSocketBind(mHandle, localPort)) {
			ErrorType error = Error::GetOSError();
			NetworkSocketClose(mHandle);
			mHandle = -1;
			return Error::Throw(error,
				String("[%s(%d)]", FastFunctionName, (Int)localPort));
		}
		mLocalIPAddress.SetPort(NetworkSocketGetPort(mHandle));
		return OnOpen();
	}

	void Socket::Close() {
		if (-1 == mHandle)
			return;
		OnClose();
		for (Int i = 0; i < mSocketThreadOperations.GetElementCount(); i++)
			if (mSocketThreadOperations[i].mThread->IsRunning())
				mSocketThreadOperations[i].mThread->AskToEnd();
		NetworkSocketClose(mHandle);
		mHandle = -1;
		mLocalIPAddress = IPAddress();
	}
	
	UShort Socket::GetLocalPort() {
		return mLocalIPAddress.GetPort();
	}

	Int Socket::GetHandle() {
		return mHandle;
	}

	void Socket::StopOperation(Int opID) {
		mSocketThreadOperations[opID].mThread->AskToEnd();
	}
}
