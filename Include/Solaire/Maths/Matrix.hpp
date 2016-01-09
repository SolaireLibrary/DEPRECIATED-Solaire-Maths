#ifndef SOLAIRE_MATRIX_HPP
#define SOLAIRE_MATRIX_HPP

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : solairelibrary@mail.com
// GitHub repository : https://github.com/SolaireLibrary/SolaireCPP

/*!
	\file Matrix.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\version 1.0.0
	\date
	Created			: 23rd September 2015
	Last Modified	: 9th January 2016
*/

#include "Vector.hpp"

namespace Solaire {

    //! \todo Implement Translation / Rotation / Scale helpers

	template<class T, const uint32_t WIDTH, const uint32_t HEIGHT>
	class Matrix{
	public:
		typedef T Scalar;                               //!< The scalar element type.
		enum : uint32_t {
		    Width = WIDTH,                              //!< The width of this Matrix.
		    Height = HEIGHT,                            //!< The height of this Matrix.
		    Min = Width < Height ? Width : Height,      //!< The smaller of Width or Height.
		    Max = Width > Height ? Width : Height       //!< The larger of Width or Height.
		};
		typedef Vector<Scalar, Width> Row;              //!< A Vector that can represent a row of this Matrix.
		typedef Vector<Scalar, Height> Column;          //!< A Vector that can represent a column of this Matrix.
	private:
		Scalar mData[Width * Height];                   //!< Contains the elements of this Matrix in row major order.
	public:
	    Matrix() throw() {
	        enum : uint32_t{Size = Width * Height};
            for(uint32_t i = 0; i < Width; ++i) {
                for(uint32_t j = 0; j < Height; ++j) {
                    mData[i * Width + j] = static_cast<Scalar>(i == j ? 1 : 0);
                }
			}
		}

	    Matrix(const Scalar aScalar) throw() {
	        enum : uint32_t{Size = Width * Height};
            for(uint32_t i = 0; i < Width; ++i) {
                for(uint32_t j = 0; j < Height; ++j) {
                    mData[i * Width + j] = static_cast<Scalar>(i == j ? aScalar : 0);
                }
			}
		}

        Matrix(const std::initializer_list<Scalar> aElements) throw() {
	        enum : uint32_t{Size = Width * Height};
	        auto j = aElements.begin();
	        const uint32_t size = aElements.size();
	        const uint32_t min = Size <= size ? Size : size;
	        for(uint32_t i = 0; i < min; ++i){
                mData[i] = *j;
                ++j;
	        }

            for(uint32_t i = min; i < Size; ++i){
                mData[i] = static_cast<Scalar>(0);
	        }
	    }

	    // C++ Operators

		template<class Scalar2>
	    explicit operator Matrix<Scalar2, Width, Height>() const throw() {
	        enum : uint32_t{Size = Width * Height};
	        Matrix<Scalar2, Width, Height> tmp;
	        const Scalar* const ptr = tmp.Ptr();
	        for(uint32_t i = 0; i < Size; ++i){
                ptr[i] = static_cast<Scalar2>(mData[i]);
	        }
	        return tmp;
	    }

        template<const uint32_t W = Width, const uint32_t H = Height, class ENABLE = typename std::enable_if<W != H>::type>
	    explicit operator Matrix<Scalar, Height, Width>() const throw() {
	       return Transpose();
	    }

		const Scalar* operator[](const uint32_t aIndex) const throw() {
			return mData + (aIndex * Width);
		}

		Scalar* operator[](const uint32_t aIndex) throw() {
			return mData + (aIndex * Width);
		}

		bool operator==(const Matrix<Scalar, Width, Height>& aOther) const throw() {
			return std::memcmp(mData, aOther.mData, sizeof(Scalar) * Width * Height) == 0;
		}

		bool operator!=(const Matrix<Scalar, Width, Height>& aOther) const throw() {
			return std::memcmp(mData, aOther.mData, sizeof(Scalar) * Width * Height) != 0;
		}

		// Misc

		const Scalar* Ptr() const throw() {
			return mData;
		}

		Scalar* Ptr() throw() {
			return mData;
		}

		Row GetRow(const uint32_t aIndex) const throw() {
		    return *reinterpret_cast<const Row*>(mData + (aIndex * Width));
		}

		Column GetColumn(const uint32_t aIndex) const throw() {
		    Column tmp;
			for(uint32_t i = 0; i < Height; ++i) {
				tmp[i] = mData[i * Width + aIndex];
			}
			return tmp;
		}

		void SetRow(const uint32_t aIndex, const Row aRow) throw() {
			std::memcpy(mData + Width * aIndex, aRow.Ptr(), sizeof(Scalar) * Width);
		}

        /*!
            \brief Set a Column of this Matrix.
            \brief aIndex The index of the Column to set.
            \brief aColumn The value to set the column to.
        */
		void SetColumn(const uint32_t aIndex, const Column aColumn) throw() {
			for(uint32_t i = 0; i < Height; ++i) {
				mData[i * Width + aIndex] = aColumn[i];
			}
		}

