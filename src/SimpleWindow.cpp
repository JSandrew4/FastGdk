/******************************************************************************/
/*                                                                            */
/*  SimpleWindow.cpp                                                          */
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

#include <Fast/SimpleWindow.hpp>
#include <Fast/SimpleApplication.hpp>
#include <Fast/Display.hpp>
#include <Fast/Monitor.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SimpleWindow::SimpleWindow(SimpleApplication *app, Display *display) :
		Window(display),
		mApplication(*app)
	{ }

	void SimpleWindow::OnExpose() {
		mApplication.OnWindowExpose();
	}

	void SimpleWindow::OnDraw() {
		mApplication.Draw();
	}

	void SimpleWindow::OnClose() {
		mApplication.OnWindowClose();
	}
}
