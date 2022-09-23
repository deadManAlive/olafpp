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

split_t deinterleave(stream_t framesstream, size_t nchannel, bool force_channel_equal_size){
    auto nframe = framesstream.size();

    if(nframe%nchannel != 0 && force_channel_equal_size){
        throw std::length_error{
            "Channels have different sizes"
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

stream_t interleave(split_t splitstream, size_t nchannel){
    size_t nframe = nchannel * splitstream[0].size();

    stream_t ilstream(nframe);

    for(size_t i = 0, j = 0; i < nframe; j++){
        for(size_t k = 0; k < nchannel && i < nframe; k++, i++){ //redundant channel size checking?
            ilstream[i] = splitstream[k][j];
        }
    }

    return ilstream;
}

stream_t convolveMultiChannel(stream_t impulse, stream_t framesstream, size_t nchannel){ //mono impulse, multi channel stream. TODO; multichannel impulse by FOR_EACH
    //deinterleave interleaved input
    split_t deIL    = deinterleave(framesstream, nchannel);

    //multichannel convolution result container
    split_t cres    = split_t(nchannel, stream_t(impulse.size() + deIL[0].size() - 1));

    //per channel convolution result container
    stream_t cchn  = stream_t(impulse.size() + deIL[0].size() - 1);

    for(size_t i = 0; i < nchannel; i++){

    }

    return interleave(cres, nchannel);
}