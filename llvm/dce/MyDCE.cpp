#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"

/*
cmake -G Ninja   -DLLVM_DIR=$(/wrk/llvm-project/build/bin/llvm-config --cmakedir)   ..
ninja
/wrk/llvm-project/build/bin/opt   -load-pass-plugin ./build/libMyDCE.so   -passes="my-dce"   test.ll   -S   -o output.ll
*/

using namespace llvm;
struct MyDCE: public PassInfoMixin<MyDCE>
{
    
    //Preserved Analyses is a class ?? & here it is boolean return value 
    //F used to get the actual IR that you are working use it to iterate blocks instr & modify code 
    //AM hold the cache of precomputed analysis use it when we need structural info

    PreservedAnalyses run(Function &F,FunctionAnalysisManager &AM)
    {
        bool Changed = true;

        while (Changed)
        {
        Changed = false;
        SmallVector<Instruction *,16> Dead; 
        //how is holds the instruction does it hold it with value
        llvm::errs() << "Running MyDCE on function: "
                 << F.getName() << "\n";
        
        for(auto &BB:F)
        {
            for(auto &I:BB)
            {
                if(I.use_empty() && !I.isTerminator()/*if not a terminator*/ && !I.mayHaveSideEffects())
                    Dead.push_back(&I); 
                //pass py reference to read we need pointer
            }
        }
        
        for(auto *I:Dead)
        {
            llvm::errs() << "Deleting: " << *I << "\n";
            I->eraseFromParent();
            Changed = true; 
        }
        //remove the instruction from parent 
        return Dead.empty() ? PreservedAnalyses::all() : PreservedAnalyses::none();
    }
    }
};


//Pass registration
//To prevent C from performing name mangling
// LLVM_ATTRIBUTE_WEAK If another definition of the same symbol exists, that's okay.
extern "C" LLVM_ATTRIBUTE_WEAK 
PassPluginLibraryInfo llvmGetPassPluginInfo() {

  return {
      LLVM_PLUGIN_API_VERSION,
      "MyDCE",
      LLVM_VERSION_STRING,

      [](PassBuilder &PB) {

        PB.registerPipelineParsingCallback(
            [](StringRef Name,
               FunctionPassManager &FPM,
               ArrayRef<PassBuilder::PipelineElement>) {

              if (Name == "my-dce") {
                FPM.addPass(MyDCE());
                return true;
              }

              return false;
            });
      }};
}