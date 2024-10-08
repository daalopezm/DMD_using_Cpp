#ifndef HEADERS
#define HEADERS

#include <vector>
#include <string>
#include <windows.h>
#include <opencv2/opencv.hpp>


// Function to load and process the image into a binary image array
std::vector<uint8_t> image_to_bin(const std::string& imagePath);
void initializeDMD(HMODULE& dllHandle, unsigned int& length, int16_t& deviceNumber, int16_t& DMDType);
void loadPattern(HMODULE& dllHandle, const std::vector<uint8_t>& rowData, unsigned int length, int16_t& DMDType, int16_t& deviceNumber);


#endif // HEADERS
