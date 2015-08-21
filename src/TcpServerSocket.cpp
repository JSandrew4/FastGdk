/******************************************************************************/
/*                                                                            */
/*  TcpServerSocket.cpp                                                       */
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

#include <Fast/TcpServerSocket.hpp>
#include <Fast/Error.hpp>
#include <Fast/Thread.hpp>
#include <Fast/Math.hpp>

#include "Network.hpp"

#include "Undefs.hpp"

namespace Fast
{
	ErrorType TcpServerSocket::OnOpen() {
		if (0 > listen(mHandle, 10))
			return Error::GetOSError();
		return kErrorNone;
	}

	void TcpServerSocket::OnClose() {
		DisconnectAllClients();
	}

	TcpServerSocket::TcpServerSocket() : Socket(SOCK_STREAM, IPPROTO_TCP) { }

	TcpServerSocket::TcpServerSocket(UShort localPort) :
		Socket(SOCK_STREAM, IPPROTO_TCP)
	{
		Open(localPort);
	}

	TcpServerSocket::~TcpServerSocket() {
		Close();
	}

	ErrorType TcpServerSocket::GetIncomingConnection(
		TcpClientConnection *client, Long timeoutMS)
	{
		socklen_t length = sizeof(sockaddr_in);
		sockaddr_in sai;
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
				Int newSocket = accept(mHandle, (sockaddr*)&sai, &length);
				if (0 < newSocket) {
					client->SetConnected(true);
					client->SetIPAddress(IPAddress(&sai));
					client->SetSocketHandle(newSocket);
					client->SetID(-1);
					return kErrorNone;
				}
			}
		}
		return Error::GetOSError();
	}

	Int TcpServerSocket::AcceptClient(
		const TcpClientConnection &clientConnection)
	{
		for (Int i = 0; i < mClientConnections.GetElementCount(); i++) {
			if (clientConnection.GetIPAddress() ==
				mClientConnections[i].GetIPAddress())
			{
				mClientConnections[i] = clientConnection;
				return i;
			}
		}
		mClientConnections.Append(clientConnection);
		return mClientConnections.GetElementCount() - 1;
	}

	void TcpServerSocket::RefuseClient(const TcpClientConnection &client) {
		NetworkSocketClose(client.GetSocketHandle());
	}

	void TcpServerSocket::DisconnectClient(Int clientID) {
		NetworkSocketClose(mClientConnections[clientID].GetSocketHandle());
		mClientConnections[clientID].SetConnected(false);
		mClientConnections[clientID].SetSocketHandle(-1);
	}

	void TcpServerSocket::DisconnectAllClients() {
		for (Int i = 1; i < mClientConnections.GetElementCount(); i++)
			if (mClientConnections[i].IsConnected())
				DisconnectClient(i);
	}

	ErrorType TcpServerSocket::Receive(Int clientID,
		NetworkByteStream *stream, Long timeoutMS)
	{
		Byte buffer[kFastMaxNetworkByteStreamSize];
		fd_set fds;
		Int result;
		struct timeval timeout;
		Int sock = mClientConnections[clientID].GetSocketHandle();
		FD_ZERO(&fds);
		FD_SET(sock, &fds);
		timeout.tv_sec = (long)(timeoutMS / 1000L);
		timeout.tv_usec = (long)(timeoutMS % 1000L);
		result = select(sock+1, &fds, 0, 0, &timeout);
		if (0 == result)
			return kErrorTimedOut;
		else if (0 < result) {
			if (FD_ISSET(sock, &fds)) {
				Int bytesReceived = recv(sock, (char*)buffer,
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

	ErrorType TcpServerSocket::Send(Int clientID,
		const NetworkByteStream &stream, Long timeoutMS)
	{
		fd_set fds;
		Int result;
		struct timeval timeout;
		Int sock = mClientConnections[clientID].GetSocketHandle();
		FD_ZERO(&fds);
		FD_SET(sock, &fds);
		timeout.tv_sec = (long)(timeoutMS / 1000L);
		timeout.tv_usec = (long)(timeoutMS % 1000L);
		result = select(sock+1, 0, &fds, 0, &timeout);
		if (0 == result)
			return kErrorTimedOut;
		else if (0 < result) {
			if (FD_ISSET(sock, &fds)) {
				Int bytesSent = send(sock, (char*)stream.GetData(),
					stream.GetSize(), 0);
				if (0 < bytesSent)
					return kErrorNone;
			}
		}
		return Error::GetOSError();
	}

	Int TcpServerSocket::StartListening() {
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new TcpServerListenThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	Int TcpServerSocket::StartReceiving(Int clientID, Long timeoutMS) {
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mTcpClientConnectionID = clientID;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new TcpServerReceiveThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	Int TcpServerSocket::StartSending(Int clientID,
		NetworkByteStream stream, Long timeoutMS)
	{
		SocketThreadOperation sto;
		sto.mID = mSocketThreadOperations.GetElementCount();
		sto.mSocket = this;
		sto.mTcpClientConnectionID = clientID;
		sto.mByteStream = stream;
		sto.mTimeoutMS = timeoutMS;
		mSocketThreadOperations.Append(sto);
		sto.mThread = new TcpServerSendThread(
			&mSocketThreadOperations[sto.mID]);
		sto.mThread->Run();
		return sto.mID;
	}

	void TcpServerSocket::OnClientConnect(Int opID, const TcpClientConnection &info,
		ErrorType error)
	{
		if (error)
			StopOperation(opID);
	}

	void TcpServerSocket::OnReceive(Int opID, Int clientID,
		NetworkByteStream stream, ErrorType error)
	{
		if (error)
			StopOperation(opID);
	}

	void TcpServerSocket::OnSend(Int opID, Int clientID, ErrorType error) {
		if (error)
			StopOperation(opID);
	}

}
