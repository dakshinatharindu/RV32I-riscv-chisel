package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class VictimCacheTest extends AnyFlatSpec with ChiselScalatestTester {

  "VictimCacheTest" should "pass" in {
    test(new VictimCache) { dut =>
      dut.io.inAddrs.poke("b00001_000000_00000".U)
      dut.io.storeAddrs.poke("b0000000000".U)
      dut.io.inValid.poke(true.B)
      dut.io.inData.poke(3.U(256.W))
      dut.io.en.poke(true.B)
      dut.clock.step()
      dut.io.en.poke(false.B)
      dut.io.inAddrs.poke("b00000_000000_00000".U)

      //   dut.io.inAddrs.poke("b00000_010000_00000".U)
      //   dut.clock.step()

      println("outAddrs : " + dut.io.outAddrs.peek())
      println("outData : " + dut.io.outData.peek())
      println("vhit : " + dut.io.vhit.peek().toString)
    }
  }
}
