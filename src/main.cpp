#include <string>
#include <fmt/core.h>
#include <sndfile.hh>

#include <structure.hpp>

int main(int argc, char **argv){
    if(argc < 2){
        fmt::print("No file provided!\n");
        return -1;
    }

    fmt::print(fmt::format("{} \n", argv[1]));

    SndfileHandle file(argv[1]);

    // return 0;

    fmt::print(fmt::format("Opened {}.\n", argv[1]));
    fmt::print(fmt::format("    Sample rate : {}\n", file.samplerate()));
    fmt::print(fmt::format("    Channels    : {}\n", file.channels()));

    return 0;
}