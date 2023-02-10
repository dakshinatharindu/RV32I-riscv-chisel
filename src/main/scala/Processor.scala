// package riscv

// import chisel3._
// import chisel3.util._
// import chisel3.stage._
// import riscv.shared.Constants._

// class Processor extends Module {
//   val io = IO(new Bundle {
//     val instr = Input(UInt(32.W))
//     val memReadBlock = Input(UInt(256.W))
//     val memAdrrs = Output(UInt(11.W))
//     val instrAddrs = Output(UInt(9.W))
//     val memWriteBlock = Output(UInt(256.W))
//     val memRead = Output(Bool())
//     val memWrite = Output(Bool())
//   })

//   val core = Module(new Core)
//   val cacheCore = Module(new Cache)

//   core.io.instr := io.instr
//   core.io.memReadData := cacheCore.io.cpuReadData
//   core.io.valid := cacheCore.io.valid

//   cacheCore.io.inMemRead := core.io.memRead
//   cacheCore.io.inMemWrite := core.io.memWrite
//   cacheCore.io.addrs := core.io.ALUOut.asUInt(15, 0)
//   cacheCore.io.cpuWriteData := core.io.memWriteData
//   cacheCore.io.storeType := core.io.storeType
//   cacheCore.io.writeBlock := io.memReadBlock

//   io.instrAddrs := core.io.instrAddrs
//   io.memWriteBlock := cacheCore.io.readBlock
//   io.memRead := cacheCore.io.outMemRead
//   io.memWrite := cacheCore.io.outMemWrite
//   io.memAdrrs := cacheCore.io.outAddrs

// }

// object Processor extends App {
//   val myverilog = (new ChiselStage).emitVerilog(
//     new Processor,
//     Array("--target-dir", "verilog/")
//   )
// }
