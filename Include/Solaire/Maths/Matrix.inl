#ifndef SOLAIRE_MATRIX_INL
#define SOLAIRE_MATRIX_INL

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
	\file Matrix.inl
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 5th September 2015
	Last Modified	: 9th January 2016
*/

namespace Solaire {

    // Matrix / Matrix

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height>& operator+=(Matrix<Scalar, Width, Height>& aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(reinterpret_cast<VectorType&>(aFirst) += reinterpret_cast<const VectorType&>(aSecond));
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height>& operator-=(Matrix<Scalar, Width, Height>& aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(reinterpret_cast<VectorType&>(aFirst) -= reinterpret_cast<const VectorType&>(aSecond));
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height, class ENABLe = typename std::enable_if<Width == Height>::type>
    Matrix<Scalar, Width, Height>& operator*=(Matrix<Scalar, Width, Height>& aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        return aFirst = aFirst * aSecond;;
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator+(const Matrix<Scalar, Width, Height>& aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        return Matrix<Scalar, Width, Height>(aFirst) += aSecond;
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator-(const Matrix<Scalar, Width, Height>& aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        return Matrix<Scalar, Width, Height>(aFirst) -= aSecond;
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height, const uint32_t MinSize = Width < Height ? Width : Height>
    Matrix<Scalar, MinSize, MinSize> operator*(const Matrix<Scalar, Width, Height>& aFirst, const Matrix<Scalar, Height, Width>& aSecond) {
        Matrix<Scalar, MinSize, MinSize> tmp;

        for(uint32_t i = 0; i < MinSize; ++i){
            const Vector<Scalar, Width>& srcRow = *reinterpret_cast<const Vector<Scalar, Width>*>(aFirst.Ptr() + Width * i);
            Scalar* const dstRow = tmp.Ptr() + Width * i;
            for(uint32_t j = 0; j < MinSize; ++j){
                dstRow[j] = srcRow.DotProduct(aSecond.GetColumn(j));
            }
        }

        return tmp;
    }

    // Matrix / Scalar

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height>& operator+=(Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(reinterpret_cast<VectorType&>(aFirst) += aSecond);
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height>& operator-=(Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(reinterpret_cast<VectorType&>(aFirst) -= aSecond);
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height>& operator*=(Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(reinterpret_cast<VectorType&>(aFirst) *= aSecond);
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height>& operator/=(Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(reinterpret_cast<VectorType&>(aFirst) /= aSecond);
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator+(const Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        return Matrix<Scalar, Width, Height>(aFirst) += aSecond;
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator-(const Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        return Matrix<Scalar, Width, Height>(aFirst) -= aSecond;
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator*(const Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        return Matrix<Scalar, Width, Height>(aFirst) *= aSecond;
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator/(const Matrix<Scalar, Width, Height>& aFirst, const Scalar aSecond) {
        return Matrix<Scalar, Width, Height>(aFirst) /= aSecond;
    }

    // Scalar / Matrix

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator+(const Scalar aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(aFirst + reinterpret_cast<const VectorType&>(aSecond));
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator-(const Scalar aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(aFirst - reinterpret_cast<const VectorType&>(aSecond));
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator*(const Scalar aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(aFirst * reinterpret_cast<const VectorType&>(aSecond));
    }

    template<class Scalar, const uint32_t Width, const uint32_t Height>
    Matrix<Scalar, Width, Height> operator/(const Scalar aFirst, const Matrix<Scalar, Width, Height>& aSecond) {
        typedef Matrix<Scalar, Width, Height> MatrixType;
        typedef Vector<Scalar, Width * Height> VectorType;
        return reinterpret_cast<MatrixType&>(aFirst / reinterpret_cast<const VectorType&>(aSecond));
    }

    // Matrix / Vector
    //! \todo Implement matrix / vector maths

    // Vector / Matrix
    //! \todo Implement vector / matrix maths
}

#endif
