/******************************************************************************/
/*                                                                            */
/*  GuiCheckBox.hpp                                                           */
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

#ifndef FastGuiCheckBoxHppIncluded
#define FastGuiCheckBoxHppIncluded

#include <Fast/Types.hpp>
#include <Fast/GuiCheckBoxState.hpp>
#include <Fast/GuiPressable.hpp>

namespace Fast
{
	class KeyEvent;
	class MouseButtonEvent;

	class FastApi GuiCheckBox : public GuiPressable
	{
	protected:
		GuiCheckBoxState	mState;
	public:
		// (Con/De)structors
		GuiCheckBox();
		~GuiCheckBox();
		// Getters
		GuiCheckBoxState	GetState() const;
		// Setters
		void				SetState(GuiCheckBoxState state);
		// Events
		virtual void	OnUnpress();
		virtual void	OnStateChange()	{ }
		// Overrides
		virtual void	OnMouseButtonPress(const MouseButtonEvent &event);
		virtual void	OnMouseButtonRelease(const MouseButtonEvent &event);
		virtual void	Draw();
	};
}

#endif // FastGuiCheckBoxHppIncluded
