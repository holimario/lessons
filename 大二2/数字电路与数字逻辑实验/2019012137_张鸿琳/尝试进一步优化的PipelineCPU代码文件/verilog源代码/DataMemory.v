// `timescale 1ns / 1ps

module DataMemory(reset, clk, Address, Write_data, MemWrite, Mem_data, Loadbyte);
	//Input Clock Signals
	input reset;
	input clk;
	//Input Data Signals
	input [31:0] Address;
	input [31:0] Write_data;
	//Input Control Signals
	// input MemRead;
	input MemWrite;
	input Loadbyte;
	//Output Data
	output [31:0] Mem_data;
	
	parameter RAM_SIZE = 128;
	parameter RAM_SIZE_BIT = 7;
	
	reg [31:0] RAM_data[RAM_SIZE - 1: 0];
//	wire [31:0] temp;
//	wire [31:0] temp0;

	//read data
//	assign temp=RAM_data[Address[RAM_SIZE_BIT + 1:2]];
//	assign temp0=Loadbyte? ((!(Address[1:0]^2'b11))? {{24{temp[7]}},temp[7:0]}:
//						(!(Address[1:0]^2'b10))? {{24{temp[15]}},temp[15:8]}:
//						(!(Address[1:0]^2'b01))? {{24{temp[23]}},temp[23:16]}:
//						{{24{temp[31]}},temp[31:24]}):temp;
	assign Mem_data = RAM_data[Address[RAM_SIZE_BIT + 1:2]];
	// assign Mem_data = MemRead? (): 32'h00000000;
	
	//write data
	integer i;
	always @(posedge reset or posedge clk) begin
		if (reset) begin
            //reset data memory		  
			for (i = 0; i < RAM_SIZE; i = i + 1)
				RAM_data[i] <= 32'h00000000;

		end else if (MemWrite) begin
			if(!Loadbyte)RAM_data[Address[RAM_SIZE_BIT + 1:2]] <= Write_data;
			else begin
				case(Address[1:0])
					2'b11:RAM_data[Address[RAM_SIZE_BIT + 1:2]][7:0] <= Write_data[7:0];
					2'b10:RAM_data[Address[RAM_SIZE_BIT + 1:2]][15:8] <= Write_data[7:0];
					2'b01:RAM_data[Address[RAM_SIZE_BIT + 1:2]][23:16] <= Write_data[7:0];
					2'b00:RAM_data[Address[RAM_SIZE_BIT + 1:2]][31:24] <= Write_data[7:0];
				endcase
			end
		end
	end

endmodule