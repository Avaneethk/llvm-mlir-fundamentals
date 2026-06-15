#map = affine_map<(d0, d1, d2) -> (d0, d1 - d2)>
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
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c4 = arith.constant 4 : index
    %c1_0 = arith.constant 1 : index
    %7 = arith.muli %4, %c1 : index
    %8 = arith.muli %4, %c4 : index
    %9 = arith.muli %4, %c1_0 : index
    scf.parallel (%arg0, %arg1, %arg2) = (%6, %6, %6) to (%4, %2, %2) step (%7, %8, %9) {
      %10 = affine.min #map(%7, %4, %arg0)
      %11 = affine.min #map(%8, %2, %arg1)
      %12 = affine.min #map(%9, %2, %arg2)
      scf.parallel (%arg3, %arg4, %arg5) = (%c0, %c0, %c0) to (%10, %11, %12) step (%4, %4, %4) {
        %13 = arith.addi %arg3, %arg0 : index
        %14 = arith.addi %arg4, %arg1 : index
        %15 = arith.addi %arg5, %arg2 : index
        memref.store %0, %alloc[%13, %14, %15] : memref<1x6x6xi32>
        scf.reduce 
      }
      scf.reduce 
    }
    %cast = memref.cast %alloc : memref<1x6x6xi32> to memref<*xi32>
    call @printMemrefI32(%cast) : (memref<*xi32>) -> ()
    return
  }
}

