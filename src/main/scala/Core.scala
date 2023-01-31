package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class Core extends Module {

  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val memReadData = Input(SInt(32.W))
    val instrAddrs = Output(UInt(32.W))
    val ALUOut = Output(SInt(32.W))
    val memWriteData = Output(SInt(32.W))
    val memRead = Output(Bool())
    val memWrite = Output(Bool())
  })

  val controlUnit = Module(new ControlUnit)
  val registerFile = Module(new RegisterFile)
  val alu = Module(new ALU)
  val immGen = Module(new ImmGen)
  val pc = Module(new PC)
  val pcIncrementer = Module(new PCIncrementer)
  val branchAdder = Module(new BranchAdder)
  val pcAluMemMux = Module(new PcALUMemMux)
  val rs2ImmMux = Module(new Rs2ImmMux)
  val pcImmMux = Module(new PcImmMux)
  val aluMemMux = Module(new ALUMemMux)
  val immBranchMux = Module(new ImmBranchMux)
  val aluBranchMux = Module(new ALUBranchMux)

  controlUnit.io.instr := io.instr
  controlUnit.io.eq := alu.io.eq
  controlUnit.io.ge := alu.io.ge
  controlUnit.io.geu := alu.io.geu

  registerFile.io.readAddr1 := io.instr(19, 15)
  registerFile.io.readAddr2 := io.instr(24, 20)
  registerFile.io.writeAddr := io.instr(11, 7)
  registerFile.io.writeData := pcAluMemMux.io.out
  registerFile.io.writeEn := controlUnit.io.regWrite

  alu.io.A := registerFile.io.readData1
  alu.io.B := rs2ImmMux.io.out
  alu.io.ALUCtrl := controlUnit.io.ALUCtrl

  immGen.io.in := io.instr
  immGen.io.format := controlUnit.io.format

  pc.io.inAddr := aluBranchMux.io.out

  pcIncrementer.io.pc := pc.io.outAddr

  branchAdder.io.pc := pc.io.outAddr
  branchAdder.io.imm := immGen.io.out

  pcAluMemMux.io.pcAluMem := controlUnit.io.pcAluMem
  pcAluMemMux.io.pcImm := pcImmMux.io.out
  pcAluMemMux.io.aluMem := aluMemMux.io.out

  rs2ImmMux.io.rs2Imm := controlUnit.io.rs2Imm
  rs2ImmMux.io.imm := immGen.io.out
  rs2ImmMux.io.rs2 := registerFile.io.readData2

  pcImmMux.io.pcImm := controlUnit.io.pcImm
  pcImmMux.io.pcPc4 := pcIncrementer.io.outAddr
  pcImmMux.io.branch := branchAdder.io.outAddr

  aluMemMux.io.aluMem := controlUnit.io.aluMem
  aluMemMux.io.ALUOut := alu.io.ALUOut
  aluMemMux.io.memReadData := io.memReadData

  immBranchMux.io.immBranch := controlUnit.io.immBranch
  immBranchMux.io.branch := branchAdder.io.outAddr
  immBranchMux.io.pc4 := pcIncrementer.io.outAddr

  aluBranchMux.io.aluBranch := controlUnit.io.aluBranch
  aluBranchMux.io.ALUOut := alu.io.ALUOut
  aluBranchMux.io.pc4Branch := immBranchMux.io.out

  io.memRead := controlUnit.io.memRead
  io.memWrite := controlUnit.io.memWrite
  io.ALUOut := alu.io.ALUOut
  io.instrAddrs := pc.io.outAddr
  io.memWriteData := registerFile.io.readData2

}

object Core extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new Core,
    Array("--target-dir", "verilog/")
  )
}
