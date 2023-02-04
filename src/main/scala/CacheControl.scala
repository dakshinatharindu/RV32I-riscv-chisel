package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._
import os.stat

class CacheControl extends Module {
  val io = IO(new Bundle {
    val inMemRead = Input(Bool())
    val inMemWrite = Input(Bool())
    val hit = Input(Bool())
    val valid = Output(Bool())
    val cacheEn = Output(Bool())
    val blockWriteEn = Output(Bool())
    val outMemRead = Output(Bool())
    val outMemWrite = Output(Bool())
  })

  val state = RegInit(false.B)
  val valid = WireDefault(false.B)
  val cacheEn = WireDefault(false.B)
  val outMemRead = WireDefault(false.B)
  val outMemWrite = WireDefault(false.B)
  val blockWriteEn = WireDefault(false.B)

  when(io.inMemRead | io.inMemWrite) {
    when(io.hit) {
      valid := true.B
      cacheEn := io.inMemWrite
    }.otherwise {
      switch(state) {
        is(false.B) {
          outMemRead := true.B
          outMemWrite := true.B
          blockWriteEn := false.B
          state := true.B
        }
        is(true.B) {
          outMemRead := false.B
          outMemWrite := false.B
          blockWriteEn := true.B
          state := false.B
        }
      }
    }
  }.otherwise {
    valid := false.B
    cacheEn := false.B
    outMemRead := false.B
    outMemWrite := false.B
    blockWriteEn := false.B
    state := false.B
  }

  io.valid := valid
  io.outMemRead := outMemRead
  io.outMemWrite := outMemWrite
  io.cacheEn := cacheEn
  io.blockWriteEn := blockWriteEn
}

object CacheControl extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new CacheControl,
    Array("--target-dir", "verilog/")
  )
}
