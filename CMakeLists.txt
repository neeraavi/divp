cmake_minimum_required(VERSION 3.10)
project(divp) 
include_directories(${divp_SOURCE_DIR}/include/divp)
add_executable(divp 
src/main.cpp 
src/name.cpp 
src/fileUtils.cpp 
src/strUtils.cpp
src/transaction.cpp
src/vectorAndMapUtils.cpp
)
