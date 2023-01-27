package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class RegisterFileTest extends AnyFlatSpec with ChiselScalatestTester {
  "RegisterFileTest" should "pass" in {
    test(new RegisterFile) { c =>
      def readExpect(addr: Int, value: Int): Unit = {
        c.io.readAddr1.poke(addr.U)
        c.io.readData1.expect(value.S)
      }
      def write(addr: Int, value: Int): Unit = {
        c.io.writeEn.poke(true.B)
        c.io.writeData.poke(value.S)
        c.io.writeAddr.poke(addr.U)
        c.clock.step(1)
        c.io.writeEn.poke(false.B)
      }
      // everything should be 0 on init
      for (i <- 0 until 32) {
        readExpect(i, 0)
        readExpect(i, 0)
      }

      // write 5 * addr + 3
      for (i <- 0 until 32) {
        write(i, 5 * i + 3)
      }

      // check that the writes worked
      for (i <- 0 until 32) {
        readExpect(i, if (i == 0) 0 else 5 * i + 3)
      }
    }
  }
}
