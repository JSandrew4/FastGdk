/******************************************************************************/
/*                                                                            */
/*  IPAddress.hpp                                                             */
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

#ifndef FastIPAddressHppIncluded
#define FastIPAddressHppIncluded

#include <Fast/Types.hpp>
#include <Fast/String.hpp>

#undef SetPort // SetPort is defined by Windows as SetPortW

namespace Fast
{
	struct SocketAddress;

	class FastApi IPAddress
	{
	private:
		// Members
		SocketAddress	*mSocketAddress;
	public:
		// (Con/De)structors
		IPAddress();
		IPAddress(const IPAddress &that);
		IPAddress(const String &address, UShort port);
		IPAddress(Int address, UShort port);
		IPAddress(void *sockAddrIn);
		~IPAddress();
		// Set/Get functions
		void			SetAddress(const String &address);
		void			SetAddress(Int address);
		String			GetAddressAsString() const;
		Int				GetAddressAsInt() const;
		void			SetPort(Short port);
		UShort			GetPort() const;
		SocketAddress*	GetSocketAddress() const;
		// Assignment operator
		IPAddress&	operator= (const IPAddress &that);
		Bool		operator==(const IPAddress &that) const;
		Bool		operator!=(const IPAddress &that) const;
	};
}

#endif // FastIPAddressHppIncluded
