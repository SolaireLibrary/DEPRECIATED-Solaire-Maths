#ifndef SOLAIRE_HEX_HPP
#define SOLAIRE_HEX_HPP

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
	\file Hex.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 9th January 2016
	Last Modified	: 9th January 2016
*/

#include <cstdint>
#include "Solaire/Core/Maths.hpp"
#include "Solaire/Core/IStream.hpp"
#include "Solaire/Core/OStream.hpp"

namespace Solaire {

    typedef char HexChar;

    namespace HexImplementation {
        static constexpr HexChar BIN2HEX_LOOKUP[17] = "0123456789ABCDEF";   //!< Lookup table for conversion of binary (nybble) to hexadecimal.

        static constexpr uint8_t HEX2BIN_LOOKUP[256] = {
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	1,
            2,	3,	4,	5,	6,	7,	8,	9,	0,	0,
            0,	0,	0,	0,	0,	10,	11,	12,	13,	14,
            15,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	10,	11,	12,
            13,	14,	15,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
            0,	0,	0,	0,	0,	0
        }; //!< Lookup table for conversion of hexadecimal to binary.
    }

    /*!
        \brief Convert a hexadecimal character into 4 bits of binary data.
        \param aHex The hex character to convert.
        \return The binary value of the character.
    */
    static constexpr uint8_t hexToBin4(const HexChar aHex) {
        return HexImplementation::HEX2BIN_LOOKUP[aHex];
    }

    /*!
        \brief Convert two hexadecimal characters into 8 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint8_t hexToBin8(const HexChar* const aHex) {
        return (hexToBin4(aHex[0]) << 4 )| hexToBin4(aHex[1]);
    }

    /*!
        \brief Convert four hexadecimal characters into 16 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint16_t hexToBin16(const HexChar* const aHex) {
        return
            (static_cast<uint16_t>(hexToBin8(aHex)) << 8) |
            static_cast<uint16_t>(hexToBin8(aHex + 2));
    }

    /*!
        \brief Convert 8 hexadecimal characters into 32 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint32_t hexToBin32(const HexChar* const aHex) {
        return
            static_cast<uint32_t>(hexToBin16(aHex) << 16) |
            static_cast<uint32_t>(hexToBin16(aHex + 4));
    }

    /*!
        \brief Convert 16 hexadecimal characters into 64 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint64_t hexToBin64(const HexChar* const aHex) {
        return
            static_cast<uint64_t>(hexToBin32(aHex) << 32L) |
            static_cast<uint64_t>(hexToBin32(aHex + 8));
    }

    /*!
        \brief Convert 4 bits of binary data into a hexadecimal character.
        \param aNybble The binary data.
        \return The hexadecimal representation of the binary data.
    */
    static constexpr HexChar bin4ToHex(const uint8_t aNybble) {
        return HexImplementation::BIN2HEX_LOOKUP[aNybble];
    }

    /*!
        \brief Convert 8 bits of binary data into two hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void bin8ToHex(const uint8_t aByte, HexChar* const aChars) {
        aChars[0] = bin4ToHex(aByte >> 4);
        aChars[1] = bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Convert 16 bits of binary data into four hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void bin16ToHex(const uint16_t aByte, HexChar* const aChars) {
        aChars[0] = bin4ToHex((aByte >> 12) & NYBBLE_0);
        aChars[1] = bin4ToHex((aByte >> 8) & NYBBLE_0);
        aChars[2] = bin4ToHex((aByte >> 4) & NYBBLE_0);
        aChars[3] = bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Convert 32 bits of binary data into eight hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void bin32ToHex(const uint32_t aByte, HexChar* const aChars) {
        aChars[0] = bin4ToHex((aByte >> 28) & NYBBLE_0);
        aChars[1] = bin4ToHex((aByte >> 24) & NYBBLE_0);
        aChars[2] = bin4ToHex((aByte >> 20) & NYBBLE_0);
        aChars[3] = bin4ToHex((aByte >> 16) & NYBBLE_0);
        aChars[4] = bin4ToHex((aByte >> 12) & NYBBLE_0);
        aChars[5] = bin4ToHex((aByte >> 8) & NYBBLE_0);
        aChars[6] = bin4ToHex((aByte >> 4) & NYBBLE_0);
        aChars[7] = bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Convert 64 bits of binary data into sixteen hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void bin64ToHex(const uint32_t aByte, HexChar* const aChars) {
        aChars[0] = bin4ToHex((aByte >> 60L) & NYBBLE_0);
        aChars[1] = bin4ToHex((aByte >> 56L) & NYBBLE_0);
        aChars[2] = bin4ToHex((aByte >> 52L) & NYBBLE_0);
        aChars[3] = bin4ToHex((aByte >> 48L) & NYBBLE_0);
        aChars[4] = bin4ToHex((aByte >> 44L) & NYBBLE_0);
        aChars[5] = bin4ToHex((aByte >> 40L) & NYBBLE_0);
        aChars[6] = bin4ToHex((aByte >> 36L) & NYBBLE_0);
        aChars[7] = bin4ToHex((aByte >> 32L) & NYBBLE_0);
        aChars[8] = bin4ToHex((aByte >> 28L) & NYBBLE_0);
        aChars[9] = bin4ToHex((aByte >> 24L) & NYBBLE_0);
        aChars[10] = bin4ToHex((aByte >> 20L) & NYBBLE_0);
        aChars[11] = bin4ToHex((aByte >> 16L) & NYBBLE_0);
        aChars[12] = bin4ToHex((aByte >> 12L) & NYBBLE_0);
        aChars[13] = bin4ToHex((aByte >> 8L) & NYBBLE_0);
        aChars[14] = bin4ToHex((aByte >> 4L) & NYBBLE_0);
        aChars[15] = bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Calculate the number of characters required to store a hexadecimal representation.
        \param aBinaryLength The number of bytes to represent.
        \return The number of characters required.
    */
    static constexpr uint32_t binaryToHexLength(const uint32_t aBinaryLength) {
        return aBinaryLength * 2;
    }

