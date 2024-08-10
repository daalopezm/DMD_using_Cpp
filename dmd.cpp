#include <iostream>
#include <windows.h>
#include <opencv.hpp>
#include <vector>

// Function to initialize the DMD
void initializeDMD(unsigned int& length, int& deviceNumber, int& DMDType) {
    // Load the DLL
    HMODULE dllHandle = LoadLibrary(TEXT("D4100_usb.dll"));
    if (!dllHandle) {
        std::cerr << "Failed to load the DLL." << std::endl;
        return;
    }

    // Function pointer declarations for the DLL functions
    typedef int(*GetNumDevFunc)();
    typedef int(*GetDMDTYPEFunc)(int);
    typedef int(*SetWDTFunc)(int, int);
    typedef int(*SetTPGEnableFunc)(int, int);

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
    int numDevices = GetNumDev();
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

// Function to load and process the image into a binary image array
std::vector<uint8_t> image_to_bin(const std::string& imagePath) {
    // Load the image
    cv::Mat img = cv::imread(imagePath);
    if (img.empty()) {
        std::cerr << "Error loading image!" << std::endl;
        return std::vector<uint8_t>();
    }

    // Resize the image to 1280x800
    cv::Mat resizedImg;
    cv::resize(img, resizedImg, cv::Size(800, 1280));

    // Convert to grayscale if the image is in color
    cv::Mat grayImg;
    if (resizedImg.channels() == 3) {
        cv::cvtColor(resizedImg, grayImg, cv::COLOR_BGR2GRAY);
    } else {
        grayImg = resizedImg;
    }

    // Binarize the image using a global threshold (Otsu's method)
    cv::Mat binaryImg;
    double threshold = cv::threshold(grayImg, binaryImg, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Convert binary image to 1-bit format (uint8_t)
    std::vector<uint8_t> binaryImgArray(binaryImg.rows * binaryImg.cols / 8, 0);
    for (int y = 0; y < binaryImg.rows; ++y) {
        for (int x = 0; x < binaryImg.cols; ++x) {
            if (binaryImg.at<uint8_t>(y, x) > 0) {
                binaryImgArray[(y * binaryImg.cols + x) / 8] |= (1 << (7 - (x % 8)));
            }
        }
    }

    // Display the original, resized, and binary images
    cv::imshow("Original Image", img);
    cv::imshow("Resized Image (1280x800)", resizedImg);
    cv::imshow("Binary Image", binaryImg);
    cv::waitKey(0); // Wait for a key press to close the images

    return binaryImgArray;
}


// Function to load the pattern onto the DMD
void loadPattern(const std::vector<uint8_t>& rowData, unsigned int length, int DMDType, short deviceNumber) {
    // Load the DLL
    HMODULE dllHandle = LoadLibrary(TEXT("D4100_usb.dll"));
    if (!dllHandle) {
        std::cerr << "Failed to load the DLL." << std::endl;
        return;
    }

    // Function pointer declarations for the DLL functions
    typedef int(*SetBlkMdFunc)(int, short);
    typedef int(*LoadControlFunc)(short);
    typedef int(*ClearFifosFunc)(short);
    typedef int(*SetRowMdFunc)(int, short);
    typedef int(*SetNSFLIPFunc)(int, short);
    typedef int(*LoadDataFunc)(const uint8_t*, unsigned int, int, short);
    typedef int(*SetBlkAdFunc)(int, short);
    typedef int(*SetRowAddrFunc)(int, short);

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

int main() {
    unsigned int length;
    short deviceNumber;
    int DMDType;

    // Initialize the DMD
    initializeDMD(length, deviceNumber, DMDType);

    // Load and process the image
    std::string imagePath = "path_to_your_image.jpg"; // Replace with your actual image path
    std::vector<uint8_t> binaryImgArray = image_to_bin(imagePath);

    std::cout << "Initialization and image processing complete." << std::endl;
    std::cout << "Chunk Size (length): " << length << std::endl;
    std::cout << "Device Number: " << deviceNumber << std::endl;
    std::cout << "DMD Type: " << DMDType << std::endl;
    std::cout << "Binary image array size: " << binaryImgArray.size() << std::endl;

    return 0;
}
