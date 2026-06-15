//SmallVector
//What — llvm::SmallVector<T, N> is a dynamic array that stores up to N elements inline (no heap) and spills to the heap when larger.

//run command : clang++ -std=c++17  llvm_SmallVector.cpp -I/usr/lib/llvm-18/include/ -O2 -o  llvm_SmallVector

//Core LLVM ADTs


#include<iostream>
using namespace std;

#include "llvm/ADT/SmallVector.h"

void exampleSmallVector() {
  llvm::SmallVector<int, 8> worklist;
  worklist.push_back(1);
  worklist.push_back(2);
  for (int v : worklist) {
    cout<<"v:"<<v<<endl;
  }
}


int main()
{
    exampleSmallVector();
    return 0;
}