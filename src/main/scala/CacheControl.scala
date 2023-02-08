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
    val vhit = Input(Bool())
    val valid = Output(Bool())
    val cacheEn = Output(Bool())
    val blockWriteEn = Output(Bool())
    val outMemRead = Output(Bool())
    val outMemWrite = Output(Bool())
    val sel = Output(Bool())
    val vcEn = Output(Bool())
    val dataSel = Output(Bool())
  })

  val state = RegInit(false.B)
  val valid = WireDefault(false.B)
  val cacheEn = WireDefault(false.B)
  val outMemRead = WireDefault(false.B)
  val outMemWrite = WireDefault(false.B)
  val blockWriteEn = WireDefault(false.B)
  val sel = WireDefault(false.B)
  val vcEn = WireDefault(false.B)
  val dataSel = WireDefault(false.B)

  when(io.inMemRead | io.inMemWrite) {
    when(io.hit) {
      valid := true.B
      cacheEn := io.inMemWrite
    }.elsewhen(io.vhit){
      switch(state){
        is(false.B){
          dataSel := false.B
          outMemRead := false.B
          outMemWrite := false.B
          vcEn := false.B
          blockWriteEn := false.B
          state := true.B
        }
        is(true.B){
          dataSel := false.B
          outMemRead := false.B
          outMemWrite := false.B
          vcEn := true.B
          blockWriteEn := true.B
          state := false.B
        }
      }
    }.otherwise {
      switch(state) {
        is(false.B) {
          outMemRead := true.B
          outMemWrite := false.B
          blockWriteEn := false.B
          vcEn := false.B
          sel := false.B
          dataSel := true.B
          state := true.B
        }
        is(true.B) {
          outMemRead := false.B
          outMemWrite := true.B
          blockWriteEn := true.B
          vcEn := true.B
          sel := true.B
          state := false.B
          dataSel := true.B
        }
      }
    }
  }.otherwise {
    valid := false.B
    cacheEn := false.B
    outMemRead := false.B
    outMemWrite := false.B
    blockWriteEn := false.B
    sel := false.B
    state := false.B
    vcEn := false.B
    dataSel := false.B
  }

  io.valid := valid
  io.outMemRead := outMemRead
  io.outMemWrite := outMemWrite
  io.cacheEn := cacheEn
  io.blockWriteEn := blockWriteEn
  io.sel := sel
  io.vcEn := vcEn
  io.dataSel := dataSel
}

object CacheControl extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new CacheControl,
    Array("--target-dir", "verilog/")
  )
}
