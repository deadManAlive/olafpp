#pragma once

#include <vector>

template <typename T>
auto convolve(std::vector<T> m1, std::vector<T> m2){
    std::vector<T> res(m1.size() + m2.size() - 1);

    for(size_t i = 0, j; i < m1.size(); i++){
        j = i;
        for(const auto em2 : m2){
            res[j++] += m1[i] * em2;
        }
    }

    return res;
}
