cmake_minimum_required(VERSION 3.20)
project(MacEngine LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD 20)
set(CMAKE_OBJCXX_STANDARD_REQUIRED ON)

# 1. A motor könyvtár: minden .cpp és .mm fájl az Engine mappából
file(GLOB_RECURSE MACENGINE_SOURCES CONFIGURE_DEPENDS
    Engine/*.cpp
    Engine/*.mm
)
add_library(MacEngine STATIC ${MACENGINE_SOURCES})

# A .mm fájlok ARC-cal (automatikus memóriakezeléssel) fordulnak, mint az Xcode-ban
target_compile_options(MacEngine PRIVATE $<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>)

# A publikus fejlécek: a felhasználó így írhatja: #include "MacEngine.h"
target_include_directories(MacEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine)

# Az alapértelmezett ikon abszolút útvonala, így bármelyik mappából indul a program, megtalálja
target_compile_definitions(MacEngine PRIVATE
    MACENGINE_DEFAULT_ICON="${CMAKE_CURRENT_SOURCE_DIR}/Engine/MacEngineIcon.png"
)

# 2. Apple frameworkök. PUBLIC, mert a motort használó programnak is linkelnie kell őket
target_link_libraries(MacEngine PUBLIC
    "-framework Cocoa"
    "-framework Metal"
    "-framework QuartzCore"
)

# 3. Példaprogram, csak akkor, ha ez a fő projekt (add_subdirectory-nél nem fordul le)
if(PROJECT_IS_TOP_LEVEL)
    add_executable(Example main.cpp)
    target_link_libraries(Example PRIVATE MacEngine)
endif()
