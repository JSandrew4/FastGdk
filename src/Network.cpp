/******************************************************************************/
/*                                                                            */
/*  Network.cpp                                                               */
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

#include "Network.hpp"

#include <Fast/IPAddress.hpp>
#include <Fast/TcpClientSocket.hpp>
#include <Fast/TcpServerSocket.hpp>
#include <Fast/UdpSocket.hpp>
#include <Fast/Error.hpp>
#include <Fast/Math.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SocketThread::SocketThread(SocketThreadOperation *sto) {
		mSocketThreadOperation = sto;
	}

	TcpServerListenThread::TcpServerListenThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void TcpServerListenThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		TcpServerSocket *s = (TcpServerSocket*)op->mSocket;
		ErrorType error;
		TcpClientConnection tcc;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->GetIncomingConnection(&tcc, Math::ClampLong(
				op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 33L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnClientConnect(op->mID, TcpClientConnection(),
					kErrorTimedOut);
			}
		}
	}

	TcpServerSendThread::TcpServerSendThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void TcpServerSendThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		TcpServerSocket *s = (TcpServerSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Send(op->mTcpClientConnectionID,
				op->mByteStream, Math::ClampLong(
					op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 33L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnSend(op->mID, op->mTcpClientConnectionID, error);
				break;
			}
		}
	}

	TcpServerReceiveThread::TcpServerReceiveThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void TcpServerReceiveThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		TcpServerSocket *s = (TcpServerSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Receive(op->mTcpClientConnectionID,
				&op->mByteStream, Math::ClampLong(
					op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 33L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnReceive(op->mID, op->mTcpClientConnectionID,
					op->mByteStream, error);
				sw.Reset();
				sw.Start();
			}
		}
	}

	TcpClientConnectThread::TcpClientConnectThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void TcpClientConnectThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		TcpClientSocket *s = (TcpClientSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Connect(op->mIPAddress, Math::ClampLong(
				op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 33L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnConnect(op->mID, op->mIPAddress, kErrorTimedOut);
				break;
			}
		}
	}

	TcpClientSendThread::TcpClientSendThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void TcpClientSendThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		TcpClientSocket *s = (TcpClientSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Send(op->mByteStream, Math::ClampLong(
				op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 33L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnSend(op->mID, error);
				break;
			}
		}
	}

	TcpClientReceiveThread::TcpClientReceiveThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void TcpClientReceiveThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		TcpClientSocket *s = (TcpClientSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Receive(&op->mByteStream, Math::ClampLong(
				op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 33L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnReceive(op->mID, op->mByteStream, error);
				sw.Reset();
				sw.Start();
			}
		}
	}

	UdpSendThread::UdpSendThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void UdpSendThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		UdpSocket *s = (UdpSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Send(op->mIPAddress, op->mByteStream, Math::ClampLong(
				op->mTimeoutMS - sw.GetElapsedMilliseconds(), 0L, 16L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnSend(op->mID, op->mIPAddress, error);
				break;
			}
		}
	}

	UdpReceiveThread::UdpReceiveThread(SocketThreadOperation *sto) :
		SocketThread(sto)
	{ }

	void UdpReceiveThread::Main() {
		SocketThreadOperation *op = mSocketThreadOperation;
		UdpSocket *s = (UdpSocket*)op->mSocket;
		ErrorType error;
		StopWatch sw;
		sw.Start();
		while (!ShouldEnd()) {
			error = s->Receive(op->mIPAddress, &op->mByteStream,
				Math::ClampLong(op->mTimeoutMS - sw.GetElapsedMilliseconds(),
					0L, 16L));
			if (0L == op->mTimeoutMS ||
				(error && kErrorTimedOut != error) ||
				(0L < op->mTimeoutMS &&
				sw.GetElapsedMilliseconds() >= op->mTimeoutMS))
			{
				if (error)
					Error::Throw(error, String("[%s(%p, %p)]",
						FastFunctionName, this, op));
				s->OnReceive(op->mID, op->mIPAddress, op->mByteStream, error);
				op->mByteStream.Clear();
				sw.Reset();
				sw.Start();
				continue;
			}
		}
	}

	Int	NetworkSocketOpen(Int type, Int protocol) {
		return socket(AF_INET, type, protocol);
	}

	Int NetworkSocketBind(Int socketHandle, UShort localPort) {
		IPAddress ip;
		Int result;
		ip.SetPort(localPort);
		result = bind(socketHandle,
			(sockaddr*)(&ip.GetSocketAddress()->mSockAddrIn),
			sizeof(*(&ip.GetSocketAddress()->mSockAddrIn)));
		if (0 > result)
			return result;
		Int opt = 1;
		result = setsockopt(socketHandle, SOL_SOCKET, SO_REUSEADDR,
			(const char*)&opt, sizeof(Int));
		return result;
	}

	void NetworkSocketListen(Int socketHandle, Int backlog) {
		listen(socketHandle, backlog);
	}

	UShort NetworkSocketGetPort(Int socketHandle) {
		sockaddr_in name;
		int namelen;
		getsockname(socketHandle, (sockaddr*)&name, &namelen);
		return ntohs(name.sin_port);
	}

	void NetworkSocketClose(Int socketHandle) {
		shutdown(socketHandle, 2); // SHUT_RDWR not defined on Windows I guess
	#if defined(FastOSWindows)
		closesocket(socketHandle);
	#elif defined(FastOSLinux)
		close(socketHandle);
	#elif defined(FastOSMacOSX)
		// TODO
	#endif
	}
}