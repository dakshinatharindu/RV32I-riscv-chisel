import os
import sys

filename = str(sys.argv[1])
print(filename)
flag = '/opt/riscv/bin/riscv32-unknown-elf-'
os.system(flag+'gcc '+filename +
          ' -s -o K_1.elf -nostartfiles -march=rv32ia -mabi=ilp32 -fPIC')
os.system(flag+'objcopy K_1.elf  -O verilog g.hex')
os.system(flag+'objdump  K_1.elf -d >  assembly.txt')

assembly = open("assembly.txt", 'r')
mem = open("InstrInit.mif", 'w')
mem.write("DEPTH = 512;\n")
mem.write("WIDTH = 32;\n")
mem.write("ADDRESS_RADIX = HEX;\n")
mem.write("DATA_RADIX = HEX;\n")
mem.write("CONTENT\n")
mem.write("BEGIN\n")

# Instruction to load the cache content after execution
mem.write("0 : 00200F93;\n")  # addi 31 0 2
mem.write("1 : 00800093;\n")  # addi 1 0 8
mem.write("2 : FFFF8F93;\n")  # addi 1 0 8
mem.write("3 : 000F9863;\n")  # bne 31 0 16
mem.write("4 : 40000F93;\n")  # addi 31 0 1024
mem.write("5 : 400FA003;\n")  # lw 0 31 1024
mem.write("6 : 0000006F;\n")  # jal 0 0

i = 0
for i, line in enumerate(assembly):
    if i < 8:
        continue
    instr = line.strip().split()[1]
    mem.write(hex(i-1)[2:] + " : " + instr + ";\n")


numberOfInstr = i - 6

mem.write("[{}..{}] : 0;\n".format(hex(numberOfInstr+6)[2:], "1FF"))
mem.write("END;\n")
mem.close()
assembly.close()
