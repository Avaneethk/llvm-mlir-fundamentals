
#include<iostream>
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/Twine.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;

//StringRef — non‑owning string view. Use for fast string parsing and diagnostics.
//Twine — lightweight concatenation helper; do not store a Twine. Convert to std::string or StringRef immediately.

void logOpName(llvm::StringRef name) {
  llvm::errs() << "op: " << name << "\n";
}

void buildMessage() {
  llvm::Twine t = llvm::Twine("op: ") + "myop";
  llvm::errs() << t.str() << "\n"; // .str() materializes std::string
}

int main()
{
    logOpName("LLVM Fundamentals");
    buildMessage();
    
    return 0;

}