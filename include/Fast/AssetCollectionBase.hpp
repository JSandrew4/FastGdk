/******************************************************************************/
/*                                                                            */
/*  AssetCollection.hpp                                                       */
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

#ifndef FastAssetCollectionBaseHppIncluded
#define FastAssetCollectionBaseHppIncluded

#include <Fast/Types.hpp>

namespace Fast
{
	class AssetImplementerBase;
	class String;
	class Checksum;

	class FastApi AssetCollectionBase
	{
	public:
		virtual void	AddReference(AssetImplementerBase *asset, Int id)	= 0;
		virtual void	RemoveReference(AssetImplementerBase *asset,
							Int id)											= 0;
	};
}

#endif // FastAssetCollectionBaseHppIncluded
