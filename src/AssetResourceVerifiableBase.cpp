/******************************************************************************/
/*                                                                            */
/*  AssetResourceVerifiableBase.cpp                                           */
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

#include <Fast/AssetResourceVerifiableBase.hpp>

namespace Fast
{
	AssetResourceVerifiableBase::AssetResourceVerifiableBase() { }

	const Checksum& AssetResourceVerifiableBase::GetChecksum() const {
		return mChecksum;
	}

	Checksum* AssetResourceVerifiableBase::GetChecksum() {
		return &mChecksum;
	}

	void AssetResourceVerifiableBase::SetChecksum(const Checksum &checksum) {
		mChecksum = checksum;
	}
}