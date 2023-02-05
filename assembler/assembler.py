Opcode = {"R": "0110011", "I": "0010011", "I_load": "0000011", "I_jalr": "1100111",
          "B": "1100011", "S": "0100011", "U_lui": "0110111", "U_auipc": "0010111", "J_jal": "1101111"}

InstrType = {"auipc": ("U_auipc",""), "lui": ("U_lui",""),
             "jal": ("J_jal",""),
             "jalr": ("I_jalr", "000"),
             "beq": ("B", "000"), "bne": ("B", "001"), "blt": ("B", "100"), "bge": ("B", "101"), "bltu": ("B", "110"), "bgeu": ("B", "111"),
             "lb": ("I_load", "000"), "lh": ("I_load", "001"), "lw": ("I_load", "010"), "lbu": ("I_load", "100"), "lhu": ("I_load", "101"),
             "sb": ("S", "000"), "sh": ("S", "001"), "sw": ("S", "010"),
             "addi": ("I", "000"), "slti": ("I", "010"), "sltiu": ("I", "011"), "xori": ("I", "100"), "ori": ("I", "110"), "andi": ("I", "111"),
             "slli": ("I", "001", "0000000"), "srli": ("I", "101", "0000000"), "srai": ("I", "101", "0100000"),
             "add": ("R", "000", "0000000"), "sub": ("R", "000", "0100000"), "sll": ("R", "001", "0000000"), "slt": ("R", "010", "0000000"), "sltu": ("R", "011", "0000000"),
             "xor": ("R", "100", "0000000"), "srl": ("R", "101", "0000000"), "sra": ("R", "101", "0100000"), "or": ("R", "110", "0000000"), "and": ("R", "111", "0000000"), }

ReadFile = open("assembler/AssemblyCodes.txt","r")
WriteFile = open("assembler/InstrInit.mif","w")
WriteFile.write("DEPTH = 512;\n")
WriteFile.write("WIDTH = 32;\n")
WriteFile.write("ADDRESS_RADIX = HEX;\n")
WriteFile.write("DATA_RADIX = BIN;\n")
WriteFile.write("CONTENT\n")
WriteFile.write("BEGIN\n")
lineNumber = 0
for instr in ReadFile:
    instr = "jal 2 100"
    instr = instr.strip().split()
    ty = InstrType[instr[0]]
    op = Opcode[ty[0]]
    code = ""

    if(ty[0] == "R"):
        rd = instr[1]
        rs1 = instr[2]
        rs2 = instr[3]
        code = ty[2] + bin(int(rs2))[2:].rjust(5, "0") + bin(int(rs1)
                                                            )[2:].rjust(5, "0") + ty[1] + bin(int(rd))[2:].rjust(5, "0") + op

    elif((ty[0] == "I") or (ty[0] == "I_load") or (ty[0] == "I_jalr")):
        rd = instr[1]
        rs1 = instr[2]
        imm = int(instr[3])
        if (len(ty) == 3):
            code = ty[2] + bin(((1 << 5) - 1) & imm)[2:].rjust(5, "0") + bin(int(rs1))[
                2:].rjust(5, "0") + ty[1] + bin(int(rd))[2:].rjust(5, "0") + op
        else:
            code = bin(((1 << 12) - 1) & imm)[2:].rjust(12, "0") + bin(int(rs1))[
                2:].rjust(5, "0") + ty[1] + bin(int(rd))[2:].rjust(5, "0") + op

    elif(ty[0] == "S"):
        rs2 = instr[1]
        rs1 = instr[2]
        imm = bin(((1 << 12) - 1) & int(instr[3]))[2:].rjust(12, "0")
        code = imm[0:7] + bin(int(rs2))[2:].rjust(5, "0")+ bin(int(rs1))[2:].rjust(5, "0") + ty[1] + imm[7:] + op

    elif(ty[0] == "B"):
        rs1 = instr[1]
        rs2 = instr[2]
        imm = bin(((1 << 13) - 1) & int(instr[3]))[2:].rjust(13, "0")
        code = imm[0] + imm[2:8] + bin(int(rs2))[2:].rjust(5, "0")+ bin(int(rs1))[2:].rjust(5, "0") + ty[1] + imm[8:12] + imm[1] + op

    elif(ty[0] == "U_auipc" or ty[0] == "U_lui"):
        rd = instr[1]
        imm = bin(((1 << 20) - 1) & int(instr[2]))[2:].rjust(20, "0")
        code = imm +  bin(int(rd))[2:].rjust(5, "0") +  op

    elif(ty[0] == "J_jal"):
        rd = instr[1]
        imm = bin(((1 << 21) - 1) & int(instr[2]))[2:].rjust(21, "0")
        code = imm[0] +imm[10:20]+ imm[9]+imm[1:9] +  bin(int(rd))[2:].rjust(5, "0") +  op
    else:
        assert False, "Invalid Instruction!!!"
    
    WriteFile.write(hex(lineNumber)[2:] + " : " + code + "\n")
    lineNumber += 1

WriteFile.write("END;\n")
WriteFile.close()
ReadFile.close()