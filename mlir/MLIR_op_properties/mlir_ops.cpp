#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/raw_ostream.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Operation.h"
#include "mlir/Dialect/Arith/IR/Arith.h"

/// RUN  cmake -G Ninja -DMLIR_DIR=/wrk/llvm-project/build/lib/cmake/mlir -DLLVM_DIR=/wrk/llvm-project/build/lib/cmake/llvm ..
/// Print each part of an MLIR operation separately

void printOperationParts(mlir::Operation *op) {
  llvm::outs() << "Operation name: " << op->getName() << "\n";

  llvm::outs() << "Operands:\n";
  for (mlir::Value operand : op->getOperands()) {
    operand.print(llvm::outs());
    llvm::outs() << "\n";
  }

  llvm::outs() << "Results:\n";
  for (mlir::Value result : op->getResults()) {
    result.print(llvm::outs());
    llvm::outs() << " (type: ";
    result.getType().print(llvm::outs());
    llvm::outs() << ")\n";
  }

  llvm::outs() << "Attributes:\n";
  for (auto attr : op->getAttrs()) {
    llvm::outs() << attr.getName() << " = ";
    attr.getValue().print(llvm::outs());
    llvm::outs() << "\n";
  }

  llvm::outs() << "Location: ";
  op->getLoc().print(llvm::outs());
  llvm::outs() << "\n";
}

int main() {
  mlir::MLIRContext context;
  context.loadDialect<mlir::arith::ArithDialect>();

  mlir::OpBuilder builder(&context);

  // Create a dummy module to hold operations
  auto module = mlir::ModuleOp::create(builder.getUnknownLoc());
  builder.setInsertionPointToStart(module.getBody());

  // Create a constant operation: %c7_i32 = arith.constant 7 : i32
  auto c7 = builder.create<mlir::arith::ConstantOp>(
      builder.getUnknownLoc(),
      builder.getIntegerAttr(builder.getIntegerType(32), 7));

  // Print the operation parts
  printOperationParts(c7.getOperation());

  return 0;
}
