module {
  memref.global "private" constant @__constant_1x6x6xi32_0 : memref<1x6x6xi32> = dense<-298> {alignment = 64 : i64}
  memref.global "private" constant @__constant_1x6x6xi32 : memref<1x6x6xi32> = dense<6220> {alignment = 64 : i64}
  func.func private @printMemrefI32(memref<*xi32>)
  func.func private @printMemrefF32(memref<*xf32>)
  func.func @main() {
    %0 = llvm.mlir.constant(-290 : i32) : i32
    %1 = llvm.mlir.constant(6 : index) : i64
    %2 = builtin.unrealized_conversion_cast %1 : i64 to index
    %3 = llvm.mlir.constant(1 : index) : i64
    %4 = builtin.unrealized_conversion_cast %3 : i64 to index
    %5 = llvm.mlir.constant(0 : index) : i64
    %6 = builtin.unrealized_conversion_cast %5 : i64 to index
    %alloc = memref.alloc() {alignment = 64 : i64} : memref<1x6x6xi32>
    scf.parallel (%arg0, %arg1, %arg2) = (%6, %6, %6) to (%4, %2, %2) step (%4, %4, %4) {
      memref.store %0, %alloc[%arg0, %arg1, %arg2] : memref<1x6x6xi32>
      scf.reduce 
    }
    %cast = memref.cast %alloc : memref<1x6x6xi32> to memref<*xi32>
    call @printMemrefI32(%cast) : (memref<*xi32>) -> ()
    return
  }
}

