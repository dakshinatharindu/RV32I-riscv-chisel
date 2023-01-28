package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val eq = Input(Bool())
    val ge = Input(Bool())
    val geu = Input(Bool())
    val format = Output(UInt(3.W))
    val ALUCtrl = Output(UInt(4.W))
    val regWrite = Output(Bool())
    val memWrite = Output(Bool())
    val memRead = Output(Bool())
    val rs2Imm = Output(Bool())
    val aluMem = Output(Bool())
    val pcAluMem = Output(Bool())
    val pcImm = Output(Bool())
    val immBranch = Output(Bool())
    val aluBranch = Output(Bool())
  })

  val opcode = io.instr(6, 0)
  val func7 = io.instr(31, 25)
  val func3 = io.instr(14, 12)
  val subFormat = opcode(6, 2)
  val funcCode = func7(5) ## func3

  val ALUCtrl = WireDefault(0.U(4.W))
  val format = WireDefault(0.U(3.W))
  val regWrite = WireDefault(false.B)
  val memWrite = WireDefault(false.B)
  val memRead = WireDefault(false.B)
  val rs2Imm = WireDefault(false.B)
  val aluMem = WireDefault(false.B)
  val pcAluMem = WireDefault(false.B)
  val pcImm = WireDefault(false.B)
  val immBranch = WireDefault(false.B)
  val aluBranch = WireDefault(false.B)

  switch(subFormat) {
    is(R_.U) {
      rs2Imm := false.B
      aluMem := false.B
      pcAluMem := true.B
      immBranch := false.B
      aluBranch := false.B

      regWrite := true.B
      memRead := false.B
      memWrite := false.B

      switch(funcCode) {
        is(ADD.U) { ALUCtrl := add.U }
        is(SUB.U) { ALUCtrl := sub.U }
        is(SLL.U) { ALUCtrl := sll.U }
        is(SLT.U) { ALUCtrl := slt.U }
        is(SLTU.U) { ALUCtrl := sltu.U }
        is(XOR.U) { ALUCtrl := xor.U }
        is(SRL.U) { ALUCtrl := srl.U }
        is(SRA.U) { ALUCtrl := sra.U }
        is(OR.U) { ALUCtrl := or.U }
        is(AND.U) { ALUCtrl := and.U }
      }

      format := R.U
    }

    is(I_.U) {
      rs2Imm := true.B
      aluMem := false.B
      pcAluMem := true.B
      immBranch := false.B
      aluBranch := false.B

      regWrite := true.B
      memRead := false.B
      memWrite := false.B

      switch(funcCode(2, 0)) {
        is("b000".U) { ALUCtrl := add.U }
        is("b010".U) { ALUCtrl := slt.U }
        is("b011".U) { ALUCtrl := sltu.U }
        is("b100".U) { ALUCtrl := xor.U }
        is("b110".U) { ALUCtrl := or.U }
        is("b111".U) { ALUCtrl := and.U }
        is("b001".U) { ALUCtrl := sll.U }
        is("b101".U) {
          when(funcCode(3) === 0.U) {
            ALUCtrl := srl.U
          }.otherwise {
            ALUCtrl := sra.U
          }
        }
      }

      format := I.U
    }

    is(I_load.U) {
      rs2Imm := true.B
      aluMem := true.B
      pcAluMem := true.B
      immBranch := false.B
      aluBranch := false.B

      regWrite := true.B
      memRead := true.B
      memWrite := false.B

      ALUCtrl := add.U

      format := I.U
    }

    is(I_jalr.U) {
      pcImm := false.B
      pcAluMem := false.B
      aluBranch := true.B

      regWrite := true.B
      memRead := false.B
      memWrite := false.B

      ALUCtrl := jalr.U

      format := I.U
    }

    is(S_.U) {
      rs2Imm := true.B
      immBranch := false.B
      aluBranch := false.B

      regWrite := false.B
      memRead := false.B
      memWrite := true.B

      ALUCtrl := add.U

      format := S.U
    }

    is(B_.U) {
      rs2Imm := false.B
      switch(func3) {
        is(BEQ.U) { immBranch := Mux(io.eq, true.B, false.B) }
        is(BNE.U) { immBranch := Mux(io.eq, false.B, true.B) }
        is(BLT.U) { immBranch := Mux(io.ge, false.B, true.B) }
        is(BGE.U) { immBranch := Mux(io.ge, true.B, false.B) }
        is(BLTU.U) { immBranch := Mux(io.geu, false.B, true.B) }
        is(BGEU.U) { immBranch := Mux(io.geu, true.B, false.B) }
      }
      aluBranch := false.B

      regWrite := false.B
      memRead := false.B
      memWrite := false.B

      format := B.U
    }

    is(U_lui.U) {
      rs2Imm := false.B
      aluMem := false.B
      pcAluMem := true.B
      immBranch := false.B
      aluBranch := false.B

      regWrite := true.B
      memRead := false.B
      memWrite := false.B

      ALUCtrl := selectB.U

      format := U.U
    }

    is(U_auipc.U) {
      pcAluMem := false.B
      pcImm := true.B
      immBranch := false.B
      aluBranch := false.B

      regWrite := true.B
      memRead := false.B
      memWrite := false.B

      format := U.U
    }
    is(J_jal.U) {
      pcAluMem := false.B
      pcImm := false.B
      immBranch := true.B
      aluBranch := false.B

      regWrite := true.B
      memRead := false.B
      memWrite := false.B

      format := J.U
    }
  }

  io.regWrite := regWrite
  io.memWrite := memWrite
  io.memRead := memRead
  io.rs2Imm := rs2Imm
  io.aluMem := aluMem
  io.pcAluMem := pcAluMem
  io.pcImm := pcImm
  io.immBranch := immBranch
  io.aluBranch := aluBranch
  io.ALUCtrl := ALUCtrl
  io.format := format

}

class Decoder extends Module {
  val io = IO(new Bundle {
    val opcode = Input(UInt(7.W))
    val format = Output(UInt(3.W))
  })

  val op = io.opcode(6, 2)
  val res = WireDefault(0.U(3.W))

  when(op === R_.U) {
    res := R.U
  }.elsewhen(op === I_.U | op === I_jalr.U | op === I_load.U) {
    res := I.U
  }.elsewhen(op === S_.U) {
    res := S.U
  }.elsewhen(op === B_.U) {
    res := B.U
  }.elsewhen(op === U_lui.U | op === U_auipc.U) {
    res := U.U
  }.elsewhen(op === J_jal.U) {
    res := J.U
  }

  io.format := res
}

object ControlUnit extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new ControlUnit,
    Array("--target-dir", "verilog/")
  )
}
