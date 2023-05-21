// `timescale 1ns / 1ps

module EX_MEM_Reg(
    input wire clk,
    input wire reset,
    input wire RegWri,
    input wire MemReadi,
    input wire MemWri,
    input wire [1:0] MemtoRegi,
    input wire [31:0] PCi,
    input wire [4:0] RegAddri,
    input wire [31:0] RegDatai,
    input wire [31:0] ALUOuti,
    input wire loadbytei,
    output reg RegWro,
    output reg MemReado,
    output reg MemWro,
    output reg [1:0] MemtoRego,
    output reg [31:0] PCo,
    output reg [4:0] RegAddro,
    output reg [31:0] RegDatao,
    output reg [31:0] ALUOuto,
    output reg loadbyteo
    );

    always @(posedge clk or posedge reset) begin
        if(reset)begin
            RegWro<=0;
            MemReado<=0;
            MemWro<=0;
            MemtoRego<=0;
            PCo<=0;
            RegAddro<=0;
            RegDatao<=0;
            ALUOuto<=0;
            loadbyteo<=0;
        end
        else begin
            RegWro<=RegWri;
            MemReado<=MemReadi;
            MemWro<=MemWri;
            MemtoRego<=MemtoRegi;
            PCo<=PCi;
            RegAddro<=RegAddri;
            RegDatao<=RegDatai;
            ALUOuto<=ALUOuti;
            loadbyteo<=loadbytei;
        end
    end
endmodule