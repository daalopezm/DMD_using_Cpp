#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdint>
#include "headers.h"


std::pair<std::vector<uint8_t>, std::vector<uint8_t>> splitPattern(const std::vector<uint8_t>& rowData, unsigned int length) {
    // Load first half of the screen
    std::vector<uint8_t> chunk1(rowData.begin(), rowData.begin() + length);
    // Load second half of the screen
    std::vector<uint8_t> chunk2(rowData.begin() + length, rowData.end());

    return std::make_pair(chunk1, chunk2);
}