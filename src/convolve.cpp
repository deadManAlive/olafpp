#include <convolve.h>
#include <stdexcept>

std::vector<double> convolve(stream_t m1, stream_t m2){
    stream_t res(m1.size() + m2.size() - 1);

    for(size_t i = 0, j; i < m1.size(); i++){
        j = i;
        for(const auto em2 : m2){
            res[j++] += m1[i] * em2;
        }
    }

    return res;
}

split_t deinterleave(stream_t framesstream, int nchannel, bool force_channel_equal_size){
    auto nframe = framesstream.size();

    if(nframe%nchannel != 0 && force_channel_equal_size){
        throw std::length_error{
            "Channels have different size"
        };
    }

    split_t chbuffer(nchannel);

    for(auto& c : chbuffer){
        c.reserve(nframe/2);
    }

    for(size_t i = 0; i < nframe; i++){
        chbuffer[i%nchannel].push_back(framesstream[i]);
    }

    return chbuffer;
}

stream_t interleave(split_t splitstream, int nchannel){
    size_t nframe = 0;

    for(const auto& channel : splitstream){
        for(const auto& s : channel){
            nframe++;
        }
    }

    stream_t ilstream(nframe);

    for(size_t i = 0, j = 0; i < nframe; j++){
        for(size_t k = 0; k < static_cast<size_t>(nchannel) && i < nframe; k++, i++){ //redundant channel size checking?
            ilstream[i] = splitstream[k][j];
        }
    }

    return ilstream;
}
