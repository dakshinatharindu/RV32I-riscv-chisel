package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class Core extends Module {

  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val memReadData = Input(UInt(32.W))
    val cpu_wait = Input(Bool())
    val cpu_ready = Input(Bool())
    val instrAddrs = Output(UInt(9.W))
    val ALUOut = Output(SInt(32.W))
    val memWriteData = Output(UInt(32.W))
    // val memRead = Output(Bool())
    val memWrite = Output(Bool())
    val storeType = Output(UInt(2.W))
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
  val pcStall = Module(new PcStallMux)
  val loadSelector = Module(new LoadSelector)

  controlUnit.io.instr := io.instr
  controlUnit.io.eq := alu.io.eq
  controlUnit.io.ge := alu.io.ge
  controlUnit.io.geu := alu.io.geu
  controlUnit.io.cpu_ready := io.cpu_ready
  controlUnit.io.cpu_wait := io.cpu_wait

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

  pc.io.inAddr := pcStall.io.out

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
  aluMemMux.io.memReadData := loadSelector.io.outData

  immBranchMux.io.immBranch := controlUnit.io.immBranch
  immBranchMux.io.branch := branchAdder.io.outAddr
  immBranchMux.io.pc4 := pcIncrementer.io.outAddr

  aluBranchMux.io.aluBranch := controlUnit.io.aluBranch
  aluBranchMux.io.ALUOut := alu.io.ALUOut
  aluBranchMux.io.pc4Branch := immBranchMux.io.out

  pcStall.io.stall := controlUnit.io.stall
  pcStall.io.current := pc.io.outAddr
  pcStall.io.next := aluBranchMux.io.out

  loadSelector.io.func3 := io.instr(14, 12)
  loadSelector.io.inData := io.memReadData

  // io.memRead := controlUnit.io.memRead
  io.memWrite := controlUnit.io.memWrite
  io.ALUOut := alu.io.ALUOut
  io.instrAddrs := (pc.io.outAddr >> 2.U) (8, 0)
  io.memWriteData := registerFile.io.readData2.asUInt
  io.storeType := controlUnit.io.storeType

}

object Core extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new Core,
    Array("--target-dir", "verilog/")
  )
}
