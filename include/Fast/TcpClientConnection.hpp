/******************************************************************************/
/*                                                                            */
/*  TcpClientConnection.hpp                                                   */
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

#ifndef FastTcpClientConnectionHppIncluded
#define FastTcpClientConnectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/IPAddress.hpp>

namespace Fast
{
	class FastApi TcpClientConnection
	{
	protected:
		Int			mID;
		Int			mSocketHandle;
		Bool		mIsConnected;
		IPAddress	mIPAddress;
	public:
		// Constructors
		TcpClientConnection();
		TcpClientConnection(Int id, Int socketHandle,
			Bool isConnected, const IPAddress &ip);
		// Gets
		Int					GetID() const;
		Int					GetSocketHandle() const;
		Bool				IsConnected() const;
		const IPAddress&	GetIPAddress() const;
		// Sets
		void	SetID(Int id);
		void	SetSocketHandle(Int socketHandle);
		void	SetConnected(Bool isConnected);
		void	SetIPAddress(const IPAddress &ip);
		// Operators
		Bool	operator==(const TcpClientConnection &that) const;
		Bool	operator!=(const TcpClientConnection &that) const;
	};
}

#endif // FastTcpClientConnectionHppIncluded