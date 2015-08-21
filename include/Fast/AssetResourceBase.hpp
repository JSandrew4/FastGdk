/******************************************************************************/
/*                                                                            */
/*  AssetResourceBase.hpp                                                     */
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

#ifndef FastAssetResourceBaseHppIncluded
#define FastAssetResourceBaseHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Array.hpp>
#include <Fast/String.hpp>
#include <Fast/Checksum.hpp>

namespace Fast
{
	class AssetImplementerBase;

	template <typename T> class FastApi AssetResourceBase
	{
	protected:
		String							mName;
		Array<AssetImplementerBase*>	mAssetImplementerArray;
		Bool							mIsActive;
		Bool							mIsRetained;
		T								mProperties;
	public:

		// (Con/De)structors

		AssetResourceBase() {
			mIsActive = false;
			mIsRetained = false;
		}

		// Getters

		const String& GetName() const {
			return mName;
		}

		Array<AssetImplementerBase*>* GetAssetImplementerArray() {
			return &mAssetImplementerArray;
		}

		const Array<AssetImplementerBase*>& GetAssetImplementerArray() const {
			return mAssetImplementerArray;
		}

		Bool IsActive() const {
			return mIsActive;
		}

		Bool IsRetained() const {
			return mIsRetained;
		}

		const T& GetProperties() const {
			return mProperties;
		}

		T* GetProperties() {
			return &mProperties;
		}

		// Setters

		void SetName(const String &name) {
			mName = name;
		}

		void SetActive(Bool isActive) {
			mIsActive = isActive;
		}

		void SetRetained(Bool isRetained) {
			mIsRetained = isRetained;
		}

		void SetProperties(const T &properties) {
			mProperties = properties;
		}
	};
}

#endif // FastAssetResourceBaseHppIncluded
