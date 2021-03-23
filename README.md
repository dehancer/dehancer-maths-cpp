# dehancer-maths-cpp

## Requirements
Install: 
1. https://github.com/dnevera/base64cpp
1. https://github.com/dnevera/ed25519cpp
1. win32/mvsc+clang:  /c/vcpkg/vcpkg install openblas
1. win32/mvsc+clang:  /c/vcpkg/vcpkg install lapack

Windows GCC
=======

    # mingw
    # Install https://www.msys2.org/
    # https://blog.jetbrains.com/clion/2020/12/setting-up-clang-on-windows/

    pacman -S mingw-w64-x86_64-toolchain
    pacman -S mingw-w64-x86_64-clang
    pacman -S mingw-w64-x86_64-cmake
    pacman -S libcurl
    pacman -S zlib-devel
    pacman -S libcurl-devel


Windows MVSC
=======
    # Requrements: 
    # Visual Studio, English Language Pack!
    # https://vcpkg.info/
    # GitBash

    cd C:
    git clone https://github.com/microsoft/vcpkg
    cd /c/vcpkg/
    ./bootstrap-vcpkg.sh
    /c/vcpkg/vcpkg integrate install
    /c/vcpkg/vcpkg install gtest

    # cmake integration
    -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake