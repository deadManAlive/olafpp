#include <string>
#include <fmt/core.h>
#include <exception>

#include <structure.hpp>

using namespace riffio;

Header::Header(std::ifstream& input_stream){

    input_stream.read(reinterpret_cast<char*>(&main_header), 36);
}

size_t Header::getFileSizeInBytes(){
    return main_header.chunkSize + 8;
}

uint16_t Header::getAudioFormat(){
    return main_header.audioFormat;
}

uint16_t Header::getNumChannels(){
    return main_header.numChannels;
}

uint32_t Header::getSampleRate(){
    return main_header.sampleRate;
}

uint32_t Header::getByteRate(){
    return main_header.byteRate;
}

uint16_t Header::getBlockAlign(){
    return main_header.blockAlign;
}

uint16_t Header::getBitDepth(){
    return main_header.bitDepth;
}

bool Header::isRIFF(){
    return fmt::format("{}{}{}{}", main_header.chunkID[0], main_header.chunkID[1], main_header.chunkID[2], main_header.chunkID[3]).compare("RIFF") == 0 ? true : false;
}

bool Header::isWAVE(){
    return fmt::format("{}{}{}{}", main_header.subchunk1ID[0], main_header.subchunk1ID[1], main_header.subchunk1ID[2], main_header.subchunk1ID[3]).compare("WAVE") == 0 ? true : false;
}

Data::Data(std::ifstream& input_stream) : Header(input_stream){
    
}