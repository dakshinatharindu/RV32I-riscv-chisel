package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ImmGenTest extends AnyFlatSpec with ChiselScalatestTester {
  "ImmGenTest" should "pass" in {
    test(new ImmGen) { dut =>
      dut.io.in.poke("h024000ef".U)
      dut.io.format.poke(J.U)
      println(dut.io.out.peek())
    }
  }
}
