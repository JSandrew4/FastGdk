/******************************************************************************/
/*                                                                            */
/*  GuiPressable.hpp                                                          */
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

#ifndef FastGuiPressableHppIncluded
#define FastGuiPressableHppIncluded

#include <Fast/Types.hpp>
#include <Fast/GuiSelectable.hpp>

namespace Fast
{
	class FastApi GuiPressable : public GuiSelectable
	{
	protected:
		Bool	mIsPressed;
	public:
		// (Con/De)structors
		GuiPressable();
		// Getters
		Bool	IsPressed() const;
		// Events
		virtual void	OnKeyPress(const KeyEvent &event);
		virtual void	OnKeyRelease(const KeyEvent &event);
		virtual void	OnMouseButtonPress(const MouseButtonEvent &event);
		virtual void	OnMouseButtonRelease(const MouseButtonEvent &event);
		virtual void	OnHover();
		virtual void	OnUnhover();
		virtual void	OnPress();
		virtual void	OnUnpress();
	};
}

#endif // FastGuiPressableHppIncluded
