// `timescale 1ns / 1ps

module ID_EX_Reg(
    input wire clk,
    input wire reset,
    input wire flush,
    input wire Branchi,
    input wire ALUSrc1i,
    input wire ALUSrc2i,
    input wire RegWri,
    input wire [1:0] RegDsti,
    input wire [4:0] ALUOpi,
    input wire MemReadi,
    input wire MemWri,
    input wire [1:0] MemtoRegi,
    input wire [31:0] PCi,
    input wire [4:0] shamti,
    input wire [31:0] reg1i,
    input wire [31:0] reg2i,
    input wire [31:0] extimmi,
    input wire [4:0] rti,
    input wire [4:0] rdi,
    input wire [4:0] rsi,
    input wire loadbytei,
    output reg Brancho,
    output reg ALUSrc1o,
    output reg ALUSrc2o,
    output reg RegWro,
    output reg [1:0] RegDsto,
    output reg [4:0] ALUOpo,
    output reg MemReado,
    output reg MemWro,
    output reg [1:0] MemtoRego,
    output reg [31:0] PCo,
    output reg [4:0] shamto,
    output reg [31:0] reg1o,
    output reg [31:0] reg2o,
    output reg [31:0] extimmo,
    output reg [4:0] rto,
    output reg [4:0] rdo,
    output reg [4:0] rso,
    output reg loadbyteo
    );


    always @(posedge clk or posedge reset) begin
        if(reset)begin
            Brancho<=0;
            ALUSrc1o<=0;
            ALUSrc2o<=0;
            RegWro<=0;
            RegDsto<=0;
            ALUOpo<=0;
            MemReado<=0;
            MemWro<=0;
            MemtoRego<=0;
            PCo<=0;
            shamto<=0;
            reg1o<=0;
            reg2o<=0;
            extimmo<=0;
            rto<=0;
            rdo<=0;
            rso<=0;
            loadbyteo<=0;
        end
        else if(flush)begin
            Brancho<=0;
            ALUSrc1o<=0;
            ALUSrc2o<=0;
            RegWro<=0;
            RegDsto<=0;
            ALUOpo<=0;
            MemReado<=0;
            MemWro<=0;
            MemtoRego<=0;
            PCo<=0;
            shamto<=0;
            reg1o<=0;
            reg2o<=0;
            extimmo<=0;
            rto<=0;
            rdo<=0;
            rso<=0;
            loadbyteo<=0;
        end
        else begin
            Brancho<=Branchi;
            ALUSrc1o<=ALUSrc1i;
            ALUSrc2o<=ALUSrc2i;
            RegWro<=RegWri;
            RegDsto<=RegDsti;
            ALUOpo<=ALUOpi;
            MemReado<=MemReadi;
            MemWro<=MemWri;
            MemtoRego<=MemtoRegi;
            PCo<=PCi;
            shamto<=shamti;
            reg1o<=reg1i;
            reg2o<=reg2i;
            extimmo<=extimmi;
            rto<=rti;
            rdo<=rdi;
            rso<=rsi;
            loadbyteo<=loadbytei;
        end
    end

endmodule