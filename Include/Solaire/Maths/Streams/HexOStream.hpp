#ifndef SOLAIRE_HEX_OSTREAM_HPP
#define SOLAIRE_HEX_OSTREAM_HPP

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
	\file HexOStream.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 12th January 2016
	Last Modified	: 12th January 2016
*/

#include "Solaire/Core/OStream.hpp"
#include "Solaire/Maths/Hex.hpp"


namespace Solaire {

	class BinToHexOStream : public OStream {
    private:
        OStream& mStream;
    private:
        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL writeU8(const uint8_t aValue) throw() override {
            char buf[2];
            bin8ToHex(aValue, buf);
            mStream.write(buf, 2);
        }

        void SOLAIRE_EXPORT_CALL writeU16(const uint16_t aValue) throw() override {
            char buf[4];
            bin16ToHex(aValue, buf);
            mStream.write(buf, 4);
        }

        void SOLAIRE_EXPORT_CALL writeU32(const uint32_t aValue) throw() override {
            char buf[8];
            bin16ToHex(aValue, buf);
            mStream.write(buf, 8);
        }

        void SOLAIRE_EXPORT_CALL writeU64(const uint64_t aValue) throw() override {
            char buf[16];
            bin64ToHex(aValue, buf);
            mStream.write(buf, 16);
        }

        void SOLAIRE_EXPORT_CALL writeI8(const int8_t aValue) throw() override {
            char buf[2];
            bin8ToHex(*reinterpret_cast<const uint8_t*>(&aValue), buf);
            mStream.write(buf, 2);
        }

        void SOLAIRE_EXPORT_CALL writeI16(const int16_t aValue) throw() override {
            char buf[4];
            bin16ToHex(*reinterpret_cast<const uint16_t*>(&aValue), buf);
            mStream.write(buf, 4);
        }

        void SOLAIRE_EXPORT_CALL writeI32(const int32_t aValue) throw() override {
            char buf[8];
            bin32ToHex(*reinterpret_cast<const uint32_t*>(&aValue), buf);
            mStream.write(buf, 8);
        }

        void SOLAIRE_EXPORT_CALL writeI64(const int64_t aValue) throw() override {
            char buf[16];
            bin64ToHex(*reinterpret_cast<const uint64_t*>(&aValue), buf);
            mStream.write(buf, 16);
        }

        void SOLAIRE_EXPORT_CALL writeF(const float aValue) throw() override {
            enum{SIZE = sizeof(float) * 2};
            char buf[SIZE];
            binaryToHex(&aValue, sizeof(float), buf, SIZE);
            mStream.write(buf, SIZE);
        }

        void SOLAIRE_EXPORT_CALL writeD(const double aValue) throw() override {
            enum{SIZE = sizeof(double) * 2};
            char buf[SIZE];
            binaryToHex(&aValue, sizeof(double), buf, SIZE);
            mStream.write(buf, SIZE);
        }

        void SOLAIRE_EXPORT_CALL writeC(const char aValue) throw() override {
            char buf[2];
            bin8ToHex(*reinterpret_cast<const uint8_t*>(&aValue), buf);
            mStream.write(buf, 2);
        }

    public:
        BinToHexOStream(OStream& aStream) :
            mStream(aStream)
        {}

        SOLAIRE_EXPORT_CALL ~BinToHexOStream() {

        }

        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL write(const void* const aPtr, const uint32_t aBytes) throw() override {
            const uint32_t size = aBytes * 2;
            char* ptr = new char[size];
            binaryToHex(aPtr, aBytes, ptr, size);
            mStream.write(ptr, size);
            delete[] ptr;
        }

        bool SOLAIRE_EXPORT_CALL isOffsetable() const throw() override {
            return mStream.isOffsetable();
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() override {
            return mStream.getOffset();
        }

        bool SOLAIRE_EXPORT_CALL setOffset(const int32_t aOffset) throw() override {
            return mStream.setOffset(aOffset);
        }
    };

    class HexToBinOStream : public OStream {
    private:
        OStream& mStream;
        HexChar mBuffer[2];
        bool mBufferSet;
    private:
        void pushByte(const HexChar aValue) throw() {
            if(mBufferSet) {
                mBuffer[0] = aValue;
                mBufferSet = true;
            }else {
                mBuffer[1] = aValue;
                mBufferSet = false;
                mStream << hexToBin8(mBuffer);
            }
        }

        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL writeU8(const uint8_t aValue) throw() override {
            pushByte(*reinterpret_cast<const HexChar*>(aValue));
        }

