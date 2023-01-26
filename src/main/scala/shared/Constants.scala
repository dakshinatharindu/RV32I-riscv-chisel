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
}
// the following does NOT result in an unsigned shift
// // res := (a.asUInt >> 1).asSInt
// // work around
// res := (a >> 1) & 0x7fffffff.S