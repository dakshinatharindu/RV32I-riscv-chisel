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

  val register_file = Reg(Vec(32, SInt(32.W)))
  io.r_data1 := register_file(io.r_addr1)
  io.r_data2 := register_file(io.r_addr2)

  when (io.w_en){
    register_file(io.w_addr) := io.w_data
  }
}
