/******************************************************************************/
/*                                                                            */
/*  SimpleApplication.cpp                                                     */
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

#include <Fast/SimpleApplication.hpp>
#include <Fast/SimpleWindow.hpp>
#include <Fast/Timer.hpp>
#include <Fast/Display.hpp>
#include <Fast/Monitor.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/GraphicsContext.hpp>
#include <Fast/FontCollection.hpp>

#include "Undefs.hpp"

namespace Fast
{
	SimpleApplication::SimpleApplication(Int argc, Char **argv) :
		Application(argc, argv),
		mIsRunning(true),
		mDisplay(),
		mWindow(this, &mDisplay),
		mAudioContext(),
		mTimer()
	{ }

	SimpleApplication::~SimpleApplication() { }
	
	void SimpleApplication::Update() { }

	void SimpleApplication::Draw() {
		mWindow.GetGraphicsContext()->StartRender();
		//glClear(GL_COLOR_BUFFER_BIT);
		mWindow.GetGraphicsContext()->FinishRender();
	}

	void SimpleApplication::OnWindowExpose() { }

	void SimpleApplication::OnWindowClose() {
		Quit();
	}

	void SimpleApplication::Run() {
		mTimer.Start();
		while(mIsRunning) {
			mWindow.Update();
			mAudioContext.Update(mTimer.GetElapsedMilliseconds());
			Update();
			mWindow.Draw();
			mTimer.Update();
		}
	}

	void SimpleApplication::Quit() {
		mIsRunning = false;
	}

	Bool SimpleApplication::IsRunning() const {
		return mIsRunning;
	}

	Display* SimpleApplication::GetDisplay() {
		return &mDisplay;
	}

	const Display& SimpleApplication::GetDisplay() const {
		return mDisplay;
	}

	SimpleWindow* SimpleApplication::GetWindow() {
		return &mWindow;
	}

	const SimpleWindow& SimpleApplication::GetWindow() const {
		return mWindow;
	}

	Timer* SimpleApplication::GetTimer() {
		return &mTimer;
	}

	const Timer& SimpleApplication::GetTimer() const {
		return mTimer;
	}

	AudioContext* SimpleApplication::GetAudioContext() {
		return &mAudioContext;
	}

	const AudioContext& SimpleApplication::GetAudioContext() const {
		return mAudioContext;
	}
}
