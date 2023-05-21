// `timescale 1ns / 1ps

module MEM_WB_Reg(
    input wire clk,
    input wire reset,
    input wire RegWri,
    input wire [1:0] MemtoRegi,
    input wire [31:0] PCi,
    input wire [4:0] RegAddri,
    input wire [31:0] MemDatai,
    input wire [31:0] ALUOuti,
    output reg RegWro,
    output reg [1:0] MemtoRego,
    output reg [31:0] PCo,
    output reg [4:0] RegAddro,
    output reg [31:0] MemDatao,
    output reg [31:0] ALUOuto
    );

    always @(posedge clk or posedge reset) begin
        if(reset)begin
            RegWro<=0;
            MemtoRego<=0;
            PCo<=0;
            RegAddro<=0;
            MemDatao<=0;
            ALUOuto<=0;
        end
        else begin
            RegWro<=RegWri;
            MemtoRego<=MemtoRegi;
            PCo<=PCi;
            RegAddro<=RegAddri;
            MemDatao<=MemDatai;
            ALUOuto<=ALUOuti;
        end
    end
endmodule