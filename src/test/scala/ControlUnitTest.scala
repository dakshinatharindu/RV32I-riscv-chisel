package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class ControlUnitTest extends AnyFlatSpec with ChiselScalatestTester {

  "ControlUnitTest" should "pass" in {
    test(new ControlUnit) { dut =>


      dut.io.instr.poke("b00000000100000000000000010010011".U)
      println("format " + dut.io.format.peek().toString)
      println("ALUCtrl " + dut.io.ALUCtrl.peek().toString)
      println("regWrite " + dut.io.regWrite.peek().toString)
      println("memWrite " + dut.io.memWrite.peek().toString)
      println("memRead " + dut.io.memRead.peek().toString)
      println("rs2Imm " + dut.io.rs2Imm.peek().toString)
      println("aluMem " + dut.io.aluMem.peek().toString)
      println("pcAluMem " + dut.io.pcAluMem.peek().toString)
      println("pcImm " + dut.io.pcImm.peek().toString)
      println("immBranch " + dut.io.immBranch.peek().toString)
      println("aluBranch " + dut.io.aluBranch.peek().toString)
      println("storeType " + dut.io.storeType.peek().toString)

    }
  }
}
