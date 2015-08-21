/******************************************************************************/
/*                                                                            */
/*  UdpSocket.hpp                                                             */
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

#ifndef FastUdpSocketHppIncluded
#define FastUdpSocketHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Socket.hpp>
#include <Fast/NetworkByteStream.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class IPAddress;
	class Game;
	
	class FastApi UdpSocket : public Socket
	{
	private:
		// Hide these functions. No copying sockets!
		UdpSocket(const UdpSocket &that) : Socket(0, 0) { }
		UdpSocket& operator=(const UdpSocket &that)
			{ return *this; }
	protected:
		ErrorType	OnOpen();
		void		OnClose();
	public:
		// (Con/De)structors
		UdpSocket();
		UdpSocket(UShort localPort);
		~UdpSocket();
		// Misc
		ErrorType	Send(const IPAddress &toIPAddress,
						const NetworkByteStream& packet, Long timeoutMS = 0L);
		Int			StartSending(const IPAddress &toIPAddress,
						const NetworkByteStream &packet,
						Long timeoutMS = 5000L);
		ErrorType	Receive(const IPAddress &fromIPAddres,
						NetworkByteStream *packet, Long timeoutMS = 0L);
		Int			StartReceiving(const IPAddress &fromIPAddress,
						Long timeoutMS = 5000L);
		// Virtuals
		virtual void	OnSend(Int opID, const IPAddress &toIPAddress,
							ErrorType error);
		virtual void	OnReceive(Int opID, const IPAddress &fromIPAddress,
							NetworkByteStream packet, ErrorType error);
	};
}

#endif // FastUdpSocketHppIncluded
