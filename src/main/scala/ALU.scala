package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import scala.annotation.switch
import riscv.shared.Constants._

class ALU extends Module {
  val io = IO(new Bundle {
    val ALUCtrl = Input(UInt(4.W))
    val A = Input(SInt(32.W))
    val B = Input(SInt(32.W))
    val ALUOut = Output(SInt(32.W))
    val eq = Output(Bool())
    val ge = Output(Bool())
    val geu = Output(Bool())
  })

  val A = io.A
  val B = io.B
  val shamt = B(4, 0)

  val res = WireDefault(0.S(32.W))

  io.eq := Mux(A === B, true.B, false.B)
  io.ge := Mux(A >= B, true.B, false.B)
  io.geu := Mux(A.asUInt >= B.asUInt, true.B, false.B)

  switch(io.ALUCtrl) {
    is(and.U) { res := A & B }
    is(or.U) { res := A | B }
    is(xor.U) { res := A ^ B }
    is(add.U) { res := A + B }
    is(sub.U) { res := A - B }
    is(slt.U) { res := Mux(A < B, 1.S, 0.S) }
    is(sll.U) { res := A << shamt }
    is(sltu.U) { res := Mux(A.asUInt < B.asUInt, 1.S, 0.S) }
    is(srl.U) { res := (A.asUInt >> shamt).asSInt }
    is(sra.U) { res := A >> shamt }
    is(jalr.U) { res := (A + B) & ~1.S }
    is(selectB.U) { res := B }

  }
  io.ALUOut := res
}

