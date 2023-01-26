package riscv

import chisel3._
import chisel3.util._
import scala.annotation.switch
import riscv.shared.Constants._

class ALU extends Module {
  val io = IO(new Bundle {
    val ALUCtrl = Input(UInt(4.W))
    val A = Input(SInt(32.W))
    val B = Input(SInt(32.W))
    val ALUOut = Output(SInt(32.W))
    val eq = Output(UInt(1.W))
    val ge = Output(UInt(1.W))
    val geu = Output(UInt(1.W))
  })

  val A = io.A
  val B = io.B
  val shamt = B(4, 0)

  val res = WireDefault(0.S(32.W))
  val eq = WireDefault(0.U(1.W))
  val ge = WireDefault(0.U(1.W))
  val geu = WireDefault(0.U(1.W))

  eq := Mux(A === B, 1.U, 0.U)
  ge := Mux(A > B, 1.U, 0.U)
  geu := Mux(A.asUInt > B.asUInt, 1.U, 0.U)

  switch(io.ALUCtrl) {
    is(and.U) { res := A & B }
    is(or.U) { res := A | B }
    is(xor.U) { res := A ^ B }
    is(add.U) { res := A + B }
    is(sub.U) { res := A - B }
    is(slt.U) { res := Mux(A < B, 1.S, 0.S) }
    is(sll.U) { res := (A << shamt).asSInt }
    is(sltu.U) { res := (A.asUInt < B.asUInt).asSInt }
    is(srl.U) { res := (A.asUInt >> shamt).asSInt }
    is(sra.U) { res := A >> shamt }

  }
  io.ALUOut := res
  io.eq := eq
  io.ge := ge
  io.geu := geu
}

// object ALU extends App {
//   (new chisel3.stage.ChiselStage).emitVerilog(new ALU())
// }
