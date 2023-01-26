package riscv

import chisel3._
import chisel3.util._
import riscv.shared.Constants._

class ImmGen extends Module {
  val io = IO(new Bundle {
    val in = Input(UInt(32.W))
    val format = Input(UInt(3.W))
    val out = Output(SInt(32.W))
  })

  val in = io.in
  val format = io.format
  val res = WireDefault(0.S(32.W))

  switch(format) {
    is(I.U) { res := in(31, 20).asSInt }
    is(S.U) { res := (in(31, 25) ## in(11, 7)).asSInt }
    is(B.U) {
      res := (in(31) ## in(7) ## in(30, 25) ## in(11, 8) ## 0.U(1.W)).asSInt
    }
    is(U.U) { res := (in(31, 12) ## 0.U(12.W)).asSInt }
    is(J.U) {
      res := (in(31) ## in(19, 12) ## in(20) ## in(30, 25) ## in(24, 21) ## 0.U(
        1.W
      )).asSInt
    }
  }
  io.out := res
}
