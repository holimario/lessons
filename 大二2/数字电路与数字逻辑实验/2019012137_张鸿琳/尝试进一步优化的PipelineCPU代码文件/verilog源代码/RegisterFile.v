// // `timescale 1ns / 1ps

// module RegisterFile(reset, clk, RegWrite, Read_register1, Read_register2, Write_register, Write_data, Read_data1, Read_data2);
// 	//Input Clock Signals
// 	input reset;
// 	input clk;
// 	//Input Control Signals
// 	input RegWrite;
// 	//Input Data Signals
// 	input [4:0] Read_register1;
// 	input [4:0] Read_register2; 
// 	input [4:0] Write_register;
// 	input [31:0] Write_data;
// 	//Output Data Signals
// 	output [31:0] Read_data1;
// 	output [31:0] Read_data2;
	
// 	reg [31:0] RF_data[31:1];
	
// 	//read data
// 	assign Read_data1 = (Read_register1 == 5'b00000)? 32'h00000000: RF_data[Read_register1];
// 	assign Read_data2 = (Read_register2 == 5'b00000)? 32'h00000000: RF_data[Read_register2];
	
// 	integer i;
// 	always @(posedge reset or posedge clk) begin
// 		if (reset) begin
// 			for (i = 1; i < 32; i = i + 1) begin
// 				if(i==16)RF_data[i] <= 32'd75;
// 				else if(i==17) RF_data[i] <= 32'd4;
// 				else RF_data[i] <= 32'h00000000;
// 			end
// 		end else if (RegWrite) begin
// 			RF_data[Write_register] <= Write_data;
// 		end
// 	end

// endmodule

// `timescale 1ns / 1ps

module RegisterFile(reset, clk, RegWrite, Read_register1, Read_register2, Write_register, Write_data, Read_data1, Read_data2);
//Input Clock Signals
input reset;
input clk;
//Input Control Signals
input RegWrite;
//Input Data Signals
input [4:0] Read_register1;
input [4:0] Read_register2; 
input [4:0] Write_register;
input [31:0] Write_data;
//Output Data Signals
output [31:0] Read_data1;
output [31:0] Read_data2;

reg [31:0] RF_data[31:0];

//read data
assign Read_data1 = RF_data[Read_register1];
assign Read_data2 = RF_data[Read_register2];

integer i;
always @(posedge reset or posedge clk) begin
	if (reset) begin
		// for (i = 1; i < 32; i = i + 1) begin
		// 	if(i==16)RF_data[i] <= 32'd75;
		// 	else if(i==17) RF_data[i] <= 32'd4;
		// 	else RF_data[i] <= 32'h00000000;
		// end
		for (i = 0; i < 32; i = i + 1) begin
			RF_data[i] <= 32'h00000000;
		end
	end else if (RegWrite) begin
		RF_data[Write_register] <= Write_data;
	end
end

endmodule