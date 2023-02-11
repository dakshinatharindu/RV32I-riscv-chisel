package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class CoreTest extends AnyFlatSpec with ChiselScalatestTester {

  "CoreTest" should "pass" in {
    test(new Core) { dut =>
      dut.io.instr.poke("h06100793".U)
      dut.clock.step()
      dut.io.instr.poke("hfef407a3".U)
      
      println("ALUOut " + dut.io.ALUOut.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      println("outAddr " + dut.io.instrAddrs.peek().toString)
      println("memWriteData " + dut.io.memWriteData.peek().toString)
      println("storeType " + dut.io.storeType.peek().toString)

    }
  }
}
