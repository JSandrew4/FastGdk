/******************************************************************************/
/*                                                                            */
/*  AudioListener.hpp                                                         */
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

#ifndef FastAudioListenerHppIncluded
#define FastAudioListenerHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Vector2D.hpp>
#include <Fast/Vector3D.hpp>
#include <Fast/Color.hpp>
#include <Fast/VertexStruct.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class FastApi AudioListener
	{
	private:
		Vector3D	mPosition;
		Vector3D	mLookAt;
		Vector3D	mUp;
	public:
		// (Con/De)structors
		AudioListener();
		AudioListener(const AudioListener &that);
		~AudioListener();
		// Gets
		const Vector3D&	GetPosition() const;
		const Vector3D&	GetLookAt() const;
		const Vector3D&	GetUpVector() const;
		// Sets
		void			SetPosition(const Vector3D &position);
		void			SetLookAt(const Vector3D &lookAt);
		void			SetUpVector(const Vector3D &up);
		void			SetOrientation(const Vector3D &lookAt,
							const Vector3D &up);
		// Operators
		AudioListener&	operator= (const AudioListener &that);
		Bool			operator==(const AudioListener &that) const;
		Bool			operator!=(const AudioListener &that) const;
	};
}

#endif // FastAudioListenerHppIncluded