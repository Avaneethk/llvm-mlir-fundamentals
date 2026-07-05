cmake_minimum_required(VERSION 3.20)

project(AddZeroMLIR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM + MLIR
find_package(LLVM REQUIRED CONFIG)
find_package(MLIR REQUIRED CONFIG)

list(APPEND CMAKE_MODULE_PATH ${MLIR_CMAKE_DIR})
include(AddLLVM)
include(AddMLIR)
include(TableGen)
include(HandleLLVMOptions)

message(STATUS "LLVM DIR: ${LLVM_DIR}")
message(STATUS "MLIR DIR: ${MLIR_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${MLIR_INCLUDE_DIRS})

add_definitions(${LLVM_DEFINITIONS})

# Your executable
add_executable(addzero
    main.cpp
    AddZeroPass.cpp
)

# Link MLIR + LLVM libs (minimum set for your case)
target_link_libraries(addzero
    MLIRIR
    MLIRPass
    MLIRSupport
    MLIRParser
    MLIRFuncDialect
    MLIRArithDialect
    MLIRTransforms
    LLVMCore
    LLVMSupport
)