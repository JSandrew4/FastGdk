/******************************************************************************/
/*                                                                            */
/*  TcpClientSocket.cpp                                                       */
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

#include <Fast/TcpClientSocket.hpp>
#include <Fast/Error.hpp>
#include <Fast/Thread.hpp>
#include <Fast/Math.hpp>

#include "Network.hpp"
#include "Undefs.hpp"

namespace Fast
{
	ErrorType TcpClientSocket::OnOpen() {
		return kErrorNone;
	}

	void TcpClientSocket::OnClose() { }

	TcpClientSocket::TcpClientSocket() : Socket(SOCK_STREAM, IPPROTO_TCP) { }

	TcpClientSocket::TcpClientSocket(UShort localPort) :
		Socket(SOCK_STREAM, IPPROTO_TCP)
	{
		Open(localPort);
	}

	TcpClientSocket::~TcpClientSocket() {
		Close();
	}

	ErrorType TcpClientSocket::Connect(
		const IPAddress &serverIP, Long timeoutMS)
	{
		sockaddr sai;
		fd_set fds;
		Int result;
		struct timeval timeout;
		FD_ZERO(&fds);
		FD_SET(mHandle, &fds);
		timeout.tv_sec = (long)(timeoutMS / 1000L);
		timeout.tv_usec = (long)(timeoutMS % 1000L);
		result = connect(mHandle,
			(sockaddr*)(&serverIP.GetSocketAddress()->mSockAddrIn),
			sizeof(sockaddr_in));
		if (0 == result) {
			mServerIPAddress = serverIP;
			mIsConnected = true;
			return kErrorNone;
		} else {
			ErrorType error = Error::GetOSError();
			if (kErrorInProgress == error) {
				result = select(mHandle+1, NULL, &fds, NULL, &timeout);
				if (0 == result)
					return kErrorTimedOut;
				else if (0 < result) {
					mServerIPAddress = serverIP;
					mIsConnected = true;
					return kErrorNone;
				}
			}
		}
		return Error::GetOSError();
	}

	Bool TcpClientSocket::IsConnected() const {
		return mIsConnected;
	}

	ErrorType TcpClientSocket::Receive(
		NetworkByteStream *stream, Long timeoutMS)
	{
		Byte buffer[kFastMaxNetworkByteStreamSize];
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
				Int bytesReceived = recv(mHandle, (char*)buffer,
					kFastMaxNetworkByteStreamSize, 0);
				if (0 < bytesReceived) {
					stream->Clear();
					stream->Write(buffer, bytesReceived);
					return kErrorNone;
				}
			}
		}
		return Error::GetOSError();
	}

	ErrorType TcpClientSocket::Send(NetworkByteStream stream, Long timeoutMS) {
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
				Int bytesSent = send(mHandle, (char*)stream.GetData(),
					stream.GetSize(), 0);
				if (0 < bytesSent)
					return kErrorNone;
			}
		}
		return Error::GetOSError();
	}

	Int TcpClientSocket::StartConnecting(
		const IPAddress &serverIP, Long timeoutMS)
	{
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mIPAddress = serverIP;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new TcpClientConnectThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	Int TcpClientSocket::StartReceiving(Long timeoutMS) {
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new TcpClientReceiveThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	Int TcpClientSocket::StartSending(NetworkByteStream stream, Long timeoutMS)
	{
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mByteStream = stream;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new TcpClientSendThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	void TcpClientSocket::OnConnect(Int opID, const IPAddress &serverIP,
		ErrorType error)
	{
		if (error)
			StopOperation(opID);
	}

	void TcpClientSocket::OnReceive(Int opID, NetworkByteStream stream,
		ErrorType error)
	{
		if (error)
			StopOperation(opID);
	}

	void TcpClientSocket::OnSend(Int opID, ErrorType error) {
		if (error)
			StopOperation(opID);
	}
}