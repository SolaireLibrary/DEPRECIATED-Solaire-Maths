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
        } //!< Lookup table for conversion of hexadecimal to binary.
    }

    /*!
        \brief Convert a hexadecimal character into 4 bits of binary data.
        \param aHex The hex character to convert.
        \return The binary value of the character.
    */
    static constexpr uint8_t HexToNybble(const HexChar aHex) {
        return HexImplementation::HEX2BIN_LOOKUP[aHex];
    }

    /*!
        \brief Convert two hexadecimal characters into 8 bits of binary data.
        \param aHex0 The first character.
        \param aHex1 The second character.
        \return The binary data.
    */
    static constexpr uint8_t HexToByte(const HexChar aHex0, const HexChar aHex1) {
        return (HexToNybble(aHex0) << 4 )| HexToNybble(aHex1);
    }

    /*!
        \brief Convert 4 bits of binary data into a hexadecimal character.
        \param aNybble The binary data.
        \return The hexadecimal representation of the binary data.
    */
    static constexpr HexChar NybbleToHex(const uint8_t aNybble) {
        return HexImplementation::BIN2HEX_LOOKUP[aNybble];
    }

    /*!
        \brief Convert 8 bits of binary data into two hexadecimal characters.
        \param aByte The binary data.
        \param aChars The address to write the hex characters into.
    */
    static void ByteToHex(const uint8_t aByte, HexChar* const aChars) {
        aChars[0] = NybbleToHex(aByte >> 4);
        aChars[1] = NybbleToHex(aByte & NYBBLE_0);
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
            ByteToHex(bin[aBinaryLength - (i + 1)], aHex + i * 2);
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
            *bin = HexToByte(hex[0], hex[1]);
            hex += 2;
            --bin;
        }

        // Convert trailing character, if present
        if((end - hex) == 1) {
            *bin = HexToNybble(*hex) << 4;
        }
        return true;
    }

}

#endif
