#include "llvm/TargetParser/Triple.h"
#include "llvm/Support/raw_ostream.h"

int main()
{
    // pointer array
    const char *triple[] = {
        "riscv32-unknown-elf",
        "x86_64-linux-gnu",
        "aarch64-apple-darwin",
    };

    for(auto *t:triple) {
        llvm::Triple T(t);
        llvm::outs()<< "Triple: "<<t<<"\n"<< "Arch: "<<T.getArchName()<<"\n"<< "Vendor: "<<T.getOSName()<<"\n"<<T.isArch32Bit()<<"\n";
    }

    llvm::Triple Custom;
    Custom.setArch(llvm::Triple::riscv32);
    llvm::outs()<<Custom.str()<<"\n";


}