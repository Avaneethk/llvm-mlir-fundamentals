#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;

int main()
{
llvm::DenseMap<llvm::StringRef, int> idx;
idx["foo"] = 42;
for(auto &k:idx)
llvm::outs()<< "\n"<<k.first<<" "<<k.second<<" "<<"\n";
return 0;
}