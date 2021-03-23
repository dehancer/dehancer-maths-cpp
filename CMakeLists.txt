cmake_minimum_required(VERSION 3.12)

#
# Project
#
set(PROJECT_LIB dehancer_maths_cpp)
project(${PROJECT_LIB} VERSION 0.3.1)

#
# Options
#
option(BUILD_TESTING "Enable creation of Armadilli tests." OFF)
option(DEHANCER_TARGET_ARCH "")

if (DEHANCER_TARGET_ARCH)
    #
    # x86_64-apple-macos10.13
    # or
    # arm64-apple-macos11
    #
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -target ${DEHANCER_TARGET_ARCH}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -target ${DEHANCER_TARGET_ARCH}")
endif ()

option(DEHANCER_COMMON_DIR  "")
if (NOT DEHANCER_COMMON_DIR)
    set(DEHANCER_COMMON_DIR ${CMAKE_BINARY_DIR}/tmp)
endif ()

option(EXTERNAL_INSTALL_LOCATION  "")
if (NOT EXTERNAL_INSTALL_LOCATION)
    set (EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
endif ()


#
# Global setttings
#
set(VERSION_FILE "version.txt")
set(CMAKE_CXX_STANDARD 11)


if (NOT WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -fvisibility=hidden -Wno-unused-command-line-argument")
endif ()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -ffast-math")

# googletes, etc
set (EXTERNAL_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/external)
set (EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
set (EXTERNAL_INCLUDE_DIR ${EXTERNAL_INSTALL_LOCATION}/include)

#
# Generators
#
file (WRITE "${VERSION_FILE}" "${PROJECT_NAME} ${PROJECT_VERSION}")

#
# Packages
#
find_package (PkgConfig QUIET)
find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)
find_package(Threads REQUIRED)

if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "pkg-config not found!" )
    message(FATAL_ERROR "sudo apt-get install pkg-config, or brew install pkg-config")
endif()

#
# Programms
#
find_program(CCACHE_FOUND ccache)
find_program(MAKE_EXE NAMES gmake nmake make)

#
# CCache settings
#
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)


#
# Compiler settings
#

message(STATUS "CMAKE_CXX_COMPILER_ID: " ${CMAKE_CXX_COMPILER_ID})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")

    message(STATUS "Using Clang" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++17-extensions")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    message(STATUS "Using gcc" )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -W -Wall -Wextra -Wno-ignored-qualifiers -Wvariadic-macros -pthread -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_FLAGS "-fvisibility=hidden -Wno-pedantic")
    set(CMAKE_LINK_DEPENDS_NO_SHARED TRUE)

    add_compile_options(-lpthread)

    if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DX86_LINUX")
    endif()

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")

    message( FATAL_ERROR "The project does not support Intel compiler" )

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")

    message( FATAL_ERROR "The project does not support MSVC compiler" )

endif()

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -EHsc -Wno-deprecated-declarations")
    add_definitions(/MT /DWIN32=1 /D_ITERATOR_DEBUG_LEVEL=0)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -rdynamic")
endif ()

#
# Package manager
#
include(ExternalProject)

#
# External project dependencies
#
set(COMMON_DEPENDENCIES)
set(COMMON_LIBRARIES ${BLAS_LIBRARIES};${LAPACK_LIBRARIES};${CMAKE_THREAD_LIBS_INIT};${MKL_LIBRARIES})

#
# Google TEST
#
if (BUILD_TESTING)
    find_package(GTest)
    if (NOT GTEST_FOUND)
        ExternalProject_Add(googletest
                GIT_REPOSITORY https://github.com/google/googletest
                CMAKE_ARGS
                -DCMAKE_BUILD_TYPE=Release
                -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}
                -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
                -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
                -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
                -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
                -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
                PREFIX ${CMAKE_BINARY_DIR}/tmp
                )
        set(COMMON_DEPENDENCIES ${COMMON_DEPENDENCIES};googletest)

        include_directories(
                ./
                ../include
                ${CMAKE_BINARY_DIR}/external/include
        )

        link_directories(
                ${CMAKE_BINARY_DIR}/external/lib
        )

    endif()
endif ()

pkg_check_modules(armadillo armadillo)

if (armadillo_FOUND)

    include_directories(
            ${armadillo_INCLUDE_DIRS}
    )
    link_directories(
            ${armadillo_LIBRARY_DIRS}
    )
    set(COMMON_LIBRARIES ${armadillo_LIBRARIES};${COMMON_LIBRARIES})

else()

    ExternalProject_Add(armadillo-lib
            GIT_REPOSITORY https://github.com/dehancer/armadillo-code
            GIT_TAG 9.700.x
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DBUILD_TESTING=OFF
            -DDETECT_HDF5=false
            -DCMAKE_BUILD_TYPE=Release
            -DDEHANCER_TARGET_ARCH=${DEHANCER_TARGET_ARCH}
            -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
            PREFIX ${CMAKE_BINARY_DIR}/tmp
            )

    set(COMMON_DEPENDENCIES ${COMMON_DEPENDENCIES};armadillo-lib)
    set(COMMON_LIBRARIES armadillo;${COMMON_LIBRARIES})

    link_directories(
            ${CMAKE_BINARY_DIR}/external/lib
    )

endif()


#
# Details
#
add_subdirectory(lib)

if(BUILD_TESTING)
    add_subdirectory(tests)
    enable_testing ()
endif()

# Install package
#
if (NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR  lib)
endif ()
if (NOT CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR  include)
endif ()

set(prefix ${CMAKE_INSTALL_PREFIX})
set(exec_prefix "\${prefix}")
set(libdir "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
set(includedir "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")

configure_file(${CMAKE_SOURCE_DIR}/dehancer-maths-cpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/dehancer-maths-cpp.pc @ONLY)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/dehancer-maths-cpp.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
        )