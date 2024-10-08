# Check if the 'build' directory exists
if (-Not (Test-Path -Path "./build")) {
    # If it doesn't exist, create it
    mkdir "./build"
}

# Navigate into the 'build' directory
cd "./build"

# Run CMake with the toolchain file
cmake -DCMAKE_TOOLCHAIN_FILE="../Win32Toolchain.cmake" ..

# Build the project in Debug mode for Win32 platform
cmake --build . --config Debug -- /p:Platform=Win32

# Copy the file to the 'copies' directory inside 'build'
Copy-Item -Path "../D4100_usb.dll" -Destination "./Debug/D4100_usb.dll" -Force

cd ..