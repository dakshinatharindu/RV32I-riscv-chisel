package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class L1Test extends AnyFlatSpec with ChiselScalatestTester {

  "L1Test" should "pass" in {
    test(new L1) { dut =>
      dut.io.addrs.poke("b00000_000000_00000".U)
      dut.io.blockWriteEn.poke(true.B)
      dut.io.writeBlock.poke(3.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.io.addrs.poke("b00001_000000_00000".U)
      dut.io.writeBlock.poke(5.U(256.W))
      dut.clock.step()
      dut.clock.step()

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
      dut.io.addrs.poke("b00000_000000_00000".U)
      dut.io.inMemRead.poke(true.B)
      dut.io.writeBlock.poke(3.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.addrs.poke("b00001_000000_00000".U)
      dut.io.writeBlock.poke(5.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.io.inMemRead.poke(false.B)
      dut.io.inMemWrite.poke(true.B)
      dut.io.cpuWriteData.poke(34.U)
      dut.io.storeType.poke(0.U)
      dut.clock.step()
      dut.io.inMemRead.poke(true.B)
      dut.io.inMemWrite.poke(false.B)
      dut.io.addrs.poke("b00010_000000_00000".U)
      dut.io.writeBlock.poke(7.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.addrs.poke("b00011_000000_00000".U)
      dut.io.writeBlock.poke(9.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.addrs.poke("b00110_000000_00000".U)
      dut.io.writeBlock.poke(11.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.addrs.poke("b00111_000000_00000".U)
      dut.io.writeBlock.poke(13.U(256.W))
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()

      println("valid : " + dut.io.valid.peek().toString)
      println("outMemRead : " + dut.io.outMemRead.peek().toString)
      println("outMemWrite : " + dut.io.outMemWrite.peek().toString)
      println("cpuReadData : " + dut.io.cpuReadData.peek().toString)
      println("readBlock : " + dut.io.readBlock.peek().toString)
    }
  }
}
