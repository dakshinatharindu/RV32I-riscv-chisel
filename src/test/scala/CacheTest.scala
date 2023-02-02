package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class L1Test extends AnyFlatSpec with ChiselScalatestTester {

  "L1Test" should "pass" in {
    test(new L1) { dut =>
      dut.io.addrs.poke(2.U)
      dut.io.wen.poke(true.B)
      dut.io.writeData.poke("b00000000_00000000_00001101_11111101".U)
      dut.clock.step()
      dut.io.addrs.poke(2.U)
      dut.io.storeType.poke(2.U)
      dut.io.writeData.poke("b00000000_00001000_00000001_11111111".U)
      dut.clock.step()
      println("data : " + dut.io.readData.peek().toString)
      println("hit : " + dut.io.hit.peek().toString)
    }
  }
}
