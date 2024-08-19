#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdint>
#include "headers.h"


// Function to load the pattern onto the DMD
void loadPattern(std::vector<uint8_t>& chunk1, std::vector<uint8_t>& chunk2, bool& loaded_chunk1, bool& loaded_chunk2, int16_t& DMDType, int16_t& deviceNumber, unsigned int length) {

    // Load half of the screen
    SetRowMd(2, deviceNumber); // DMD Row Address 0
    SetRowAddr(0, deviceNumber);
    LoadControl(deviceNumber);    
    loaded_chunk1 = LoadData(chunk1.data(), length, DMDType, deviceNumber);

    // Load second half of the screen
    SetRowMd(2, deviceNumber); // DMD Row Address 400
    SetRowAddr(400, deviceNumber);
    LoadControl(deviceNumber);
    loaded_chunk2 = LoadData(chunk2.data(), length, DMDType, deviceNumber);
}


