#pragma once

#include <vector>

using split_t = std::vector<std::vector<double>>; //channel-split in vector of vectors
using stream_t = std::vector<double>; //std::vector alias for unsplitted stream

std::vector<double> convolve(stream_t m1, std::vector<double> m2);
split_t deinterleave(stream_t framesstream, int nchannel, bool force_channel_equal_size = true);
stream_t interleave(split_t splitstream, int nchannel);
