package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class LoadSelector extends Module {

  val io = IO(new Bundle {
    val func3 = Input(UInt(3.W))
    val byteSel = Input(UInt(2.W))
    val inData = Input(UInt(32.W))
    val outData = Output(SInt(32.W))
  })

  val res = WireDefault(0.S(32.W))

  switch(io.func3) {
    is("b000".U) {
      switch(io.byteSel) {
        is("b00".U) { res := io.inData(7, 0).asSInt }
        is("b01".U) { res := io.inData(15, 8).asSInt }
        is("b10".U) { res := io.inData(23, 16).asSInt }
        is("b11".U) { res := io.inData(31, 24).asSInt }
      }
    }
    is("b001".U) {
      res := Mux(
        io.byteSel(1) === 0.U,
        io.inData(15, 0).asSInt,
        io.inData(31, 16).asSInt
      )
    }
    is("b010".U) { res := io.inData.asSInt }
    is("b100".U) {
      switch(io.byteSel) {
        is("b00".U) { res := (0.U(24.W) ## io.inData(7, 0)).asSInt }
        is("b01".U) { res := (0.U(24.W) ## io.inData(15, 8)).asSInt }
        is("b10".U) { res := (0.U(24.W) ## io.inData(23, 16)).asSInt }
        is("b11".U) { res := (0.U(24.W) ## io.inData(31, 24)).asSInt }
      }
    }
    is("b101".U) {
      res := Mux(
        io.byteSel(1) === 0.U,
        (0.U(16.W) ## io.inData(15, 0)).asSInt,
        (0.U(16.W) ## io.inData(31, 16)).asSInt
      )
    }

  }

  io.outData := res
}

object LoadSelector extends App {
  val myverilog = (new ChiselStage).emitVerilog(
    new LoadSelector,
    Array("--target-dir", "verilog/")
  )
}
