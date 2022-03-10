#include <string>
#include <fmt/core.h>
#include <sndfile.hh>
#include <chrono>
#include <filesystem>

#include <convolve.h>

int main(int argc, char **argv){
    if(argc < 2){
        fmt::print("No file provided!\n");
        return 2;
    }
    else if(!std::filesystem::exists(argv[1])){
        fmt::print(fmt::format("File \"{}\" not found!\n", argv[1]));
        return 2;
    }

    //================OPENING FILE================//

    SndfileHandle file = SndfileHandle(argv[1]);

    fmt::print(fmt::format("Opened {}.\n", argv[1]));
    fmt::print(fmt::format("    Sample rate : {}\n", file.samplerate()));
    fmt::print(fmt::format("    Channels    : {}\n", file.channels()));
    fmt::print(fmt::format("    Format      : {}\n", file.format()));

    std::vector<double> samples(file.frames());
    file.read(&samples[0], int(file.frames()));

    fmt::print(fmt::format("    Samples     : {}\n", samples.size()));

    //================CONVOLUTION================

    std::vector<double> impulse{1, 0.5, 0.25, 0.125};

    auto start = std::chrono::high_resolution_clock::now(); //clock in

    std::vector<double> res = convolve(samples, impulse); //res to output

    auto stop = std::chrono::high_resolution_clock::now(); //clock out
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //================POST PROCESS================

    fmt::print(fmt::format("Finished convolving {} by {} samples in {} ms.\n", samples.size(), impulse.size(), duration.count()));

    return 0;
}