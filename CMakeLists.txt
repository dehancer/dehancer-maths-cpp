cmake_minimum_required(VERSION 3.22)

#
# Project
#
set(PROJECT_LIB dehancer_maths_cpp)
project(${PROJECT_LIB} VERSION 0.12.0)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()


#
# Options
#
option(BUILD_TESTING "Enable creation of Armadillo tests." OFF)
option(DEHANCER_TARGET_ARCH "")
option(VCPKG_TARGET_TRIPLET "")

option(DEHANCER_COMMON_DIR  "")
if (NOT DEHANCER_COMMON_DIR)
    set(DEHANCER_COMMON_DIR ${CMAKE_BINARY_DIR}/tmp)
endif ()

option(EXTERNAL_INSTALL_LOCATION  "")
if (NOT EXTERNAL_INSTALL_LOCATION)
    set (EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)
endif ()


#
# Global settings
#
set(VERSION_FILE "version.txt")
set(CMAKE_CXX_STANDARD 17)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++ -fvisibility=default -Wno-unused-command-line-argument")
endif ()

#
# Generators
#
file (WRITE "${VERSION_FILE}" "${PROJECT_NAME} ${PROJECT_VERSION}")

#
# Packages
#
find_package (PkgConfig QUIET)

if(LINUX)

    find_package (lapack)

    if (LAPACK_NOT_FOUND)
        message(FATAL "LAPACK has not bin found at all. $ git clone https://github.com/Reference-LAPACK/lapack-release and install")
    else()
        message("LAPACK LIBRARY: ${LAPACK_LIBRARIES}")
    endif ()

else()

    find_package (LAPACK REQUIRED)
    find_package (BLAS REQUIRED)

endif()

set(CMAKE_INSTALL_LIBDIR  "lib")

if (LINUX)

    set(DEHANCER_EXT_MATH_LIB)

    set(FORTRAN_LIB_PATHS ${CMAKE_SYSTEM_LIBRARY_PATH};/usr/lib/gcc/x86_64-redhat-linux/8;/usr/lib/gcc/x86_64-linux-gnu/9;/usr/lib/gcc/x86_64-linux-gnu/8;/usr/lib/gcc/x86_64-linux-gnu;/lib64;/lib;/usr/lib64;/usr/lib;/usr/local/lib64;/usr/local/lib;/opt/local/lib64;/opt/local/lib)

    message(STATUS "FORTRAN_LIB_PATHS: ${FORTRAN_LIB_PATHS}")

    find_library(GFORTRAN_LIBRARY
            NAMES gfortran
            PATHS ${FORTRAN_LIB_PATHS}
            REQUIRED
            )

    find_library(GQUADMATH_LIBRARY
            NAMES quadmath
            PATHS ${FORTRAN_LIB_PATHS}
            )

    message("GFORTRAN_LIBRARY: ${GFORTRAN_LIBRARY}")

    set(DEHANCER_EXT_MATH_LIB ${BLAS_LIBRARIES};${LAPACK_LIBRARIES})

    if (GFORTRAN_LIBRARY)
        set(DEHANCER_EXT_MATH_LIB ${DEHANCER_EXT_MATH_LIB};${GFORTRAN_LIBRARY};m)
    else ()
        set(DEHANCER_EXT_MATH_LIB ${DEHANCER_EXT_MATH_LIB};m)
    endif ()

    find_library(DEHANCER_EXT_MATH_LIB REQUIRED ${DEHANCER_EXT_MATH})

else()
    set(DEHANCER_EXT_MATH_LIB ${BLAS_LIBRARIES};${LAPACK_LIBRARIES})
endif ()

include_directories(${BLAS_INCLUDE_DIRS} ${LAPACK_INCLUDE_DIRS})

