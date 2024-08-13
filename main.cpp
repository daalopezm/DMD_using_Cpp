/*
You need opencv x32 bit. Usually, the source code is provided and you need to build
it. To do that, download opencv 4.10.0, cmake 3.30.2 x64 bit and 

cd C:\opencv\build
mkdir x32
cd x32
cmake -G "Visual Studio 17 2022" -A Win32 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=C:\opencv\build\x32\install C:\opencv\sources
cmake --build . --config Debug -- /p:Platform=Win32
cmake --install . --config Debug (optional)

Once build the requirements, proceed to build the project. Be aware of modify the CmakeLists.txt
according to any additional change in the files or extra required library. 
cmake -DCMAKE_TOOLCHAIN_FILE="../Win32Toolchain.cmake" ..
cmake --build . --config Debug -- /p:Platform=Win32
*/ 

#include "headers.h"
#include <cstdint>

int main() {
    // Load the DLL
    HMODULE dllHandle = LoadLibrary(TEXT("D4100_usb.dll"));

    if (!dllHandle) {
        std::cerr << "Failed to load the DLL." << std::endl;
        return 0;
    }
    // Initialize variables
    int totalRows = 16 * 50;
    int rowSize = 1280;

    std::vector<uint8_t> rowData0(totalRows * rowSize / 8, 0);   // Filled with 0s
    std::vector<uint8_t> rowData1(totalRows * rowSize / 8, 255); // Filled with 255s

    // Initialize the DMD
    unsigned int length;
    int16_t deviceNumber;
    int16_t DMDType;
    initializeDMD(dllHandle, length, deviceNumber, DMDType);

    std::cout << "Device Number: " << deviceNumber << std::endl;
    std::cout << "DMD Type: " << DMDType << std::endl;
    std::cout << "Chunk Size (length): " << length << std::endl;

    bool var = true;

    // Main loop to handle user input
    while (true) {
        std::cout << "Press 't' to test, 'l' to load an image, or 'q' to quit: ";
        char key = std::cin.get(); // Wait for user input

        if (key == 'q' || key == 'Q') {
            std::cout << "Exiting program." << std::endl;
            break;  // Exit the loop and close the program
        } else if (key == 't' || key == 'T') {
            // Run a test pattern
            std::cout << "Running test pattern (press q to quit) ..." << std::endl;
            // Infinite loop to alternate between rowData0 and rowData1
            char escape = 'p';
            while (escape != 'q' || escape != 'Q') {
                char escape_ = std::cin.get();
                escape = escape_;
                if (var) {
                    loadPattern(dllHandle, rowData0, length, DMDType, deviceNumber);
                    std::cout << "Running test pattern 0 ..." << std::endl;
                    var = false;
                } else {
                    loadPattern(dllHandle, rowData1, length, DMDType, deviceNumber);
                    std::cout << "Running test pattern 1 ..." << std::endl;
                    var = true;
                }
            }
            break;
        } else if (key == 'l' || key == 'L') {
            // Load and process the image
            std::string imagePath;
            std::cin.ignore(); // Clear the input buffer
            std::cout << "Enter the path to the image: ";
            std::getline(std::cin, imagePath);

            std::vector<uint8_t> binaryImgArray = image_to_bin(imagePath);
            std::cout << "Binary image array size: " << binaryImgArray.size() << std::endl;
            std::cout << "Initialization and image processing complete." << std::endl;

            // Load the pattern onto the DMD
            loadPattern(dllHandle, binaryImgArray, length, DMDType, deviceNumber);
        } else {
            std::cout << "Invalid input. Please press 't', 'l', or 'q'." << std::endl;
        }
    }

    FreeLibrary(GetModuleHandle(TEXT("D4100_usb.dll")));

    return 0;
}