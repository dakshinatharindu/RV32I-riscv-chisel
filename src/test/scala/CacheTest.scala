package riscv

import chisel3._
import chiseltest._
import org.scalatest.flatspec.AnyFlatSpec

import riscv.shared.Constants._

class L1Test extends AnyFlatSpec with ChiselScalatestTester {

  "L1Test" should "pass" in {
    test(new L1) { dut =>
      dut.io.addrs.poke("b00000_000000_00100".U)
      dut.io.writeBlock.poke("b100000000_00000000_00001101_11111101".U(256.W))
      dut.io.blockWriteEn.poke(true.B)
      dut.io.cpuWriteEn.poke(false.B)
      dut.clock.step()
      // dut.io.storeType.poke(0.U)
      // dut.io.cpuWriteData.poke("b00000000_00001000_00000000_11111111".U)
      // dut.io.cpuWriteEn.poke(true.B)
      // dut.clock.step()
      dut.io.addrs.poke("b00000_000000_00100".U)
      println("data : " + dut.io.cpuReadData.peek())
      println("data : " + dut.io.readBlock.peek())
      println("hit : " + dut.io.hit.peek().toString)
    }
  }
}

// class VCTest extends AnyFlatSpec with ChiselScalatestTester {

//   "VCTest" should "pass" in {
//     test(new VC) { dut =>
//       dut.io.addrs.poke(6.U)
//       dut.io.wen.poke(true.B)
//       dut.io.writeData.poke("b100".U)
//       dut.clock.step()
//       println("inx :" + dut.io.index.peek().toString)
//     }
//   }
// }
