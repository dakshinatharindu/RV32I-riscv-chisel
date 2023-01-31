package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class CoreTest extends AnyFlatSpec with ChiselScalatestTester {

  "CoreTest" should "pass" in {
    test(new Core) { dut =>
      dut.io.instr.poke("b0000000_01111_00000_000_00001_0010011".U)

      dut.clock.step()
      dut.io.instr.poke("b0000000_00001_00000_010_00000_0100011".U)
      println("ALUOut " + dut.io.ALUOut.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      println("outAddr " + dut.io.instrAddrs.peek().toString)
      println("memWriteData " + dut.io.memWriteData.peek().toString)
      dut.clock.step()
      dut.io.instr.poke("b0000000_00000_00000_000_00000_1101111".U)

      println("ALUOut " + dut.io.ALUOut.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      println("outAddr " + dut.io.instrAddrs.peek().toString)
      println("memWriteData " + dut.io.memWriteData.peek().toString)
      dut.clock.step()
      println("outAddr " + dut.io.instrAddrs.peek().toString)
      dut.clock.step()
      println("outAddr " + dut.io.instrAddrs.peek().toString)
      dut.clock.step()
      println("outAddr " + dut.io.instrAddrs.peek().toString)

    }
  }
}