		Matrix<Scalar, Height, Width> Inverse() const throw() {
			//! \todo Implement matrix inversion
			return Matrix<Scalar, Height, Width>();
		}

        /*!
            \brief Rotate this Matrix by 90 degrees.
        */
		Matrix<Scalar, Height, Width> Transpose() const throw() {
			Matrix<Scalar, Height, Width> tmp;
			for(uint32_t i = 0; i < Width; ++i) {
				tmp.SetColumn(i, GetRow(i));
			}
			return tmp;
		}
	};

    // Matrix / Vector
    //! \todo Implement matrix / vector maths

    // Vector / Matrix
    //! \todo Implement vector / matrix maths

    // Typedefs

	template<class T>
	using Matrix2 = Matrix<T, 2, 2>;            //!< A 2x2 Matrix.

	template<class T>
	using Matrix3 = Matrix<T, 3, 3>;            //!< A 3x3 Matrix.

	template<class T>
	using Matrix4 = Matrix<T, 4, 4>;            //!< A 4x4 Matrix.

	typedef Matrix2<uint8_t>	Matrix2U8;      //!< A 2x2 Matrix using unsigned 8 bit scalars.
	typedef Matrix2<int8_t>		Matrix2I8;      //!< A 2x2 Matrix using signed 8 bit scalars.
	typedef Matrix2<uint16_t>	Matrix2U16;     //!< A 2x2 Matrix using unsigned 16 bit scalars.
	typedef Matrix2<int16_t>	Matrix2I16;     //!< A 2x2 Matrix using signed 16 bit scalars.
	typedef Matrix2<uint32_t>	Matrix2U32;     //!< A 2x2 Matrix using unsigned 32 bit scalars.
	typedef Matrix2<int32_t>	Matrix2I32;     //!< A 2x2 Matrix using signed 32 bit scalars.
	typedef Matrix2<uint64_t>	Matrix2U64;     //!< A 2x2 Matrix using unsigned 64 bit scalars.
	typedef Matrix2<int64_t>	Matrix2I64;     //!< A 2x2 Matrix using signed 64 bit scalars.
	typedef Matrix2<float>		Matrix2F;       //!< A 2x2 Matrix using single precision scalars.
	typedef Matrix2<double>		Matrix2D;       //!< A 2x2 Matrix using double precision scalars.

	typedef Matrix3<uint8_t>	Matrix3U8;      //!< A 3x3 Matrix using unsigned 8 bit scalars.
	typedef Matrix3<int8_t>		Matrix3I8;      //!< A 3x3 Matrix using signed 8 bit scalars.
	typedef Matrix3<uint16_t>	Matrix3U16;     //!< A 3x3 Matrix using unsigned 16 bit scalars.
	typedef Matrix3<int16_t>	Matrix3I16;     //!< A 3x3 Matrix using signed 16 bit scalars.
	typedef Matrix3<uint32_t>	Matrix3U32;     //!< A 3x3 Matrix using unsigned 32 bit scalars.
	typedef Matrix3<int32_t>	Matrix3I32;     //!< A 3x3 Matrix using signed 32 bit scalars.
	typedef Matrix3<uint64_t>	Matrix3U64;     //!< A 3x3 Matrix using unsigned 64 bit scalars.
	typedef Matrix3<int64_t>	Matrix3I64;     //!< A 3x3 Matrix using signed 64 bit scalars.
	typedef Matrix3<float>		Matrix3F;       //!< A 3x3 Matrix using single precision scalars.
	typedef Matrix3<double>		Matrix3D;       //!< A 3x3 Matrix using double precision scalars.

	typedef Matrix4<uint8_t>	Matrix4U8;      //!< A 4x4 Matrix using unsigned 8 bit scalars.
	typedef Matrix4<int8_t>		Matrix4I8;      //!< A 4x4 Matrix using signed 8 bit scalars.
	typedef Matrix4<uint16_t>	Matrix4U16;     //!< A 4x4 Matrix using unsigned 16 bit scalars.
	typedef Matrix4<int16_t>	Matrix4I16;     //!< A 4x4 Matrix using signed 16 bit scalars.
	typedef Matrix4<uint32_t>	Matrix4U32;     //!< A 4x4 Matrix using unsigned 32 bit scalars.
	typedef Matrix4<int32_t>	Matrix4I32;     //!< A 4x4 Matrix using signed 32 bit scalars.
	typedef Matrix4<uint64_t>	Matrix4U64;     //!< A 4x4 Matrix using unsigned 64 bit scalars.
	typedef Matrix4<int64_t>	Matrix4I64;     //!< A 4x4 Matrix using signed 64 bit scalars.
	typedef Matrix4<float>		Matrix4F;       //!< A 4x4 Matrix using single precision scalars.
	typedef Matrix4<double>		Matrix4D;       //!< A 4x4 Matrix using double precision scalars.
}

#include "Matrix.inl"

#endif
