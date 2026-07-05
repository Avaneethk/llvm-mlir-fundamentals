#include "AddZeroPattern.h"

#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"

using namespace mlir;
using namespace mlir::func;

struct AddZeroPass : public PassWrapper<AddZeroPass,OperationPass<ModuleOp>> {
    //ModuleOp module = getOperation();
    void runOnOperation() override {
        ModuleOp module = getOperation();
        //create patterns list 
        RewritePatternSet patterns(&getContext());
        //custom pattern 
        patterns.add<AddZeroPattern>(&getContext());
        if (failed(applyPatternsGreedily(module,std::move(patterns))))
        //appyly greedily is expecting greedy pattern 
        //if (failed(applyPatternsGreedily(module,patterns)))
        {
           signalPassFailure();
        }
    }
};

//pass registration
std::unique_ptr<mlir::Pass> createAddZeroPass() {
    return std::make_unique<AddZeroPass>();
}
