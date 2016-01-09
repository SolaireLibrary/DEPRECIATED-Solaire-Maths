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
    static constexpr uint8_t HexToBin4(const HexChar aHex) {
        return HexImplementation::HEX2BIN_LOOKUP[aHex];
    }

    /*!
        \brief Convert two hexadecimal characters into 8 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint8_t HexToBin8(const HexChar* const aHex) {
        return (HexToBin4(aHex[0]) << 4 )| HexToBin4(aHex[1]);
    }

    /*!
        \brief Convert four hexadecimal characters into 16 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint16_t HexToBin16(const HexChar* const aHex) {
        return
            static_cast<uint16_t>(HexToBin8(aHex) << 4) |
            static_cast<uint16_t>(HexToBin8(aHex + 4));
    }

    /*!
        \brief Convert 8 hexadecimal characters into 32 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint32_t HexToBin32(const HexChar* const aHex) {
        return
            static_cast<uint32_t>(HexToBin16(aHex) << 16) |
            static_cast<uint32_t>(HexToBin16(aHex + 4));
    }

    /*!
        \brief Convert 16 hexadecimal characters into 64 bits of binary data.
        \param aHex The characters to convert.
        \return The binary data.
    */
    static constexpr uint64_t HexToBin64(const HexChar* const aHex) {
        return
            static_cast<uint64_t>(HexToBin32(aHex) << 32L) |
            static_cast<uint64_t>(HexToBin32(aHex + 8));
    }

    /*!
        \brief Convert 4 bits of binary data into a hexadecimal character.
        \param aNybble The binary data.
        \return The hexadecimal representation of the binary data.
    */
    static constexpr HexChar Bin4ToHex(const uint8_t aNybble) {
        return HexImplementation::BIN2HEX_LOOKUP[aNybble];
    }

    /*!
        \brief Convert 8 bits of binary data into two hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void Bin8ToHex(const uint8_t aByte, HexChar* const aChars) {
        aChars[0] = Bin4ToHex(aByte >> 4);
        aChars[1] = Bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Convert 16 bits of binary data into four hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void Bin16ToHex(const uint16_t aByte, HexChar* const aChars) {
        aChars[0] = Bin4ToHex((aByte >> 12) & NYBBLE_0);
        aChars[1] = Bin4ToHex((aByte >> 8) & NYBBLE_0);
        aChars[2] = Bin4ToHex((aByte >> 4) & NYBBLE_0);
        aChars[3] = Bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Convert 32 bits of binary data into eight hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void Bin32ToHex(const uint32_t aByte, HexChar* const aChars) {
        aChars[0] = Bin4ToHex((aByte >> 28) & NYBBLE_0);
        aChars[1] = Bin4ToHex((aByte >> 24) & NYBBLE_0);
        aChars[2] = Bin4ToHex((aByte >> 20) & NYBBLE_0);
        aChars[3] = Bin4ToHex((aByte >> 16) & NYBBLE_0);
        aChars[4] = Bin4ToHex((aByte >> 12) & NYBBLE_0);
        aChars[5] = Bin4ToHex((aByte >> 8) & NYBBLE_0);
        aChars[6] = Bin4ToHex((aByte >> 4) & NYBBLE_0);
        aChars[7] = Bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Convert 64 bits of binary data into sixteen hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void Bin64ToHex(const uint32_t aByte, HexChar* const aChars) {
        aChars[0] = Bin4ToHex((aByte >> 60L) & NYBBLE_0);
        aChars[1] = Bin4ToHex((aByte >> 56L) & NYBBLE_0);
        aChars[2] = Bin4ToHex((aByte >> 52L) & NYBBLE_0);
        aChars[3] = Bin4ToHex((aByte >> 48L) & NYBBLE_0);
        aChars[4] = Bin4ToHex((aByte >> 44L) & NYBBLE_0);
        aChars[5] = Bin4ToHex((aByte >> 40L) & NYBBLE_0);
        aChars[6] = Bin4ToHex((aByte >> 36L) & NYBBLE_0);
        aChars[7] = Bin4ToHex((aByte >> 32L) & NYBBLE_0);
        aChars[8] = Bin4ToHex((aByte >> 28L) & NYBBLE_0);
        aChars[9] = Bin4ToHex((aByte >> 24L) & NYBBLE_0);
        aChars[10] = Bin4ToHex((aByte >> 20L) & NYBBLE_0);
        aChars[11] = Bin4ToHex((aByte >> 16L) & NYBBLE_0);
        aChars[12] = Bin4ToHex((aByte >> 12L) & NYBBLE_0);
        aChars[13] = Bin4ToHex((aByte >> 8L) & NYBBLE_0);
        aChars[14] = Bin4ToHex((aByte >> 4L) & NYBBLE_0);
        aChars[15] = Bin4ToHex(aByte & NYBBLE_0);
    }

    /*!
        \brief Calculate the number of characters required to store a hexadecimal representation.
        \param aBinaryLength The number of bytes to represent.
        \return The number of characters required.
    */
    static constexpr uint32_t BinaryToHexLength(const uint32_t aBinaryLength) {
        return aBinaryLength * 2;
    }

    /*!
        \brief Calculate the number of bytes required to store a binary representation of hexadecimal data.
        \param aBinaryLength The number of characters to represent.
        \return The number of bytes required.
    */
    static constexpr uint32_t HexToBinaryLength(const uint32_t aHexLength) {
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
    static bool BinaryToHex(const void* const aBinary, const uint32_t aBinaryLength, HexChar* const aHex, const uint32_t aHexLength) {
        if(aHexLength < BinaryToHexLength(aBinaryLength)) return false;
        const uint8_t* const bin = static_cast<const uint8_t*>(aBinary);
        for(uint32_t i = 0; i < aBinaryLength; ++i) {
            Bin8ToHex(bin[aBinaryLength - (i + 1)], aHex + i * 2);
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
    static bool HexToBinary(const HexChar* const aHex, const uint32_t aHexLength, void* const aBinary, const uint32_t aBinaryLength) {
        if(aHexLength < HexToBinaryLength(aHexLength)) return false;
        const HexChar* hex = aHex;
        const HexChar* end = hex + aHexLength;
        uint8_t* bin = static_cast<uint8_t*>(aBinary) + (aBinaryLength - 1);

        // Convert all paired characters
        while((end - hex) >= 2){
            *bin = HexToBin8(hex);
            hex += 2;
            --bin;
        }

        // Convert trailing character, if present
        if((end - hex) == 1) {
            *bin = HexToBin4(*hex) << 4;
        }
        return true;
    }

}

#endif
