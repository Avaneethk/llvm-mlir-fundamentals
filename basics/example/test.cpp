#include<iostream>

using namespace std;

/*
loop dependency 
use-def chain
for %next_i we have  %i = phi i32[0, %entry],[%next_i, %body]
for %next_s we have  %s = phi i32[0, %entry],[%next_s, %body]

entry:
  br label %loop
loop:
  %i = phi i32[0, %entry],[%next_i, %body]
  %s = phi i32[0, %entry],[%next_s, %body]
  %cmp = icmp slt i32 %i, 5
  br i1 %cmp,label %body,label %exit
body:
  %next_s = add i32 %s, %i
  %next_i = add i32 %i, 1
  br label %loop
exit:
  ret i32 %s

MLIR 

cf.br ^loop(%c0, %c0)
^loop(%i : i32, %s : i32):
  %cmp = arith.cmpi slt, %i, %c5 : i32
  cf.cond_br %cmp,^body,^exit(%s)
^body:
  %nextS = arith.addi %s, %i : i32
  %nextI = arith.addi %i, %c1 : i32
  cf.br ^loop(%nextI, %nextS)
^exit(%result : i32):
  return %result : i32

Why PHI/block arguments are needed?
Because i and s receive values from two different predecessors:
entry  -> initial values
body   -> loop-carried values

zero-overhead abstractions

func.func @foo(%n : i32) -> i32 {

  %c0 = arith.constant 0 : i32
  %c2 = arith.constant 1 : i32

  %result = scf.while (%i = %c0) : (i32) -> (i32) 
  {
    %cond = arith.cmpi slt, %i, %n : i32
    scf.condition(%cond) %i : i32 ; Continue looping Pass value 4 to the body region if condition is true
  }
  do
  {
  ^bb0(%i : i32):
    %next = arith.addi %i, %c2 : i32
    scf.yield %next : i32 ; "I'm done with this iteration. Here are the values for the next iteration."
  }

  func.return %result : i32
}

*/

int main()
{
    int i = 0;
    int s = 0;

    while(i < 5)
    {
        s = s + i;
        i++;
    }
    cout<<"sum is :"<<s<<endl;

    return s;
}