package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class OtherComponentsTets extends AnyFlatSpec with ChiselScalatestTester {
  "OtherComponents" should "pass" in {
    test(new BranchAdder) { dut =>
     dut.io.pc.poke(5.U)
     dut.io.imm.poke(-1.S)
     println(dut.io.outAddr.peek().toString)
    }
  }
}

