#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/CFG.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

#include <set>

using namespace llvm;


void DFS(BasicBlock *BB,
         std::set<BasicBlock*> &Visited)
{

    if(Visited.count(BB))
        return;


    Visited.insert(BB);


    errs() << "Visited : "
           << BB->getName()
           << "\n";


    for(BasicBlock *Succ :
            successors(BB))
    {
        DFS(Succ,Visited);
    }
}



int main(int argc,char **argv)
{

    InitLLVM X(argc,argv);


    LLVMContext Context;

    SMDiagnostic Err;


    auto M =
        parseIRFile(argv[1],
                    Err,
                    Context);


    if(!M)
    {
        Err.print(argv[0],errs());
        return 1;
    }


    for(Function &F:*M)
    {

        if(F.isDeclaration())
            continue;


        errs()<<"Function : "
              <<F.getName()
              <<"\n";


        std::set<BasicBlock*> Visited;


        BasicBlock &Entry =
            F.getEntryBlock();


        DFS(&Entry,Visited);


        errs()<<"\nUnreachable Blocks\n";


        for(BasicBlock &BB:F)
        {

            if(!Visited.count(&BB))
            {
                errs()
                <<BB.getName()
                <<"\n";
            }
        }
    }

}