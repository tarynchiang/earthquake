# Install script for directory: /Users/Chiangyiting/Desktop/csci4611/repo-chian141/dev/MinGfx/tests/blank_window

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/Chiangyiting/Desktop/csci4611/repo-chian141")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xTestsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/Chiangyiting/Desktop/csci4611/repo-chian141/dev/MinGfx/build/tests/blank_window/mingfx-test-blank-window")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mingfx-test-blank-window" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mingfx-test-blank-window")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/Chiangyiting/Desktop/csci4611/repo-chian141/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mingfx-test-blank-window")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "/Users/Chiangyiting/Desktop/csci4611/repo-chian141/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mingfx-test-blank-window")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/strip" -u -r "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/mingfx-test-blank-window")
    endif()
  endif()
endif()

