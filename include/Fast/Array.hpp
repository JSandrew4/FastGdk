/******************************************************************************/
/*                                                                            */
/*  Array.hpp                                                                 */
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

#ifndef FastArrayHppIncluded
#define FastArrayHppIncluded

#include <Fast/Types.hpp>
#include <Fast/Exception.hpp>
#include <Fast/ExceptionType.hpp>
#include <Fast/String.hpp>

#include <cstdlib>
#include <cstring>
#include <new>

namespace Fast
{
	template <typename T> class FastApi Array
	{
	private:
		T	*mElements;
		Int	mElementCountCapacity;
		Int	mElementCount;
	public:
		// (Con/De)structors
		
		Array() {
			mElements = NULL;
			mElementCount = 0;
			mElementCountCapacity = 0;
		}

		Array(const Array &that) {
			this->mElements = NULL;
			this->mElementCount = 0;
			this->mElementCountCapacity = 0;
			Assign(that);
		}

		Array(Int size, const T &copyConstructor = T()) {
			this->mElements = NULL;
			this->mElementCount = 0;
			this->mElementCountCapacity = 0;
			SetElementCount(size, copyConstructor);
		}

		Array(T *elements, Int elementCount) {
			this->mElements = NULL;
			this->mElementCount = 0;
			this->mElementCountCapacity = 0;
			for (Int i = 0; i < elementCount; i++)
				this->Append(elements[i]);
		}
		
		~Array() {
			free(mElements);
		}

		// Size functions
		
		void SetElementCountCapacity(Int capacity, const T &copyConstructor = T()) {
			if (capacity <= mElementCountCapacity) {
				SetElementCount(capacity, copyConstructor);
				return;
			} else if (mElementCountCapacity == 0) {
				mElements = (T*)calloc((size_t)capacity, sizeof(T));
			} else {
				T *tempData = (T*)calloc((size_t)capacity, sizeof(T));
				for (Int i = 0; i < mElementCountCapacity; i++)
					new (&tempData[i]) T(mElements[i]);
				free(mElements);
				mElements = tempData;
			}
			mElementCountCapacity = capacity;
		}

		void SetElementCount(Int size, const T &copyConstructor = T()) {
			if (size == mElementCount)
				return;
			if (size > mElementCountCapacity) {
				Int newCapacity = (mElementCountCapacity < 2) ?
					2 : mElementCountCapacity;
				while (size > newCapacity)
					newCapacity *= 2;
				SetElementCountCapacity(newCapacity, copyConstructor);
			}
			if (size > mElementCount)
				for (Int i = mElementCount; i < size; i++)
					new (&mElements[i]) T(copyConstructor);
			if (size < mElementCount) {
				for (Int i = size; i < mElementCount; i++) {
					mElements[i].~T();
					memset(&mElements[i], 0, sizeof(T));
				}
			}
			mElementCount = size;
		}

		Int GetElementCountCapacity() const {
			return mElementCountCapacity;
		}

		Int GetElementCount() const {
			return mElementCount;
		}

		Bool IsEmpty() const {
			return (mElementCount == 0);
		}
		
		// Get functions
		
		const T& GetElement(Int index) const {
			if (index >= mElementCount || 0 > index)
				Exception::Throw(kExceptionOutOfRange,
					"[Array<T>::At(" + String::FromInt(index) + ")]");
			return mElements[index];
		}
		
		T& GetElement(Int index) {
			if (index >= mElementCount || 0 > index)
				Exception::Throw(kExceptionOutOfRange,
					"[Array<T>::At(" + String::FromInt(index) + ")]");
			return mElements[index];
		}

		T* GetData() {
			return mElements;
		}

		const T* GetData() const {
			return mElements;
		}
		
		// Modify functions
		
		void Assign(const Array &that) {
			this->Clear();
			for (Int i = 0; i < that.GetElementCount(); i++)
				this->Append(that.mElements[i]);
		}
		
		void Append(const T &t, Int count = 1) {
			if (count <= 0)
				return;
			SetElementCount(mElementCount + count, t);
		}

		void Insert(const T &t, Int index, Int count = 1) {
			if (index > mElementCount)
				Exception::Throw(kExceptionOutOfRange,
					String("[Array<T>::Insert(T, %d, %d)]",
						index, count));
			if (count <= 0)
				return;
			if (index == mElementCount) {
				Append(t, count);
				return;
			}
			SetElementCount(mElementCount+count, t);
			Int i;
			for (i = (mElementCount-1); i >= (index+count); i--)
				mElements[i] = mElements[i-count];
			for (i = 0; i < count; i++)
				mElements[index+i] = t;
		}

		void Replace(const T &t, Int index) {
			if (index > mElementCount)
				Exception::Throw(kExceptionOutOfRange,
					String("[Array<T>::Replace(T, %d)]", index));
			mElements[index] = t;
		}

		void Append(const Array<T> &tArray) {
			for (Int i = 0; i < tArray.GetElementCount(); i++)
				Append(tArray[i]);
		}

		void Insert(const Array<T> &tArray, Int index) {
			for (Int i = 0; i < tArray.GetElementCount(); i++)
				Insert(tArray[i], index + i);
		}

		void Replace(const Array<T> &tArray, Int index) {
			for (Int i = 0; i < tArray.GetElementCount(); i++)
				Replace(tArray[i], index + i);
		}

		void Erase(Int index, Int elementCount = 1) {
			if ((index+elementCount) > mElementCount)
				Exception::Throw(kExceptionOutOfRange,
					String("[Array<T>::Erase(%d, %d)]",
						index, elementCount));
			if (elementCount <= 0)
				return;
			for (Int i = index; i < (index+elementCount); i++) {
				mElements[i].~T();
				memset(&mElements[i], 0, sizeof(T));
			}
			for (Int i = index; (i+elementCount) < mElementCount; i++)
				new (&mElements[i]) T(mElements[i+elementCount]);
			// SetElementCount down. We can't just call SetElementCount() in case our
			//	object doesn't have a default constructor)
			Int size = mElementCount - elementCount;
			for (Int i = mElementCount - elementCount; i < mElementCount; i++) {
				mElements[i].~T();
				memset(&mElements[i], 0, sizeof(T));
			}
			mElementCount = size;
		}

		void Clear() {
			// SetElementCount down to zero. We can't just call SetElementCount() in
			//	case our object doesn't have a default constructor
			for (Int i = 0; i < mElementCount; i++) {
				mElements[i].~T();
				memset(&mElements[i], 0, sizeof(T));
			}
			mElementCount = 0;
		}
		
		// Assignment operator
		
		Array& operator=(const Array &that) {
			this->Assign(that);
			return *this;
		}

		// Append operator

		Array& operator+=(const T &that) {
			this->Append(that);
			return *this;
		}

		// Access operators

		T& operator[](const Int index) {
			if (index >= mElementCount || 0 > index)
				Exception::Throw(kExceptionOutOfRange,
					String("[Array<T>::operator[](%d)]", index));
			return mElements[index];
		}

		const T & operator[](const Int index) const {
			if (index >= mElementCount || 0 > index)
				Exception::Throw(kExceptionOutOfRange,
					String("[Array<T>::operator[](%d)]", index));
			return mElements[index];
		}
	};

	template class FastApi Array<Byte>;
	template class FastApi Array<UByte>;
	template class FastApi Array<Short>;
	template class FastApi Array<UShort>;
	template class FastApi Array<Int>;
	template class FastApi Array<UInt>;
	template class FastApi Array<Long>;
	template class FastApi Array<ULong>;
	template class FastApi Array<Float>;
	template class FastApi Array<Double>;
	template class FastApi Array<String>;
}

#endif // FastArrayHppIncluded
