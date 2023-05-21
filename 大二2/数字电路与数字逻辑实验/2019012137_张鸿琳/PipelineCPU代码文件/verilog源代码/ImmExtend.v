// `timescale 1ns / 1ps

module ImmExtend(ExtOp, Immediate, ImmExtOut); 
    //Input Control Signals
    input [1:0] ExtOp; //'0'-zero extension, '1'-signed extension
    //Input
    input [15:0] Immediate;
    //Output
    output [31:0] ImmExtOut;
    
    assign ImmExtOut = (ExtOp==2'd0)? {16'h0000, Immediate}:
                        (ExtOp==2'd1)? {{16{Immediate[15]}}, Immediate}:
                        (ExtOp==2'd2)? {Immediate, 16'h0000}:32'd0;

endmodule
