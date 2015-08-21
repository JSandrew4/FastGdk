/******************************************************************************/
/*                                                                            */
/*  Display.hpp                                                               */
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

#ifndef FastDisplayHppIncluded
#define FastDisplayHppIncluded

#include <Fast/Types.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/VideoMode.hpp>

namespace Fast
{
	class Monitor;

	class FastApi Display
	{
	private:
		Array<Monitor>		mMonitorArray;
		Int					mMainMonitorID;
		CXDisplay			*mXDisplay;
		CXRRScreenResources	*mXRRScreenResources;
		Int					mXRREventBase;
		// Hide these functions. No copying displays!
		Display(const Display &that) { }
		Display& operator=(const Display &that) { return *this; }
	public:
		// (Con/De)structors
		Display();
		~Display();
		// Getters
		Int						GetMonitorCount() const;
		Monitor*				GetMonitor(Int index);
		const Monitor&			GetMonitor(Int index) const;
		CXDisplay*				GetXDisplay();
		CXRRScreenResources*	GetXRRScreenResources();
		Int						GetXRREventBase() const;
		Monitor*				GetMainMonitor();
		const Monitor&			GetMainMonitor() const;
		Monitor*				GetActiveMonitor();
		const Monitor&			GetActiveMonitor() const;
		// Misc
		void	RefreshMonitors();
	};
}

#endif // FastDisplayHppIncluded
