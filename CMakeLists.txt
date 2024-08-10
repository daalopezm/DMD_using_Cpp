cmake_minimum_required(VERSION 3.10)

# Project Name
project(DMDcontrol)

# Ensure the project is built for 32-bit architecture
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "This project is configured to build as a 32-bit application.")
endif()

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Specify the path to OpenCVConfig.cmake
set(OpenCV_DIR "C:/openCV/build/x32")

# Specify the path to the 32-bit libraries and include directories
include_directories("C:/opencv/build/include")
link_directories("C:/opencv/build/x32/lib")

# Include custom headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add the executable
add_executable(DMDControl main.cpp image_to_bin.cpp initializeDMD.cpp)

# Link against OpenCV libraries
target_link_libraries(DMDControl ${OpenCV_LIBS})
