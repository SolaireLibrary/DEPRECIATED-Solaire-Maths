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

namespace Solaire { namespace Test {

    static constexpr bool binaryBlockFn(const int8_t aBytes, const int8_t aMin, const int8_t aMax) throw() {
        return aBytes >= aMin && aBytes < aMax;
    }

    template<const uint32_t BYTES>
    struct ByteArray {
    private:
        uint8_t mBytes[BYTES];
    };

    template<const uint32_t BYTES, typename ENABLE = void>
    struct BinaryBlockStruct {
        typedef ByteArray<BYTES> Type;
    };

    template<const uint32_t BYTES>
    struct BinaryBlockStruct<BYTES, typename std::enable_if<binaryBlockFn(BYTES, 33, 65)>::type> {
        typedef uint64_t Type;
    };

    template<const uint32_t BYTES>
    struct BinaryBlockStruct<BYTES, typename std::enable_if<binaryBlockFn(BYTES, 17, 33)>::type> {
        typedef uint32_t Type;
    };

    template<const uint32_t BYTES>
    struct BinaryBlockStruct<BYTES, typename std::enable_if<binaryBlockFn(BYTES, 9, 17)>::type> {
        typedef uint16_t Type;
    };

    template<const uint32_t BYTES>
    struct BinaryBlockStruct<BYTES, typename std::enable_if<binaryBlockFn(BYTES, 0, 9)>::type> {
        typedef uint8_t Type;
    };

    template<const uint32_t BYTES>
    using BinaryBlock = typename BinaryBlockStruct<BYTES>::Type;

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

    template<const uint8_t BITS, const uint8_t OFFSET>
    struct ElementInfo {
        enum : uint64_t {
            Bits = BITS,
            Offset = OFFSET,
            IsByteAligned = isByteAligned(Offset),
            Mask = static_cast<uint64_t>(MASKS[Bits]) << Offset
        };
        typedef BinaryBlock<BITS> Type;
    };

    template<const uint8_t XBITS, const uint8_t YBITS, const uint8_t ZBITS, const uint8_t WBITS>
    struct VectorInfo{
        enum {
            TotalBits = XBITS + YBITS + ZBITS + WBITS,
            IsByteAligned = isByteAligned(TotalBits)
        };
        typedef BinaryBlock<TotalBits> Type;

        typedef ElementInfo<
            XBITS,
            0
        > X;

        typedef ElementInfo<
            YBITS,
            XBITS
        > Y;

        typedef ElementInfo<
            ZBITS,
            XBITS + YBITS
        > Z;

        typedef ElementInfo<
            WBITS,
            XBITS + YBITS + ZBITS
        > W;
    };

}}


#endif