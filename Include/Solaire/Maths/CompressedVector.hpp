#ifndef SOLAIRE_COMPRESSED_VECTOR_HPP
#define SOLAIRE_COMPRESSED_VECTOR_HPP

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
	\file CompressedVector.hpp
	\brief Contains code for an N dimentional vector class with typedefs for commonly used vector types.
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 13th January 2016
	Last Modified	: 13th January 2016
*/

#include <cmath>
#include <cstdint>
#include <limits>
#include "Solaire/Core/BinaryBlock.hpp"
#include "Solaire/Core/IntegerContainer.hpp"

namespace Solaire { namespace Test {

    static constexpr bool isByteAligned(const uint32_t aBits) throw() {
        return (static_cast<float>(aBits) / 8.f) == static_cast<float>(aBits / 8);
    }

    static constexpr uint64_t MASKS[33] = {
        0x00,
        0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF,                         // 8 bit
        0x01F, 0x03F, 0x07F, 0x0FF, 0x1FF, 0x3FF, 0x7F, 0xFFF,                  // 16 bit
        0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FF, 0xFFFF,          // 32 bit
        0x01FFF, 0x03FFF, 0x07FFF, 0x0FFFF, 0x1FFFF, 0x3FFFF, 0x7FFF, 0xFFFFF,  // 64 bit
    };

    ////

    template<const uint8_t BITS, const bool SIGN>
    struct ElementInfo {
        enum : uint64_t {
            Bits = BITS,
            Signed = SIGN
        };
        typedef BinaryBlock<BITS, Signed> Type;

        enum : Type {
            Min = Signed ? (static_cast<int64_t>(MASKS[Bits] / 2) - 1) * -1 : 0,
            Max = Signed ? MASKS[Bits] / 2 : (MASKS[Bits] + 1)
        };

        static constexpr float scale(const Type aValue) {
            return static_cast<float>(aValue) / static_cast<float>(Max);
        }
    };

    template<
        const uint8_t XBITS, const uint8_t YBITS, const uint8_t ZBITS, const uint8_t WBITS,
        const bool XSIGN = false, const bool YSIGN = false, const bool ZSIGN = false, const bool WSIGN = false
    >
    class CompressedVector {
    public:
        enum {
            TotalBits = XBITS + YBITS + ZBITS + WBITS,
            IsByteAligned = isByteAligned(TotalBits),
            Size = (XBITS == 0 ? 0 : 1) + (YBITS == 0 ? 0 : 1) + (ZBITS == 0 ? 0 : 1) + (WBITS == 0 ? 0 : 1)
        };

        typedef ElementInfo<XBITS, XSIGN> XInfo;
        typedef ElementInfo<YBITS, YSIGN> YInfo;
        typedef ElementInfo<ZBITS, ZSIGN> ZInfo;
        typedef ElementInfo<WBITS, WSIGN> WInfo;

        typedef IntegerContainer4<typename XInfo::Type, typename YInfo::Type, typename ZInfo::Type, typename WInfo::Type> Scalar;

        typedef CompressedVector<
            XBITS, YBITS, ZBITS, WBITS,
            XSIGN, YSIGN, ZSIGN, WSIGN
        > Self;

       enum : char {
            Index0 =
                XInfo::Bits > 0 ? 'X' :
                YInfo::Bits > 0 ? 'Y' :
                ZInfo::Bits > 0 ? 'Z' :
                WInfo::Bits > 0 ? 'W' :
                '?',

            Index1 =
                Index0 == '?' ? '?' :
                Index0 != 'Y' && YInfo::Bits > 0 ? 'Y' :
                Index0 != 'Z' && ZInfo::Bits > 0 ? 'Z' :
                Index0 != 'W' && WInfo::Bits > 0 ? 'W' :
                '?',

            Index2 =
                Index1 == '?' ? '?' :
                Index0 != 'Z' && Index1 != 'Z' && ZInfo::Bits > 0 ? 'Z' :
                Index0 != 'W' && Index1 != 'W' && WInfo::Bits > 0 ? 'W' :
                '?',

