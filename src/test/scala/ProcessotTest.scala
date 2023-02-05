package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ProcessorTest extends AnyFlatSpec with ChiselScalatestTester {

  "ProcessorTest" should "pass" in {
    test(new Processor) { dut =>
      dut.io.instr.poke("b00010110010000000000000010010011".U)
      dut.clock.step()
      dut.io.instr.poke("b00000000000100000010000000100011".U)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.instr.poke("b01000000000000000000000100010011".U)
      dut.clock.step()
      dut.io.instr.poke("b01000000000000010010000110000011".U)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.instr.poke("b00000000000000000000111111101111".U)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      println("instrAddrs " + dut.io.instrAddrs.peek().toString)
      println("memAdrrs " + dut.io.memAdrrs.peek().toString)
      println("memWriteBlock " + dut.io.memWriteBlock.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      

    }
  }
}

