/******************************************************************************/
/*                                                                            */
/*  SimpleApplication.hpp                                                     */
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

#ifndef FastSimpleApplicationHppIncluded
#define FastSimpleApplicationHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Application.hpp>
#include <Fast/AudioContext.hpp>
#include <Fast/Display.hpp>
#include <Fast/SimpleWindow.hpp>
#include <Fast/Timer.hpp>

namespace Fast
{
	class FastApi SimpleApplication : public Application
	{
	private:
		Bool				mIsRunning;
		Display				mDisplay;
		SimpleWindow		mWindow;
		Timer				mTimer;
		AudioContext		mAudioContext;
	public:
		// (Con/De)structors
		SimpleApplication(Int argc, Char **argv);
		~SimpleApplication();
		// Event functions
		virtual void	Update();
		virtual void	Draw();
		virtual void	OnWindowExpose();
		virtual void	OnWindowClose();
		// Control functions
		void	Run();
		void	Quit();
		// Get functions
		Bool						IsRunning() const;
		Display*					GetDisplay();
		const Display&				GetDisplay() const;
		SimpleWindow*				GetWindow();
		const SimpleWindow&			GetWindow() const;
		Timer*						GetTimer();
		const Timer&				GetTimer() const;
		AudioContext*				GetAudioContext();
		const AudioContext&			GetAudioContext() const;
	};
}

#endif // FastSimpleApplicationHppIncluded
