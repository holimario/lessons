// `timescale 1ns / 1ps

module InstMemory(reset, clk, Address, Mem_data);
	//Input Clock Signals
	input reset;
	input clk;
	//Input Data Signals
	input [31:0] Address;
	//Output Data
	output [31:0] Mem_data;
	
	parameter RAM_SIZE = 128;
	parameter RAM_SIZE_BIT = 7;
	
	reg [31:0] RAM_data[RAM_SIZE - 1: 0];

	//read data
	assign Mem_data =  RAM_data[Address[RAM_SIZE_BIT + 1:2]];
	
	//write data
	integer i;
	always @(posedge reset or posedge clk) begin
		if (reset) begin
		    // init instruction memory
//		    RAM_data[8'd0] <=32'h3c014000;
//            RAM_data[8'd1] <=32'h34370018;
//            RAM_data[8'd2] <=32'h3c014000;
//            RAM_data[8'd3] <=32'h3436001c;
//            RAM_data[8'd4] <=32'h3c014000;
//            RAM_data[8'd5] <=32'h34350020;
//            RAM_data[8'd6] <=32'h24050000;
//            RAM_data[8'd7] <=32'h24070100;
//            RAM_data[8'd8] <=32'h2410ffff;
//            RAM_data[8'd9] <=32'h2411ffff;
//            RAM_data[8'd10] <=32'h20acffff;
//            RAM_data[8'd11] <=32'h20ebffff;
//            RAM_data[8'd12] <=32'h1320ffff;
//            RAM_data[8'd13] <=32'h8eb90000;
//            RAM_data[8'd14] <=32'h00000000;
//            RAM_data[8'd15] <=32'h8ec80000;
//            RAM_data[8'd16] <=32'h20090021;
//            RAM_data[8'd17] <=32'h11090004;
//            RAM_data[8'd18] <=32'h218c0001;
//            RAM_data[8'd19] <=32'h22100001;
//            RAM_data[8'd20] <=32'h0800000c;
//            RAM_data[8'd21] <=32'ha1880000;
//            RAM_data[8'd22] <=32'h1300ffff;
//            RAM_data[8'd23] <=32'h8eb80000;
//            RAM_data[8'd24] <=32'h00000000;
//            RAM_data[8'd25] <=32'h8ec80000;
//            RAM_data[8'd26] <=32'h20090021;
//            RAM_data[8'd27] <=32'h11090004;
//            RAM_data[8'd28] <=32'h216b0001;
//            RAM_data[8'd29] <=32'h22310001;
//            RAM_data[8'd30] <=32'h08000016;
//            RAM_data[8'd31] <=32'ha1680000;
//            RAM_data[8'd32] <=32'h00102021;
//            RAM_data[8'd33] <=32'h00113021;
//            RAM_data[8'd34] <=32'h0c000025;
//            RAM_data[8'd35] <=32'h00000000;
//            RAM_data[8'd36] <=32'h1000ffff;
//            RAM_data[8'd37] <=32'h24080000;
//            RAM_data[8'd38] <=32'h240a0000;
//            RAM_data[8'd39] <=32'h00866822;
//            RAM_data[8'd40] <=32'h0005c821;
//            RAM_data[8'd41] <=32'h0007c021;
//            RAM_data[8'd42] <=32'h24090000;
//            RAM_data[8'd43] <=32'h00197821;
//            RAM_data[8'd44] <=32'h00187021;
//            RAM_data[8'd45] <=32'h81eb0000;
//            RAM_data[8'd46] <=32'h81cc0000;
//            RAM_data[8'd47] <=32'h00000000;
//            RAM_data[8'd48] <=32'h158b0007;
//            RAM_data[8'd49] <=32'h00000000;
//            RAM_data[8'd50] <=32'h00000000;
//            RAM_data[8'd51] <=32'h21290001;
//            RAM_data[8'd52] <=32'h0126082a;
//            RAM_data[8'd53] <=32'h1420fff7;
//            RAM_data[8'd54] <=32'h21ce0001;
//            RAM_data[8'd55] <=32'h21ef0001;
//            RAM_data[8'd56] <=32'h15260003;
//            RAM_data[8'd57] <=32'h00000000;
//            RAM_data[8'd58] <=32'h00000000;
//            RAM_data[8'd59] <=32'h214a0001;
//            RAM_data[8'd60] <=32'h010d082a;
//            RAM_data[8'd61] <=32'h1420ffec;
//            RAM_data[8'd62] <=32'h21080001;
//            RAM_data[8'd63] <=32'h23390001;
//            RAM_data[8'd64] <=32'h000a1021;
//            RAM_data[8'd65] <=32'haee20000;
//            RAM_data[8'd66] <=32'h24080010;
//            RAM_data[8'd67] <=32'haea80000;
//            RAM_data[8'd68] <=32'h24140100;
//            RAM_data[8'd69] <=32'h24130300;
//            RAM_data[8'd70] <=32'h3c014000;
//            RAM_data[8'd71] <=32'h34230010;
//            RAM_data[8'd72] <=32'h24092710;
//            RAM_data[8'd73] <=32'h1520ffff;
//            RAM_data[8'd74] <=32'h20010004;
//            RAM_data[8'd75] <=32'h01214822;
//            RAM_data[8'd76] <=32'h00000000;
//            RAM_data[8'd77] <=32'h0293a026;
//            RAM_data[8'd78] <=32'h08000048;
//            RAM_data[8'd79] <=32'hac740000;
//            RAM_data[8'd80] <=32'h03e00008;
            
