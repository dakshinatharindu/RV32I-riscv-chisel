// package riscv

// import chisel3._
// import chiseltest._
// import org.scalatest.flatspec.AnyFlatSpec

// import riscv.shared.Constants._

// class ProcessorTest extends AnyFlatSpec with ChiselScalatestTester {

//   "ProcessorTest" should "pass" in {
//     test(new Processor) { dut =>
//       dut.io.instr.poke("h00200F93".U)
//       dut.clock.step()
//       dut.io.instr.poke("h00200F93".U)
//       dut.clock.step()
//       dut.io.instr.poke("hFFFF8F93".U)
//       dut.clock.step()
//       dut.io.instr.poke("h20F9C63".U)
//       dut.clock.step()
//       dut.io.instr.poke("hFFFF8F93".U)
//       dut.clock.step()
//       dut.io.instr.poke("h20F9C63".U)
//       dut.clock.step()

//       println("instrAddrs " + dut.io.instrAddrs.peek().toString)
//       println("memAdrrs " + dut.io.memAdrrs.peek().toString)
//       println("memWriteBlock " + dut.io.memWriteBlock.peek().toString)
//       println("memRead " + dut.io.memRead.peek().toString)
//       println("memWrite " + dut.io.memWrite.peek().toString)

//     }
//   }
// }
