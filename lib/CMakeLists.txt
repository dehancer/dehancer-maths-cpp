include(CMakePackageConfigHelpers)

set(CMAKE_INSTALL_PREFIX /usr/local/${PROJECT_LIB})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ../include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/
        ${EXTERNAL_LOCATION}
)

FILE(GLOB PUBLIC_INCLUDE_FILES
        ${CMAKE_SOURCE_DIR}/include/dehancer/*.hpp
        )

FILE(GLOB PUBLIC_SPLINE_INCLUDE_FILES
        ${CMAKE_SOURCE_DIR}/include/dehancer/spline/*.hpp
        )

FILE(GLOB PUBLIC_DETAILS_INCLUDE_FILES
        ${CMAKE_SOURCE_DIR}/include/dehancer/details/*.hpp
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

target_link_libraries (
        ${PROJECT_LIB}  PUBLIC
)

target_include_directories(
        ${PROJECT_LIB}
        PUBLIC
        ../include
        ${EXTERNAL_INCLUDE_DIR}
        ${EXTERNAL_LOCATION}/nlohmann
)

if (COMMON_DEPENDENCIES)
    #add_dependencies(${PROJECT_LIB} ${COMMON_DEPENDENCIES})
endif ()

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


FILE(GLOB PUBLIC_ARMADILLO_INCLUDE_FILES
        ${EXTERNAL_INSTALL_LOCATION}/include/armadillo
        )
FILE(GLOB PUBLIC_ARMADILLO_LIB_FILES
        ${EXTERNAL_INSTALL_LOCATION}/lib/*armadillo*.*
        )
install(FILES   ${PUBLIC_ARMADILLO_INCLUDE_FILES} DESTINATION include)
install(DIRECTORY   ${EXTERNAL_INSTALL_LOCATION}/include/armadillo_bits DESTINATION include)
install(FILES   ${PUBLIC_ARMADILLO_LIB_FILES} DESTINATION lib)

install(TARGETS ${PROJECT_LIB}   DESTINATION lib)
install(FILES   ${PUBLIC_INCLUDE_FILES} DESTINATION include/dehancer)
install(FILES   ${PUBLIC_SPLINE_INCLUDE_FILES} DESTINATION include/dehancer/spline)
install(FILES   ${PUBLIC_DETAILS_INCLUDE_FILES} DESTINATION include/dehancer/details)
install(FILES   ${project_config} ${version_config} DESTINATION lib/cmake/${PROJECT_LIB})
install(FILES cmake/${PROJECT_LIB}.cmake DESTINATION lib/cmake/${PROJECT_LIB})