#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Module.h"

using namespace llvm;

int main(int argc, char **argv) {

    InitLLVM X(argc, argv);

    if (argc != 2) {
        errs() << "Usage: ./cfg_traversal <file.ll>\n";
        return 1;
    }

    LLVMContext Context;
    SMDiagnostic Err;

    std::unique_ptr<Module> M =
        parseIRFile(argv[1], Err, Context);

    if (!M) {
        Err.print(argv[0], errs());
        return 1;
    }

    //-------------------------------------------------------
    // Traverse every function
    //-------------------------------------------------------

    for (Function &F : *M) {

        if (F.isDeclaration())
            continue;

        outs() << "=====================================\n";
        outs() << "Function : " << F.getName() << "\n";
        outs() << "=====================================\n";

        //---------------------------------------------------
        // Traverse every Basic Block
        //---------------------------------------------------

        for (BasicBlock &BB : F) {

            outs() << "\n-------------------------------------\n";
            outs() << "Basic Block : ";

            if (BB.hasName())
                outs() << BB.getName();
            else
                outs() << "(unnamed)";

            outs() << "\n";

            //-----------------------------------------------
            // Print predecessors
            //-----------------------------------------------

            outs() << "Predecessors : ";

            for (BasicBlock *Pred : predecessors(&BB))
                outs() << Pred->getName() << " ";

            outs() << "\n";

            //-----------------------------------------------
            // Print successors
            //-----------------------------------------------

            outs() << "Successors   : ";

            for (BasicBlock *Succ : successors(&BB))
                outs() << Succ->getName() << " ";

            outs() << "\n";

            //-----------------------------------------------
            // Print Instructions
            //-----------------------------------------------

            outs() << "\nInstructions\n";

            for (Instruction &I : BB) {

                outs() << "---------------------------------\n";

                outs() << "Opcode : "
                       << I.getOpcodeName()
                       << "\n";

                outs() << "Instruction : ";

                I.print(outs());

                outs() << "\n";

                //-------------------------------------------
                // Operands
                //-------------------------------------------

                outs() << "Operands\n";

                for (Use &U : I.operands()) {

                    Value *V = U.get();

                    outs() << "    ";

                    if (V->hasName())
                        outs() << V->getName();
                    else
                        V->print(outs());

                    outs() << "\n";
                }
            }
        }
    }

    return 0;
}