message("BLASS/LAPACK: ${DEHANCER_EXT_MATH_LIB}")


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
    set(CMAKE_CXX_FLAGS "-fvisibility=default -Wno-pedantic")
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
    add_definitions(/MT /DWIN32=1 /D_ITERATOR_DEBUG_LEVEL=0 /GR /Ob0)
    string(TOLOWER  ${CMAKE_BUILD_TYPE} BUILD_TYPE)
    if (${BUILD_TYPE} STREQUAL "debug")
        add_definitions(/MTd)
    endif()
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
set(COMMON_LIBRARIES ${DEHANCER_EXT_MATH_LIB};${CMAKE_THREAD_LIBS_INIT};${MKL_LIBRARIES})

string(STRIP "${CMAKE_C_FLAGS} -D_ITERATOR_DEBUG_LEVEL=0" C_FLAGS)
string(STRIP "${CMAKE_CXX_FLAGS} -D_ITERATOR_DEBUG_LEVEL=0" CXX_FLAGS)

include(FetchContent)

#
# Google Test
#
if (BUILD_TESTING)

    find_package(GTest)

    if (NOT GTest_FOUND)

        string(STRIP "${CMAKE_C_FLAGS} -D_ITERATOR_DEBUG_LEVEL=0" C_FLAGS)
        string(STRIP "${CMAKE_CXX_FLAGS} -D_ITERATOR_DEBUG_LEVEL=0" CXX_FLAGS)

        set(CMAKE_OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}" CACHE STRING "" FORCE)

        FetchContent_Declare(
                googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG      v1.14.0
                SOURCE_DIR "${CMAKE_BINARY_DIR}/googletest-src"
        )

        FetchContent_MakeAvailable(googletest)
#        FetchContent_GetProperties(googletest)
#
#        if(NOT googletest_POPULATED)
#            FetchContent_Populate(googletest)
#            add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
#        endif()

    endif ()

endif ()

#if (LINUX)
    set (BUILD_SMOKE_TEST OFF CACHE INTERNAL "BUILD_SMOKE_TEST OFF")
    set (BUILD_SHARED_LIBS OFF CACHE INTERNAL "BUILD_SHARED_LIBS OFF")
#endif ()

FetchContent_Declare(
        armadillo
#        GIT_REPOSITORY https://github.com/dehancer/armadillo-code
#        GIT_TAG  9.700.x
        GIT_REPOSITORY https://gitlab.com/conradsnicta/armadillo-code
        GIT_TAG     12.8.x
        GIT_PROGRESS YES
        GIT_SHALLOW YES
        SOURCE_DIR "${CMAKE_BINARY_DIR}/armadillo-src"
        BINARY_DIR "${CMAKE_BINARY_DIR}/armadillo-build"
)
FetchContent_MakeAvailable(armadillo)

FetchContent_GetProperties(armadillo)

# On iOS Armadillo has to be built with ARMA_USE_WRAPPER defined.
if(armadillo_POPULATED AND CMAKE_SYSTEM_NAME STREQUAL "iOS")
    file(READ "${armadillo_SOURCE_DIR}/include/armadillo_bits/config.hpp" CONTENT)
    string(REGEX REPLACE "//[ ]+#define[ ]+ARMA_USE_WRAPPER" "#define ARMA_USE_WRAPPER" CONTENT_MODIFIED "${CONTENT}")
    file(WRITE "${armadillo_SOURCE_DIR}/include/armadillo_bits/config.hpp" "${CONTENT_MODIFIED}")
    message(STATUS "Armadillo DODODO: ${armadillo_SOURCE_DIR}")
endif()

include_directories(
        ${armadillo_SOURCE_DIR}/include
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(COMMON_LIBRARIES armadillo;${COMMON_LIBRARIES})

#
# Details
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(BUILD_TESTING)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
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
set(extra_math_libs "${DEHANCER_EXT_MATH_LIB}")


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dehancer-maths-cpp.pc.in ${CMAKE_CURRENT_BINARY_DIR}/dehancer-maths-cpp.pc @ONLY)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/dehancer-maths-cpp.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
        )
