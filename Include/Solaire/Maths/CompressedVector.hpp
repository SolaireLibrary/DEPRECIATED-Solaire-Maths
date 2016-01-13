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

   // template<const uint32_t BYTES, typename ENABLE = typename std::enable_if<binaryBlockFn(BYTES, 65, INT8_MAX)>::type>
    //using BinaryBlock = ByteArray<BYTES>;

   // template<const uint32_t BYTES, typename ENABLE = typename std::enable_if<binaryBlockFn(BYTES, 33, 64)>::type>
    //using BinaryBlock = uint64_t;

    template<const uint32_t BYTES, typename ENABLE = typename std::enable_if<binaryBlockFn(BYTES, 17, 32)>::type>
    using BinaryBlock = uint32_t;

    //template<const uint32_t BYTES, typename ENABLE = typename std::enable_if<binaryBlockFn(BYTES, 9, 16)>::type>
    //using BinaryBlock = uint16_t;

    //template<const uint32_t BYTES, typename ENABLE = typename std::enable_if<binaryBlockFn(BYTES, 0, 8)>::type>
    //using BinaryBlock = uint8_t;

    static constexpr bool isByteAligned(const uint32_t aBits) throw() {
        return (static_cast<float>(aBits) / 8.f) == static_cast<float>(aBits / 8);
    }

    static constexpr uint8_t MASKS[8] = {
        0x01, 0x03, 0x07, 0x0F,
        0x1F, 0x3F, 0x7F, 0xFF
    };

    static constexpr uint64_t generateMask(const uint64_t aOffset, const uint8_t aBits) throw() {
        return static_cast<uint64_t>(MASKS[aBits]) << aOffset;
    }

    ////

    template<const uint8_t BITS, const bool BYTE_ALIGNED, uint64_t MASK>
    struct ElementInfo {
        enum : uint64_t {
            Bits = BITS,
            IsByteAligned = BYTE_ALIGNED,
            Mask = MASK
        };
        typedef BinaryBlock<BITS> Type;
    };

    template<const uint8_t XBITS, const uint8_t YBITS, const uint8_t ZBITS, const uint8_t WBITS>
    struct VectorInfo{
        enum {
            TotalBits = XBITS + YBITS + ZBITS + WBITS
        };
        typedef BinaryBlock<TotalBits> Type;

        typedef ElementInfo<
            XBITS,
            isByteAligned(TotalBits),
            generateMask(0, XBITS)
        > X;

        typedef ElementInfo<
            YBITS,
            isByteAligned(TotalBits) && isByteAligned(XBITS),
            generateMask(XBITS, YBITS)
        > Y;

        typedef ElementInfo<
            ZBITS,
            isByteAligned(TotalBits) && isByteAligned(XBITS + YBITS),
            generateMask(XBITS + YBITS, ZBITS)
        > Z;

        typedef ElementInfo<
            WBITS,
            isByteAligned(TotalBits) && isByteAligned(XBITS + YBITS + ZBITS),
            generateMask(XBITS + YBITS + ZBITS, WBITS)
        > W;
    };

}}


#endif
