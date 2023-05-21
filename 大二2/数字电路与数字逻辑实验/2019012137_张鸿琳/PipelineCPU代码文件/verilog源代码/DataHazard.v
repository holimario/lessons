// `timescale 1ns / 1ps

module DataHazard(//solve load-use hazard, (other instruction) and (jr or jalr) hazard, other data hazard
    input wire ex_mem_regwr,
    input wire mem_wb_regwr,
    input wire ex_mem_memwr,
    input wire [4:0] if_id_rt,
    input wire [4:0] if_id_rs,
    input wire [4:0] id_ex_rs,
    input wire [4:0] id_ex_rt,
    input wire id_ex_memread,
    input wire [4:0] ex_mem_regaddr,
    input wire [4:0] mem_wb_regaddr,
    output wire [1:0] A,
    output wire [1:0] B,
    output wire C,
    // output wire [1:0] D,
    output wire keep,
    output wire flush_id_ex
    // output wire flush_ex_mem,
    );

    //load-use, keep pc, if/id and flush id/ex
    assign keep=(id_ex_memread && ((id_ex_rt==if_id_rs) || (id_ex_rt==if_id_rt)))?1:0;
    assign flush_id_ex=(id_ex_memread && ((id_ex_rt==if_id_rs) || (id_ex_rt==if_id_rt)))?1:0;

    //forward
    assign A=(ex_mem_regwr && ~ex_mem_regaddr && (ex_mem_regaddr==id_ex_rs))? 1:
                (mem_wb_regwr && ~mem_wb_regaddr && (mem_wb_regaddr==id_ex_rs))? 2:0;
    assign B=(ex_mem_regwr && ~ex_mem_regaddr && (ex_mem_regaddr==id_ex_rt))? 1:
                (mem_wb_regwr && ~mem_wb_regaddr && (mem_wb_regaddr==id_ex_rt))? 2:0;

    //lw-sw
    assign C=(ex_mem_memwr && (ex_mem_regaddr==mem_wb_regaddr))?1:0;

    //(other instruction) and (jr or jalr), ignore..................

endmodule