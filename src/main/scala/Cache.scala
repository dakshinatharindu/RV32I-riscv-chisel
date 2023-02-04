package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._
import os.read

class CacheLine extends Bundle {
  val validBit = Bool()
  val tag = UInt(5.W)
  val line = Vec(8, UInt(32.W))
}

class L1 extends Module {
  val io = IO(new Bundle {
    val addrs = Input(UInt(16.W))
    val cpuWriteData = Input(UInt(32.W))
    val cpuReadData = Output(UInt(32.W))
    val storeType = Input(UInt(2.W))
    val cpuWriteEn = Input(Bool())

    val readBlock = Output(UInt(256.W))
    val writeBlock = Input(UInt(256.W))
    val blockWriteEn = Input(Bool())

    val hit = Output(Bool())
  })

  val cache = RegInit(VecInit(Seq.fill(64)(0.U.asTypeOf(new CacheLine))))

  // reading
  val cacheLine = io.addrs(10, 5)
  val validBit = cache(cacheLine).validBit
  val tag = io.addrs(15, 11)
  val hit = (validBit === 1.U) & (tag === cache(cacheLine).tag)
  io.cpuReadData := cache(cacheLine).line(io.addrs(4, 2))
  io.readBlock := cache(cacheLine).line.asUInt
  io.hit := hit

  // // writing

  when(io.blockWriteEn) {
    cache(cacheLine).validBit := true.B
    cache(cacheLine).tag := tag
    for (j <- 0 to 7) {
      cache(cacheLine).line(j.U) := io.writeBlock((j + 1) * 32 - 1, j * 32)
    }

  }

  val cacheData = WireDefault(0.U(32.W))
  val temp = cache(cacheLine).line(io.addrs(4, 2))
  when(io.cpuWriteEn & hit) {
    switch(io.storeType) {
      is("b00".U) {
        cacheData := temp(31, 8) ## io.cpuWriteData(7, 0)
      }
      is("b01".U) {
        cacheData := temp(31, 16) ## io.cpuWriteData(15, 0)
      }
      is("b10".U) {
        cacheData := io.cpuWriteData
      }
    }
    cache(cacheLine).line(io.addrs(4, 2)) := cacheData
  }

}

class Cache extends Module {
  val io = IO(new Bundle {
    val inMemRead = Input(Bool())
    val inMemWrite = Input(Bool())
    val addrs = Input(UInt(16.W))
    val cpuWriteData = Input(UInt(32.W))
    val cpuReadData = Output(UInt(32.W))
    val storeType = Input(UInt(2.W))
    val valid = Output(Bool())
    val readBlock = Output(UInt(256.W))
    val writeBlock = Input(UInt(256.W))
    val outMemRead = Output(Bool())
    val outMemWrite = Output(Bool())
  })

  val cache = Module(new L1)
  val cacheControl = Module(new CacheControl)

  cache.io.addrs := io.addrs
  cache.io.cpuWriteData := io.cpuWriteData
  cache.io.storeType := io.storeType
  cache.io.cpuWriteEn := cacheControl.io.cacheEn
  cache.io.writeBlock := io.writeBlock
  cache.io.blockWriteEn := cacheControl.io.blockWriteEn

  cacheControl.io.inMemRead := io.inMemRead
  cacheControl.io.inMemWrite := io.inMemWrite
  cacheControl.io.hit := cache.io.hit

  io.cpuReadData := cache.io.cpuReadData
  io.valid := cacheControl.io.valid
  io.readBlock := cache.io.readBlock
  io.outMemRead := cacheControl.io.outMemRead
  io.outMemWrite := cacheControl.io.outMemWrite

}

object Cache extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new Cache,
    Array("--target-dir", "verilog/")
  )
}
