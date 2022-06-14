cmake_minimum_required(VERSION 3.10)
project(divp) 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra")
include_directories(${divp_SOURCE_DIR}/include/divp)
add_executable(divp 
src/main.cpp 
src/name.cpp 
src/dateUtils.cpp 
src/fileUtils.cpp 
src/strUtils.cpp
src/akt.cpp
src/nameFileProcessor.cpp
src/transaction.cpp
src/vectorAndMapUtils.cpp
include/divp/akt.hpp
include/divp/dateUtils.hpp
include/divp/fileUtils.hpp
include/divp/name.hpp
include/divp/nameFileProcessor.hpp
include/divp/strUtils.hpp
include/divp/transaction.hpp
include/divp/vectorAndMapUtils.hpp
)
target_link_libraries(divp ncurses)
