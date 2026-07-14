#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetLowering.h"
/*
clang++ 03_target_machine.cpp     -o 03_target_machine     $(/wrk/llvm-project/build-riscv/bin/llvm-config \
        --cxxflags \
        --ldflags \
        --system-libs \
        --libs all)
*/
using namespace llvm;
int main()
{
    InitializeAllTargetInfos();
    InitializeAllTargets();
    InitializeAllTargetMCs();
    InitializeAllAsmPrinters();

    llvm::Triple T("riscv32-unknown-elf");

    std::string Error;
    auto *Target = llvm::TargetRegistry::lookupTarget(T,Error);

    llvm::TargetOptions Opt;
    auto *TM = Target->createTargetMachine(
        T,
        "generic-rv32",
        "+m,+f",
        Opt,
        llvm::Reloc::Static
    );
    llvm::outs()<<"Target Machine"<<"\n";
    llvm::outs()<<"Triple: "<<TM->getTargetTriple().str()<<"\n";
    llvm::outs()<<"CPU:"<<TM->getTargetFeatureString()<<"\n";
    llvm::outs()<<"Datalayout "<<TM->createDataLayout().getStringRepresentation()<<"\n";

    llvm::LLVMContext ctx;
    llvm::SMDiagnostic Diag;
    auto M = llvm::parseIRFile("test.ll",Diag,ctx);
    M->setDataLayout(TM->createDataLayout());

    return 0;
}