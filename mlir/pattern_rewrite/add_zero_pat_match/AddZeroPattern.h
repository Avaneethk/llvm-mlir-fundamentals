

/*
rewrite driver is tracking:

worklists
use-def chains
recursive rewrites
notifications
legality

If you modify the IR behind its back, it loses track of what's happening.
So all mutations must go through PatternRewriter.
This is a major design principle in MLIR.

*/

#include "mlir/IR/PatternMatch.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include <memory>
#include "mlir/Pass/Pass.h"

using namespace llvm;
using namespace mlir;
using namespace mlir::arith;

std::unique_ptr<mlir::Pass> createAddZeroPass();


class AddZeroPattern: public OpRewritePattern<arith::AddIOp>
{
    //constructor inheritance
    using OpRewritePattern<arith::AddIOp>::OpRewritePattern;
    public:
    LogicalResult matchAndRewrite(arith::AddIOp op,PatternRewriter &rewriter) const override
    {
        Value lhs=op.getLhs();
        Value rhs=op.getRhs();
        
       // check RHS == 0
        if (auto cst = rhs.getDefiningOp<arith::ConstantOp>()) {
            if (auto intAttr = dyn_cast<IntegerAttr>(cst.getValue())) {
                if (intAttr.getInt() == 0) {
                    rewriter.replaceOp(op, lhs);
                    return success();
                }
            }
        }

        // check LHS == 0
        if (auto cst = lhs.getDefiningOp<arith::ConstantOp>()) {
            if (auto intAttr = dyn_cast<IntegerAttr>(cst.getValue())) {
                if (intAttr.getInt() == 0) {
                    rewriter.replaceOp(op, rhs);
                    return success();
                }
            }
        }


     return failure();


    }
};