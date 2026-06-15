//cmake -G Ninja -DMLIR_DIR=/wrk/llvm-project/build/lib/cmake/mlir -DLLVM_DIR=/wrk/llvm-project/build/lib/cmake/llvm ..
// ninja
// ./llvm_ex6
/*
cmake_minimum_required(VERSION 3.20)

project(llvm_ex6)

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

add_executable(llvm_ex6
    llvm_ex6.cpp
)

target_link_libraries(llvm_ex6 PRIVATE
    MLIRIR
    MLIRSupport
    MLIRArithDialect
)
*/

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Operation.h"
#include "mlir/Dialect/Arith/IR/Arith.h"

// Function to print the DenseMap
void printDenseMapOpVec(const llvm::DenseMap<mlir::Operation*, llvm::SmallVector<int,4>> &m) {
  for (auto &kv : m) {
    mlir::Operation *op = kv.first;
    llvm::outs() << "Op name: " << op->getName() << " | op: ";
    op->print(llvm::outs());
    llvm::outs() << "\nValues: ";
    for (int x : kv.second)
      llvm::outs() << x << " ";
    llvm::outs() << "\n\n";
  }
}

int main() {
  mlir::MLIRContext context;

  context.loadDialect<mlir::arith::ArithDialect>();

  mlir::OpBuilder builder(&context);

  // Create a dummy module to hold operations
  auto module = mlir::ModuleOp::create(builder.getUnknownLoc());

  // Insert a simple constant operation
  builder.setInsertionPointToStart(module.getBody());
  auto constOp = builder.create<mlir::arith::ConstantOp>(
      builder.getUnknownLoc(),
      builder.getIntegerAttr(builder.getIntegerType(32), 42));

  // Insert a second constant operation
  auto constOp2 = builder.create<mlir::arith::ConstantOp>(
      builder.getUnknownLoc(),
      builder.getIntegerAttr(builder.getIntegerType(32), 7));

  // Build DenseMap mapping operations to vectors of ints
  llvm::DenseMap<mlir::Operation*, llvm::SmallVector<int,4>> opMap;
  opMap[constOp.getOperation()] = {1, 2, 3};
  opMap[constOp2.getOperation()] = {10, 20};

  // Print the map
  printDenseMapOpVec(opMap);

  return 0;
}
