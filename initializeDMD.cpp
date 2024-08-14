#include <iostream>
#include <windows.h>
#include <cstdint>
#include "headers.h"

// Function to initialize the DMD
void initializeDMD(unsigned int& length, int16_t& deviceNumber, int16_t& DMDType) {
    


    // Check if the function pointers are valid
    if (!GetNumDev || !GetDMDTYPE || !SetWDT || !SetTPGEnable) {
        std::cerr << "Failed to get function pointers from the DLL." << std::endl;
        FreeLibrary(dllHandle);
        return;
    }

    // Check the number of connected devices
    int16_t numDevices = GetNumDev();
    std::cout << "Number of connected devices: " << numDevices << std::endl;

    // Define the device number
    deviceNumber = numDevices - 1;

    if (numDevices < 1) {
        std::cerr << "No DLP Discovery 4100 Development Platforms connected." << std::endl;
        FreeLibrary(dllHandle);
        return;
    }

    // A chunk should be at most 640000 bits
    unsigned int chunkSize = 512000 / 8;  // 640 kilobits chunks for DLP650LNIR
    length = chunkSize;

    // Get DMD type
    DMDType = GetDMDTYPE(deviceNumber);

    // Disable watchdog timer and internal pattern generation
    SetWDT(0, deviceNumber);
    SetTPGEnable(0, deviceNumber);

    // Free the DLL after usage
    // FreeLibrary(dllHandle);
}