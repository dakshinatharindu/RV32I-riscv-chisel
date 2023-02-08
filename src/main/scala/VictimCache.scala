package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._
import os.read
import firrtl.PrimOps

class VictimCacheLine extends Bundle {
  val validBit = Bool()
  val tag = UInt(11.W)
  val line = Vec(8, UInt(32.W))
}

class VictimCache extends Module {
  val io = IO(new Bundle {
    val inData = Input(UInt(256.W))
    val inAddrs = Input(UInt(16.W))
    val storeAddrs = Input(UInt(11.W))
    val inValid = Input(Bool())
    val outData = Output(UInt(256.W))
    val outAddrs = Output(UInt(11.W))
    val vhit = Output(Bool())
    val en = Input(Bool())
  })

  val victimCache = RegInit(
    VecInit(Seq.fill(4)(0.U.asTypeOf(new VictimCacheLine)))
  )
  val replaceReg = RegInit(0.U(2.W))
  val dataBuffer = RegInit(0.U(256.W))
  val addrsBuffer = RegInit(0.U(11.W))

  val tag = io.inAddrs(15, 5)
  val inx = victimCache.indexWhere(x => ((x.tag === tag) & (x.validBit)))
  val hit =
    Mux(inx < 3.U, true.B, Mux(victimCache(3.U).tag === tag, true.B, false.B))
  val validBit = victimCache(inx).validBit
  val vhit = validBit & hit

  io.outAddrs := addrsBuffer
  io.outData := dataBuffer
  io.vhit := vhit

  when(vhit) {
    when(io.en) {
      victimCache(inx).validBit := io.inValid
      victimCache(inx).tag := io.storeAddrs
      for (j <- 0 to 7) {
        victimCache(inx).line(j.U) := io.inData((j + 1) * 32 - 1, j * 32)
      }
    }
    dataBuffer := victimCache(inx).line.asUInt
    addrsBuffer := victimCache(inx).tag
  }.otherwise {
    when(io.en) {
      victimCache(replaceReg).validBit := io.inValid
      victimCache(replaceReg).tag := io.storeAddrs
      for (j <- 0 to 7) {
        victimCache(replaceReg).line(j.U) := io.inData((j + 1) * 32 - 1, j * 32)
      }
      replaceReg := replaceReg + 1.U(2.W)
    }
    dataBuffer := victimCache(replaceReg).line.asUInt
    addrsBuffer := victimCache(replaceReg).tag
  }

}

object VictimCache extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new VictimCache,
    Array("--target-dir", "verilog/")
  )
}
