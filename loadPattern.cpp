#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdint>
#include "headers.h"

// Function to load the pattern onto the DMD
void loadPattern(const std::vector<uint8_t>& rowData, unsigned int length, int16_t& DMDType, int16_t& deviceNumber) {

    // Load first half of the screen
    std::vector<uint8_t> chunk(rowData.begin(), rowData.begin() + length);

    SetRowMd(2, deviceNumber); // DMD Row Address 0
    SetRowAddr(0, deviceNumber);
    LoadControl(deviceNumber);
    //SetRowMd(3, deviceNumber); // Set First row address
    //SetNSFLIP(0, deviceNumber); // Causes the DLPC410 to reverse order of row loading, effectively flipping the image
    //LoadControl(deviceNumber); // DMD Block Operations -- Execute!

    //SetRowMd(1, deviceNumber); //If RowMd==1 and NSFLIP==0 Increment internal row address by '1' - write concurrent data into that row
    //SetNSFLIP(0, deviceNumber);
    //LoadControl(deviceNumber); // DMD Block Operations -- Execute!

    //ClearFifos(deviceNumber);
    LoadData(chunk.data(), length, DMDType, deviceNumber);

    // Load second half of the screen
    chunk.assign(rowData.begin() + length, rowData.end());

    SetRowMd(2, deviceNumber); // DMD Row Address 400
    SetRowAddr(400, deviceNumber);
    LoadControl(deviceNumber);

    //SetRowMd(1, deviceNumber); //If RowMd==1 and NSFLIP==0 Increment internal row address by '1' - write concurrent data into that row
    //SetNSFLIP(0, deviceNumber);
    //LoadControl(deviceNumber);

    //ClearFifos(deviceNumber);
    LoadData(chunk.data(), length, DMDType, deviceNumber);

    // Free the DLL after usage
    //FreeLibrary(dllHandle);
}


