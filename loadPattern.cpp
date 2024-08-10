#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdint>
#include "headers.h"

// Function to load the pattern onto the DMD
void loadPattern(const std::vector<uint8_t>& rowData, unsigned int length, int16_t& DMDType, int16_t& deviceNumber) {
    // Load the DLL
    HMODULE dllHandle = LoadLibrary(TEXT("D4100_usb.dll"));
    if (!dllHandle) {
        std::cerr << "Failed to load the DLL." << std::endl;
        return;
    }

    // Function pointer declarations for the DLL functions
    typedef int16_t(*SetBlkMdFunc)(int16_t, int16_t);
    typedef int16_t(*LoadControlFunc)(int16_t);
    typedef int16_t(*ClearFifosFunc)(int16_t);
    typedef int16_t(*SetRowMdFunc)(int16_t, int16_t);
    typedef int16_t(*SetNSFLIPFunc)(int16_t, int16_t);
    typedef int (*LoadDataFunc)(const uint8_t*, unsigned int, int16_t, int16_t);
    typedef int16_t(*SetBlkAdFunc)(int16_t, int16_t);
    typedef int16_t(*SetRowAddrFunc)(int16_t, int16_t);

    // Get function pointers to the functions from the DLL
    SetBlkMdFunc SetBlkMd = (SetBlkMdFunc)GetProcAddress(dllHandle, "SetBlkMd");
    LoadControlFunc LoadControl = (LoadControlFunc)GetProcAddress(dllHandle, "LoadControl");
    ClearFifosFunc ClearFifos = (ClearFifosFunc)GetProcAddress(dllHandle, "ClearFifos");
    SetRowMdFunc SetRowMd = (SetRowMdFunc)GetProcAddress(dllHandle, "SetRowMd");
    SetNSFLIPFunc SetNSFLIP = (SetNSFLIPFunc)GetProcAddress(dllHandle, "SetNSFLIP");
    LoadDataFunc LoadData = (LoadDataFunc)GetProcAddress(dllHandle, "LoadData");
    SetBlkAdFunc SetBlkAd = (SetBlkAdFunc)GetProcAddress(dllHandle, "SetBlkAd");
    SetRowAddrFunc SetRowAddr = (SetRowAddrFunc)GetProcAddress(dllHandle, "SetRowAddr");

    if (!SetBlkMd || !LoadControl || !ClearFifos || !SetRowMd || !SetNSFLIP || !LoadData || !SetBlkAd || !SetRowAddr) {
        std::cerr << "Failed to get function pointers from the DLL." << std::endl;
        FreeLibrary(dllHandle);
        return;
    }

    // Load first half of the screen
    std::vector<uint8_t> chunk(rowData.begin(), rowData.begin() + length);

    SetBlkMd(0, deviceNumber);
    LoadControl(deviceNumber);
    ClearFifos(deviceNumber);

    SetRowMd(3, deviceNumber);
    SetNSFLIP(0, deviceNumber);
    LoadControl(deviceNumber);

    SetRowMd(1, deviceNumber);
    SetNSFLIP(0, deviceNumber);
    LoadControl(deviceNumber);

    ClearFifos(deviceNumber);
    LoadData(chunk.data(), length, DMDType, deviceNumber);
    SetBlkMd(3, deviceNumber);
    SetBlkAd(8, deviceNumber);
    LoadControl(deviceNumber);

    SetBlkMd(0, deviceNumber);
    LoadControl(deviceNumber);

    // Load second half of the screen
    chunk.assign(rowData.begin() + length, rowData.end());

    SetRowMd(2, deviceNumber);
    SetRowAddr(400, deviceNumber);
    LoadControl(deviceNumber);

    SetRowMd(1, deviceNumber);
    SetNSFLIP(0, deviceNumber);
    LoadControl(deviceNumber);

    ClearFifos(deviceNumber);
    LoadData(chunk.data(), length, DMDType, deviceNumber);
    SetBlkMd(3, deviceNumber);
    SetBlkAd(8, deviceNumber);
    LoadControl(deviceNumber);

    // Free the DLL after usage
    FreeLibrary(dllHandle);
}


