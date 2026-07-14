#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;


int main()
{
    //Each backend registers itself
    
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();

    //List everything in registry
    
    llvm::outs() <<"All registered targets \n";
    
    for(const auto &T:llvm::TargetRegistry::targets())
    {
        llvm::outs() <<" "<<T.getName() <<"--"<<T.getShortDescription() << "\n";
    }

    //Look up a specific target by triple
    
    llvm::outs() <<"Lookup by triple " <<"\n";
    std::string Error;
   
    auto *RV=llvm::TargetRegistry::lookupTarget("x86_64",Error);
    
    if(RV)
        llvm::outs() <<"x86 :"<<RV->getName() <<"\n";
    else
        llvm::outs() <<"x86 "<< Error <<"\n";

}