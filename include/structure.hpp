#pragma once

#include <array>
#include <fmt/core.h>
#include <string>

namespace riff{
    typedef struct RIFFHEADER{
        char chunkID[4]; //"RIFF"
        uint32_t chunkSize; //total file size - (chunkID + chunkSize)
        char format[4]; //riff format
    } rhead;

    typedef struct WAVHEADER{
        char subchunk1ID[4]; //"fmt "
        uint32_t subchunk1Size;
        uint16_t audioFormat; //audio storage format (PCM,...)
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitDepths;
    } whead;

    template<typename T, uint32_t SIZE>
    struct wdata{
        char subchunk2ID[4]; //"data"
        uint32_t subchunk2Size;
        std::array<T, SIZE> data_container;
    };    
}

//RAII?
namespace structure{
    class rhead{
        private:
            char chunkID[4];
            uint32_t chunkSize;
            char format[4];
        public:
            std::string getChunkID(){
                return fmt::format("{}{}{}{}", chunkID[0], chunkID[1], chunkID[2], chunkID[3]);
            }
            uint32_t getChunkSize(){
                return chunkSize;
            }
            std::string getFormat(){
                return fmt::format("{}{}{}{}", format[0], format[1], format[2], format[3]);
            }
    };

    class whead{
        private:
            char subchunk1ID[4]; //"fmt "
            uint32_t subchunk1Size;
            uint16_t audioFormat; //audio storage format (PCM,...)
            uint16_t numChannels;
            uint32_t sampleRate;
            uint32_t byteRate;
            uint16_t blockAlign;
            uint16_t bitDepth;
        public:
            std::string getSubChunk1ID(){
                return fmt::format("{}{}{}{}", subchunk1ID[0], subchunk1ID[1], subchunk1ID[2], subchunk1ID[3]);
            }
            uint32_t getSubChunk1Size(){
                return subchunk1Size;
            }
            uint16_t getAudioFormat(){
                return audioFormat;
            }
            uint16_t getNumChannels(){
                return numChannels;
            }
            uint32_t getSampleRate(){
                return sampleRate;
            }
            uint32_t getByteRate(){
                return byteRate;
            }
            uint16_t getBlockAlign(){
                return blockAlign;
            }
            uint16_t getBitDepth(){
                return bitDepth;
            }
    };

    template<typename T, size_t SIZE>
    class wdata{
        private:
            char subchunk2ID[4];
            uint32_t subchunk2Size;
            std::array<T, SIZE> data_container;
        public:
            std::string getSubChunk2ID(){
                return fmt::format("{}{}{}{}", subchunk2ID[0], subchunk2ID[1], subchunk2ID[2], subchunk2ID[3]);
            }
            uint32_t getSubChunk2Size(){
                return subchunk2Size;
            }
            T getDataAt(size_t pos){
                return data_container.at(pos);
            }
            std::array<T, SIZE> getDataContainer(){
                return data_container;
            }
    };
}