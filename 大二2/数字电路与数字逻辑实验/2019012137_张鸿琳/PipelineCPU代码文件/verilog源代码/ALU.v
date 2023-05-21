// `timescale 1ns / 1ps

module ALU(ALUOp, In1, In2, Zero, Result);
    // Control Signals
    input [4:0] ALUOp;
    // Input Data Signals
    input [31:0] In1;
    input [31:0] In2;
    // Output 
    output reg Zero;
    output reg [31:0] Result;

    always @(*)
	begin
    case(ALUOp[3:0])
        4'd0:begin//add
            Result<=In1+In2;
            Zero<=0;
        end
        4'd1:begin//sub
            Result<=In1-In2;
            Zero<=0;
        end
        4'd2:begin//and
            Result<=In1&In2;
            Zero<=0;
        end
        4'd3:begin//or
            Result<=In1|In2;
            Zero<=0;
        end
        4'd4:begin//xor
            Result<=In1^In2;
            Zero<=0;
        end
        4'd5:begin//nor
            Result<=~(In1|In2);
            Zero<=0;
        end
        4'd6:begin//leftshift
            Result<=In2<<In1;
            Zero<=0;
        end
        4'd7:begin//rightshift
            case(ALUOp[4])
                0:begin
                    Result<=In2>>In1;
                    Zero<=0;
                end
                1:begin
                    Result<=($signed(In2))>>>In1;
                    Zero<=0;
                end
            endcase
        end
        4'd8:begin//compare
            case(ALUOp[4])
                0:begin
                    if(In1<In2)Result<=1;
                    else Result<=0;
                    Zero<=0;
                end
                1:begin
                    if(In1[31]==1&&In1[31]==0)Result<=1;
                    else if(In1[31]==0&&In2[31]==1)Result<=0;
                    else if(In1[31]==0&&In2[31]==0)begin
                        if(In1<In2)Result<=1;
                        else Result<=0;
                    end
                    else begin
                        if(In1>In2)Result<=1;
                        else Result<=0;
                    end
                    Zero<=0;
                end
            endcase
        end
        4'd9:begin//equal
            if(In1==In2)begin
                Result<=0;
                Zero<=1;
            end
            else begin
                Result<=1;
                Zero<=0;
            end
        end
        4'd10:begin//notequal
            if(In1!=In2)begin
                Result<=0;
                Zero<=1;
            end
            else begin
                Result<=1;
                Zero<=0;
            end
        end
        4'd11:begin//less or equal than zero
            if(In1<=0)begin
                Result<=0;
                Zero<=1;
            end
            else begin
                Result<=1;
                Zero<=0;
            end
        end
        4'd12:begin//greater than zero
            if(In1>0)begin
                Result<=0;
                Zero<=1;
            end
            else begin
                Result<=1;
                Zero<=0;
            end
        end
        4'd13:begin//less than zero
            if(In1<0)begin
                Result<=0;
                Zero<=1;
            end
            else begin
                Result<=1;
                Zero<=0;
            end
        end
    endcase
	end

endmodule
