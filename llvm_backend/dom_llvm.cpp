#include "llvm/IR/CFG.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"

#include "llvm/IR/Dominators.h"

#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

void printTree(const DomTreeNode *Node, int Depth = 0) {

    for (int i = 0; i < Depth; i++)
        outs() << "  ";

    outs() << Node->getBlock()->getName() << "\n";

    for (DomTreeNode *Child : *Node)
        printTree(Child, Depth + 1);
}

int main(int argc, char **argv) {

    InitLLVM X(argc, argv);

    if (argc != 2) {
        errs() << "Usage: " << argv[0] << " test.ll\n";
        return 1;
    }

    LLVMContext Context;
    SMDiagnostic Err;

    auto M = parseIRFile(argv[1], Err, Context);

    if (!M) {
        Err.print(argv[0], errs());
        return 1;
    }

    for (Function &F : *M) {

        if (F.isDeclaration())
            continue;

        outs() << "====================================\n";
        outs() << "Function : " << F.getName() << "\n";
        outs() << "====================================\n\n";

        //--------------------------------------------------
        // Build Dominator Tree
        //--------------------------------------------------

        DominatorTree DT(F);

        //--------------------------------------------------
        // Immediate Dominators
        //--------------------------------------------------

        outs() << "Immediate Dominators\n";
        outs() << "---------------------------\n";

        for (BasicBlock &BB : F) {

            outs() << BB.getName() << " : ";

            DomTreeNode *Node = DT.getNode(&BB);

            if (Node->getIDom())
                outs() << Node->getIDom()->getBlock()->getName();
            else
                outs() << "None";

            outs() << "\n";
        }

        //--------------------------------------------------
        // Dominator Tree
        //--------------------------------------------------

        outs() << "\nDominator Tree\n";
        outs() << "---------------------------\n";

        printTree(DT.getRootNode());

        //--------------------------------------------------
        // Dominance Queries
        //--------------------------------------------------

        outs() << "\nDominance Queries\n";
        outs() << "---------------------------\n";

        BasicBlock *Entry = nullptr;
        BasicBlock *Header = nullptr;
        BasicBlock *Body = nullptr;
        BasicBlock *Exit = nullptr;

        for (BasicBlock &BB : F) {

            if (BB.getName() == "entry")
                Entry = &BB;
            else if (BB.getName() == "header")
                Header = &BB;
            else if (BB.getName() == "body")
                Body = &BB;
            else if (BB.getName() == "exit")
                Exit = &BB;
        }

    }

    return 0;
}