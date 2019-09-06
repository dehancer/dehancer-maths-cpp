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

if (COMMON_DEPENDECIES)
    add_dependencies(${PROJECT_LIB} ${COMMON_DEPENDECIES})
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


install(TARGETS ${PROJECT_LIB}   DESTINATION lib)
install(FILES   ${PUBLIC_INCLUDE_FILES} DESTINATION include/dehancer)
install(FILES   ${PUBLIC_SPLINE_INCLUDE_FILES} DESTINATION include/dehancer/spline)
install(FILES   ${PUBLIC_DETAILS_INCLUDE_FILES} DESTINATION include/dehancer/details)
install(FILES   ${project_config} ${version_config} DESTINATION lib/cmake/${PROJECT_LIB})
install(FILES cmake/${PROJECT_LIB}.cmake DESTINATION lib/cmake/${PROJECT_LIB})