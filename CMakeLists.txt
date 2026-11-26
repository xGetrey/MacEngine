cmake_minimum_required(VERSION 3.20)
project(MacEngine LANGUAGES CXX OBJCXX)

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

install(TARGETS MacEngine
    EXPORT MacEngineTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY Engine/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MacEngine
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT MacEngineTargets
    NAMESPACE MacEngine::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MacEngine
)
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/MacEngineConfig.cmake
    "include(\"\${CMAKE_CURRENT_LIST_DIR}/MacEngineTargets.cmake\")\n"
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MacEngineConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MacEngine
)
