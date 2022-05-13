# Install script for directory: /home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/wxWidgets-3.1.6/build/cmake/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/base/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/net/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/core/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/adv/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/aui/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/html/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/propgrid/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/ribbon/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/richtext/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/webview/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/stc/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/xrc/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/media/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/gl/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/qa/cmake_install.cmake")
  include("/home/user/Dokumente/Source/vscode/c++/WurstAutoBuildGen/build/wxWidgets-3.1.6/libs/xml/cmake_install.cmake")

endif()

