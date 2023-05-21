module uart_mem
(
    input clk,
    input reset,
    input [31:0] addr,
    input [31:0] addr_cpu,
    input rd_en,
    input rd_en_cpu,
    input wr_en,
    input wr_en_cpu,
    output wire [31:0] rdata,
    output wire [31:0] rdata_cpu,
    input [31:0] wdata,
    input [31:0] wdata_cpu
    );
    
    reg [7:0] UART_TX;
    reg [7:0] UART_RX;
    reg tx_done;//tx完成
    reg rx_done;//rx完成
    reg state;
    reg [1:0] AN;

    assign rdata=rd_en? ((addr[7:0]==8'h18)?{{24{UART_TX[7]}},UART_TX}:
                        (addr[7:0]==8'h1c)?{{24{UART_RX[7]}},UART_RX}:
                        (addr[7:0]==8'h20)?{27'h0,state,rx_done,tx_done,2'h0}:
                        (addr[7:0]==8'h10)?{22'h0,AN,8'h0}:32'h0):32'h0;
    
    assign rdata_cpu=rd_en_cpu? ((addr_cpu[7:0]==8'h18)?{{24{UART_TX[7]}},UART_TX}:
                        (addr_cpu[7:0]==8'h1c)?{{24{UART_RX[7]}},UART_RX}:
                        (addr_cpu[7:0]==8'h20)?{27'h0,state,rx_done,tx_done,2'h0}:32'h0):32'h0;

    always@(posedge clk or posedge reset)begin
    begin
        if(reset)begin
            UART_TX<=8'h00;
            UART_RX<=8'h00;
            tx_done<=1'b0;
            rx_done<=1'b0;
            state<=1'b0;
            AN<=2'b00;
        end
        else begin
            case(addr[7:0])
                8'h18:begin//tx_info
                    if(rd_en)begin
                        tx_done<=0;
                    end
                end
                8'h1c:begin//rx_info
                    if(wr_en)begin 
                        UART_RX<=wdata[7:0];
                        rx_done<=1;
                    end
                end
            endcase
            case(addr_cpu[7:0])
                8'h18:begin//tx_info
                    if(wr_en_cpu)begin
                        UART_TX<=wdata_cpu[7:0];
                        tx_done<=1;
                    end
                end
                8'h1c:begin//rx_info
                    if(rd_en_cpu)begin
                        rx_done<=0;
                    end
                end
                8'h20:begin
                    if(wr_en_cpu)begin
                        state<=wdata_cpu[4];
                    end
                end
                8'h10:begin
                    if(wr_en_cpu)begin
                        AN<=wdata_cpu[9:8];
                    end
                end
            endcase
            end
        end
    end

endmodule
