cmake_minimum_required(VERSION 3.20)

project(mlir_tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MLIR REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found MLIR: ${MLIR_DIR}")
message(STATUS "Found LLVM: ${LLVM_DIR}")

include_directories(SYSTEM
  ${LLVM_INCLUDE_DIRS}
  ${MLIR_INCLUDE_DIRS}
)

add_definitions(${LLVM_DEFINITIONS})

add_executable(mlir_tree
    mlir_tree.cpp
)

target_link_libraries(mlir_tree PRIVATE
    MLIRIR
    MLIRSupport
    MLIRArithDialect
    MLIRFuncDialect
)