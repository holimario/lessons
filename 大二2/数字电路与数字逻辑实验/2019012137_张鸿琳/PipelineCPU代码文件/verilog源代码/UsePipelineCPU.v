module UsePipelineCPU(
    input clk,      // 100MHz
    input rst,      // S1 
    input mem2uart, // SW0, send message
    input Rx_Serial,
    output Tx_Serial,
    output [7:0] Cathodes,
    output reg [1:0] AN
    );

    parameter CLKS_PER_BIT = 16'd10417;  // 100M/9600

    reg send_done;
    reg [31:0] addr;
    reg rd_en;
    reg wr_en;
    wire [31:0] rdata;
    reg [31:0] wdata;

    
    PipelineCPU PipelineCPU(
        .reset(rst), 
        .clk(clk), 
        .out_wr(wr_en), 
        .out_wdata(wdata), 
        .out_address(addr), 
        .out_read(rdata), 
        .out_rd(rd_en)
        );

    /*--------------------------------UART RX-------------------------*/
    wire Rx_DV;
    wire [7:0] Rx_Byte;
    reg clear;
    
    uart_rx #(.CLKS_PER_BIT(CLKS_PER_BIT)) uart_rx_inst
        (.i_Clock(clk),
        .i_Rx_Serial(Rx_Serial),
        .o_Rx_DV(Rx_DV),
        .o_Rx_Byte(Rx_Byte),
        .clear(clear)
        );
        
    /*--------------------------------UART TX-------------------------*/
    reg Tx_DV;
    reg [7:0] Tx_Byte;
    wire Tx_Active;
    wire Tx_Done;
    
    
    uart_tx #(.CLKS_PER_BIT(CLKS_PER_BIT)) uart_tx_inst
        (.i_Clock(clk),
        .i_Tx_DV(Tx_DV),
        .i_Tx_Byte(Tx_Byte),
        .o_Tx_Active(Tx_Active),
        .o_Tx_Serial(Tx_Serial),
        .o_Tx_Done(Tx_Done)
        );
        
    
    reg [31:0] cntByteTime;
    
    always@(posedge clk or posedge rst)begin
        if(rst)begin
            addr <= 32'd0;
            rd_en <= 1'b0;
            wr_en <= 1'b0;
            wdata <= 32'd0;
            send_done <= 1'b0;
            cntByteTime <= 32'd0;
            Tx_DV <= 1'b0;
            Tx_Byte <= 8'd0;

            clear<=0;
            AN<=0;
            
        end
        else
        begin

            // uart to memory
            if(Rx_DV)begin
                // receive data
                addr <= 32'h4000001c;
                clear <= 1'd1;
                wr_en <= 1'b1;
                wdata <= {24'h0,Rx_Byte};
            end
            else begin
                wr_en <= 1'b0;
                clear <= 1'd0;
            end
        
            // memory to uart
            if(mem2uart==1'b1)begin
                // 1Byte time
                if(send_done == 0 && cntByteTime == CLKS_PER_BIT*20)begin
                    Tx_DV <= 1'b1;
                    send_done <= 1;
                end
                else if(send_done == 0 && cntByteTime != CLKS_PER_BIT*20)begin
                    rd_en<= 1'b1;
                    addr<=32'h40000018;
                    Tx_Byte <= rdata[7:0];
                    cntByteTime <= cntByteTime+1'b1;
                    Tx_DV <= 1'b0;
                end
                else begin
                    Tx_DV <= 1'b0;
                    rd_en<= 1'b1;
                    addr<=32'h40000010;
                    AN<= rdata[9:8];
                end
            end
            else begin
                AN<=0;
            end
        end    
    end

    wire [7:0] temp;

    assign temp=(mem2uart==1'b0)?8'h00:Tx_Byte;

    assign Cathodes=(AN==2'b01 && temp[3:0]==4'b0000)?8'b00111111://0
                    (AN==2'b01 && temp[3:0]==4'b0001)?8'b00000110://1
                    (AN==2'b01 && temp[3:0]==4'b0010)?8'b01011011://2
                    (AN==2'b01 && temp[3:0]==4'b0011)?8'b01001111://3
                    (AN==2'b01 && temp[3:0]==4'b0100)?8'b01100110://4
                    (AN==2'b01 && temp[3:0]==4'b0101)?8'b01101101://5
                    (AN==2'b01 && temp[3:0]==4'b0110)?8'b01111101://6
                    (AN==2'b01 && temp[3:0]==4'b0111)?8'b00000111://7
                    (AN==2'b01 && temp[3:0]==4'b1000)?8'b01111111://8
                    (AN==2'b01 && temp[3:0]==4'b1001)?8'b01101111://9
                    (AN==2'b01 && temp[3:0]==4'b1010)?8'b01110111://a
                    (AN==2'b01 && temp[3:0]==4'b1011)?8'b01111100://b
                    (AN==2'b01 && temp[3:0]==4'b1100)?8'b00111001://c
                    (AN==2'b01 && temp[3:0]==4'b1101)?8'b01011110://d
                    (AN==2'b01 && temp[3:0]==4'b1110)?8'b01111001://e
                    (AN==2'b01 && temp[3:0]==4'b1111)?8'b01110001://f
                    (AN==2'b10 && temp[7:4]==4'b0000)?8'b00111111://0
                    (AN==2'b10 && temp[7:4]==4'b0001)?8'b00000110://1
                    (AN==2'b10 && temp[7:4]==4'b0010)?8'b01011011://2
                    (AN==2'b10 && temp[7:4]==4'b0011)?8'b01001111://3
                    (AN==2'b10 && temp[7:4]==4'b0100)?8'b01100110://4
                    (AN==2'b10 && temp[7:4]==4'b0101)?8'b01101101://5
                    (AN==2'b10 && temp[7:4]==4'b0110)?8'b01111101://6
                    (AN==2'b10 && temp[7:4]==4'b0111)?8'b00000111://7
                    (AN==2'b10 && temp[7:4]==4'b1000)?8'b01111111://8
                    (AN==2'b10 && temp[7:4]==4'b1001)?8'b01101111://9
                    (AN==2'b10 && temp[7:4]==4'b1010)?8'b01110111://a
                    (AN==2'b10 && temp[7:4]==4'b1011)?8'b01111100://b
                    (AN==2'b10 && temp[7:4]==4'b1100)?8'b00111001://c
                    (AN==2'b10 && temp[7:4]==4'b1101)?8'b01011110://d
                    (AN==2'b10 && temp[7:4]==4'b1110)?8'b01111001://e
                    (AN==2'b10 && temp[7:4]==4'b1111)?8'b01110001://f
                    8'b0;

endmodule

