package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ImmGenTest extends AnyFlatSpec with ChiselScalatestTester {
  "ImmGenTest" should "pass" in {
    test(new ImmGen) { dut =>
      dut.io.in.poke("b001010101010_00000_000_00000_1100111".U)
      dut.io.format.poke(5.U)
      println(dut.io.out.peek())
    }
  }
}
