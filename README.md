## DMD Code in c++, 
CPP code to run a DMD DLP650LNIR with Discover 4100 controller. You can upload images. 
Opencv x32 bit is required. Usually, the source code is provided and you need to build
it. To do that, download opencv 4.10.0, cmake 3.30.2 x64 bit and run the following in powershell of whatever terminal you use:

``cd C:\opencv\build
mkdir x32
cd x32
cmake -G "Visual Studio 17 2022" -A Win32 -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=C:\opencv\build\x32\install C:\opencv\sources
cmake --build . --config Debug -- /p:Platform=Win32
cmake --install . --config Debug (optional)``

Once build the requirements, proceed to build the project. Be aware of modify the CmakeLists.txt
according to any additional change in the files or extra required library. 
``cmake -DCMAKE_TOOLCHAIN_FILE="../Win32Toolchain.cmake" ..
cmake --build . --config Debug -- /p:Platform=Win32``

The main.cpp run all the necesary functions and also loads the library. The executable can be found in ./build/Debug.
To build the code, run the powersell script "build_project.ps1". 

# References
- [DLP® Discovery™ 4100 Development Kit Technical Reference Manual User's Guide](https://www.ti.com/lit/ug/dlpu053/dlpu053.pdf)
- [DLPC410 DMD Digital Controller](https://www.ti.com/lit/ds/dlps024g/dlps024g.pdf?ts=1718122328291)
- [DLPD4X00KIT: Question for LoadData function in USB DLL API](https://e2e.ti.com/support/dlp-products-group/dlp/f/dlp-products-forum/830823/dlpd4x00kit-question-for-loaddata-function-in-usb-dll-api)
- [DLPD4X00KIT: Download my binary patterns to the DMD( DLP4100 & DLP7000 ) with USB DLL API.](https://e2e.ti.com/support/dlp-products-group/dlp/f/dlp-products-forum/827507/dlpd4x00kit-download-my-binary-patterns-to-the-dmd-dlp4100-dlp7000-with-usb-dll-api) 
- [Files to extend this project](https://e2e.ti.com/support/dlp-products-group/dlp/f/dlp-products-forum/812675/dlplcrc410evm-comunicate-with-the-dlplcrc410evm-through-matlab-or-python/3018700#3018700)
