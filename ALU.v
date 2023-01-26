module ALU(
  input         clock,
  input         reset,
  input  [3:0]  io_ALUCtrl,
  input  [31:0] io_A,
  input  [31:0] io_B,
  output [31:0] io_ALUOut,
  output        io_eq,
  output        io_ge,
  output        io_geu
);
  wire [4:0] shamt = io_B[4:0]; // @[ALU.scala 21:16]
  wire [31:0] _res_T_1 = $signed(io_A) & $signed(io_B); // @[ALU.scala 33:26]
  wire [31:0] _res_T_3 = $signed(io_A) | $signed(io_B); // @[ALU.scala 34:25]
  wire [31:0] _res_T_5 = $signed(io_A) ^ $signed(io_B); // @[ALU.scala 35:26]
  wire [31:0] _res_T_8 = $signed(io_A) + $signed(io_B); // @[ALU.scala 36:26]
  wire [31:0] _res_T_11 = $signed(io_A) - $signed(io_B); // @[ALU.scala 37:26]
  wire  _res_T_13 = $signed(io_A) < $signed(io_B); // @[ALU.scala 38:32]
  wire [62:0] _GEN_11 = {{31{io_A[31]}},io_A}; // @[ALU.scala 39:27]
  wire [62:0] _res_T_14 = $signed(_GEN_11) << shamt; // @[ALU.scala 39:27]
  wire  _res_T_18 = io_A < io_B; // @[ALU.scala 40:47]
  wire [31:0] _res_T_21 = io_A >> shamt; // @[ALU.scala 41:44]
  wire [31:0] _res_T_22 = $signed(io_A) >>> shamt; // @[ALU.scala 42:26]
  wire [31:0] _GEN_0 = 4'h9 == io_ALUCtrl ? $signed(_res_T_22) : $signed(32'sh0); // @[ALU.scala 32:22 42:21 23:24]
  wire [31:0] _GEN_1 = 4'h8 == io_ALUCtrl ? $signed(_res_T_21) : $signed(_GEN_0); // @[ALU.scala 32:22 41:21]
  wire [31:0] _GEN_2 = 4'h7 == io_ALUCtrl ? $signed({32{_res_T_18}}) : $signed(_GEN_1); // @[ALU.scala 32:22 40:22]
  wire [62:0] _GEN_3 = 4'h6 == io_ALUCtrl ? $signed(_res_T_14) : $signed({{31{_GEN_2[31]}},_GEN_2}); // @[ALU.scala 32:22 39:21]
  wire [62:0] _GEN_4 = 4'h5 == io_ALUCtrl ? $signed({63{_res_T_13}}) : $signed(_GEN_3); // @[ALU.scala 32:22 38:21]
  wire [62:0] _GEN_5 = 4'h4 == io_ALUCtrl ? $signed({{31{_res_T_11[31]}},_res_T_11}) : $signed(_GEN_4); // @[ALU.scala 32:22 37:21]
  wire [62:0] _GEN_6 = 4'h3 == io_ALUCtrl ? $signed({{31{_res_T_8[31]}},_res_T_8}) : $signed(_GEN_5); // @[ALU.scala 32:22 36:21]
  wire [62:0] _GEN_7 = 4'h2 == io_ALUCtrl ? $signed({{31{_res_T_5[31]}},_res_T_5}) : $signed(_GEN_6); // @[ALU.scala 32:22 35:21]
  wire [62:0] _GEN_8 = 4'h1 == io_ALUCtrl ? $signed({{31{_res_T_3[31]}},_res_T_3}) : $signed(_GEN_7); // @[ALU.scala 32:22 34:20]
  wire [62:0] _GEN_9 = 4'h0 == io_ALUCtrl ? $signed({{31{_res_T_1[31]}},_res_T_1}) : $signed(_GEN_8); // @[ALU.scala 32:22 33:21]
  assign io_ALUOut = _GEN_9[31:0]; // @[ALU.scala 23:24]
  assign io_eq = $signed(io_A) == $signed(io_B); // @[ALU.scala 28:15]
  assign io_ge = $signed(io_A) > $signed(io_B); // @[ALU.scala 29:15]
  assign io_geu = io_A > io_B; // @[ALU.scala 30:23]
endmodule
