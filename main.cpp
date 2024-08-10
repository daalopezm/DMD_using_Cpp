/*
to build 
cmake -DCMAKE_TOOLCHAIN_FILE="../Win32Toolchain.cmake" ..
cmake --build . --config Debug -- /p:Platform=Win32
*/ 

#include "headers.h"

int main() {
    unsigned int length;
    int16_t deviceNumber;
    int16_t DMDType;

    // Initialize the DMD
    initializeDMD(length, deviceNumber, DMDType);
    // Load and process the image
    std::string imagePath = "./che.jpg"; // Replace with your actual image path
    std::vector<uint8_t> binaryImgArray = image_to_bin(imagePath);

    std::cout << "Binary image array size: " << binaryImgArray.size() << std::endl;
    std::cout << "Initialization and image processing complete." << std::endl;
    std::cout << "Chunk Size (length): " << length << std::endl;
    std::cout << "Device Number: " << deviceNumber << std::endl;
    std::cout << "DMD Type: " << DMDType << std::endl;
    std::cout << "Binary image array size: " << binaryImgArray.size() << std::endl;

    return 0;
}