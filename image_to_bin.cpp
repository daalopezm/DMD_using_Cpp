#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "headers.h"


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
    cv::resize(img, resizedImg, cv::Size(1280, 800));

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

