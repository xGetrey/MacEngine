What will be installed

  /usr/local/lib/libMacEngine.a          the library (Apple Silicon and Intel)
  /usr/local/include/MacEngine/          the header files
  /usr/local/lib/cmake/MacEngine/        files for CMake find_package

An older MacEngine in /usr/local/include/MacEngine is removed first.

Requirements

  macOS 13 or newer
  Xcode Command Line Tools (xcode-select --install)
  CMake 3.20 or newer

How to use it

  In your CMakeLists.txt:

    find_package(MacEngine REQUIRED)
    target_link_libraries(MyGame PRIVATE MacEngine::MacEngine)

  In your code:

    #include <MacEngine/MacEngine.h>

How to uninstall

  Run this in the Terminal:

    sudo rm -rf /usr/local/include/MacEngine /usr/local/lib/cmake/MacEngine /usr/local/lib/libMacEngine.a
    sudo pkgutil --forget io.github.xgetrey.macengine.MacEngine

More information: https://github.com/xGetrey/MacEngine