            Index3 =
                Index2 == '?' ? '?' :
                Index0 != 'W' && Index1 != 'W' && Index2 != 'W' && WInfo::Bits > 0 ? 'W' :
                '?'
        };
    public:
        typename XInfo::Type X : XBITS;
        typename YInfo::Type Y : YBITS;
        typename ZInfo::Type Z : ZBITS;
        typename WInfo::Type W : WBITS;
    public:

        // Constructors

        CompressedVector() :
            X(0),
            Y(0),
            Z(0),
            W(0)
        {}

        CompressedVector(const Scalar aX, const Scalar aY) :
            X(aX),
            Y(aY),
            Z(0),
            W(0)
        {}

        CompressedVector(const Scalar aX, const Scalar aY, const Scalar aZ) :
            X(aX),
            Y(aY),
            Z(aZ),
            W(0)
        {}

        CompressedVector(const Scalar aX, const Scalar aY, const Scalar aZ, const Scalar aW) :
            X(aX),
            Y(aY),
            Z(aZ),
            W(aW)
        {}


        // C++ operators

        /*!
            \brief Access an element of this vector.
            \param aIndex The element to access.
            \return A copy of the scalar element.
        */
	    Scalar operator[](const uint32_t aIndex) const throw() {
	        switch(aIndex) {
            case 0  : return Index0 == 'X' ? X : Index0 == 'Y' ? Y : Index0 == 'Z' ? Z : Index0 == 'W' ? W : 0;
            case 1  : return Index1 == 'Y' ? Y : Index1 == 'Z' ? Z : Index1 == 'W' ? W : 0;
            case 2  : return Index2 == 'Z' ? Z : Index2 == 'W' ? W : 0;
            case 3  : return Index3 == 'W' ? W : 0;
            default : return 0;
	        }
	    }

        /*!
            \brief Compare this vector to another.
            \param aOther The second vector.
            \return True if this vector is equal to \a aOther.
        */
		bool operator==(const Self aOther) const throw() {
			return std::memcmp(this, &aOther, sizeof(Self)) == 0;
		}

        /*!
            \brief Compare this vector to another.
            \param aOther The second vector.
            \return True if this vector is not equal to \a aOther.
        */
		bool operator!=(const Self aOther) const throw() {
			return std::memcmp(this, &aOther, sizeof(Self)) != 0;
		}

        /*!
            \brief Compare this vector to another.
            \detail This is implemented using the (squared) magnitude.
            \param aOther The second vector.
            \return True if this vector is less than \a aOther.
        */
		bool operator<(const Self aOther) const throw() {
			return magnitudeSquared() < aOther.magnitudeSquared();
		}

        /*!
            \brief Compare this vector to another.
            \detail This is implemented using the (squared) magnitude.
            \param aOther The second vector.
            \return True if this vector is greater than \a aOther.
        */
		bool operator>(const Self aOther) const throw() {
			return magnitudeSquared() > aOther.magnitudeSquared();
		}

        /*!
            \brief Compare this vector to another.
            \detail This is implemented using the (squared) magnitude.
            \param aOther The second vector.
            \return True if this vector is less than, or equal to \a aOther.
        */
		bool operator<=(const Self aOther) const throw() {
			return magnitudeSquared() <= aOther.magnitudeSquared();
		}

        /*!
            \brief Compare this vector to another.
            \detail This is implemented using the (squared) magnitude.
            \param aOther The second vector.
            \return True if this vector is greater than, or equal to \a aOther.
        */
		bool operator>=(const Self aOther) const throw() {
			return magnitudeSquared() >= aOther.magnitudeSquared();
		}

        // Misc

        /*!
            \brief Calculate the sum of all elements in the vector.
            \return The sum.
        */
		Scalar sum() const throw() {
			return X + Y + Z + W;
		}

