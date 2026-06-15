module {
  func.func private @printMemrefI32(tensor<*xi32>)
  func.func private @printMemrefF32(tensor<*xf32>)
  func.func @main() {
    %7 = "tosa.const"() <{values = dense<6220> : tensor<1x6x6xi32>}> : () -> tensor<1x6x6xi32>
    %9 = "tosa.const"() <{values = dense<-298> : tensor<1x6x6xi32>}> : () -> tensor<1x6x6xi32>
    %51 = tosa.bitwise_or %7, %9 : (tensor<1x6x6xi32>, tensor<1x6x6xi32>) -> tensor<1x6x6xi32>
    %cast = tensor.cast %51 : tensor<1x6x6xi32> to tensor<*xi32>
    call @printMemrefI32(%cast) : (tensor<*xi32>) -> ()
    return
  }
}