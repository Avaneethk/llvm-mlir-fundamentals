#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/PassManager.h"

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Plugins/PassPlugin.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"


#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct MyCSE : public PassInfoMixin<MyCSE> {

  PreservedAnalyses run(Function &F,
                        FunctionAnalysisManager &AM) {

    bool Changed = false;

    for (BasicBlock &BB : F) {

      DenseMap<StringRef, Instruction *> ExprTable;
      SmallVector<Instruction *, 16> Dead;

      for (Instruction &I : BB) {

        auto *BO = dyn_cast<BinaryOperator>(&I);
        if (!BO)
          continue;

     
        std::string Key;
        raw_string_ostream OS(Key);

        //OS << BO->getOpcodeName() << "_";
        //BO->getOperand(0)->printAsOperand(OS, false);
        //OS << "_";
        //BO->getOperand(1)->printAsOperand(OS, false);
        //OS.flush();

        auto It = ExprTable.find(Key);

        if (It != ExprTable.end()) {

          Instruction *Existing = It->second;

          errs() << "[CSE] Replacing:\n";
          errs() << "  " << I << "\n";
          errs() << "with\n";
          errs() << "  " << *Existing << "\n";

          I.replaceAllUsesWith(Existing);
          Dead.push_back(&I);
          Changed = true;

        } else {
          ExprTable[Key] = &I;
        }
      }

      
      for (auto &Pair : ExprTable) {
        errs() << Pair.first << " -> " << *(Pair.second) << "\n";
      }

      for (Instruction *I : Dead)
        I->eraseFromParent();
    }

    return Changed ? PreservedAnalyses::none()
                   : PreservedAnalyses::all();
  }
};

} // namespace

// ----------------------------
// Plugin Registration
// ----------------------------
extern "C" LLVM_ATTRIBUTE_WEAK
PassPluginLibraryInfo llvmGetPassPluginInfo() {

  return {
      LLVM_PLUGIN_API_VERSION,
      "MyCSE",
      LLVM_VERSION_STRING,

      [](PassBuilder &PB) {

        PB.registerPipelineParsingCallback(
            [](StringRef Name,
               FunctionPassManager &FPM,
               ArrayRef<PassBuilder::PipelineElement>) {

              if (Name == "my-cse") {
                FPM.addPass(MyCSE());
                return true;
              }

              return false;
            });
      }};
}