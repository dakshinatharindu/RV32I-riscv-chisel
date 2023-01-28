package riscv.shared

object Constants {

  // ALUCtrl
  val and = 0x0 // 0000
  val or = 0x1 // 0001
  val xor = 0x2 // 0010
  val add = 0x3 // 0011
  val sub = 0x4 // 0110
  val slt = 0x5 // 0111
  val sll = 0x6 // 1000
  val sltu = 0x7 // 1001
  val srl = 0x8 // 1010
  val sra = 0x9 // 1011
  val jalr = 0xa // 1010
  val selectB = 0xb // 1011

  // Instruction Format
  val R = 0x0 // 00100
  val I = 0x1 // 00100
  val S = 0x2 // 01000
  val B = 0x3 // 11000
  val U = 0x4 // 01101
  val J = 0x5 // 11011

  // Sub Instruction Format
  val R_ = "b01100"
  val I_ = "b00100"
  val I_jalr = "b11001"
  val I_load = "b00000"
  val S_ = "b01000"
  val B_ = "b11000"
  val U_lui = "b01101"
  val U_auipc = "b00101"
  val J_jal = "b11011"

  // ALU funcCode
  val ADD = "b0000"
  val SUB = "b1000"
  val SLL = "b0001"
  val SLT = "b0010"
  val SLTU = "b0011"
  val XOR = "b0100"
  val SRL = "b0101"
  val SRA = "b1101"
  val OR = "b0110"
  val AND = "b0111"

  // Branch func3
  val BEQ = "b000"
  val BNE = "b001"
  val BLT = "b100"
  val BGE = "b101"
  val BLTU = "b110"
  val BGEU = "b111"
}
