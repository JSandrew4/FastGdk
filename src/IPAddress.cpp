/******************************************************************************/
/*                                                                            */
/*  IPAddress.cpp                                                             */
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

#include <Fast/IPAddress.hpp>

// TODO: Replace stringstream stuff
#include <sstream>
#include <cstring>

#include "Network.hpp"
#include "Undefs.hpp"

namespace Fast
{
	IPAddress::IPAddress() {
		mSocketAddress = new SocketAddress;
		mSocketAddress->mSockAddrIn.sin_family = AF_INET;
		mSocketAddress->mSockAddrIn.sin_addr.s_addr = htons(0);
		mSocketAddress->mSockAddrIn.sin_port = htons(0);
	}

	IPAddress::IPAddress(const IPAddress &that) {
		mSocketAddress = new SocketAddress;
		*this = that;
	}

	IPAddress::IPAddress(const String &address, UShort port) {
		mSocketAddress = new SocketAddress;
		mSocketAddress->mSockAddrIn.sin_family = AF_INET;
		mSocketAddress->mSockAddrIn.sin_port = htons(port);
		mSocketAddress->mSockAddrIn.sin_addr.s_addr = inet_addr(address.GetAsciiString().mData);
	}

	IPAddress::IPAddress(Int address, UShort port) {
		mSocketAddress = new SocketAddress;
		mSocketAddress->mSockAddrIn.sin_family = AF_INET;
		mSocketAddress->mSockAddrIn.sin_port = htons(port);
		mSocketAddress->mSockAddrIn.sin_addr.s_addr = htonl(address);
	}

	IPAddress::IPAddress(void *sockAddrIn) {
		mSocketAddress = new SocketAddress;
		memcpy(&mSocketAddress->mSockAddrIn, sockAddrIn, sizeof(sockaddr_in));
	}

	IPAddress::~IPAddress() {
		delete mSocketAddress;
	}

	void IPAddress::SetAddress(const String &address) {
		mSocketAddress->mSockAddrIn.sin_addr.s_addr = inet_addr(address.GetAsciiString().mData);
	}

	void IPAddress::SetAddress(Int address) {
		mSocketAddress->mSockAddrIn.sin_addr.s_addr = htonl(address);
	}

	String IPAddress::GetAddressAsString() const {
		std::stringstream ss;
	#if defined(FastOSWindows)
		ss <<
			(Int)mSocketAddress->mSockAddrIn.sin_addr.S_un.S_un_b.s_b1 << '.' <<
			(Int)mSocketAddress->mSockAddrIn.sin_addr.S_un.S_un_b.s_b2 << '.' <<
			(Int)mSocketAddress->mSockAddrIn.sin_addr.S_un.S_un_b.s_b3 << '.' <<
			(Int)mSocketAddress->mSockAddrIn.sin_addr.S_un.S_un_b.s_b4;
	#elif defined(FastOSLinux)
		// TODO
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
		return String(ss.str().c_str());
	}

	Int IPAddress::GetAddressAsInt() const {
		return ntohl(mSocketAddress->mSockAddrIn.sin_addr.s_addr);
	}

	void IPAddress::SetPort(Short port) {
		mSocketAddress->mSockAddrIn.sin_port = htons(port);
	}

	UShort IPAddress::GetPort() const {
		return ntohs(mSocketAddress->mSockAddrIn.sin_port);
	}

	SocketAddress* IPAddress::GetSocketAddress() const {
		return mSocketAddress;
	}

	IPAddress& IPAddress::operator=(const IPAddress &that) {
		memcpy(&this->mSocketAddress->mSockAddrIn, &that.mSocketAddress->mSockAddrIn, sizeof(sockaddr_in));
		return * this;
	}

	Bool IPAddress::operator==(const IPAddress &that) const {
		if (0 == memcmp(&this->mSocketAddress->mSockAddrIn, &that.mSocketAddress->mSockAddrIn, sizeof(sockaddr_in)))
			return true;
		return false;
	}

	Bool IPAddress::operator!=(const IPAddress &that) const {
		if (0 != memcmp(&this->mSocketAddress->mSockAddrIn, &that.mSocketAddress->mSockAddrIn, sizeof(sockaddr_in)))
			return true;
		return false;
	}
}
