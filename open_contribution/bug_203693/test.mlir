func.func @member_access(
    %arg0: !emitc.lvalue<!emitc.opaque<"mystruct">>) {
        %0 = "emitc.member"(%arg0) {member = "a"}
        : (!emitc.lvalue<!emitc.opaque<"mystruct">>)
        -> !emitc.lvalue<i32>

        return}