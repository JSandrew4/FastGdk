/******************************************************************************/
/*                                                                            */
/*  TcpClientConnection.cpp                                                   */
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

#include <Fast/TcpClientConnection.hpp>

#include "Undefs.hpp"

namespace Fast
{
	TcpClientConnection::TcpClientConnection() {
		mID = -1;
		mSocketHandle = -1;
		mIsConnected = false;
	}

	TcpClientConnection::TcpClientConnection(Int id, Int socket,
		Bool isConnected, const IPAddress &ip)
	{
		mID = id;
		mSocketHandle = socket;
		mIsConnected = isConnected;
		mIPAddress = ip;
	}

	Int TcpClientConnection::GetID() const {
		return mID;
	}

	Int TcpClientConnection::GetSocketHandle() const {
		return mSocketHandle;
	}

	Bool TcpClientConnection::IsConnected() const {
		return mIsConnected;
	}

	const IPAddress& TcpClientConnection::GetIPAddress() const {
		return mIPAddress;
	}

	void TcpClientConnection::SetID(Int id) {
		mID = id;
	}

	void TcpClientConnection::SetSocketHandle(Int socket) {
		mSocketHandle = socket;
	}

	void TcpClientConnection::SetConnected(Bool isConnected) {
		mIsConnected = isConnected;
	}

	void TcpClientConnection::SetIPAddress(const IPAddress &ip) {
		mIPAddress = ip;
	}

	Bool TcpClientConnection::operator==(
		const TcpClientConnection &that) const
	{
		if (this->mID != that.mID)
			return false;
		if (this->mSocketHandle != that.mSocketHandle)
			return false;
		if (this->mIsConnected != that.mIsConnected)
			return false;
		if (this->mIPAddress != that.mIPAddress)
			return false;
		return true;
	}

	Bool TcpClientConnection::operator!=(
		const TcpClientConnection &that) const
	{
		if (this->mID != that.mID)
			return true;
		if (this->mSocketHandle != that.mSocketHandle)
			return true;
		if (this->mIsConnected != that.mIsConnected)
			return true;
		if (this->mIPAddress != that.mIPAddress)
			return true;
		return false;
	}
}