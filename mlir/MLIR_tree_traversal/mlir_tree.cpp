#include "llvm/Support/raw_ostream.h"

#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Operation.h"

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"

int main() {

  //--------------------------------------------------
  // Create Context
  //--------------------------------------------------

  mlir::MLIRContext context;

  context.loadDialect<
      mlir::func::FuncDialect,
      mlir::arith::ArithDialect>();

  mlir::OpBuilder builder(&context);

  //--------------------------------------------------
  // Create Module
  //--------------------------------------------------

  auto module =
      mlir::ModuleOp::create(builder.getUnknownLoc());

  //--------------------------------------------------
  // Create Function
  //--------------------------------------------------

  auto funcType =
      builder.getFunctionType({}, {});

  auto func =
      mlir::func::FuncOp::create(
          builder.getUnknownLoc(),
          "main",
          funcType);

  module.push_back(func);

  //--------------------------------------------------
  // Create Entry Block
  //--------------------------------------------------

  mlir::Block *entry = func.addEntryBlock();

  builder.setInsertionPointToStart(entry);

  //--------------------------------------------------
  // Create Operations
  //--------------------------------------------------

  builder.create<mlir::arith::ConstantOp>(
      builder.getUnknownLoc(),
      builder.getI32IntegerAttr(42));

  builder.create<mlir::arith::ConstantOp>(
      builder.getUnknownLoc(),
      builder.getI32IntegerAttr(7));

  builder.create<mlir::func::ReturnOp>(
      builder.getUnknownLoc());

  //--------------------------------------------------
  // DFS Walk of IR
  //--------------------------------------------------

  llvm::outs() << "IR Walk\n\n";

  module.walk([](mlir::Operation *op) {

      llvm::outs()
          << "Visited : "
          << op->getName()
          << "\n";

  });

  return 0;
}