        void SOLAIRE_EXPORT_CALL writeU16(const uint16_t aValue) throw() override {
            if(mBufferSet) {
                const HexChar* const ptr = reinterpret_cast<const HexChar*>(&aValue);
                pushByte(ptr[0]);
                pushByte(ptr[1]);
            }else {
                mStream << hexToBin8(reinterpret_cast<const HexChar*>(&aValue));
            }
        }

        void SOLAIRE_EXPORT_CALL writeU32(const uint32_t aValue) throw() override {
            if(mBufferSet) {
                const HexChar* const ptr = reinterpret_cast<const HexChar*>(&aValue);
                pushByte(ptr[0]);
                mStream << hexToBin8(ptr + 1);
                pushByte(ptr[3]);
            }else {
                mStream << hexToBin16(reinterpret_cast<const HexChar*>(&aValue));
            }
        }

        void SOLAIRE_EXPORT_CALL writeU64(const uint64_t aValue) throw() override {
            if(mBufferSet) {
                const HexChar* const ptr = reinterpret_cast<const HexChar*>(&aValue);
                pushByte(ptr[0]);
                mStream << hexToBin16(ptr + 1);
                mStream << hexToBin8(ptr + 5);
                pushByte(ptr[7]);
            }else {
                mStream << hexToBin32(reinterpret_cast<const HexChar*>(&aValue));
            }
        }

        void SOLAIRE_EXPORT_CALL writeI8(const int8_t aValue) throw() override {
            pushByte(*reinterpret_cast<const HexChar*>(aValue));
        }

        void SOLAIRE_EXPORT_CALL writeI16(const int16_t aValue) throw() override {
            if(mBufferSet) {
                const HexChar* const ptr = reinterpret_cast<const HexChar*>(&aValue);
                pushByte(ptr[0]);
                pushByte(ptr[1]);
            }else {
                mStream << hexToBin8(reinterpret_cast<const HexChar*>(&aValue));
            }
        }

        void SOLAIRE_EXPORT_CALL writeI32(const int32_t aValue) throw() override {
            if(mBufferSet) {
                const HexChar* const ptr = reinterpret_cast<const HexChar*>(&aValue);
                pushByte(ptr[0]);
                mStream << hexToBin8(ptr + 1);
                pushByte(ptr[3]);
            }else {
                mStream << hexToBin16(reinterpret_cast<const HexChar*>(&aValue));
            }
        }

        void SOLAIRE_EXPORT_CALL writeI64(const int64_t aValue) throw() override {
            if(mBufferSet) {
                const HexChar* const ptr = reinterpret_cast<const HexChar*>(&aValue);
                pushByte(ptr[0]);
                mStream << hexToBin16(ptr + 1);
                mStream << hexToBin8(ptr + 5);
                pushByte(ptr[7]);
            }else {
                mStream << hexToBin32(reinterpret_cast<const HexChar*>(&aValue));
            }
        }

        void SOLAIRE_EXPORT_CALL writeF(const float aValue) throw() override {
            //! \todo Optimise writeF
            write(&aValue, sizeof(float));
        }

        void SOLAIRE_EXPORT_CALL writeD(const double aValue) throw() override {
            //! \todo Optimise writeD
            write(&aValue, sizeof(double));
        }

        void SOLAIRE_EXPORT_CALL writeC(const char aValue) throw() override {
            pushByte(*reinterpret_cast<const HexChar*>(aValue));
        }

    public:
        HexToBinOStream(OStream& aStream) :
            mStream(aStream),
            mBufferSet(false)
        {}

        SOLAIRE_EXPORT_CALL ~HexToBinOStream() {
            // Handle trailing byte
            if(mBufferSet){
                pushByte('0');
            }
        }

        // Inherited from OStream

        void SOLAIRE_EXPORT_CALL write(const void* const aPtr, const uint32_t aBytes) throw() override {
            //! \todo Optimise write
            const HexChar* const hex = static_cast<const HexChar*>(aPtr);
            for(uint32_t i = 0; i < aBytes; ++i) {
                pushByte(hex[i]);
            }
        }

        bool SOLAIRE_EXPORT_CALL isOffsetable() const throw() override {
            return mStream.isOffsetable();
        }

        int32_t SOLAIRE_EXPORT_CALL getOffset() const throw() override {
            return mStream.getOffset();
        }

        bool SOLAIRE_EXPORT_CALL setOffset(const int32_t aOffset) throw() override {
            return mStream.setOffset(aOffset);
        }
    };

}

#endif
