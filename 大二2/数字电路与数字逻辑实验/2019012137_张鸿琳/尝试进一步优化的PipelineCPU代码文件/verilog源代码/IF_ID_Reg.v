// `timescale 1ns / 1ps

module IF_ID_Reg(
    input wire clk, 
    input wire reset, 
    input wire flush, 
    input wire keep,
    input wire [31:0] Inst, 
    input wire [31:0] PCin, 
    output reg [5:0] OpCode,
    output reg [5:0] Funct,
    output reg [4:0] rs,
    output reg [4:0] rt,
    output reg [4:0] rd,
    output reg [4:0] shamt,
    output reg [15:0] imm,
    output reg [31:0] PCout
    );

always @(posedge clk or posedge reset) begin
    if(reset )begin//|| (flush && !keep)
        OpCode<=0;
        Funct<=0;
        rs<=0;
        rt<=0;
        rd<=0;
        shamt<=0;
        imm<=0;
        PCout<=0;
    end
    else if(flush)begin
        OpCode<=0;
        Funct<=0;
        rs<=0;
        rt<=0;
        rd<=0;
        shamt<=0;
        imm<=0;
        PCout<=0;
    end
    else begin
        if(!keep)begin
            OpCode<=Inst[31:26];
            rs<=Inst[25:21];
            rt<=Inst[20:16];
            rd<=Inst[15:11];
            shamt<=Inst[10:6];
            Funct<=Inst[5:0];
            imm<=Inst[15:0];
            PCout<=PCin;
        end
        else begin
            OpCode<=OpCode;
            rs<=rs;
            rt<=rt;
            rd<=rd;
            shamt<=shamt;
            Funct<=Funct;
            imm<=imm;
            PCout<=PCout;
        end
    end
end
endmodule