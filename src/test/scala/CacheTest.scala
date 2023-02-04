package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class L1Test extends AnyFlatSpec with ChiselScalatestTester {

  "L1Test" should "pass" in {
    test(new L1) { dut =>
      dut.io.addrs.poke("b00000_000000_00100".U)
      dut.io.writeBlock.poke("b100000000_00000000_00001101_11111101".U(256.W))
      dut.io.blockWriteEn.poke(true.B)
      dut.io.cpuWriteEn.poke(false.B)
      dut.clock.step()
      // dut.io.storeType.poke(0.U)
      // dut.io.cpuWriteData.poke("b00000000_00001000_00000000_11111111".U)
      // dut.io.cpuWriteEn.poke(true.B)
      // dut.clock.step()
      dut.io.addrs.poke("b00000_000000_00100".U)
      println("data : " + dut.io.cpuReadData.peek())
      println("data : " + dut.io.readBlock.peek())
      println("hit : " + dut.io.hit.peek().toString)
    }
  }
}

class CacheTest extends AnyFlatSpec with ChiselScalatestTester {

  "CacheTest" should "pass" in {
    test(new Cache) { dut =>
      dut.io.addrs.poke(0.U)
      dut.io.inMemRead.poke(true.B)
      dut.io.writeBlock.poke("b100000000_00000000_00001101_11111101".U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.io.addrs.poke("b00000_000001_00000".U)
      dut.io.writeBlock.poke("b00000000_00000000_00000000_11100101".U(256.W))
      dut.clock.step()
      dut.clock.step()

      dut.io.inMemRead.poke(false.B)
      dut.io.inMemWrite.poke(true.B)
      dut.io.cpuWriteData.poke("b00000000_00000000_00000000_00000001".U)
      dut.io.storeType.poke(2.U)
      dut.io.addrs.poke("b00000_000000_00000".U)
      dut.clock.step()
      println("valid : " + dut.io.valid.peek().toString)
      println("outMemRead : " + dut.io.outMemRead.peek().toString)
      println("outMemWrite : " + dut.io.outMemWrite.peek().toString)
      println("cpuReadData : " + dut.io.cpuReadData.peek().toString)
      println("readBlock : " + dut.io.readBlock.peek().toString)
    }
  }
}
