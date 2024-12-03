# Install script for directory: /Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src

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
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Catch2" TYPE FILE FILES
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-build/Catch2Config.cmake"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-build/Catch2ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/Catch2" TYPE DIRECTORY FILES "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/docs/" REGEX "/doxygen$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Catch2" TYPE FILE FILES
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/ParseAndAddCatchTests.cmake"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/Catch.cmake"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/CatchAddTests.cmake"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/CatchShardTests.cmake"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/CatchShardTestsImpl.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Catch2" TYPE FILE FILES
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/gdbinit"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-src/extras/lldbinit"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/pkgconfig" TYPE FILE FILES
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-build/catch2.pc"
    "/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-build/catch2-with-main.pc"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/oghenefejiroabohweyere/Documents/algo_learn/b_tree/build-unix/_deps/catch2-build/src/cmake_install.cmake")

endif()

