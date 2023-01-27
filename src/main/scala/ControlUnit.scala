package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val format = Output(UInt(3.W))
    val ALUCtrl = Output(UInt(4.W))
  })

  val opcode = io.instr(6, 0)
  val func7 = io.instr(31, 25)
  val func3 = io.instr(14, 12)
  val format = io.format
  val subFormat = opcode(6, 2)

  val formatGen = Module(new Decoder)
  formatGen.io.opcode := opcode
  format := formatGen.io.format

  val aluCotrol = Module(new ALUControl)
  aluCotrol.io.funcCode := func7(5) ## func3
  aluCotrol.io.subFormat := subFormat
  io.ALUCtrl := aluCotrol.io.ALUCtrl

}

class ALUControl extends Module {
  val io = IO(new Bundle {
    val subFormat = Input(UInt(5.W))
    val funcCode = Input(UInt(4.W)) // func_code = instr[30,14-12]
    val ALUCtrl = Output(UInt(4.W))
  })

  val subFormat = io.subFormat
  val funcCode = io.funcCode
  val res = WireDefault(0.U(4.W))

  switch(subFormat) {
    is(R_.U) {
      switch(funcCode) {
        is(ADD.U) { res := add.U }
        is(SUB.U) { res := sub.U }
        is(SLL.U) { res := sll.U }
        is(SLT.U) { res := slt.U }
        is(SLTU.U) { res := sltu.U }
        is(XOR.U) { res := xor.U }
        is(SRL.U) { res := srl.U }
        is(SRA.U) { res := sra.U }
        is(OR.U) { res := or.U }
        is(AND.U) { res := and.U }
      }
    }
    is(I_.U) {
      switch(funcCode(2, 0)) {
        is("b000".U) { res := add.U }
        is("b010".U) { res := slt.U }
        is("b011".U) { res := sltu.U }
        is("b100".U) { res := xor.U }
        is("b110".U) { res := or.U }
        is("b111".U) { res := and.U }
        is("b001".U) { res := sll.U }
        is("b101".U) {
          when(funcCode(3) === 0.U) {
            res := srl.U
          }.otherwise {
            res := sra.U
          }
        }
      }
    }
    is(I_jalr.U) { res := jalr.U }
    is(I_load.U) { res := add.U }
    is(S_.U) { res := add.U }
    is(U_lui.U) { res := selectB.U }
    // is(U_auipc.U) {res := selectB.U}
    // is(J_jal.U) {res := selectB.U}

  }
  io.ALUCtrl := res
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
