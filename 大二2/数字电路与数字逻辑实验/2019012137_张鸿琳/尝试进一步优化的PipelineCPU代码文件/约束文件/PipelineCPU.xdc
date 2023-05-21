#100MHz
set_property PACKAGE_PIN P17 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]
create_clock -name clk -period 10.000 [get_ports clk]

#S6
set_property PACKAGE_PIN R17 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]

#S1
set_property PACKAGE_PIN R1 [get_ports mem2uart]
set_property IOSTANDARD LVCMOS33 [get_ports mem2uart]

#UART
set_property PACKAGE_PIN N5 [get_ports Rx_Serial]
set_property PACKAGE_PIN T4 [get_ports Tx_Serial]

set_property IOSTANDARD LVCMOS33 [get_ports Rx_Serial]
set_property IOSTANDARD LVCMOS33 [get_ports Tx_Serial]

set_property -dict {PACKAGE_PIN B4 IOSTANDARD LVCMOS33} [get_ports {Cathodes[0]}]
set_property -dict {PACKAGE_PIN A4 IOSTANDARD LVCMOS33} [get_ports {Cathodes[1]}]
set_property -dict {PACKAGE_PIN A3 IOSTANDARD LVCMOS33} [get_ports {Cathodes[2]}]
set_property -dict {PACKAGE_PIN B1 IOSTANDARD LVCMOS33} [get_ports {Cathodes[3]}]
set_property -dict {PACKAGE_PIN A1 IOSTANDARD LVCMOS33} [get_ports {Cathodes[4]}]
set_property -dict {PACKAGE_PIN B3 IOSTANDARD LVCMOS33} [get_ports {Cathodes[5]}]
set_property -dict {PACKAGE_PIN B2 IOSTANDARD LVCMOS33} [get_ports {Cathodes[6]}]
set_property -dict {PACKAGE_PIN D5 IOSTANDARD LVCMOS33} [get_ports {Cathodes[7]}]

set_property -dict {PACKAGE_PIN G2 IOSTANDARD LVCMOS33} [get_ports {AN[1]}]
set_property -dict {PACKAGE_PIN C2 IOSTANDARD LVCMOS33} [get_ports {AN[0]}]
# set_property -dict {PACKAGE_PIN C1 IOSTANDARD LVCMOS33} [get_ports {AN[1]}]
# set_property -dict {PACKAGE_PIN H1 IOSTANDARD LVCMOS33} [get_ports {AN[0]}]

# create_clock -period 10.000 -name CLK -waveform {0.000 5.000} [get_ports clk]