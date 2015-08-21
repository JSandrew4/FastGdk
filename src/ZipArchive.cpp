/******************************************************************************/
/*                                                                            */
/*  ZipArchive.cpp                                                            */
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

#include <Fast/ZipArchive.hpp>

#include <zip.h>

#include "Undefs.hpp"

namespace Fast
{
	ZipArchive::ZipArchive() {
		mZipHandle = 0;
	}

	ZipArchive::ZipArchive(const String &fileName) {
		mZipHandle = 0;
		Open(fileName);
	}

	ZipArchive::~ZipArchive() {
		Close();
	}

	const String& ZipArchive::GetName() const {
		return mName;
	}

	Bool ZipArchive::IsOpen() {
		return mZipHandle ? true : false;
	}

	Czip* ZipArchive::GetZipHandle() {
		return mZipHandle;
	}

	void ZipArchive::Open(const String &fileName) {
		Int error = 0;
		mZipHandle = (zip*)zip_open(fileName.GetCString(), 0, &error);
	}

	void ZipArchive::Close() {
		zip_close((zip*)mZipHandle);
	}
}