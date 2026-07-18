#include "llvm/IR/Module.h"
#include "llvm/IR/CFG.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"

#include <map>
#include <vector>
#include <algorithm>

using namespace llvm;


std::map<BasicBlock*,int> State;


std::vector<BasicBlock*> PostOrder;



void DFS(BasicBlock *BB)
{

    State[BB]=1;

    
    errs()<<"Visit "
          <<BB->getName()
          <<"\n";


    for(BasicBlock *Succ:
        successors(BB))
    {


        if(State[Succ]==1)
        {
            errs()<<"Back Edge : "
                  <<BB->getName()
                  <<" -> "
                  <<Succ->getName()
                  <<"\n";
        }


        else if(State[Succ]==0)
        {
            DFS(Succ);
        }
    }


    State[BB]=2;


    PostOrder.push_back(BB);
}



int main(int argc,char **argv)
{

    InitLLVM X(argc,argv);


    LLVMContext Context;

    SMDiagnostic Err;


    auto M=parseIRFile(argv[1],
                      Err,
                      Context);


    if(!M)
        return 1;



    Function &F=*M->begin();
    outs()<<F.getName()<<"\n";


    BasicBlock &Entry=F.getEntryBlock();
    outs()<<Entry.getName()<<"\n";



    DFS(&Entry);



    errs()<<"\nPost Order\n";


    for(auto B:PostOrder)
        errs()<<B->getName()<<"\n";



    reverse(PostOrder.begin(),
            PostOrder.end());



    errs()<<"\nReverse Post Order\n";


    for(auto B:PostOrder)
        errs()<<B->getName()<<"\n";


}