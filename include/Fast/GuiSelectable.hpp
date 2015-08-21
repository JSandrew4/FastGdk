/******************************************************************************/
/*                                                                            */
/*  GuiSelectable.hpp                                                         */
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

#ifndef FastGuiSelectableHppIncluded
#define FastGuiSelectableHppIncluded

#include <Fast/Types.hpp>
#include <Fast/GuiWidget.hpp>

namespace Fast
{
	class FastApi GuiSelectable : public GuiWidget
	{
	protected:
		Bool			mIsSelected;
		GuiSelectable	*mNext;
		GuiSelectable	*mPrevious;
	public:
		// (Con/De)structors
		GuiSelectable();
		~GuiSelectable();
		// Getters
		Bool					IsSelected() const;
		GuiSelectable*			GetNextSelectable();
		const GuiSelectable&	GetNextSelectable() const;
		GuiSelectable*			GetPreviousSelectable();
		const GuiSelectable&	GetPreviousSelectable() const;
		// Setters
		void	SetNextSelectable(GuiSelectable *next);
		void	SetPreviousSelectable(GuiSelectable *previous);
		// Events
		virtual void	OnKeyPress(const KeyEvent &event);
		virtual void	OnMouseButtonPress(const MouseButtonEvent &event);
		virtual void	OnSelect();
		virtual void	OnUnselect();
		// Misc
		virtual void	Draw() = 0;
	};
}

#endif // FastGuiSelectableHppIncluded
