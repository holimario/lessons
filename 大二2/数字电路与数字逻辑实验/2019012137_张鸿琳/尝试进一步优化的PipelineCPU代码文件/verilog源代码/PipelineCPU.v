// `timescale 1ns / 1ps

module PipelineCPU (reset, clk, out_wr, out_wdata, out_address, out_read, out_rd);

    //Input Clock Signals
    input reset;
    input clk;

    input out_wr;
    input out_rd;
    input [31:0] out_wdata;
    input [31:0] out_address;
    output [31:0] out_read;
    
    parameter ra=31;

    wire [1:0] A;
    wire [1:0] B;
    wire C;
    
    wire [31:0] pci;
    wire [31:0] pco;
    reg keep=0;
    PC PC(
        .reset(reset),
        .clk(clk),
        .PC_i(pci),
        .keep(keep),
        .PC_o(pco)
        );
    
    wire [31:0] inst;
    InstMemory InstMemory(
        .reset(reset), 
        .clk(clk), 
        .Address(pco),
        .Mem_data(inst)
        );
    
    reg if_id_flush=0;
    wire [31:0] if_pc;
    wire [5:0] id_opcode;
    wire [5:0] id_funct;
    wire [4:0] id_rs;
    wire [4:0] id_rt;
    wire [4:0] id_rd;
    wire [4:0] id_shamt;
    wire [15:0] id_imm;
    wire [31:0] id_pc;
    IF_ID_Reg IF_ID_Reg(
    .clk(clk), 
    .reset(reset), 
    .flush(if_id_flush), 
    .keep(keep),
    .Inst(inst), 
    .PCin(if_pc), 
    .OpCode(id_opcode),
    .Funct(id_funct),
    .rs(id_rs),
    .rt(id_rt),
    .rd(id_rd),
    .shamt(id_shamt),
    .imm(id_imm),
    .PCout(id_pc)
    );


    wire [1:0] jump;
    wire id_branch;
    wire id_regwr;
    wire [1:0] extop;
    wire id_alusrc1;
    wire id_alusrc2;
    wire [4:0] id_aluop;
    wire [1:0] id_regdst;
    wire id_memread;
    wire id_memwr;
    wire [1:0] id_memtoreg;
    wire id_loadbyte;
    Control Control(
        .OpCode(id_opcode), 
        .Funct(id_funct), 
        .Jump(jump), 
        .Branch(id_branch), 
        .RegWr(id_regwr), 
        .ExtOp(extop),
        .ALUSrc1(id_alusrc1), 
        .ALUSrc2(id_alusrc2), 
        .ALUOp(id_aluop),
        .RegDst(id_regdst), 
        .MemRead(id_memread), 
        .MemWr(id_memwr),
        .MemtoReg(id_memtoreg),
        .loadbyte(id_loadbyte)
        );

    wire wb_regwr;
    wire [31:0] id_reg1;
    wire [31:0] id_reg2;
    wire [31:0] id_reg10;
    wire [31:0] id_reg20;
    wire [4:0] wb_regaddr;
    wire [31:0] writereg;
        RegisterFile RegisterFile(
        .reset(reset), 
        .clk(clk), 
        .RegWrite(wb_regwr), 
        .Read_register1(id_rs), 
        .Read_register2(id_rt), 
        .Write_register(wb_regaddr), 
        .Write_data(writereg), 
        .Read_data1(id_reg10), 
        .Read_data2(id_reg20)
        );

    wire [31:0] id_extimm;
    ImmExtend ImmExtend(
        .ExtOp(extop), 
        .Immediate(id_imm), 
        .ImmExtOut(id_extimm)
        ); 

    reg id_ex_flush=0;
    wire ex_branch;
    wire ex_alusrc1;
    wire ex_alusrc2;
    wire ex_regwr;
    wire [1:0] ex_regdst;
    wire [4:0] ex_aluop;
    wire ex_memread;
    wire ex_memwr;
    wire [1:0] ex_memtoreg;
    wire [31:0] ex_pc;
    wire [4:0] ex_shamt;
    wire [31:0] ex_extimm;
    wire [4:0] ex_rt;
    wire [4:0] ex_rd;
    wire [4:0] ex_rs;
    wire [31:0] ex_reg1;
    wire [31:0] ex_reg2;
    wire ex_loadbyte;
    ID_EX_Reg ID_EX_Reg(
    .clk(clk),
    .reset(reset),
    .flush(id_ex_flush),
    .Branchi(id_branch),
    .ALUSrc1i(id_alusrc1),
    .ALUSrc2i(id_alusrc2),
    .RegWri(id_regwr),
    .RegDsti(id_regdst),
    .ALUOpi(id_aluop),
    .MemReadi(id_memread),
    .MemWri(id_memwr),
    .MemtoRegi(id_memtoreg),
    .PCi(id_pc),
    .shamti(id_shamt),
    .reg1i(id_reg1),
    .reg2i(id_reg2),
    .extimmi(id_extimm),
    .rti(id_rt),
    .rdi(id_rd),
    .rsi(id_rs),
    .Brancho(ex_branch),
    .ALUSrc1o(ex_alusrc1),
    .ALUSrc2o(ex_alusrc2),
    .RegWro(ex_regwr),
    .RegDsto(ex_regdst),
    .ALUOpo(ex_aluop),
    .MemReado(ex_memread),
    .MemWro(ex_memwr),
    .MemtoRego(ex_memtoreg),
    .PCo(ex_pc),
    .shamto(ex_shamt),
    .reg1o(ex_reg1),
    .reg2o(ex_reg2),
    .extimmo(ex_extimm),
    .rto(ex_rt),
    .rdo(ex_rd),
    .rso(ex_rs),
    .loadbytei(id_loadbyte),
    .loadbyteo(ex_loadbyte)
    );

    wire [31:0] in1;
    wire [31:0] in2;
    wire zero;
    wire [31:0] ex_res;
    ALU ALU(
        .ALUOp(ex_aluop), 
        .In1(in1), 
        .In2(in2), 
        .Zero(zero), 
        .Result(ex_res)
        );
    

    wire mem_memwr;
    wire [4:0] ex_regaddr;
    wire mem_regwr;
    wire mem_memread;
    wire [1:0] mem_memtoreg;
    wire [31:0] mem_pc;
    wire [4:0] mem_regaddr;
    wire [31:0] mem_regdata;
    wire [31:0] mem_aluout;
    wire mem_loadbyte;
    EX_MEM_Reg EX_MEM_Reg(
    .clk(clk),
    .reset(reset),
    .RegWri(ex_regwr),
    .MemReadi(ex_memread),
    .MemWri(ex_memwr),
    .MemtoRegi(ex_memtoreg),
    .PCi(ex_pc),
    .RegAddri(ex_regaddr),
    .RegDatai(ex_reg2),
    .ALUOuti(ex_res),
    .RegWro(mem_regwr),
    .MemReado(mem_memread),
    .MemWro(mem_memwr),
    .MemtoRego(mem_memtoreg),
    .PCo(mem_pc),
    .RegAddro(mem_regaddr),
    .RegDatao(mem_regdata),
    .ALUOuto(mem_aluout),
    .loadbytei(ex_loadbyte),
    .loadbyteo(mem_loadbyte)
    );
    
    assign ex_regaddr=(ex_regdst==0)?ex_rt:
                        (ex_regdst==1)?ex_rd:
                        (ex_regdst==2)?5'd31:5'd0;

    wire [31:0] writedata;
    wire [31:0] mem_readdata;
    wire [31:0] mem_readdatax;
    wire [31:0] mem_readdata1;
    wire [31:0] mem_readdata2;
    DataMemory DataMemory(
        .reset(reset),
        .clk(clk), 
        .Address(mem_aluout), 
        .Write_data(writedata), 
        // .MemRead(mem_memread), 
        .MemWrite(mem_memwr), 
        .Mem_data(mem_readdatax),
        .Loadbyte(mem_loadbyte)
        );
        
        assign mem_readdata1=mem_loadbyte? ((!(mem_aluout[1:0]^2'b11))? {{24{mem_readdatax[7]}},mem_readdatax[7:0]}:
                                (!(mem_aluout[1:0]^2'b10))? {{24{mem_readdatax[15]}},mem_readdatax[15:8]}:
                                (!(mem_aluout[1:0]^2'b01))? {{24{mem_readdatax[23]}},mem_readdatax[23:16]}:
                                {{24{mem_readdatax[31]}},mem_readdatax[31:24]}):mem_readdatax;

        wire read_cpu;
        wire [31:0] addr_cpu;
        uart_mem UARTMemory(
        .clk(clk),
        .reset(reset),
        .addr(out_address),
        .addr_cpu(addr_cpu),
        .rd_en(out_rd),
        .rd_en_cpu(read_cpu),
        .wr_en(out_wr),
        .wr_en_cpu(mem_memwr),
        .wdata(out_wdata),
        .wdata_cpu(writedata),
        .rdata(out_read),
        .rdata_cpu(mem_readdata2)
    );

    assign mem_readdata=(mem_aluout[31:28]==4'h4)? mem_readdata2:mem_readdata1;
    assign addr_cpu=(mem_aluout[31:28]==4'h4)? mem_aluout:32'h0;
    assign read_cpu=(mem_aluout[31:28]==4'h4)? mem_memread:0;

    assign writedata=(C==0)?mem_regdata:writereg;

    wire [1:0] wb_memtoreg;
    wire [31:0] wb_pc;
    wire [31:0] wb_aluout;
    wire [31:0] wb_readdata;
    MEM_WB_Reg MEM_WB_Reg(
    .clk(clk),
    .reset(reset),
    .RegWri(mem_regwr),
    .MemtoRegi(mem_memtoreg),
    .PCi(mem_pc),
    .RegAddri(mem_regaddr),
    .MemDatai(mem_readdata),
    .ALUOuti(mem_aluout),
    .RegWro(wb_regwr),
    .MemtoRego(wb_memtoreg),
    .PCo(wb_pc),
    .RegAddro(wb_regaddr),
    .MemDatao(wb_readdata),
    .ALUOuto(wb_aluout)
    );

    assign writereg=(wb_memtoreg==0)?wb_aluout:
                    (wb_memtoreg==1)?wb_readdata:
                    (wb_memtoreg==2)?wb_pc:32'b0;

//    wire id_ex_flush_1;
//    wire id_ex_flush_2;
    DataHazard DataHazard(
    .ex_mem_regwr(mem_regwr),
    .mem_wb_regwr(wb_regwr),
    .ex_mem_memwr(mem_memwr),
    .if_id_rt(id_rt),
    .if_id_rs(id_rs),
    .id_ex_rs(ex_rs),
    .id_ex_rt(ex_rt),
    .id_ex_memread(ex_memread),
    .ex_mem_regaddr(mem_regaddr),
    .mem_wb_regaddr(wb_regaddr),
    .A(A),
    .B(B),
    .C(C)
//    .keep(keep),
//    .flush_id_ex(id_ex_flush_1)
    );

    wire pcsrc;
//    ControlHazard ControlHazard(
//    .Jump(jump),
//    .PCSrc(pcsrc),
//    .flush_if_id(if_id_flush),
//    .flush_id_ex(id_ex_flush_2)
//    );

//    assign id_ex_flush=id_ex_flush_1 | id_ex_flush_2;

    assign in1=(ex_alusrc1==0)?{17'b0,ex_shamt}:
    (A==0)?ex_reg1:
    (A==1)?mem_aluout:
    (A==2)?writereg:32'b0;
    
    assign in2=(ex_alusrc2==1)?ex_extimm:
    (B==0)?ex_reg2:
    (B==1)?mem_aluout:
    (B==2)?writereg:32'b0;

    assign if_pc=pco+4;

    assign pcsrc=ex_branch & zero;

    assign pci=(pcsrc==1)?((ex_extimm<<2)+ex_pc):(jump==2'd2)?id_reg1:
                (jump==2'd1)?{id_pc[31:28],id_rs,id_rt,id_imm,2'b00}:
                (jump==2'd0)?(pco+4):32'b0;

    //forwarding in ID stage
    assign id_reg1=(wb_regwr && (wb_regaddr!=0) && ((id_rs==wb_regaddr)))?writereg:id_reg10;
    assign id_reg2=(wb_regwr && (wb_regaddr!=0) && ((id_rt==wb_regaddr)))?writereg:id_reg20;
    
//    wire nop;
//    assign nop=(inst==32'd0)?1:0;

endmodule