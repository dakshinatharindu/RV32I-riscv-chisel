module ProcessorTop(
input clock,
input reset,
output led,
output reset_led
);

wire [24:0]  q;
wire slowClock;
wire  [31:0]  io_instr;
wire  [255:0] io_memReadBlock;
wire [10:0]  io_memAdrrs;
wire [8:0]  io_instrAddrs;
wire [255:0] io_memWriteBlock;
wire         io_memRead;
wire         io_memWrite;


SlowClock counter(clock, q);
assign slowClock = q[10];
assign led = q[10];
assign reset_led = ~reset;
Processor processor(slowClock,
 ~reset,io_instr,
 io_memReadBlock,
 io_memAdrrs,
 io_instrAddrs,
 io_memWriteBlock,
 io_memRead,
 io_memWrite
 );

 DataMem dataMem(io_memAdrrs,
 slowClock,
 io_memWriteBlock,
 io_memRead,
 io_memWrite,
 io_memReadBlock
 );

 InstructionMem instructionMem(
    io_instrAddrs,
    clock,
    32'b0,
    1'b0,
    io_instr
 );

endmodule
