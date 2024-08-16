#ifndef HEADERS
#define HEADERS

#include <vector>
#include <string>
#include <windows.h>
#include <utility>
#include <opencv2/opencv.hpp>

// Function pointer declarations for the DLL functions
typedef int16_t(*GetNumDevFunc)();
typedef int16_t(*GetDMDTYPEFunc)(int16_t);
typedef int16_t(*SetWDTFunc)(int16_t, int16_t);
typedef int16_t(*SetTPGEnableFunc)(int16_t, int16_t);
typedef int16_t(*SetBlkMdFunc)(int16_t, int16_t);
typedef int16_t(*LoadControlFunc)(int16_t);
typedef int16_t(*ClearFifosFunc)(int16_t);
typedef int16_t(*SetRowMdFunc)(int16_t, int16_t);
typedef int16_t(*SetNSFLIPFunc)(int16_t, int16_t);
typedef int (*LoadDataFunc)(const uint8_t*, unsigned int, int16_t, int16_t);
typedef int16_t(*SetBlkAdFunc)(int16_t, int16_t);
typedef int16_t(*SetRowAddrFunc)(int16_t, int16_t);

// Declare external variables and function pointers
extern HMODULE dllHandle;
extern GetNumDevFunc GetNumDev;
extern GetDMDTYPEFunc GetDMDTYPE;
extern SetWDTFunc SetWDT;
extern SetTPGEnableFunc SetTPGEnable;
extern SetBlkMdFunc SetBlkMd;
extern LoadControlFunc LoadControl;
extern ClearFifosFunc ClearFifos;
extern SetRowMdFunc SetRowMd;
extern SetNSFLIPFunc SetNSFLIP;
extern LoadDataFunc LoadData;
extern SetBlkAdFunc SetBlkAd;
extern SetRowAddrFunc SetRowAddr;


// Function declarations
std::vector<uint8_t> image_to_bin(const std::string& imagePath);
void initializeDMD(unsigned int& length, int16_t& deviceNumber, int16_t& DMDType);
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> splitPattern(const std::vector<uint8_t>& rowData, unsigned int length);
void loadPattern(std::vector<uint8_t>& chunk1, std::vector<uint8_t>& chunk2, bool& loaded_chunk1, bool& loaded_chunk2, int16_t& DMDType, int16_t& deviceNumber, unsigned int length);

#endif // HEADERS
