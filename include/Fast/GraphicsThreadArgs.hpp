/******************************************************************************/
/*                                                                            */
/*  GraphicsThreadArgs.hpp                                                    */
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

#ifndef FastGraphicsThreadArgsHppIncluded
#define FastGraphicsThreadArgsHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/RenderItem.hpp>

namespace Fast
{
	class GraphicsContext;
	class Window;
	class GraphicsContextInterface;
	class GraphicsIOCommand;
	class Mutex;
	class Conditional;

	class FastApi GraphicsThreadArgs
	{
	public:
		GraphicsContext				*mContext;
		Window						*mWindow;
		GraphicsContextInterface	*mInterface;
		Int							*mMultisampleCount;
		Bool						*mShouldRender;
		Bool						*mIsCommandWaiting;
		Bool						*mIsCommandReady;
		Array<Int>					*mDepthChangeIndices;
		Array<RenderItem>			*mRenderItems;
		Mutex						*mRenderMutex;
		Mutex						*mCommandIssueMutex;
		Mutex						*mCommandIssueFinishMutex;
		Conditional					*mCommandIssueFinishConditional;
		GraphicsIOCommand			*mGraphicsIOCommand;
		ErrorType					*mGLError;
		// (Con/De)structors
		GraphicsThreadArgs(GraphicsContext *graphicsContext, Window *window,
			Int *multisampleCount,
			GraphicsContextInterface *graphicsContextInterface,
			Bool *shouldRender, Bool *isCommandWaiting, Bool *isCommandReady,
			Array<Int> *depthChangeIndices, Array<RenderItem> *renderItems,
			Mutex *renderMutex, Mutex *commandIssueMutex,
			Mutex *commandIssueFinishMutex,
			Conditional *commandIssueFinishConditional,
			GraphicsIOCommand *graphicsIOCommand, ErrorType *glError);
	};
}

#endif // FastGraphicsThreadArgsHppIncluded