/******************************************************************************/
/*                                                                            */
/*  TcpClientSocket.hpp                                                       */
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

#ifndef FastTcpClientSocketHppIncluded
#define FastTcpClientSocketHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Socket.hpp>
#include <Fast/IPAddress.hpp>
#include <Fast/NetworkByteStream.hpp>

namespace Fast
{
	class FastApi TcpClientSocket : public Socket
	{
	private:
		Bool	mIsConnected;
		// Hide these functions. No copying sockets!
		TcpClientSocket(const TcpClientSocket &that) : Socket(0, 0) { }
		TcpClientSocket& operator=(const TcpClientSocket &that)
			{ return *this; }
	protected:
		IPAddress	mServerIPAddress;
		ErrorType	OnOpen();
		void		OnClose();
	public:
		// (Con/De)structors
		TcpClientSocket();
		TcpClientSocket(UShort localPort);
		~TcpClientSocket();
		// Misc
		ErrorType		Connect(const IPAddress &serverIP,
							Long timeoutMS = 5000L);
		Bool			IsConnected() const;
		ErrorType		Receive(NetworkByteStream *stream,
							Long timeoutMS = 0L);
		ErrorType		Send(NetworkByteStream stream, Long timeoutMS = 0L);
		Int				StartConnecting(const IPAddress &serverIP,
							Long timeoutMS = 5000L);
		Int				StartReceiving(Long timeoutMS = 5000L);
		Int				StartSending(NetworkByteStream stream,
							Long timeoutMS = 5000L);
		// Virtuals
		virtual void	OnConnect(Int opID, const IPAddress &serverIP,
							ErrorType error);
		virtual void	OnReceive(Int opID, NetworkByteStream stream,
							ErrorType error);
		virtual void	OnSend(Int opID, ErrorType error);
	};
}

#endif // FastTcpClientSocketHppIncluded
