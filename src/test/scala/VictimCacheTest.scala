package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class VictimCacheTest extends AnyFlatSpec with ChiselScalatestTester {

  "VictimCacheTest" should "pass" in {
    test(new VictimCache) { dut =>
      dut.io.inAddrs.poke("b00000_000000_00000".U)
      dut.io.storeAddrs.poke("b00000000010".U)
      dut.io.inData.poke("b00000000_00000000_00001101_11111101".U(256.W))
      dut.io.en.poke(true.B)
      dut.clock.step()
      dut.io.en.poke(false.B)
      dut.io.inAddrs.poke("b00000_000010_00000".U)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.inAddrs.poke("b00000_000011_00000".U)
      dut.io.inData.poke("b00000000_00000000_00000000_11111101".U(256.W))
      dut.io.storeAddrs.poke("b00000000011".U)
      dut.io.en.poke(true.B)
      dut.clock.step()
      dut.io.en.poke(false.B)
      dut.clock.step()
      dut.io.inAddrs.poke("b00000_000010_00000".U)
      dut.clock.step()

      println("outAddrs : " + dut.io.outAddrs.peek())
      println("outData : " + dut.io.outData.peek())
      println("vhit : " + dut.io.vhit.peek().toString)
    }
  }
}
