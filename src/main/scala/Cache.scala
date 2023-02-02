package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._
import os.read

class L1 extends Module {
  val io = IO(new Bundle {
    val addrs = Input(UInt(12.W))
    val writeData = Input(UInt(32.W))
    val storeType = Input(UInt(2.W))
    val wen = Input(Bool())
    val readData = Output(UInt(32.W))
    val hit = Output(Bool())
  })

  val cache = RegInit(VecInit(Seq.fill(64)(0.U(37.W))))
  // reading
  val cacheLine = io.addrs(7, 2)
  val validBit = cache(cacheLine)(36)
  val tag = cache(cacheLine)(35, 32)
  val hit = (validBit === 1.U) & (tag === io.addrs(11, 8))
  io.readData := cache(cacheLine)(31, 0)
  io.hit := hit

  // writing
  val cacheData = WireDefault(0.U(37.W))
  when(io.wen & hit) {
    switch(io.storeType) {
      is("b00".U) {
        cacheData := 1.U ## io.addrs(11, 8) ## cache(cacheLine)(31, 8) ## io
          .writeData(7, 0)
      }
      is("b01".U) {
        cacheData := 1.U ## io.addrs(11, 8) ## cache(cacheLine)(31, 16) ## io
          .writeData(15, 0)
      }
      is("b10".U) {
        cacheData := 1.U ## io.addrs(11, 8) ## io.writeData
      }
    }
  }.elsewhen(io.wen) {
    cacheData := 1.U ## io.addrs(11, 8) ## io.writeData
  }
  cache(cacheLine) := cacheData

}

class VC extends Module {
  val io = IO(new Bundle {
    val addrs = Input(UInt(12.W))

    val readData = Output(UInt(32.W))
    val hit = Output(Bool())
  })
}

object L1 extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new L1,
    Array("--target-dir", "verilog/")
  )
}
