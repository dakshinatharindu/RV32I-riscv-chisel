package riscv

import chisel3._
import chisel3.util._
import riscv.shared.Constants._

class ControlUnit extends Module {
  val io = IO(new Bundle {
    val instr = Input(UInt(32.W))
    val format = Output(UInt(3.W))
  })

  val opcode = io.instr(6, 0)
  val func7 = io.instr(31, 25)
  val func3 = io.instr(14, 12)
  val format = io.format

  val format_gen = Module(new FormatGen)
  format_gen.io.opcode := opcode
  format := format_gen.io.format

}

class FormatGen extends Module {
  val io = IO(new Bundle {
    val opcode = Input(UInt(7.W))
    val format = Output(UInt(3.W))
  })

  val op = io.opcode(6, 2)
  val res = WireDefault(0.U(3.W))

  when(op === "b01100".U) {
    res := R.U
  }.elsewhen(op === "b00100".U | op === "b00000".U | op === "b11001".U) {
    res := I.U
  }.elsewhen(op === "b01000".U) {
    res := S.U
  }.elsewhen(op === "b11000".U) {
    res := B.U
  }.elsewhen(op === "b01101".U | op === "b00101".U) {
    res := U.U
  }.elsewhen(op === "b11011".U) {
    res := J.U
  }

  io.format := res
}

object Format extends App {
  val s = getVerilogString(new ControlUnit())
  println(s)
}
