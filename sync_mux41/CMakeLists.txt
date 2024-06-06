cmake_minimum_required(VERSION 3.10)
project(sync_mux41_main)
 
set(CMAKE_CXX_STANDARD 17) #systemc-2.3.4 cannot support version 17
 
set(SYSTEMC_INLCUDE_DIRS "/home/sjh/work/systemc-3.0.0/include")
include_directories(${SYSTEMC_INLCUDE_DIRS})
file(GLOB_RECURSE SYSTEMC_LIB "/home/sjh/work/systemc-3.0.0/lib-linux64/*.so")
 
 
add_executable(${PROJECT_NAME} sync_mux41_main.cpp)
target_link_libraries(${PROJECT_NAME} ${SYSTEMC_LIB})