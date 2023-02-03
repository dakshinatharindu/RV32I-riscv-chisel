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
class VictimCacheLine extends Bundle {
  val record = UInt(4.W)
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

class VC extends Module {
  val io = IO(new Bundle {
    val addrs = Input(UInt(16.W))
    val writeBlock = Input(UInt(256.W))
    val wen = Input(Bool())
    val read = Input(Bool())
    val readBlock = Output(UInt(256.W))
    val hit = Output(Bool())
  })

  val victimCache = RegInit(
    VecInit(Seq.fill(16)(0.U.asTypeOf(new VictimCacheLine)))
  )

  val tag = io.addrs(15, 11)
  val inx = victimCache.indexWhere(x => x.tag === tag)
  val hit =
    Mux(inx < 15.U, true.B, Mux(victimCache(15.U).tag === tag, true.B, false.B)) & victimCache(inx).validBit
  val min =
    victimCache.map(x => x.record).reduceLeft((x, y) => Mux(x < y, x, y))
  val minIdx = victimCache.indexWhere(x => x.record === min)
  io.hit := hit

  when(hit) {
    io.readBlock := victimCache(inx).line.asUInt
    when(io.read) { victimCache(inx).record := victimCache(inx).record + 1.U }
  }.otherwise {
    io.readBlock := victimCache(minIdx).line.asUInt
  }

  when(io.wen) {
    when(hit) {
      victimCache(inx).validBit := true.B
      victimCache(inx).tag := tag
      victimCache(inx).record := 0.U
      for (j <- 0 to 7) {
        victimCache(inx).line(j.U) := io.writeBlock((j + 1) * 32 - 1, j * 32)
      }
    }.otherwise {
      victimCache(minIdx).validBit := true.B
      victimCache(minIdx).tag := tag
      victimCache(minIdx).record := 0.U
      for (j <- 0 to 7) {
        victimCache(minIdx).line(j.U) := io.writeBlock((j + 1) * 32 - 1, j * 32)
      }
    }
  }

}

object VC extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new VC,
    Array("--target-dir", "verilog/")
  )
}
