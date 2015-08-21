/******************************************************************************/
/*                                                                            */
/*  UdpSocket.cpp                                                             */
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

#include <Fast/UdpSocket.hpp>
#include <Fast/Error.hpp>
#include <Fast/Thread.hpp>
#include <Fast/Math.hpp>

#include "Network.hpp"

#include "Undefs.hpp"

namespace Fast
{
	ErrorType UdpSocket::OnOpen() {
		return kErrorNone;
	}

	void UdpSocket::OnClose() { }

	UdpSocket::UdpSocket() : Socket(SOCK_DGRAM, IPPROTO_UDP) { }

	UdpSocket::UdpSocket(UShort localPort) : Socket(SOCK_DGRAM, IPPROTO_UDP) {
		Open(localPort);
	}

	UdpSocket::~UdpSocket() {
		Close();
	}

	ErrorType UdpSocket::Send(const IPAddress &toIPAddress,
		const NetworkByteStream &packet, Long timeoutMS)
	{
		fd_set fds;
		Int result;
		struct timeval timeout;
		FD_ZERO(&fds);
		FD_SET(mHandle, &fds);
		timeout.tv_sec = (long)(timeoutMS / 1000L);
		timeout.tv_usec = (long)(timeoutMS % 1000L);
		result = select(mHandle+1, 0, &fds, 0, &timeout);
		if (0 == result)
			return kErrorTimedOut;
		else if (0 < result) {
			if (FD_ISSET(mHandle, &fds)) {
				Int bytesSent = sendto(mHandle, (char*)packet.GetData(),
					packet.GetSize(), 0,
					(sockaddr*)(&toIPAddress.GetSocketAddress()->mSockAddrIn),
					sizeof(*(&toIPAddress.GetSocketAddress()->mSockAddrIn)));
				if (0 < bytesSent)
					return kErrorNone;
			}
		}
		return Error::GetOSError();
	}

	Int UdpSocket::StartSending(const IPAddress &toIPAddress,
		const NetworkByteStream &packet, Long timeoutMS)
	{
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mIPAddress = toIPAddress;
		sto.mByteStream = packet;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new UdpSendThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	ErrorType UdpSocket::Receive(const IPAddress &fromIPAddress,
		NetworkByteStream *packet, Long timeoutMS)
	{
		Byte buffer[kFastMaxNetworkByteStreamSize];
		socklen_t length = sizeof(sockaddr_in);
		fd_set fds;
		Int result;
		struct timeval timeout;
		FD_ZERO(&fds);
		FD_SET(mHandle, &fds);
		timeout.tv_sec = (long)(timeoutMS / 1000L);
		timeout.tv_usec = (long)(timeoutMS % 1000L);
		result = select(mHandle+1, &fds, 0, 0, &timeout);
		if (0 == result)
			return kErrorTimedOut;
		else if (0 < result) {
			if (FD_ISSET(mHandle, &fds)) {
				Int bytesReceived = recvfrom(mHandle,
					(char*)buffer, kFastMaxNetworkByteStreamSize, 0,
					(sockaddr*)&fromIPAddress.GetSocketAddress()->mSockAddrIn,
					(socklen_t*)&length);
				if (0 < bytesReceived) {
					packet->Clear();
					packet->Write(buffer, bytesReceived);
					return kErrorNone;
				}
			}
		}
		return Error::GetOSError();
	}

	Int UdpSocket::StartReceiving(const IPAddress &fromIPAddress,
		Long timeoutMS)
	{
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mIPAddress = fromIPAddress;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new UdpReceiveThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	void UdpSocket::OnSend(Int opID, const IPAddress &toIPAddress,
		ErrorType error)
	{
		if (error)
			StopOperation(opID);
	}

	void UdpSocket::OnReceive(Int opID, const IPAddress &fromIPAddress,
		NetworkByteStream packet, ErrorType error)
	{
		if (error)
			StopOperation(opID);
	}
}
