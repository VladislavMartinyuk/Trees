cmake_minimum_required(VERSION 3.16)

project(Trees LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Trees main.cpp
    BinarySearchTree.h)

include(GNUInstallDirs)
install(TARGETS Trees
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
