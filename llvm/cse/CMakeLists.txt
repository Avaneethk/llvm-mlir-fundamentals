cmake_minimum_required(VERSION 3.20)

project(MyDCE)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")

include(AddLLVM)

add_library(MyCSE MODULE
    MyCSE.cpp
)

target_include_directories(MyCSE PRIVATE
    ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(MyCSE PRIVATE
    ${LLVM_DEFINITIONS}
)

target_compile_features(MyCSE PRIVATE cxx_std_17)

# LLVM itself is usually built without RTTI
set_target_properties(MyCSE PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

if(NOT LLVM_ENABLE_RTTI)
    target_compile_options(MyCSE PRIVATE -fno-rtti)
endif()