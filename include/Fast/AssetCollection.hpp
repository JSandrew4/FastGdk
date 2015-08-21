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

#ifndef FastAssetCollectionHppIncluded
#define FastAssetCollectionHppIncluded

#include <Fast/Types.hpp>
#include <Fast/AssetCollectionBase.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/Checksum.hpp>
#include <Fast/AssetImplementer.hpp>
#include <Fast/ErrorType.hpp>

// TODO: Remove
#include <stdio.h>

namespace Fast
{
	class AssetData;
	class StreamReader;

	template <typename T> class FastApi AssetCollection :
		public AssetCollectionBase
	{
	protected:

		Array<T>	mResources;

		void UnloadReferences(Int id) {
			if (0 >= mResources[id].GetAssetImplementerArray(
				)->GetElementCount())
			{
				mResources[id].SetActive(false);
			}
			while (mResources[id].IsActive()) {
				printf("mResources[%d]{%p}.GetAssetImplementerArray()->GetElement{%p}Count() = %d\n",
					id, &mResources[id], mResources[id].GetAssetImplementerArray()->GetElement(0),
					mResources[id].GetAssetImplementerArray()->GetElementCount());
				if (mResources[id].GetAssetImplementerArray()->GetElement(0))
					mResources[id].GetAssetImplementerArray(
						)->GetElement(0)->Unbind();
			}
		}

	public:

		AssetCollection() { }

		Int AddResource(const T &resource, AssetImplementerBase *asset) {
			// Find an available resource slot
			for (Int i = 0; i < mResources.GetElementCount(); i++) {
				if (!mResources[i].IsActive()) {
					mResources[i] = resource;
					mResources[i].SetActive(true);
					mResources[i].SetRetained(false);
					AddReference(asset, i);
					return i;
				}
			}
			// If no available slot, append a new one
			mResources.Append(resource);
			Int id = mResources.GetElementCount() - 1;
			mResources[id].SetActive(true);
			mResources[id].SetRetained(false);
			AddReference(asset, id);
			return id;
		}

		void AddReference(AssetImplementerBase *asset, Int id) {
			mResources[id].GetAssetImplementerArray()->Append(asset);
			printf("%s being added. %d refs now\n",
				mResources[id].GetName().GetCString(), GetReferenceCount(id));
		}

		void RemoveReference(AssetImplementerBase *asset, Int id) {
			if (mResources.IsEmpty())
				return;
			if (mResources[id].GetAssetImplementerArray()->IsEmpty())
				return;
			for (Int i = 0;
				i < mResources[id].GetAssetImplementerArray(
					)->GetElementCount(); i++)
			{
				if (mResources[id].GetAssetImplementerArray()->GetElement(i) ==
					asset)
				{
					mResources[id].GetAssetImplementerArray()->Erase(i);
					printf("%s ref removed. %d refs now\n",
						mResources[id].GetName().GetCString(), GetReferenceCount(id));
					if (GetReferenceCount(id) <= 0 &&
						!mResources[id].IsRetained())
					{
						printf("Resource %s unloaded\n", mResources[id].GetName());
						UnloadResource(id);
					}
					return;
				}
			}
		}

		T* GetResource(Int id) {
			return &mResources[id];
		}

		const T& GetResource(Int id) const {
			return mResources[id];
		}

		Int GetReferenceCount(Int id) {
			return mResources[id].GetAssetImplementerArray()->GetElementCount();
		}

		void UnloadAllResources() {
			for (Int i = 0; i < mResources.GetElementCount(); i++)
				UnloadResource(i);
		}

		void SetResourceRetained(Int id, Bool isRetained) {
			mResources[id].SetRetained(isRetained);
			if (!isRetained && 0 == GetReferenceCount(id))
				UnloadResource(id);
		}

		Bool IsResourceRetained(Int id) {
			return mResources[id].IsRetained();
		}

		virtual void	UnloadResource(Int id)	= 0;
	};
}

#endif // FastAssetCollectionHppIncluded
