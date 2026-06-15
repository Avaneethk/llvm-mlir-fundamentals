
#include<iostream>
#include<vector>

using namespace std;

#include "llvm/ADT/ArrayRef.h"

//ArrayRef<T> is a non‑owning, read‑only view of contiguous memory;

//Run command clang++ -std=c++17 llvm_Arrayref.cpp $(/wrk/llvm-project/build/bin/llvm-config --cxxflags --ldflags --libs support) -O2 -o llvm_Arrayref


void process(llvm::ArrayRef<int> arr) {
  for (int x : arr) { cout<<"X: "<<x<<endl; }
}

int main() {
  std::vector<int> v = {1,2,3};
  process(v); 
  return 0;
}
