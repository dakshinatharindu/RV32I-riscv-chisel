package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class L1Test extends AnyFlatSpec with ChiselScalatestTester {

  "L1Test" should "pass" in {
    test(new L1) { dut =>
      dut.io.blockWriteEn.poke(true.B)
      dut.io.writeBlock.poke(0.U)
      dut.clock.step()
      dut.io.blockWriteEn.poke(false.B)
      dut.io.addrs.poke(15.U)
      dut.io.cpuWriteEn.poke(true.B)
      dut.io.storeType.poke(0.U)
      dut.io.cpuWriteData.poke(97)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()

      dut.io.addrs.poke(14.U)
      dut.io.cpuWriteEn.poke(true.B)
      dut.io.storeType.poke(0.U)
      dut.io.cpuWriteData.poke(98)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      // dut.io.outMemRead.poke(true.B)
      // dut.clock.step()

      println("data : " + dut.io.cpuReadData.peek())
      println("data : " + dut.io.readBlock.peek())
      println("bufferAddrs : " + dut.io.bufferAddrs.peek())
      println("hit : " + dut.io.hit.peek().toString)
      println("outValid : " + dut.io.outValid.peek().toString)
    }
  }
}

class CacheTest extends AnyFlatSpec with ChiselScalatestTester {

  "CacheTest" should "pass" in {
    test(new Cache) { dut =>
      dut.io.addrs.poke(15.U)
      dut.io.inMemWrite.poke(true.B)
      dut.io.cpuWriteData.poke(97)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      // dut.io.outMemRead.poke(true.B)
      // dut.clock.step()

      println("valid : " + dut.io.valid.peek().toString)
      println("outMemRead : " + dut.io.outMemRead.peek().toString)
      println("outMemWrite : " + dut.io.outMemWrite.peek().toString)
      println("cpuReadData : " + dut.io.cpuReadData.peek().toString)
      println("readBlock : " + dut.io.readBlock.peek().toString)
    }
  }
}
