/******************************************************************************/
/*                                                                            */
/*  SkeletonAnimation.hpp                                                     */
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

#ifndef FastSkeletonAnimationHppIncluded
#define FastSkeletonAnimationHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/SkeletonAnimationCollection.hpp>
#include <Fast/ErrorType.hpp>
#include <Fast/Array.hpp>

namespace Fast
{
	class String;
	class StreamReader;
	class SkeletonAnimationData;

	class FastApi SkeletonAnimation :
		public AssetImplementer<SkeletonAnimationCollection,
			SkeletonAnimationResource>
	{
	public:
		// (Con/De)structors
		SkeletonAnimation();
		SkeletonAnimation(const SkeletonAnimation &that);
		SkeletonAnimation(const String &fileName,
			SkeletonAnimationCollection *collection);
		SkeletonAnimation(const SkeletonAnimationData &data,
			SkeletonAnimationCollection *collection);
		SkeletonAnimation(StreamReader *streamReader,
			SkeletonAnimationCollection *collection);
		~SkeletonAnimation();
		// Allocators
		ErrorType	Bind(Int id);
		ErrorType	Load(const String &fileName,
						SkeletonAnimationCollection *collection);
		ErrorType	Load(const SkeletonAnimationData &data,
						SkeletonAnimationCollection *collection);
		ErrorType	Load(StreamReader *streamReader,
						SkeletonAnimationCollection *collection);
		void		Unbind();
		// Operators
		SkeletonAnimation&	operator= (const SkeletonAnimation &that);
		Bool				operator==(const SkeletonAnimation &that) const;
		Bool				operator!=(const SkeletonAnimation &that) const;
	};

	template class FastApi Array<SkeletonAnimation>;
}

#endif // FastSkeletonAnimationHppIncluded