        /*!
            \brief Calculate the mean element in the vector.
            \return The mean element.
        */
		Scalar average() const throw() {
			return sum() / Size;
		}

        /*!
            \brief Compute square of the magnitude of this vector.
            \detail This is faster than Magnitude().
            \return The square of the magnitude.
            \see Magnitude
        */
       Scalar magnitudeSquared() const throw() {
			return (X * X) + (Y * Y) + (Z * Z) + (W * W);
		}

        /*!
            \brief Compute magnitude of this vector.
            \return The magnitude.
            \see MagnitudeSquared
        */
		Scalar magnitude() const throw() {
			return static_cast<Scalar>(std::sqrt(static_cast<double>(magnitudeSquared())));
		}

        /*!
            \brief Compute normalised form of this vector.
            \return The normalised unit vector.
        */
		Self normalise() const throw() {
			return Self(*this) / magnitude();
		}

        /*!
            \brief Compute the dot product of two vectors.
            \param aOther The second vector.
            \return The dot product.
        */
		Scalar dotProduct(const Self aOther) const throw() {
			return (X * aOther.X) + (Y * aOther.Y) + (Z * aOther.Z) + (W * aOther.W);
		}

        /*!
            \brief Compute the cross product of two vectors.
            \param aOther The second vector.
            \return The cross product.
        */
		Self crossProduct(const Self aOther) const throw() {
		    return Self(
                (Y * aOther.Z) - (Z * aOther.Y),
                (Z * aOther.Z) - (X * aOther.Z),
                (X * aOther.Y) - (Y * aOther.Z),
                0
		    );
		}

        /*!
            \brief Perform linear interpolation between two vectors.
            \param aOther The other vector.
            \param aWeight The weighting bias for this vector.
            \return The interpolated vector.
        */
		Self lerp(const Self aOther, const double aWeight) const throw() {
			return Self(
               static_cast<Scalar>((1.0 - aWeight) * static_cast<double>(X) + aWeight * static_cast<double>(aOther.X)),
               static_cast<Scalar>((1.0 - aWeight) * static_cast<double>(Y) + aWeight * static_cast<double>(aOther.Y)),
               static_cast<Scalar>((1.0 - aWeight) * static_cast<double>(Z) + aWeight * static_cast<double>(aOther.Z)),
               static_cast<Scalar>((1.0 - aWeight) * static_cast<double>(W) + aWeight * static_cast<double>(aOther.W))
            );
		}

		//! \todo Swizzle

		explicit operator Vector<Scalar, Size>() const {
		    Vector<Scalar, Size> tmp;
            for(uint32_t i = 0; i < Size; ++i) tmp[i] = operator[](i);
            return tmp;
		}
    };

    template<class T>
    static void PrintElementInfo(const char aElement) {
        std::cout << "Info - Element " << aElement << std::endl;
        std::cout << "Bits\t: " << T::Bits << std::endl;
        std::cout << "Signed\t: " << T::Signed << std::endl;
        std::cout << "Type\t: " << sizeof(typename T::Type) << " bytes" << std::endl;
        std::cout << "Min\t: " << T::Min << std::endl;
        std::cout << "Max\t: " << T::Max << std::endl;

    }

    template<class T>
    static void PrintVectorInfo() {
        std::cout << "Info - Vector" << std::endl;
        std::cout << "TotalBits\t: " << T::TotalBits << std::endl;
        std::cout << "IsByteAligned\t: " << T::IsByteAligned << std::endl;
        std::cout << std::endl;
        PrintElementInfo<typename T::XInfo>('X');
        std::cout << std::endl;
        PrintElementInfo<typename T::YInfo>('Y');
        std::cout << std::endl;
        PrintElementInfo<typename T::ZInfo>('Z');
        std::cout << std::endl;
        PrintElementInfo<typename T::WInfo>('W');
    }

}}

#include "Solaire/Maths/CompressedVector.inl"


#endif
