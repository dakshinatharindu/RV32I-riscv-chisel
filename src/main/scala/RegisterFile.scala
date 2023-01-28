package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class RegisterFile extends Module {
  val io = IO(new Bundle {
    val readAddr1 = Input(UInt(5.W))
    val readAddr2 = Input(UInt(5.W))
    val writeAddr = Input(UInt(5.W))
    val writeData = Input(SInt(32.W))
    val writeEn = Input(Bool())
    val readData1 = Output(SInt(32.W))
    val readData2 = Output(SInt(32.W))
  })

  val registerFile = RegInit(VecInit(Seq.fill(32)(0.S(32.W))))
  when(io.readAddr1 === 0.U) {
    io.readData1 := 0.S
  }.otherwise {
    io.readData1 := registerFile(io.readAddr1)
  }

  when(io.readAddr2 === 0.U) {
    io.readData2 := 0.S
  }.otherwise {
    io.readData2 := registerFile(io.readAddr2)
  }

  when(io.writeEn) {
    registerFile(io.writeAddr) := io.writeData
  }
}

// object RegisterFile extends App {
//   val myverilog = (new ChiselStage).emitVerilog(
//     new RegisterFile,
//     Array("--target-dir", "verilog/")
//   )
// }
