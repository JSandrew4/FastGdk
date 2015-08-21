/******************************************************************************/
/*                                                                            */
/*  AssetCollectionVerifiable.hpp                                             */
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

#ifndef FastAssetCollectionVerifiableHppIncluded
#define FastAssetCollectionVerifiableHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollectionBase.hpp>
#include <Fast/AssetCollection.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/Checksum.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class AssetData;
	class StreamReader;

	template <typename T> class FastApi AssetCollectionVerifiable :
		public AssetCollection<typename T>
	{
	public:

		Int GetIDByName(const String &name) {
			if (name.IsEmpty())
				return -1;
			for (Int i = 0; i < mResources.GetElementCount(); i++) {
				if (mResources[i].IsActive() && mResources[i].GetName() == name)
				{
					return i;
				}
			}
			return -1;
		}

		Int GetIDByChecksum(const Checksum &checksum) {
			if (checksum.IsEmpty())
				return -1;
			for (Int i = 0; i < mResources.GetElementCount(); i++) {
				if (mResources[i].IsActive() &&
					*mResources[i].GetChecksum() == checksum)
				{
					return i;
				}
			}
			return -1;
		}

		virtual ErrorType	LoadResource(const AssetData &assetData)	= 0;
		virtual void		UnloadResource(Int id)						= 0;
	};
}

#endif // FastAssetCollectionVerifiableHppIncluded
