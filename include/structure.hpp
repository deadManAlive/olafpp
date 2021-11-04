#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>

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
}

namespace riffio{
    class Header{ //and Infos
        private:
            //part of file with exact size & position
            struct FHEAD { 
                uint8_t chunkID[4];        //4
                uint32_t chunkSize;     //4
                uint8_t format[4];         //4
                uint8_t subchunk1ID[4];    //4
                uint32_t subchunk1Size; //4
                uint16_t audioFormat;   //2
                uint16_t numChannels;   //2
                uint32_t sampleRate;    //4
                uint32_t byteRate;      //4
                uint16_t blockAlign;    //2
                uint16_t bitDepth;      //2
            } main_header;               //36

            //interpolated
            bool dataPosition;
        public:
            //C/D
            Header(std::ifstream& input_stream);

            //header methods
            size_t getFileSizeInBytes();
            uint16_t getAudioFormat();
            uint16_t getNumChannels();
            uint32_t getSampleRate();
            uint32_t getByteRate();
            uint16_t getBlockAlign();
            uint16_t getBitDepth();
            bool isRIFF();
            bool isWAVE();
    };

    class Data : public Header{
        private:
            std::vector<double> data_container;
        public:
            Data(std::ifstream& input_stream);
    };
}