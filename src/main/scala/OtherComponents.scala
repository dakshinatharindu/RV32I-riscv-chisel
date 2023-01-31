package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class PC extends Module {
  val io = IO(new Bundle {
    val inAddr = Input(UInt(32.W))
    val outAddr = Output(UInt(32.W))
  })

  io.outAddr := RegNext(io.inAddr, 0.U)
}

class PCIncrementer extends Module {
  val io = IO(new Bundle {
    val pc = Input(UInt(32.W))
    val outAddr = Output(UInt(32.W))
  })

  io.outAddr := io.pc + 4.U(32.W)
}

class BranchAdder extends Module {
  val io = IO(new Bundle {
    val pc = Input(UInt(32.W))
    val imm = Input(SInt(32.W))
    val outAddr = Output(UInt(32.W))
  })

  io.outAddr := (io.pc.asSInt + io.imm).asUInt
}

class Rs2ImmMux extends Module {
  val io = IO(new Bundle {
    val rs2Imm = Input(Bool())
    val rs2 = Input(SInt(32.W))
    val imm = Input(SInt(32.W))
    val out = Output(SInt(32.W))
  })

  io.out := Mux(io.rs2Imm, io.imm, io.rs2)
}

class ALUMemMux extends Module {
  val io = IO(new Bundle {
    val aluMem = Input(Bool())
    val ALUOut = Input(SInt(32.W))
    val memReadData = Input(SInt(32.W))
    val out = Output(SInt(32.W))
  })

  io.out := Mux(io.aluMem, io.memReadData, io.ALUOut)
}

class PcALUMemMux extends Module {
  val io = IO(new Bundle {
    val pcAluMem = Input(Bool())
    val aluMem = Input(SInt(32.W))
    val pcImm = Input(UInt(32.W))
    val out = Output(SInt(32.W))
  })

  io.out := Mux(io.pcAluMem, io.aluMem, io.pcImm.asSInt)
}

class PcImmMux extends Module {
  val io = IO(new Bundle {
    val pcImm = Input(Bool())
    val pcPc4 = Input(UInt(32.W))
    val branch = Input(UInt(32.W))
    val out = Output(UInt(32.W))
  })

  io.out := Mux(io.pcImm, io.branch, io.pcPc4)
}

class ImmBranchMux extends Module {
  val io = IO(new Bundle {
    val immBranch = Input(Bool())
    val pc4 = Input(UInt(32.W))
    val branch = Input(UInt(32.W))
    val out = Output(UInt(32.W))
  })

  io.out := Mux(io.immBranch, io.branch, io.pc4)
}

class ALUBranchMux extends Module {
  val io = IO(new Bundle {
    val aluBranch = Input(Bool())
    val pc4Branch = Input(UInt(32.W))
    val ALUOut = Input(SInt(32.W))
    val out = Output(UInt(32.W))
  })

  io.out := Mux(io.aluBranch, io.ALUOut.asUInt, io.pc4Branch)
}

class PcStallMux extends Module {
  val io = IO(new Bundle {
    val stall = Input(Bool())
    val next = Input(UInt(32.W))
    val current = Input(UInt(32.W))
    val out = Output(UInt(32.W))
  })

  io.out := Mux(io.stall, io.next, io.current)
}

// object PC extends App {
//   val myverilog = (new ChiselStage).emitVerilog(
//     new PC,
//     Array("--target-dir", "verilog/")
//   )
// }
