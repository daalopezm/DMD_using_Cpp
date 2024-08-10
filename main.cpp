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

int main() {
    unsigned int length;
    int16_t deviceNumber;
    int16_t DMDType;

    
    // Load and process the image
    std::string imagePath = "./che.jpg"; // Replace with your actual image path
    std::vector<uint8_t> binaryImgArray = image_to_bin(imagePath);
    


    std::cout << "Binary image array size: " << binaryImgArray.size() << std::endl;
    std::cout << "Initialization and image processing complete." << std::endl;


    // Initialize the DMD
    initializeDMD(length, deviceNumber, DMDType);
    std::cout << "Device Number: " << deviceNumber << std::endl;
    std::cout << "DMD Type: " << DMDType << std::endl;
    std::cout << "Chunk Size (length): " << length << std::endl;
    loadPattern(binaryImgArray, length, DMDType, deviceNumber);

    // Wait for the user to press the 'q' key to exit
    std::cout << "Press 'q' to exit the program." << std::endl;
    while (true) {
        char key = cv::waitKey(0); // Wait for a key press indefinitely
        if (key == 'q' || key == 'Q') {  // Check if the key is 'q' or 'Q'
            std::cout << "Exiting program." << std::endl;
            break;  // Exit the loop and close the program
        }
    }
    return 0;
}