/******************************************************************************/
/*                                                                            */
/*  AssetImplementer.hpp                                                      */
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

#ifndef FastAssetImplementerHppIncluded
#define FastAssetImplementerHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetImplementerBase.hpp>
#include <Fast/ErrorType.hpp>

namespace Fast
{
	class AssetCollectionBase;
	class AssetData;

	template <typename T, typename U>
	class FastApi AssetImplementer :
		public AssetImplementerBase
	{
	protected:
		T	*mCollection;
		Int	mID;
	public:
		AssetImplementer() {
			mCollection = NULL;
			mID = -1;
		}

		ErrorType Bind(T *collection, Int id) {
			if (!collection || 0 > id) {
				if (mCollection && -1 < mID)
					mCollection->RemoveReference(this, mID);
				mID = id;
				mCollection = NULL;
			} else {
				if (mCollection == collection && mID != id && -1 < mID) {
					mCollection->RemoveReference(this, mID);
				} else {
					if (mCollection && -1 < mID)
						mCollection->RemoveReference(this, mID);
					mCollection = collection;
				}
				mID = id;
				mCollection->AddReference(this, mID);
			}
			return kErrorNone;
		}

		Int GetID() const {
			return mID;
		}

		T* GetCollection() {
			return mCollection;
		}

		const T& GetCollection() const {
			return *mCollection;
		}

		const U& GetResource() const {
			return GetCollection().GetResource(mID);
		}

		virtual void		Unbind()		= 0;
	};
}

#endif // FastAssetImplementerHppIncluded
