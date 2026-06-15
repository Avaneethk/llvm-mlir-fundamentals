module {
  llvm.func @malloc(i64) -> !llvm.ptr
  llvm.mlir.global private constant @__constant_1x6x6xi32_0(dense<-298> : tensor<1x6x6xi32>) {addr_space = 0 : i32, alignment = 64 : i64} : !llvm.array<1 x array<6 x array<6 x i32>>>
  llvm.mlir.global private constant @__constant_1x6x6xi32(dense<6220> : tensor<1x6x6xi32>) {addr_space = 0 : i32, alignment = 64 : i64} : !llvm.array<1 x array<6 x array<6 x i32>>>
  llvm.func @printMemrefI32(i64, !llvm.ptr) attributes {sym_visibility = "private"}
  llvm.func @printMemrefF32(i64, !llvm.ptr) attributes {sym_visibility = "private"}
  llvm.func @main() {
    %0 = llvm.mlir.constant(4 : index) : i64
    %1 = llvm.mlir.constant(0 : index) : i64
    %2 = llvm.mlir.constant(0 : index) : i64
    %3 = llvm.mlir.constant(1 : index) : i64
    %4 = llvm.mlir.constant(-290 : i32) : i32
    %5 = llvm.mlir.constant(6 : index) : i64
    %6 = llvm.mlir.constant(1 : index) : i64
    %7 = llvm.mlir.constant(6 : index) : i64
    %8 = llvm.mlir.constant(6 : index) : i64
    %9 = llvm.mlir.constant(1 : index) : i64
    %10 = llvm.mlir.constant(36 : index) : i64
    %11 = llvm.mlir.constant(36 : index) : i64
    %12 = llvm.mlir.zero : !llvm.ptr
    %13 = llvm.getelementptr %12[36] : (!llvm.ptr) -> !llvm.ptr, i32
    %14 = llvm.ptrtoint %13 : !llvm.ptr to i64
    %15 = llvm.mlir.constant(64 : index) : i64
    %16 = llvm.add %14, %15 : i64
    %17 = llvm.call @malloc(%16) : (i64) -> !llvm.ptr
    %18 = llvm.ptrtoint %17 : !llvm.ptr to i64
    %19 = llvm.mlir.constant(1 : index) : i64
    %20 = llvm.sub %15, %19 : i64
    %21 = llvm.add %18, %20 : i64
    %22 = llvm.urem %21, %15 : i64
    %23 = llvm.sub %21, %22 : i64
    %24 = llvm.inttoptr %23 : i64 to !llvm.ptr
    %25 = llvm.mlir.poison : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)>
    %26 = llvm.insertvalue %17, %25[0] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %27 = llvm.insertvalue %24, %26[1] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %28 = llvm.mlir.constant(0 : index) : i64
    %29 = llvm.insertvalue %28, %27[2] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %30 = llvm.insertvalue %6, %29[3, 0] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %31 = llvm.insertvalue %7, %30[3, 1] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %32 = llvm.insertvalue %8, %31[3, 2] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %33 = llvm.insertvalue %10, %32[4, 0] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %34 = llvm.insertvalue %8, %33[4, 1] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %35 = llvm.insertvalue %9, %34[4, 2] : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> 
    %36 = llvm.mul %3, %0 : i64
    %37 = llvm.mlir.constant(0 : index) : i64
    %38 = llvm.mlir.constant(1 : index) : i64
    %39 = llvm.mlir.constant(4 : index) : i64
    %40 = llvm.mlir.constant(1 : index) : i64
    %41 = llvm.mlir.constant(1 : index) : i64
    %42 = llvm.mlir.constant(1 : index) : i64
    %43 = llvm.mlir.constant(1 : index) : i64
    %44 = llvm.mul %36, %39 : i64
    llvm.br ^bb1(%2 : i64)
  ^bb1(%45: i64):  // 2 preds: ^bb0, ^bb39
    %46 = llvm.icmp "slt" %45, %3 : i64
    llvm.cond_br %46, ^bb2, ^bb40
  ^bb2:  // pred: ^bb1
    llvm.br ^bb3(%2 : i64)
  ^bb3(%47: i64):  // 2 preds: ^bb2, ^bb38
    %48 = llvm.icmp "slt" %47, %5 : i64
    llvm.cond_br %48, ^bb4, ^bb39
  ^bb4:  // pred: ^bb3
    llvm.br ^bb5(%2 : i64)
  ^bb5(%49: i64):  // 2 preds: ^bb4, ^bb37
    %50 = llvm.icmp "slt" %49, %5 : i64
    llvm.cond_br %50, ^bb6, ^bb38
  ^bb6:  // pred: ^bb5
    llvm.br ^bb7(%1 : i64)
  ^bb7(%51: i64):  // 2 preds: ^bb6, ^bb36
    %52 = llvm.icmp "slt" %51, %3 : i64
    llvm.cond_br %52, ^bb8, ^bb37
  ^bb8:  // pred: ^bb7
    llvm.br ^bb9(%1 : i64)
  ^bb9(%53: i64):  // 2 preds: ^bb8, ^bb35
    %54 = llvm.icmp "slt" %53, %36 : i64
    llvm.cond_br %54, ^bb10, ^bb36
  ^bb10:  // pred: ^bb9
    llvm.br ^bb11(%1 : i64)
  ^bb11(%55: i64):  // 2 preds: ^bb10, ^bb34
    %56 = llvm.icmp "slt" %55, %3 : i64
    llvm.cond_br %56, ^bb12, ^bb35
  ^bb12:  // pred: ^bb11
    llvm.br ^bb13(%37 : i64)
  ^bb13(%57: i64):  // 2 preds: ^bb12, ^bb33
    %58 = llvm.icmp "slt" %57, %3 : i64
    llvm.cond_br %58, ^bb14, ^bb34
  ^bb14:  // pred: ^bb13
    llvm.br ^bb15(%37 : i64)
  ^bb15(%59: i64):  // 2 preds: ^bb14, ^bb32
    %60 = llvm.icmp "slt" %59, %44 : i64
    llvm.cond_br %60, ^bb16, ^bb33
  ^bb16:  // pred: ^bb15
    llvm.br ^bb17(%37 : i64)
  ^bb17(%61: i64):  // 2 preds: ^bb16, ^bb31
    %62 = llvm.icmp "slt" %61, %3 : i64
    llvm.cond_br %62, ^bb18, ^bb32
  ^bb18:  // pred: ^bb17
    llvm.br ^bb19(%37 : i64)
  ^bb19(%63: i64):  // 2 preds: ^bb18, ^bb30
    %64 = llvm.icmp "slt" %63, %3 : i64
    llvm.cond_br %64, ^bb20, ^bb31
  ^bb20:  // pred: ^bb19
    llvm.br ^bb21(%37 : i64)
  ^bb21(%65: i64):  // 2 preds: ^bb20, ^bb29
    %66 = llvm.icmp "slt" %65, %3 : i64
    llvm.cond_br %66, ^bb22, ^bb30
  ^bb22:  // pred: ^bb21
    llvm.br ^bb23(%37 : i64)
  ^bb23(%67: i64):  // 2 preds: ^bb22, ^bb28
    %68 = llvm.icmp "slt" %67, %3 : i64
    llvm.cond_br %68, ^bb24, ^bb29
  ^bb24:  // pred: ^bb23
    %69 = llvm.add %57, %45 : i64
    %70 = llvm.add %59, %47 : i64
    %71 = llvm.add %61, %49 : i64
    %72 = llvm.add %63, %51 : i64
    %73 = llvm.add %65, %53 : i64
    %74 = llvm.add %67, %55 : i64
    %75 = llvm.mlir.constant(true) : i1
    %76 = llvm.mul %57, %3 : i64
    %77 = llvm.add %76, %45 : i64
    %78 = llvm.icmp "ult" %77, %3 : i64
    %79 = llvm.mul %59, %36 : i64
    %80 = llvm.add %79, %47 : i64
    %81 = llvm.icmp "ult" %80, %5 : i64
    %82 = llvm.and %78, %81 : i1
    %83 = llvm.mul %61, %3 : i64
    %84 = llvm.add %83, %49 : i64
    %85 = llvm.icmp "ult" %84, %5 : i64
    %86 = llvm.and %82, %85 : i1
    %87 = llvm.mul %63, %3 : i64
    %88 = llvm.add %87, %51 : i64
    %89 = llvm.icmp "ult" %88, %3 : i64
    %90 = llvm.and %86, %89 : i1
    %91 = llvm.mul %65, %3 : i64
    %92 = llvm.add %91, %53 : i64
    %93 = llvm.icmp "ult" %92, %36 : i64
    %94 = llvm.and %90, %93 : i1
    %95 = llvm.mul %67, %3 : i64
    %96 = llvm.add %95, %55 : i64
    %97 = llvm.icmp "ult" %96, %3 : i64
    %98 = llvm.and %94, %97 : i1
    llvm.cond_br %98, ^bb25, ^bb28
  ^bb25:  // pred: ^bb24
    %99 = llvm.add %72, %69 : i64
    %100 = llvm.add %73, %70 : i64
    %101 = llvm.add %74, %71 : i64
    %102 = llvm.mul %72, %3 : i64
    %103 = llvm.add %102, %69 : i64
    %104 = llvm.icmp "ult" %103, %3 : i64
    %105 = llvm.mul %73, %3 : i64
    %106 = llvm.add %105, %70 : i64
    %107 = llvm.icmp "ult" %106, %5 : i64
    %108 = llvm.and %104, %107 : i1
    %109 = llvm.mul %74, %3 : i64
    %110 = llvm.add %109, %71 : i64
    %111 = llvm.icmp "ult" %110, %5 : i64
    %112 = llvm.and %108, %111 : i1
    llvm.cond_br %112, ^bb26, ^bb27
  ^bb26:  // pred: ^bb25
    %113 = llvm.mlir.constant(36 : index) : i64
    %114 = llvm.mul %99, %113 overflow<nsw, nuw> : i64
    %115 = llvm.mlir.constant(6 : index) : i64
    %116 = llvm.mul %100, %115 overflow<nsw, nuw> : i64
    %117 = llvm.add %114, %116 overflow<nsw, nuw> : i64
    %118 = llvm.add %117, %101 overflow<nsw, nuw> : i64
    %119 = llvm.getelementptr inbounds|nuw %24[%118] : (!llvm.ptr, i64) -> !llvm.ptr, i32
    llvm.store %4, %119 : i32, !llvm.ptr
    llvm.br ^bb27
  ^bb27:  // 2 preds: ^bb25, ^bb26
    llvm.br ^bb28
  ^bb28:  // 2 preds: ^bb24, ^bb27
    %120 = llvm.add %67, %3 : i64
    llvm.br ^bb23(%120 : i64)
  ^bb29:  // pred: ^bb23
    %121 = llvm.add %65, %3 : i64
    llvm.br ^bb21(%121 : i64)
  ^bb30:  // pred: ^bb21
    %122 = llvm.add %63, %3 : i64
    llvm.br ^bb19(%122 : i64)
  ^bb31:  // pred: ^bb19
    %123 = llvm.add %61, %3 : i64
    llvm.br ^bb17(%123 : i64)
  ^bb32:  // pred: ^bb17
    %124 = llvm.add %59, %36 : i64
    llvm.br ^bb15(%124 : i64)
  ^bb33:  // pred: ^bb15
    %125 = llvm.add %57, %3 : i64
    llvm.br ^bb13(%125 : i64)
  ^bb34:  // pred: ^bb13
    %126 = llvm.add %55, %3 : i64
    llvm.br ^bb11(%126 : i64)
  ^bb35:  // pred: ^bb11
    %127 = llvm.add %53, %3 : i64
    llvm.br ^bb9(%127 : i64)
  ^bb36:  // pred: ^bb9
    %128 = llvm.add %51, %3 : i64
    llvm.br ^bb7(%128 : i64)
  ^bb37:  // pred: ^bb7
    %129 = llvm.add %49, %3 : i64
    llvm.br ^bb5(%129 : i64)
  ^bb38:  // pred: ^bb5
    %130 = llvm.add %47, %44 : i64
    llvm.br ^bb3(%130 : i64)
  ^bb39:  // pred: ^bb3
    %131 = llvm.add %45, %3 : i64
    llvm.br ^bb1(%131 : i64)
  ^bb40:  // pred: ^bb1
    %132 = llvm.mlir.constant(1 : index) : i64
    %133 = llvm.alloca %132 x !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)> : (i64) -> !llvm.ptr
    llvm.store %35, %133 : !llvm.struct<(ptr, ptr, i64, array<3 x i64>, array<3 x i64>)>, !llvm.ptr
    %134 = llvm.mlir.constant(3 : index) : i64
    %135 = llvm.mlir.poison : !llvm.struct<(i64, ptr)>
    %136 = llvm.insertvalue %134, %135[0] : !llvm.struct<(i64, ptr)> 
    %137 = llvm.insertvalue %133, %136[1] : !llvm.struct<(i64, ptr)> 
    llvm.call @printMemrefI32(%134, %133) : (i64, !llvm.ptr) -> ()
    llvm.return
  }
}

