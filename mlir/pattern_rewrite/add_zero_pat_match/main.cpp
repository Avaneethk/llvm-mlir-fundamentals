#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Parser/Parser.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Support/FileUtilities.h"
#include "llvm/Support/raw_ostream.h"

#include "AddZeroPattern.h"

using namespace mlir;

int main(int argc, char **argv) {
    MLIRContext context;

    // 1. Load dialects
    context.loadDialect<arith::ArithDialect>();
    context.getOrLoadDialect<func::FuncDialect>();

    // 2. Example IR
    const char *ir = R"mlir(
        module {
          func.func @test(%arg0 : i32) -> i32 {
            %c0 = arith.constant 0 : i32
            %1 = arith.addi %arg0, %c0 : i32
            return %1 : i32
          }
        }
    )mlir";

    // 3. Parse IR
    auto module = parseSourceString<ModuleOp>(ir, &context);
    if (!module) {
        llvm::errs() << "Failed to parse IR\n";
        return 1;
    }

    // 4. Create PassManager
    PassManager pm(&context);

    // 5. Add your pass
    pm.addPass(createAddZeroPass());

    // 6. Run pass pipeline
    if (failed(pm.run(module.get()))) {
        llvm::errs() << "Pass failed\n";
        return 1;
    }

    // 7. Print transformed IR
    module->dump();

    return 0;
}