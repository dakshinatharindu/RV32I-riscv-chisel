package riscv

import chisel3._
import chisel3.util._
import chisel3.stage._
import riscv.shared.Constants._

class InstructionMemory extends Module{
    val io = IO(new Bundle{
        val addrs = Input(UInt())
    })
}
