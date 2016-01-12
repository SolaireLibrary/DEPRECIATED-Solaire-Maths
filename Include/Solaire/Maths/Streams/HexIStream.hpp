#ifndef SOLAIRE_HEX_ISTREAM_HPP
#define SOLAIRE_HEX_ISTREAM_HPP

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
	\file HexIStream.hpp
	\brief
	\author
	Created			: Adam Smith
	Last modified	: Adam Smith
	\date
	Created			: 12th January 2016
	Last Modified	: 12th January 2016
*/

#include "Solaire/Core/IStream.hpp"
#include "Solaire/Core/Container.hpp"
#include "Solaire/Core/Maths.hpp"

namespace Solaire {

	class HexToBinIStream : public IStream {
    private:
        IStream& mStream;
    private:
        uint8_t readByte() throw() {
            HexChar buffer[2];
            mStream >> buffer[0];
            if(mStream.end()) {
                buffer[1] = '0';
            }else {
                mStream >> buffer[1];
            }
            return hexToBin8(buffer);
        }

        // Inherited from IStream

        uint8_t SOLAIRE_EXPORT_CALL readU8() throw() override {
            return readByte();
        }

        uint16_t SOLAIRE_EXPORT_CALL readU16() throw() override {
            return combine16(
                readByte(),
                readByte()
            );
        }

        uint32_t SOLAIRE_EXPORT_CALL readU32() throw() override {
            return combine32(
                readByte(),
                readByte(),
                readByte(),
                readByte()
            );
        }

        uint64_t SOLAIRE_EXPORT_CALL readU64() throw() override {
            return combine64(
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte()
            );
        }

        int8_t SOLAIRE_EXPORT_CALL readI8() throw() override {
            return signCast(readByte());
        }

        int16_t SOLAIRE_EXPORT_CALL readI16() throw() override {
            return signCast(combine16(
                readByte(),
                readByte()
            ));
        }

        int32_t SOLAIRE_EXPORT_CALL readI32() throw() override {
            return signCast(combine32(
                readByte(),
                readByte(),
                readByte(),
                readByte()
            ));

        }

        int64_t SOLAIRE_EXPORT_CALL readI64() throw() override {
            return signCast(combine64(
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte()
            ));
        }

        float SOLAIRE_EXPORT_CALL readF() throw() override {
            //! \todo Optimise readF
            float tmp;
            read(&tmp, sizeof(float));
            return tmp;
        }

        double SOLAIRE_EXPORT_CALL readD() throw() override {
            //! \todo Optimise readD
            double tmp;
            read(&tmp, sizeof(double));
            return tmp;
        }

        char SOLAIRE_EXPORT_CALL readC() throw() override {
            return static_cast<char>(readByte());
        }

    public:
        HexToBinIStream(IStream& aStream) :
            mStream(aStream)
        {}

        SOLAIRE_EXPORT_CALL ~HexToBinIStream() {

        }

        // Inherited from IStream

        void SOLAIRE_EXPORT_CALL read(void* const aAddress, const uint32_t aBytes) throw() override {
            uint8_t* const ptr = static_cast<uint8_t*>(aAddress);
            for(uint32_t i = 0; i < aBytes; ++i) ptr[i] = readByte();
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

        bool SOLAIRE_EXPORT_CALL end() const throw() override {
            return mStream.end();
        }

    };

    class BinToHexIStream : public IStream {
    private:
        IStream& mStream;
        HexChar mBuffer;
        bool mBufferSet;
    private:
        uint8_t readByte() throw() {
            if(mBufferSet) {
                mBufferSet = false;
                return mBuffer;
            }

            HexChar buf[2];
            uint8_t byte;
            mStream >> byte;
            bin8ToHex(byte, buf);
            mBufferSet = true;
            mBuffer = buf[1];
            return buf[0];
        }

        // Inherited from IStream

        uint8_t SOLAIRE_EXPORT_CALL readU8() throw() override {
            return readByte();
        }

        uint16_t SOLAIRE_EXPORT_CALL readU16() throw() override {
            return combine16(
                readByte(),
                readByte()
            );
        }

        uint32_t SOLAIRE_EXPORT_CALL readU32() throw() override {
            return combine32(
                readByte(),
                readByte(),
                readByte(),
                readByte()
            );
        }

        uint64_t SOLAIRE_EXPORT_CALL readU64() throw() override {
            return combine64(
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte()
            );
        }

        int8_t SOLAIRE_EXPORT_CALL readI8() throw() override {
            return signCast(readByte());
        }

        int16_t SOLAIRE_EXPORT_CALL readI16() throw() override {
            return signCast(combine16(
                readByte(),
                readByte()
            ));
        }

        int32_t SOLAIRE_EXPORT_CALL readI32() throw() override {
            return signCast(combine32(
                readByte(),
                readByte(),
                readByte(),
                readByte()
            ));
        }

        int64_t SOLAIRE_EXPORT_CALL readI64() throw() override {
            return signCast(combine64(
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte(),
                readByte()
            ));
        }

        float SOLAIRE_EXPORT_CALL readF() throw() override {
            float value;
            read(&value, sizeof(float));
            return value;
        }

        double SOLAIRE_EXPORT_CALL readD() throw() override {
            double value;
            read(&value, sizeof(double));
            return value;
        }

        char SOLAIRE_EXPORT_CALL readC() throw() override {
            return static_cast<char>(readByte());
        }

    public:
        BinToHexIStream(IStream& aStream) :
            mStream(aStream),
            mBufferSet(false)
        {}

        SOLAIRE_EXPORT_CALL ~BinToHexIStream() {
            //! \todo Handle trailing byte
        }

        // Inherited from IStream

        void SOLAIRE_EXPORT_CALL read(void* const aAddress, const uint32_t aBytes) throw() override {
            uint8_t* const ptr = static_cast<uint8_t*>(aAddress);
            for(uint32_t i = 0; i < aBytes; ++i) {
                ptr[i] = readByte();
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

        bool SOLAIRE_EXPORT_CALL end() const throw() override {
            return mStream.end() && ! mBufferSet;
        }

    };

}

#endif
