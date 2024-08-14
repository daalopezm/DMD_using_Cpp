#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdint>
#include "headers.h"

// Function to load the pattern onto the DMD
void loadPattern(const std::vector<uint8_t>& rowData, unsigned int length, int16_t& DMDType, int16_t& deviceNumber) {

    // Get function pointers to the functions from the DLL


    if (!SetBlkMd || !LoadControl || !ClearFifos || !SetRowMd || !SetNSFLIP || !LoadData || !SetBlkAd || !SetRowAddr) {
        std::cerr << "Failed to get function pointers from the DLL." << std::endl;
        FreeLibrary(dllHandle);
        return;
    }

    // Load first half of the screen
    std::vector<uint8_t> chunk(rowData.begin(), rowData.begin() + length);

    //SetBlkMd(0, deviceNumber); // DMD Block Operations -- NOP
    //LoadControl(deviceNumber); // DMD Block Operations -- Execute!
    //ClearFifos(deviceNumber);

    SetRowMd(3, deviceNumber); // Set First row address
    SetNSFLIP(0, deviceNumber); // Causes the DLPC410 to reverse order of row loading, effectively flipping the image
    LoadControl(deviceNumber); // DMD Block Operations -- Execute!

    SetRowMd(1, deviceNumber); //If RowMd==1 and NSFLIP==0 Increment internal row address by '1' - write concurrent data into that row
    SetNSFLIP(0, deviceNumber);
    LoadControl(deviceNumber); // DMD Block Operations -- Execute!

    ClearFifos(deviceNumber);
    LoadData(chunk.data(), length, DMDType, deviceNumber);
    //SetBlkMd(3, deviceNumber); // Global Reset Request
    //SetBlkAd(8, deviceNumber);
    //LoadControl(deviceNumber);

    //SetBlkMd(0, deviceNumber); // DMD Block Operations -- NOP
    //LoadControl(deviceNumber);

    // Load second half of the screen
    chunk.assign(rowData.begin() + length, rowData.end());

    SetRowMd(2, deviceNumber); // DMD Row Address 400
    SetRowAddr(400, deviceNumber);
    LoadControl(deviceNumber);

    SetRowMd(1, deviceNumber); //If RowMd==1 and NSFLIP==0 Increment internal row address by '1' - write concurrent data into that row
    SetNSFLIP(0, deviceNumber);
    LoadControl(deviceNumber);

    ClearFifos(deviceNumber);
    LoadData(chunk.data(), length, DMDType, deviceNumber);
    //SetBlkMd(3, deviceNumber);
    //SetBlkAd(8, deviceNumber);
    //LoadControl(deviceNumber);

    // Free the DLL after usage
    //FreeLibrary(dllHandle);
}


