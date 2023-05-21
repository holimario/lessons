// `timescale 1ns / 1ps

module Control(OpCode, Funct, 
                Jump, Branch, RegWr, ExtOp,
                ALUSrc1, ALUSrc2, ALUOp,
                RegDst, MemRead, MemWr,
                MemtoReg, loadbyte);
    //Input Clock Signals
    // input reset;
    // input clk;
    //Input Signals
    input  [5:0] OpCode;
    input  [5:0] Funct;
    //Output Control Signals
    output reg [1:0] Jump;
    output reg Branch;
    output reg RegWr;
    output reg [1:0] ExtOp;
    output reg ALUSrc1,ALUSrc2;
    output reg [4:0] ALUOp;
    output reg [1:0] RegDst;
    output reg MemRead,MemWr;
    output reg [1:0] MemtoReg;
    output reg loadbyte;

    //OpCode
    parameter R=6'h00;
    parameter lw=6'h23;
    parameter sw=6'h2b;
    parameter lb=6'h20;
    parameter sb=6'h28;
    parameter lui=6'h0f;
    parameter addi=6'h08;
    parameter addiu=6'h09;
    parameter andi=6'h0c;
    parameter ori=6'h0d;
    parameter slti=6'h0a;
    parameter sltiu=6'h0b;
    parameter beq=6'h04;
    parameter bne=6'h05;
    parameter blez=6'h06;
    parameter bgtz=6'h07;
    parameter bltz=6'h01;
    parameter j=6'h02;
    parameter jal=6'h03;

    //Funct
    parameter add=6'h20;
    parameter addu=6'h21;
    parameter sub=6'h22;
    parameter subu=6'h23;
    parameter and_=6'h24;
    parameter or_=6'h25;
    parameter xor_=6'h26;
    parameter nor_=6'h27;
    parameter sll=6'h00;
    parameter srl=6'h02;
    parameter sra=6'h03;
    parameter slt=6'h2a;
    parameter sltu=6'h2b;
    parameter jr=6'h08;
    parameter jalr=6'h09;


    always @(*) 
    begin
        case(OpCode)
        R:begin
            case(Funct)
                add:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b1,4'd0};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                addu:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd0};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                sub:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b1,4'd1};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                subu:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd1};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                and_:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd2};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                or_:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd3};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                xor_:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd4};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                nor_:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd5};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                sll:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=0;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd6};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                srl:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=0;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd7};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                sra:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=0;
                    ALUSrc2<=0;
                    ALUOp<={1'b1,4'd7};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                slt:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b1,4'd8};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                sltu:begin
                    Jump<=2'd0;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd8};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                jr:begin
                    Jump<=2'd2;
                    Branch<=0;
                    RegWr<=0;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd0};
                    RegDst<=1;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=0;
                    loadbyte<=0;
                end
                jalr:begin
                    Jump<=2'd2;
                    Branch<=0;
                    RegWr<=1;
                    ExtOp<=0;
                    ALUSrc1<=1;
                    ALUSrc2<=0;
                    ALUOp<={1'b0,4'd0};
                    RegDst<=2;
                    MemRead<=0;
                    MemWr<=0;
                    MemtoReg<=2;
                    loadbyte<=0;
                end
            endcase
        end
        lw:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd0};
            RegDst<=0;
            MemRead<=1;
            MemWr<=0;
            MemtoReg<=1;
            loadbyte<=0;
        end
        sw:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=0;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd0};
            RegDst<=0;
            MemRead<=0;
            MemWr<=1;
            MemtoReg<=0;
            loadbyte<=0;
        end
        lb:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd0};
            RegDst<=0;
            MemRead<=1;
            MemWr<=0;
            MemtoReg<=1;
            loadbyte<=1;
        end
        sb:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=0;
            ExtOp<=1;
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd0};
            RegDst<=0;
            MemRead<=0;
            MemWr<=1;
            MemtoReg<=0;
            loadbyte<=1;
        end
        lui:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=2;//lui��չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd0};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        addi:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd0};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        addiu:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b0,4'd0};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        andi:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=0;//�޷�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b0,4'd2};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        ori:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=0;//�޷�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b0,4'd3};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        slti:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b1,4'd8};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        sltiu:begin
            Jump<=2'd0;
            Branch<=0;
            RegWr<=1;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=1;
            ALUOp<={1'b0,4'd8};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        beq:begin
            Jump<=2'd0;
            Branch<=1;
            RegWr<=0;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b1,4'd9};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        bne:begin
            Jump<=2'd0;
            Branch<=1;
            RegWr<=0;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b1,4'd10};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        blez:begin
            Jump<=2'd0;
            Branch<=1;
            RegWr<=0;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b1,4'd11};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        bgtz:begin
            Jump<=2'd0;
            Branch<=1;
            RegWr<=0;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b1,4'd12};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        bltz:begin
            Jump<=2'd0;
            Branch<=1;
            RegWr<=0;
            ExtOp<=1;//�з�����չ
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b1,4'd13};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        j:begin
            Jump<=2'd1;
            Branch<=0;
            RegWr<=0;
            ExtOp<=0;
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b0,4'd0};
            RegDst<=0;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=0;
            loadbyte<=0;
        end
        jal:begin
            Jump<=2'd1;
            Branch<=0;
            RegWr<=1;
            ExtOp<=0;
            ALUSrc1<=1;
            ALUSrc2<=0;
            ALUOp<={1'b0,4'd0};
            RegDst<=2;
            MemRead<=0;
            MemWr<=0;
            MemtoReg<=2;
            loadbyte<=0;
        end
        endcase
    end
    
endmodule