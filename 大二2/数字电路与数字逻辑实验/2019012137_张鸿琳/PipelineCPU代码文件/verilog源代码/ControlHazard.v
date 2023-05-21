// `timescale 1ns / 1ps

module ControlHazard(
    input [1:0] Jump,
    input PCSrc,
    output flush_if_id,
    output flush_id_ex
    );

    assign flush_if_id=(Jump!=0 || PCSrc!=0)?1:0;
    assign flush_id_ex=(PCSrc!=0)?1:0;

endmodule