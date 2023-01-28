package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ControlUnitTest extends AnyFlatSpec with ChiselScalatestTester {
  "DecoderTest" should "pass" in {
    test(new Decoder) { dut =>
      val opcodes = Seq(
        "b0110011".U,
        "b0010011".U,
        "b0000011".U,
        "b1100111".U,
        "b0100011".U,
        "b1100011".U,
        "b0110111".U,
        "b0010111".U,
        "b1101111".U
      )
      val expects = Seq(R.U, I.U, I.U, I.U, S.U, B.U, U.U, U.U, J.U)

      for (i <- 0 until opcodes.length) {
        dut.io.opcode.poke(opcodes(i))
        dut.io.format.expect(expects(i))
      }
    }
  }

  "ControlUnitTest" should "pass" in {
    test(new ControlUnit) { dut =>
      dut.io.instr.poke("b0000000_00000_00000_000_00000_0110111".U)
      println(dut.io.ALUCtrl.peek().toString)
    }
  }
}
