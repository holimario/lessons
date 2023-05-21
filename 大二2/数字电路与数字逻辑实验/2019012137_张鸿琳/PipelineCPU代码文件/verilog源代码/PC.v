// `timescale 1ns / 1ps

module PC(reset, clk, PC_i, keep, PC_o);
    //Input Clock Signals
    input reset;             
    input clk;                     
    input [31:0] PC_i;
    input keep;
    output reg [31:0] PC_o; 


    always@(posedge reset or posedge clk)
    begin
        if(reset) begin
            PC_o <= 0;
        end else if(!keep)begin
            PC_o <= PC_i;
        end
        else PC_o <= PC_o;
    end
endmodule