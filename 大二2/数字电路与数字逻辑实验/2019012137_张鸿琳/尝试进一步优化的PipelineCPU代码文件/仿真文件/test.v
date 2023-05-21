`timescale 1ps / 1ps
`define PERIOD 10   

module test();

reg clk;
reg rst;
reg mem2uart;
reg tx_dv;
reg [7:0] tx_byte;
reg [31:0] cntByteTime;
reg [5:0] byte_cnt;
reg info_done;

parameter CLKS_PER_BIT=32'd10417;

wire rx;
wire tx;

UsePipelineCPU usepipelinecpu(
    .clk(clk),
    .rst(rst),
    .mem2uart(mem2uart),
    .Rx_Serial(rx),
    .Tx_Serial(tx)
    );

uart_tx sendinfo
  (
   .i_Clock(clk),
   .i_Tx_DV(tx_dv),
   .i_Tx_Byte(tx_byte),
   .o_Tx_Serial(rx)
   );

initial begin
    rst=0;
    mem2uart=0;
    clk=0;
    mem2uart=0;
    tx_dv=0;
    tx_byte=0;
    cntByteTime=0;
    byte_cnt=0;
    info_done=1;
    #(1000)rst=1;
    #(1000)rst=0;
    #(1000)info_done=0;
    #(50000000) mem2uart=1;
end

initial begin
    forever
      #(`PERIOD/2) clk=~clk;
end

always @(posedge clk)
begin
    if(cntByteTime == CLKS_PER_BIT*20 && info_done==0)begin  // 1Byte time
        cntByteTime <= 32'd0;
        tx_dv <= 1'b1;
        
        if(byte_cnt==6'd0) tx_byte <= "u";
        else if(byte_cnt==6'd1) tx_byte <= "n";
        else if(byte_cnt==6'd2) tx_byte <= "u";
        else if(byte_cnt==6'd3) tx_byte <= "i";
        else if(byte_cnt==6'd4) tx_byte <= "x";
        else if(byte_cnt==6'd5) tx_byte <= " ";
        else if(byte_cnt==6'd6) tx_byte <= "i";
        else if(byte_cnt==6'd7) tx_byte <= "s";
        else if(byte_cnt==6'd8) tx_byte <= " ";
        else if(byte_cnt==6'd9) tx_byte <= "p";
        else if(byte_cnt==6'd10) tx_byte <= "u";
        else if(byte_cnt==6'd11) tx_byte <= "n";
        else if(byte_cnt==6'd12) tx_byte <= "u";
        else if(byte_cnt==6'd13) tx_byte <= "n";
        else if(byte_cnt==6'd14) tx_byte <= "u";
        else if(byte_cnt==6'd15) tx_byte <= 8'h21;
        else if(byte_cnt==6'd16) tx_byte <= "u";
        else if(byte_cnt==6'd17) tx_byte <= "n";
        else if(byte_cnt==6'd18) tx_byte <= "u";
        else if(byte_cnt==6'd19)begin
            tx_byte <= 8'h21;
            info_done<=1;
        end
        else;

        if(byte_cnt == 6'd20)begin
            byte_cnt <= 3'd0;
        end
        else begin
            byte_cnt <= byte_cnt+1'b1;  
        end
    end
    else begin
        cntByteTime <= cntByteTime+1'b1;
        tx_dv <= 1'b0;
    end
end

endmodule
