package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ProcessorTest extends AnyFlatSpec with ChiselScalatestTester {

  "ProcessorTest" should "pass" in {
    test(new Processor) { dut =>
      dut.io.instr.poke("b0000000_01011_00000_000_00001_0010011".U)
      dut.clock.step()
      dut.io.instr.poke("b0000000_00001_00000_000_00000_0100011".U)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.instr.poke("b0100000_00000_00000_000_00010_0010011".U)
      dut.clock.step()
      dut.io.instr.poke("b0100000_00001_00010_000_00000_0100011".U)
    //   dut.clock.step()
    //   dut.clock.step()
    //   dut.clock.step()
    //   dut.io.instr.poke("b0000000_00000_00000_000_00010_1101111".U)
    //   dut.clock.step()
    //   dut.clock.step()
    //   dut.clock.step()
    //   dut.clock.step()
    //   dut.clock.step()
      println("instrAddrs " + dut.io.instrAddrs.peek().toString)
      println("memAdrrs " + dut.io.memAdrrs.peek().toString)
      println("memWriteBlock " + dut.io.memWriteBlock.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      

    }
  }
}

