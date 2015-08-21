/******************************************************************************/
/*                                                                            */
/*  Network.hpp                                                               */
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

#ifndef FastNetworkHppIncluded
#define FastNetworkHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Thread.hpp>

#if defined(FastOSUnixLike)
#	include <sys/types.h>
#	include <unistd.h>
#	include <netdb.h>
#	include <arpa/inet.h>
#	include <netinet/in.h>
#	include <fcntl.h>
#	include <sys/time.h>
#	include <sys/socket.h>
#endif

namespace Fast
{
	class SocketThreadOperation;

	struct SocketAddress
	{
		sockaddr_in	mSockAddrIn;
	};

	class SocketThread : public Thread
	{
	protected:
		SocketThreadOperation	*mSocketThreadOperation;
		virtual void	Main()	= 0;
	public:
		SocketThread(SocketThreadOperation *sto);
	};

	class TcpServerListenThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		TcpServerListenThread(SocketThreadOperation *sto);
	};

	class TcpServerSendThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		TcpServerSendThread(SocketThreadOperation *sto);
	};

	class TcpServerReceiveThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		TcpServerReceiveThread(SocketThreadOperation *sto);
	};

	class TcpClientConnectThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		TcpClientConnectThread(SocketThreadOperation *sto);
	};

	class TcpClientSendThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		TcpClientSendThread(SocketThreadOperation *sto);
	};

	class TcpClientReceiveThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		TcpClientReceiveThread(SocketThreadOperation *sto);
	};

	class UdpSendThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		UdpSendThread(SocketThreadOperation *sto);
	};

	class UdpReceiveThread : public SocketThread
	{
	protected:
		void	Main();
	public:
		UdpReceiveThread(SocketThreadOperation *sto);
	};

	extern Int		NetworkSocketOpen(Int type, Int protocol);
	extern Int		NetworkSocketBind(Int socketHandle, UShort localPort);
	extern void		NetworkSocketListen(Int socketHandle, Int backlog);
	extern UShort	NetworkSocketGetPort(Int socketHandle);
	extern void		NetworkSocketClose(Int socketHandle);
}

#endif // FastNetworkHppIncluded
