`timescale 1ps / 1ps
`define PERIOD 10    //��Ӧʱ������Ϊ100MHz

module UART_MEM_tb();

reg clk;
reg rst;
reg mem2uart;
reg inv;//�ж��Ƿ�ȡ��
reg [31:0] info=32'hff00aab2;//����Ҫ���������ݣ�11111111_00000000_10101010_10110010����������
reg tx_dv;
reg [7:0] tx_byte;
reg [31:0] cntByteTime;//���ں������ݷ���ʱ��
reg [2:0] byte_cnt;
reg info_done;

parameter CLKS_PER_BIT=32'd10417;

wire r_done;
wire t_done;
wire rx;
wire tx;

UART_MEM #(.MEM_SIZE(1)) uart_mem//����1��word�Ŀռ�
(
    .clk(clk),      // 100MHz
    .rst(rst),      // S1 
    .mem2uart(mem2uart), // SW0     
    .recv_done(r_done),   // led 0 
    .send_done(t_done),   // led 1     
    .Rx_Serial(rx),
    .Tx_Serial(tx),
    .inv(inv)  //ȡ��
);

uart_tx sendinfo//����info����Ϣ
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
    inv=0;
    mem2uart=0;
    tx_dv=0;
    tx_byte=0;
    cntByteTime=0;
    byte_cnt=0;
    info_done=1;
    #(800)rst=1;//���г�ʼ��ֵ
    #(200)rst=0;
    #(1000)info_done=0;//��ʼ����info������
    #(CLKS_PER_BIT*2000)mem2uart=1;//��ʼ����洢����Ϣ
    #(CLKS_PER_BIT*2000)mem2uart=0;
    #(1000)rst=1;//��λ���������·�������
    #(1000)rst=0;
    #(1000)inv=1;//ȡ��
    #(CLKS_PER_BIT*50)inv=0;
    #(1000)mem2uart=1;//ȡ����ɣ����Է���ȡ���������
end

initial begin//����100MHzʱ��
    forever
      #(`PERIOD/2) clk=~clk;
end

always @(posedge clk)//����info��Ϣ
begin
    if(cntByteTime == CLKS_PER_BIT*20 && info_done==0)begin  // 1Byte time
        cntByteTime <= 32'd0;
        tx_dv <= 1'b1;
        
        if(byte_cnt==3'd0) tx_byte <= info[7:0];
        else if(byte_cnt==3'd1) tx_byte <= info[15:8];
        else if(byte_cnt==3'd2) tx_byte <= info[23:16];
        else if(byte_cnt==3'd3) tx_byte <= info[31:24];
        else if(byte_cnt==3'd4) tx_byte <= info[7:0];
        else if(byte_cnt==3'd5) tx_byte <= info[15:8];
        else if(byte_cnt==3'd6) tx_byte <= info[23:16];
        else if(byte_cnt==3'd7)begin
            tx_byte <= info[31:24];
            info_done<=1;
        end
        else;

        if(byte_cnt == 3'd7)begin
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
