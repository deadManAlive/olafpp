#pragma once

namespace riff{
    typedef struct RIFFHEADER{
        char chunkID[4]; //"RIFF"
        uint32_t chunkSize; //total file size - (chunkID + chunkSize)
        char format[4]; //riff format
    } rhead;

    typedef struct WAVHEADER{
        //WAV header (if RIFFHEADER.format == "WAVE")
        char subchunk1ID[4]; //"fmt "
        uint32_t subchunk1Size;
        uint16_t audioFormat; //audio storage format (PCM,...)
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitDepths;
    } whead;

    typedef struct WAVDATA{
        char subchunk2ID[4]; //"data"
        uint32_t subchunk2Size;
        void *data; //here we go again...
    } wdata;
}