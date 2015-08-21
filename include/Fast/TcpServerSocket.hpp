/******************************************************************************/
/*                                                                            */
/*  TcpServerSocket.hpp                                                       */
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

#ifndef FastTcpServerSocketHppIncluded
#define FastTcpServerSocketHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Socket.hpp>
#include <Fast/IPAddress.hpp>
#include <Fast/TcpClientConnection.hpp>
#include <Fast/NetworkByteStream.hpp>

namespace Fast
{
	class FastApi TcpServerSocket : public Socket
	{
	private:
		// Hide these functions. No copying sockets!
		TcpServerSocket(const TcpServerSocket &that) : Socket(0, 0) { }
		TcpServerSocket& operator=(const TcpServerSocket &that)
			{ return *this; }
	protected:
		Array<TcpClientConnection>	mClientConnections;
		ErrorType	OnOpen();
		void		OnClose();
	public:
		// (Con/De)structors
		TcpServerSocket();
		TcpServerSocket(UShort localPort);
		~TcpServerSocket();
		// Misc
		ErrorType	GetIncomingConnection(TcpClientConnection *client,
						Long timeoutMS = 0L);
		Int			AcceptClient(const TcpClientConnection &client);
		void		RefuseClient(const TcpClientConnection &client);
		void		DisconnectClient(Int clientID);
		void		DisconnectAllClients();
		ErrorType	Receive(Int clientID, NetworkByteStream *stream,
						Long timeoutMS = 0L);
		ErrorType	Send(Int clientID, const NetworkByteStream &stream,
						Long timeoutMS = 0L);
		Int			StartListening();
		Int			StartReceiving(Int clientID, Long timeoutMS = 5000L);
		Int			StartSending(Int clientID, NetworkByteStream stream,
						Long timeoutMS = 5000L);
		// Virtuals
		virtual void	OnClientConnect(Int opID,
							const TcpClientConnection &info, ErrorType error);
		virtual void	OnReceive(Int opID, Int clientID,
							NetworkByteStream stream, ErrorType error);
		virtual void	OnSend(Int opID, Int clientID, ErrorType error);
	};
}

#endif // FastTcpServerSocketHppIncluded
