include(CMakePackageConfigHelpers)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ../include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${EXTERNAL_LOCATION}
)

FILE(GLOB PUBLIC_INCLUDE_FILES
        ../include/dehancer/*.hpp
        )

FILE(GLOB PUBLIC_SPLINE_INCLUDE_FILES
        ../include/dehancer/spline/*.hpp
        )

FILE(GLOB PUBLIC_DETAILS_INCLUDE_FILES
        ../include/dehancer/details/*.hpp
        )

FILE(GLOB INCLUDE_FILES
        ${PUBLIC_INCLUDE_FILES}
        )

FILE(GLOB SOURCES
        ../src/*.cpp
        ../src/spline/*.cpp
        )

add_library(
        ${PROJECT_LIB}
        ${SOURCES})

if (COMMON_DEPENDENCIES)
    add_dependencies(${PROJECT_LIB} ${COMMON_DEPENDENCIES})
endif ()

target_link_libraries (
        ${PROJECT_LIB}  PUBLIC
)

target_include_directories(
        ${PROJECT_LIB}
        PUBLIC
        ../include
)

set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}")
set(namespace "${PROJECT_NAME}::")

write_basic_package_version_file(
        "${version_config}" COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "cmake/Config.cmake.in"
        "${project_config}"
        INSTALL_DESTINATION "${config_install_dir}"
)

if (NOT CMAKE_INSTALL_LIBDIR)
    set(CMAKE_INSTALL_LIBDIR lib)
endif ()

if (NOT CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include)
endif ()

install(DIRECTORY
        ${EXTERNAL_INSTALL_LOCATION}/include
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/..
        FILES_MATCHING
        PATTERN armadillo
        PATTERN dehancer* EXCLUDE
        PATTERN gtest* EXCLUDE
        PATTERN gmock* EXCLUDE
        )

install(DIRECTORY
        ${EXTERNAL_INSTALL_LOCATION}/lib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/..
        FILES_MATCHING
        PATTERN *armadillo*.*
        PATTERN armadillo.pc EXCLUDE
        PATTERN *gtest* EXCLUDE
        PATTERN *gmock* EXCLUDE
        )

install(FILES   ${PUBLIC_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dehancer)
install(FILES   ${PUBLIC_SPLINE_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dehancer/spline)
install(FILES   ${PUBLIC_DETAILS_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/dehancer/details)
install(FILES   ${project_config} ${version_config} DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_LIB})
install(FILES cmake/${PROJECT_LIB}.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_LIB})
install(TARGETS ${PROJECT_LIB}   DESTINATION ${CMAKE_INSTALL_LIBDIR})
