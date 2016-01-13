#ifndef SOLAIRE_COMPRESSED_VECTOR_INL
#define SOLAIRE_COMPRESSED_VECTOR_INL

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
	\file CompressedVector.inl
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 13th January 2016
	Last Modified	: 13th January 2016
*/

namespace Solaire { namespace Test {

    #define SOLAIRE_COMPRESSED_VECTOR_TEMPLATE template<const uint8_t XBITS, const uint8_t YBITS, const uint8_t ZBITS, const uint8_t WBITS, const bool XSIGN = false, const bool YSIGN = false, const bool ZSIGN = false, const bool WSIGN = false>
    #define SOLAIRE_COMPRESSED_VECTOR CompressedVector<XBITS, YBITS, ZBITS, WBITS, XSIGN, YSIGN, ZSIGN, WSIGN>

    // Vector / Vector

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator+=(SOLAIRE_COMPRESSED_VECTOR& aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aFirst.X += aSecond.X;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aFirst.Y += aSecond.Y;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aFirst.Z += aSecond.Z;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aFirst.W += aSecond.W;
        return aFirst;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator-=(SOLAIRE_COMPRESSED_VECTOR& aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aFirst.X -= aSecond.X;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aFirst.Y -= aSecond.Y;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aFirst.Z -= aSecond.Z;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aFirst.W -= aSecond.W;
        return aFirst;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator*=(SOLAIRE_COMPRESSED_VECTOR& aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aFirst.X *= aSecond.X;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aFirst.Y *= aSecond.Y;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aFirst.Z *= aSecond.Z;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aFirst.W *= aSecond.W;
        return aFirst;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator/=(SOLAIRE_COMPRESSED_VECTOR& aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aFirst.X /= aSecond.X;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aFirst.Y /= aSecond.Y;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aFirst.Z /= aSecond.Z;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aFirst.W /= aSecond.W;
        return aFirst;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator+(const SOLAIRE_COMPRESSED_VECTOR aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aFirst.X + aSecond.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aFirst.Y + aSecond.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aFirst.Z + aSecond.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aFirst.W + aSecond.W : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator-(const SOLAIRE_COMPRESSED_VECTOR aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aFirst.X - aSecond.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aFirst.Y - aSecond.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aFirst.Z - aSecond.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aFirst.W - aSecond.W : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator*(const SOLAIRE_COMPRESSED_VECTOR aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aFirst.X * aSecond.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aFirst.Y * aSecond.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aFirst.Z * aSecond.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aFirst.W * aSecond.W : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator/(const SOLAIRE_COMPRESSED_VECTOR aFirst, const SOLAIRE_COMPRESSED_VECTOR aSecond) throw() {
        return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aFirst.X / aSecond.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aFirst.Y / aSecond.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aFirst.Z / aSecond.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aFirst.W / aSecond.W : 0
        );
    }

    // Vector / Scalar

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator+=(SOLAIRE_COMPRESSED_VECTOR& aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aVector.X += aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aVector.Y += aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aVector.Z += aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aVector.W += aScalar;
        return aVector;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator-=(SOLAIRE_COMPRESSED_VECTOR& aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aVector.X -= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aVector.Y -= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aVector.Z -= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aVector.W -= aScalar;
        return aVector;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator*=(SOLAIRE_COMPRESSED_VECTOR& aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aVector.X *= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aVector.Y *= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aVector.Z *= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aVector.W *= aScalar;
        return aVector;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR& operator/=(SOLAIRE_COMPRESSED_VECTOR& aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
        if(SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0) aVector.X /= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0) aVector.Y /= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0) aVector.Z /= aScalar;
        if(SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0) aVector.W /= aScalar;
        return aVector;
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator+(const SOLAIRE_COMPRESSED_VECTOR aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aVector.X + aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aVector.Y + aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aVector.Z + aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aVector.W + aScalar : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator-(const SOLAIRE_COMPRESSED_VECTOR aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aVector.X - aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aVector.Y - aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aVector.Z - aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aVector.W - aScalar : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator*(const SOLAIRE_COMPRESSED_VECTOR aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aVector.X * aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aVector.Y * aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aVector.Z * aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aVector.W * aScalar : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator/(const SOLAIRE_COMPRESSED_VECTOR aVector, const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aVector.X / aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aVector.Y / aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aVector.Z / aScalar : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aVector.W / aScalar : 0
        );
    }

    // Scalar / Vector

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator+(const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar, const SOLAIRE_COMPRESSED_VECTOR aVector) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aScalar + aVector.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aScalar + aVector.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aScalar + aVector.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aScalar + aVector.W : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator-(const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar, const SOLAIRE_COMPRESSED_VECTOR aVector) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aScalar - aVector.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aScalar - aVector.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aScalar - aVector.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aScalar - aVector.W : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator*(const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar, const SOLAIRE_COMPRESSED_VECTOR aVector) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aScalar * aVector.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aScalar * aVector.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aScalar * aVector.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aScalar * aVector.W : 0
        );
    }

    SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    SOLAIRE_COMPRESSED_VECTOR operator/(const typename SOLAIRE_COMPRESSED_VECTOR::Scalar aScalar, const SOLAIRE_COMPRESSED_VECTOR aVector) throw() {
         return SOLAIRE_COMPRESSED_VECTOR(
            SOLAIRE_COMPRESSED_VECTOR::XInfo::Bits != 0 ? aScalar / aVector.X : 0,
            SOLAIRE_COMPRESSED_VECTOR::YInfo::Bits != 0 ? aScalar / aVector.Y : 0,
            SOLAIRE_COMPRESSED_VECTOR::ZInfo::Bits != 0 ? aScalar / aVector.Z : 0,
            SOLAIRE_COMPRESSED_VECTOR::WInfo::Bits != 0 ? aScalar / aVector.W : 0
        );
    }

    #undef SOLAIRE_COMPRESSED_VECTOR_TEMPLATE
    #undef SOLAIRE_COMPRESSED_VECTOR
}}


#endif