    /*!
        \brief Calculate the number of bytes required to store a binary representation of hexadecimal data.
        \param aBinaryLength The number of characters to represent.
        \return The number of bytes required.
    */
    static constexpr uint32_t hexToBinaryLength(const uint32_t aHexLength) {
        return (aHexLength >> 1) + (aHexLength & BIT_0);
    }

    /*!
        \brief Convert binary data into it's hexadecimal representation.
        \param aBinary The starting address of the binary data.
        \param aBinaryLength The number of bytes to convert.
        \param aHex The starting address to write the hexadecimal data into.
        \param aHexLength The number of writeable chars pointed to be \a aHex.
        \return False if \a aHexLength is not long enough to contain the hexadecimal representation.
    */
    static bool binaryToHex(const void* const aBinary, const uint32_t aBinaryLength, HexChar* const aHex, const uint32_t aHexLength) {
        if(aHexLength < binaryToHexLength(aBinaryLength)) return false;
        const uint8_t* const bin = static_cast<const uint8_t*>(aBinary);
        HexChar* hex = aHex;
        int32_t bytes = aBinaryLength - 1;

        while(bytes >= 7) {
            bytes -= 7;
            bin64ToHex(*reinterpret_cast<const uint64_t*>(bin + bytes), hex);
            --bytes;
            hex += 16;
        }

        if(bytes >= 3) {
            bytes -= 3;
            bin32ToHex(*reinterpret_cast<const uint32_t*>(bin + bytes), hex);
            --bytes;
            hex += 8;
        }

        if(bytes >= 1) {
            --bytes;
            bin16ToHex(*reinterpret_cast<const uint16_t*>(bin + bytes), hex);
            --bytes;
            hex += 4;
        }

        if(bytes >= 0) {
            bin8ToHex(bin[bytes], hex);
            --bytes;
            hex += 2;
        }

        return true;
    }

    /*!
        \brief Convert binary data into it's hexadecimal representation.
        \param aHex The hexadecimal characters to convert.
        \param aHexLength The number of characters to convert.
        \param aBinary The starting address to write binary data into.
        \param aBinaryLength The number of bytes pointed to by \a aBinary.
        \return False if aBinaryLength is too small to store the binary representation.
    */
    static bool hexToBinary(const HexChar* const aHex, const uint32_t aHexLength, void* const aBinary, const uint32_t aBinaryLength) {
        if(aHexLength < hexToBinaryLength(aHexLength)) return false;
        const HexChar* hex = aHex;
        const HexChar* end = hex + aHexLength;
        uint8_t* bin = static_cast<uint8_t*>(aBinary) + (aBinaryLength - 1);

        // Convert all paired characters
        while((end - hex) >= 16) {
            bin -= 7;
            *reinterpret_cast<uint64_t*>(bin) = hexToBin64(hex);
            hex += 16;
            --bin;
        }

        if((end - hex) >= 8) {
            bin -= 3;
            *reinterpret_cast<uint32_t*>(bin) = hexToBin32(hex);
            hex += 8;
            --bin;
        }

        if((end - hex) >= 4) {
            --bin;
            *reinterpret_cast<uint16_t*>(bin) = hexToBin16(hex);
            hex += 4;
            --bin;
        }

        if((end - hex) >= 2) {
            *bin = hexToBin8(hex);
            hex += 2;
            --bin;
        }

        // Convert trailing character, if present
        if((end - hex) == 1) {
            *bin = hexToBin4(*hex) << 4;
        }
        return true;
    }

    /*!
        \brief Convert binary data into it's hexadecimal representation.
        \param aDst The stream for writing hexadecimal data.
        \param aSrc The stream for reading binary data.
        \return True if the data was converted correctly.
    */
    static bool binaryToHex(OStream& aDst, IStream& aSrc) {
        uint8_t byte;
        char buf[2];
        while(! aSrc.end()) {
            aSrc >> byte;
            bin8ToHex(byte, buf);
            aDst << buf[0];
            aDst << buf[1];
        }
        return true;
    }

    /*!
        \brief Convert binary data into it's hexadecimal representation.
        \param aDst The stream for writing binary data.
        \param aSrc The stream for reading hexadecimal data.
        \return True if the data was converted correctly.
    */
    static bool hexToBinary(OStream& aDst, IStream& aSrc) {
        char buf[2];
        while(! aSrc.end()) {
            aSrc >> buf[0];
            if(aSrc.end()) {
                buf[1] = '0';
            }else {
                aSrc >> buf[1];
            }
            aDst << hexToBin8(buf);
        }
        return true;
    }

}

#endif