RAM_data[8'd0] <=32'h3c014000;
RAM_data[8'd1] <=32'h34370018;
RAM_data[8'd2] <=32'h3c014000;
RAM_data[8'd3] <=32'h3436001c;
RAM_data[8'd4] <=32'h3c014000;
RAM_data[8'd5] <=32'h34350020;
RAM_data[8'd6] <=32'h24050000;
RAM_data[8'd7] <=32'h24070100;
RAM_data[8'd8] <=32'h24100000;
RAM_data[8'd9] <=32'h24110000;
RAM_data[8'd10] <=32'h00a06020;
RAM_data[8'd11] <=32'h00e05820;
RAM_data[8'd12] <=32'h8ea80000;
RAM_data[8'd13] <=32'h00000000;
RAM_data[8'd14] <=32'h00084700;
RAM_data[8'd15] <=32'h000847c2;
RAM_data[8'd16] <=32'h1100fffb;
RAM_data[8'd17] <=32'h00000000;
RAM_data[8'd18] <=32'h00000000;
RAM_data[8'd19] <=32'h2a080100;
RAM_data[8'd20] <=32'h1100000c;
RAM_data[8'd21] <=32'h00000000;
RAM_data[8'd22] <=32'h00000000;
RAM_data[8'd23] <=32'h8ec80000;
RAM_data[8'd24] <=32'h20090021;
RAM_data[8'd25] <=32'h11090007;
RAM_data[8'd26] <=32'h00000000;
RAM_data[8'd27] <=32'h00000000;
RAM_data[8'd28] <=32'ha1880000;
RAM_data[8'd29] <=32'h218c0001;
RAM_data[8'd30] <=32'h22100001;
RAM_data[8'd31] <=32'h0800000c;
RAM_data[8'd32] <=32'h00000000;
RAM_data[8'd33] <=32'h8ea80000;
RAM_data[8'd34] <=32'h00000000;
RAM_data[8'd35] <=32'h00084700;
RAM_data[8'd36] <=32'h000847c2;
RAM_data[8'd37] <=32'h1100fffb;
RAM_data[8'd38] <=32'h00000000;
RAM_data[8'd39] <=32'h00000000;
RAM_data[8'd40] <=32'h2a280100;
RAM_data[8'd41] <=32'h1100000d;
RAM_data[8'd42] <=32'h00000000;
RAM_data[8'd43] <=32'h00000000;
RAM_data[8'd44] <=32'h8ec80000;
RAM_data[8'd45] <=32'h00000000;
RAM_data[8'd46] <=32'h20090021;
RAM_data[8'd47] <=32'h11090007;
RAM_data[8'd48] <=32'h00000000;
RAM_data[8'd49] <=32'h00000000;
RAM_data[8'd50] <=32'ha1680000;
RAM_data[8'd51] <=32'h216b0001;
RAM_data[8'd52] <=32'h22310001;
RAM_data[8'd53] <=32'h08000021;
RAM_data[8'd54] <=32'h00000000;
RAM_data[8'd55] <=32'h00102021;
RAM_data[8'd56] <=32'h00113021;
RAM_data[8'd57] <=32'h0c00003c;
RAM_data[8'd58] <=32'h00000000;
RAM_data[8'd59] <=32'h1000ffff;
RAM_data[8'd60] <=32'h24080000;
RAM_data[8'd61] <=32'h240a0000;
RAM_data[8'd62] <=32'h00866822;
RAM_data[8'd63] <=32'h0005c821;
RAM_data[8'd64] <=32'h0007c021;
RAM_data[8'd65] <=32'h24090000;
RAM_data[8'd66] <=32'h00197821;
RAM_data[8'd67] <=32'h00187021;
RAM_data[8'd68] <=32'h81eb0000;
RAM_data[8'd69] <=32'h81cc0000;
RAM_data[8'd70] <=32'h00000000;
RAM_data[8'd71] <=32'h158b0007;
RAM_data[8'd72] <=32'h00000000;
RAM_data[8'd73] <=32'h00000000;
RAM_data[8'd74] <=32'h21290001;
RAM_data[8'd75] <=32'h0126082a;
RAM_data[8'd76] <=32'h1420fff7;
RAM_data[8'd77] <=32'h21ce0001;
RAM_data[8'd78] <=32'h21ef0001;
RAM_data[8'd79] <=32'h15260003;
RAM_data[8'd80] <=32'h00000000;
RAM_data[8'd81] <=32'h00000000;
RAM_data[8'd82] <=32'h214a0001;
RAM_data[8'd83] <=32'h010d082a;
RAM_data[8'd84] <=32'h1420ffec;
RAM_data[8'd85] <=32'h21080001;
RAM_data[8'd86] <=32'h23390001;
RAM_data[8'd87] <=32'h000a1021;
RAM_data[8'd88] <=32'haee20000;
RAM_data[8'd89] <=32'h24080010;
RAM_data[8'd90] <=32'haea80000;
RAM_data[8'd91] <=32'h24140100;
RAM_data[8'd92] <=32'h24130300;
RAM_data[8'd93] <=32'h3c014000;
RAM_data[8'd94] <=32'h34230010;
RAM_data[8'd95] <=32'h24092710;
RAM_data[8'd96] <=32'h1520ffff;
RAM_data[8'd97] <=32'h20010004;
RAM_data[8'd98] <=32'h01214822;
RAM_data[8'd99] <=32'h00000000;
RAM_data[8'd100] <=32'h0293a026;
RAM_data[8'd101] <=32'h0800005f;
RAM_data[8'd102] <=32'hac740000;
RAM_data[8'd103] <=32'h03e00008;

			// RAM_data[8'd68] <=32'h03e00008;

			for (i = 8'd104; i < RAM_SIZE; i = i + 1)
				RAM_data[i] <= 32'h00000000;

		end
	end

endmodule
