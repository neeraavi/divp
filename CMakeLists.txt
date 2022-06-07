cmake_minimum_required(VERSION 3.10)
project(divp) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${divp_SOURCE_DIR}/include/divp)
add_executable(divp 
src/main.cpp 
src/name.cpp 
src/dateUtils.cpp 
src/fileUtils.cpp 
src/strUtils.cpp
src/transaction.cpp
src/vectorAndMapUtils.cpp
)
