package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class LoadSelectorTest extends AnyFlatSpec with ChiselScalatestTester {

  "LoadSelectorTest" should "pass" in {
    test(new LoadSelector) { dut =>
      dut.io.func3.poke("b001".U)
      dut.io.inData.poke("b00000000_00000000_11001010_11101011".U)
      println(dut.io.outData.peek().toString)
    }
  }
}
