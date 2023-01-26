package riscv

import chisel3._
import chisel3.util._
import riscv.shared.Constants._

class RegisterFile extends Module {
  val io = IO(new Bundle {
    val r_addr1 = Input(UInt(5.W))
    val r_addr2 = Input(UInt(5.W))
    val w_addr = Input(UInt(5.W))
    val w_data = Input(SInt(32.W))
    val w_en = Input(Bool())
    val r_data1 = Output(SInt(32.W))
    val r_data2 = Output(SInt(32.W))
  })

  val register_file = RegInit(VecInit(Seq.fill(32)(0.S(32.W))))
  when(io.r_addr1 === 0.U) {
    io.r_data1 := 0.S
  }.otherwise {
    io.r_data1 := register_file(io.r_addr1)
  }

  when(io.r_addr2 === 0.U) {
    io.r_data2 := 0.S
  }.otherwise {
    io.r_data2 := register_file(io.r_addr2)
  }

  when(io.w_en) {
    register_file(io.w_addr) := io.w_data
  }
}

object RegisterFile extends App {
  val s = getVerilogString(new RegisterFile())
  println(s)
}
