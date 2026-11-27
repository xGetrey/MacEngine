cmake_minimum_required(VERSION 3.20)

set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "")
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64" CACHE STRING "")

project(MacEngine VERSION 0.1.0 LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE MACENGINE_SOURCES CONFIGURE_DEPENDS
    Engine/*.cpp
    Engine/*.mm
)
add_library(MacEngine STATIC ${MACENGINE_SOURCES})

target_compile_options(MacEngine PRIVATE $<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>)

target_include_directories(MacEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Engine>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(MacEngine PUBLIC
    "-framework Cocoa"
    "-framework Metal"
    "-framework QuartzCore"
    "-framework Carbon"
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS MacEngine
    EXPORT MacEngineTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT MacEngine
)

install(DIRECTORY Engine/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MacEngine
    COMPONENT MacEngine
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT MacEngineTargets
    NAMESPACE MacEngine::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MacEngine
    COMPONENT MacEngine
)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/MacEngineConfig.cmake
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/MacEngineTargets.cmake\")\n"
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MacEngineConfigVersion.cmake
    COMPATIBILITY SameMinorVersion
)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MacEngineConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MacEngineConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MacEngine
    COMPONENT MacEngine
)

configure_file(LICENSE ${CMAKE_CURRENT_BINARY_DIR}/LICENSE.txt COPYONLY)

set(CPACK_PACKAGE_NAME "MacEngine")
set(CPACK_PACKAGE_VENDOR "Gulyás Péter István")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A small 2D game framework for macOS")
set(CPACK_PACKAGE_FILE_NAME "MacEngine-${PROJECT_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_BINARY_DIR}/LICENSE.txt)
set(CPACK_RESOURCE_FILE_WELCOME ${CMAKE_CURRENT_SOURCE_DIR}/packaging/Welcome.txt)
set(CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/packaging/ReadMe.txt)
set(CPACK_PREFLIGHT_MACENGINE_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/packaging/preinstall)
set(CPACK_PROJECT_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/packaging/CPackOptions.cmake)
set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/packaging/StripAttributes.cmake)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
set(CPACK_PRODUCTBUILD_IDENTIFIER "io.github.xgetrey.macengine")
set(CPACK_GENERATOR "productbuild;ZIP")
set(CPACK_COMPONENTS_ALL MacEngine)
set(CPACK_ARCHIVE_COMPONENT_INSTALL OFF)
include(CPack)
