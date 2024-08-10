#include <iostream>
#include <windows.h>
#include <cstdint>
#include "headers.h"

// Function to initialize the DMD
void initializeDMD(unsigned int& length, int16_t& deviceNumber, int16_t& DMDType) {
    // Load the DLL
    HMODULE dllHandle = LoadLibrary(TEXT("D4100_usb.dll"));
    if (!dllHandle) {
        std::cerr << "Failed to load the DLL." << std::endl;
        return;
    }

    // Function pointer declarations for the DLL functions
    typedef int16_t(*GetNumDevFunc)();
    typedef int16_t(*GetDMDTYPEFunc)(int16_t);
    typedef int16_t(*SetWDTFunc)(int16_t, int16_t);
    typedef int16_t(*SetTPGEnableFunc)(int16_t, int16_t);

    // Get function pointers to the functions from the DLL
    GetNumDevFunc GetNumDev = (GetNumDevFunc)GetProcAddress(dllHandle, "GetNumDev");
    GetDMDTYPEFunc GetDMDTYPE = (GetDMDTYPEFunc)GetProcAddress(dllHandle, "GetDMDTYPE");
    SetWDTFunc SetWDT = (SetWDTFunc)GetProcAddress(dllHandle, "SetWDT");
    SetTPGEnableFunc SetTPGEnable = (SetTPGEnableFunc)GetProcAddress(dllHandle, "SetTPGEnable");

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