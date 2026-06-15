cmake_minimum_required(VERSION 3.28)

# Setup C compiler settings
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Setup C++ compiler settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set the project name
set(CMAKE_PROJECT_NAME sam)

# Project settings
project(${CMAKE_PROJECT_NAME})

# Add the prject target
add_library(${CMAKE_PROJECT_NAME} INTERFACE)

# Add self include path
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
