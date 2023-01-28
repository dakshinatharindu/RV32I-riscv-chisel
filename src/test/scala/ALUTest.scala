package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ALUTest extends AnyFlatSpec with ChiselScalatestTester {
  "ALU" should "pass" in {
    test(new ALU) { dut =>
      def alu(a: Int, b: Int, op: Int): Int = {
        op match {
          case 0 => a & b
          case 1 => a | b
          case 2 => a ^ b
          case 3 => a + b
          case 4 => a - b
          case 5 => if (a < b) 1 else 0
          case 6 => a << b
          case _ => -123 // This shall not happen
        }
      }

      def testOne(a: Int, b: Int, fun: Int): Unit = {
        dut.io.A.poke(a.S)
        dut.io.B.poke(b.S)
        dut.io.ALUCtrl.poke(fun.U)
        // dut.io.ALUOut.expect(alu(a, b, fun).S)
        println("Result is: " + dut.io.eq.peek().toString)
      }
      testOne(-256, -256, sub)
    }
  }
}
