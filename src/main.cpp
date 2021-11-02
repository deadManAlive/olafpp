#include <iostream>
#include <string>
#include <fmt/core.h>

#include "structure.hpp"
// #include "util.hpp"

int main(int argc, char **argv){
    if(argc < 2){
        fmt::print("No file provided!\n");
        return -1;
    }

    FILE* file_handle = fopen(argv[1], "rb");
    if(!file_handle){
        fmt::print(fmt::format("Cannot open {}!\n", argv[1]));
        return -2;
    }
    fmt::print(fmt::format("Opening {}...\n", argv[1]));

    riff::rhead sample_riff_header_buffer;
    // whead sample_wav_header_buffer;
    // wdata sample_wav_data_buffer;

    fread(&sample_riff_header_buffer, 12, 1, file_handle);
    
    //==RIFF HEADER==//
    //RIFF header display
    fmt::print(fmt::format("RIFFHEADER:\t\t{}{}{}{}\n", sample_riff_header_buffer.chunkID[0], sample_riff_header_buffer.chunkID[1], sample_riff_header_buffer.chunkID[2], sample_riff_header_buffer.chunkID[3]));

    //RIFF size display
    fmt::print(fmt::format("TOTALSIZE:\t\t{} + 8 bytes\n", sample_riff_header_buffer.chunkSize));

    //RIFF format display
    std::string srform = fmt::format("{}{}{}{}", sample_riff_header_buffer.format[0], sample_riff_header_buffer.format[1], sample_riff_header_buffer.format[2], sample_riff_header_buffer.format[3]);
    fmt::print(fmt::format("RIFFFORMAT:\t\t{}\n", srform));

    //WAV test
    if(srform.compare("WAVE") != 0){
        printf("This file is not supported!");
        fmt::print("This file is not supported!");
        fclose(file_handle);
        return -3;
    }

    fclose(file_handle);
    return 0;
}