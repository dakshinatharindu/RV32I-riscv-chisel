package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class CoreTest extends AnyFlatSpec with ChiselScalatestTester {

  "CoreTest" should "pass" in {
    test(new Core) { dut =>
      // dut.io.instr.poke("h01c12083".U)
      // dut.clock.step()
      // dut.clock.step()
      // dut.clock.step()
      // dut.clock.step()
      // dut.io.cpu_ready.poke(true.B)
      // dut.clock.step()

      dut.io.instr.poke("hfef42223".U)
      dut.io.cpu_wait.poke(true.B)
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.clock.step()
      dut.io.cpu_wait.poke(false.B)
      dut.clock.step()

      println("ALUOut " + dut.io.ALUOut.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      println("Next Addr " + dut.io.instrAddrs.peek().toString)
      println("memWriteData " + dut.io.memWriteData.peek().toString)

    }
  }
}
