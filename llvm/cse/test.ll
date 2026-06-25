define i32 @foo(i32 %x, i32 %y) {
entry:

  %a = add i32 %x, %y

  %b = add i32 %x, %y

  %c = mul i32 %a, %b

  ret i32 %c
}