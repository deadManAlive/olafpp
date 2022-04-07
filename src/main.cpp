#include <string>
#include <fmt/core.h>
#include <sndfile.hh>
#include <chrono>
#include <filesystem>

#include <convolve.h>

namespace fs = std::filesystem;

int main(int argc, char **argv){
    //================CLI args test======================//

    if(argc < 2){
        fmt::print("No file provided!\n");
        return 2;
    }

    //================OPENING FILE=======================//

    fs::path sample_file(argv[1]);
    
    if(!fs::exists(sample_file)){
        fmt::print(fmt::format("File \"{}\" not found!\n", argv[1]));
        return 2;
    }

    SndfileHandle file = SndfileHandle(sample_file.string().c_str());

    fmt::print(fmt::format("Opened {} from {}.\n", sample_file.filename().string(), fs::absolute(sample_file).string()));
    fmt::print(fmt::format("    Sample rate : {}\n", file.samplerate()));
    fmt::print(fmt::format("    Channels    : {}\n", file.channels()));

    stream_t samples(file.frames());
    file.read(&samples[0], int(file.frames()));

    fmt::print(fmt::format("    Samples     : {}\n", samples.size()));

    // check http://www.mega-nerd.com/libsndfile/api.html#note2 for formats
    auto type = file.format() & SF_FORMAT_TYPEMASK;
    auto subtype = file.format() & SF_FORMAT_SUBMASK;

    fmt::print(fmt::format("    Type        : {:#04x}\n", type));
    fmt::print(fmt::format("    Subtype     : {:#04x}\n", subtype));

    //================PRE-PROCESS: DEINTERLEAVE==========//

    split_t splitchannel;

    try{
        splitchannel = deinterleave(samples, file.channels());
    }
    catch(std::exception const& err){
        fmt::print(fmt::format("{}\n", err.what()));
    }//TODO: deinterlevae-then-convolve OR convolve-with-deinterleave implementation??

    //================CONVOLUTION========================//

    stream_t impulse{1, 1/4.0, 1/16.0};

    auto start = std::chrono::high_resolution_clock::now(); //clock in

    stream_t res = convolve(samples, impulse); //res to output, TODO:APPARENTLY DATA ARE INTERLEAVED IN THE BUFFER:deil func. written

    auto stop = std::chrono::high_resolution_clock::now(); //clock out
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //================POST PROCESS & SAVE================//

    fmt::print(fmt::format("Finished convolving {} by {} = {} samples in {} ms.\n", samples.size(), impulse.size(), res.size(), duration.count()));

    std::string output_file = fmt::format("{}/{}_OUT{}", sample_file.parent_path().string(), sample_file.stem().string(), sample_file.extension().string());

    // if(fs::exists(output_file)){
    //     fmt::print(fmt::format("Can't write {}. The file already exists!\n", output_file));
    //     return 2;
    // }

    SndfileHandle result = SndfileHandle(output_file.c_str(), SFM_WRITE, file.format(), file.channels(), file.samplerate());

    result.write(&res[0], static_cast<sf_count_t>(res.size()));

    fmt::print(fmt::format("Output saved as {}\n", output_file));

    return 0;
}