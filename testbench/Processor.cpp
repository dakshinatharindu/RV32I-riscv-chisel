#include <stdlib.h>
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "VProcessor.h"
#include "verilated.h"

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VProcessor *tb = new VProcessor;

    const char *filename = "verilatorInstr.txt";
    std::fstream assemblyFile;
    assemblyFile.open("verilatorAssemblyInstr.txt", std::ios::in);
    unsigned int instr;
    bool finished = false;
    int clockCount = 0;
    int cache[64][8] = {0};
    std::vector<unsigned int> instructions;
    std::vector<std::string> assemblyInstructions;
    unsigned int instrAddrs = 0;

    std::ifstream infile(filename, std::fstream::in);
    while (infile >> std::hex >> instr) {
        instructions.push_back(instr);
    }

    if (assemblyFile.is_open()) {
        std::string assm;
        while (getline(assemblyFile, assm)) {
            assemblyInstructions.push_back(assm);
        }
        assemblyFile.close();
    }

    tb->reset = 0;
    tb->eval();
    tb->reset = 1;
    tb->eval();
    tb->reset = 0;
    tb->eval();
    while (!Verilated::gotFinish()) {
        clockCount++;
        printf("----------------------------------------------------------\n");
        std::cout << "\t\t" << std::setfill('0') << std::setw(8) << std::hex
                  << instructions[instrAddrs] << "\t"
                  << assemblyInstructions[instrAddrs] << std::endl;
        tb->io_instr = instructions[instrAddrs];
        tb->clock = 0;
        tb->eval();

        printf("clock count :%d\n", clockCount);
        printf("Instr. Addrs. :%d\n", tb->io_instrAddrs);
        printf("\n");
        printf("ALUCTRL :%d\n", tb->Processor__DOT__core__DOT__controlUnit_io_ALUCtrl);
        printf("ALUOUT/cacheAddrs :%d\n", tb->Processor__DOT__core__DOT__alu__DOT___GEN_11);
        printf("ALU equal :%d\n", tb->Processor__DOT__core__DOT__alu_io_eq);
        printf("ALU greaterThanEqual :%d\n", tb->Processor__DOT__core__DOT__alu_io_ge);
        printf("ALU greaterThanEqualUnsigned :%d\n", tb->Processor__DOT__core__DOT__alu_io_geu);
        printf("\n");
        printf("Immediate :%d\n", (int)(std::bitset<32>(tb->Processor__DOT__core__DOT__immGen_io_out)).to_ulong());
        printf("RegWrite Data :%d\n", (int)(std::bitset<32>(tb->Processor__DOT__core__DOT__pcAluMemMux_io_out)).to_ulong());
        printf("RegRead Data1 :%d\n", (int)(std::bitset<32>(tb->Processor__DOT__core__DOT__registerFile_io_readData1)).to_ulong());
        printf("RegRead Data2 :%d\n", (int)(std::bitset<32>(tb->Processor__DOT__core__DOT__registerFile_io_readData2)).to_ulong());
        printf("\n");
        printf("CacheRead Data :%d\n", (int)(std::bitset<32>(tb->Processor__DOT__cacheCore__DOT__cache_io_cpuReadData)).to_ulong());
        printf("cacheRead :%d\n", tb->Processor__DOT__core__DOT__controlUnit_io_memRead);
        printf("cacheWrite :%d\n", tb->Processor__DOT__core__DOT__controlUnit_io_memWrite);
        printf("\n");
        printf("mainMemAdrrs :%d\n", tb->io_memAdrrs);
        printf("mainMemRead :%d\n", tb->io_memRead);
        printf("mainMemWrite :%d\n", tb->io_memWrite);
        printf("memWriteBlock : ");
        for (int i = 0; i < 8; i++) {
            printf("%d ", tb->io_memWriteBlock[i]);
        }
        if (instrAddrs == 2) {
            if (finished) {
                cache[0][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_0)
                        .to_ulong();
                cache[0][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_1)
                        .to_ulong();
                cache[0][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_2)
                        .to_ulong();
                cache[0][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_3)
                        .to_ulong();
                cache[0][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_4)
                        .to_ulong();
                cache[0][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_5)
                        .to_ulong();
                cache[0][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_6)
                        .to_ulong();
                cache[0][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_0_line_7)
                        .to_ulong();
                cache[1][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_0)
                        .to_ulong();
                cache[1][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_1)
                        .to_ulong();
                cache[1][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_2)
                        .to_ulong();
                cache[1][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_3)
                        .to_ulong();
                cache[1][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_4)
                        .to_ulong();
                cache[1][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_5)
                        .to_ulong();
                cache[1][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_6)
                        .to_ulong();
                cache[1][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_1_line_7)
                        .to_ulong();
                cache[2][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_0)
                        .to_ulong();
                cache[2][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_1)
                        .to_ulong();
                cache[2][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_2)
                        .to_ulong();
                cache[2][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_3)
                        .to_ulong();
                cache[2][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_4)
                        .to_ulong();
                cache[2][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_5)
                        .to_ulong();
                cache[2][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_6)
                        .to_ulong();
                cache[2][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_2_line_7)
                        .to_ulong();
                cache[3][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_0)
                        .to_ulong();
                cache[3][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_1)
                        .to_ulong();
                cache[3][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_2)
                        .to_ulong();
                cache[3][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_3)
                        .to_ulong();
                cache[3][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_4)
                        .to_ulong();
                cache[3][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_5)
                        .to_ulong();
                cache[3][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_6)
                        .to_ulong();
                cache[3][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_3_line_7)
                        .to_ulong();
                cache[4][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_0)
                        .to_ulong();
                cache[4][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_1)
                        .to_ulong();
                cache[4][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_2)
                        .to_ulong();
                cache[4][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_3)
                        .to_ulong();
                cache[4][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_4)
                        .to_ulong();
                cache[4][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_5)
                        .to_ulong();
                cache[4][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_6)
                        .to_ulong();
                cache[4][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_4_line_7)
                        .to_ulong();
                cache[5][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_0)
                        .to_ulong();
                cache[5][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_1)
                        .to_ulong();
                cache[5][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_2)
                        .to_ulong();
                cache[5][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_3)
                        .to_ulong();
                cache[5][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_4)
                        .to_ulong();
                cache[5][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_5)
                        .to_ulong();
                cache[5][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_6)
                        .to_ulong();
                cache[5][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_5_line_7)
                        .to_ulong();
                cache[6][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_0)
                        .to_ulong();
                cache[6][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_1)
                        .to_ulong();
                cache[6][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_2)
                        .to_ulong();
                cache[6][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_3)
                        .to_ulong();
                cache[6][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_4)
                        .to_ulong();
                cache[6][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_5)
                        .to_ulong();
                cache[6][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_6)
                        .to_ulong();
                cache[6][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_6_line_7)
                        .to_ulong();
                cache[7][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_0)
                        .to_ulong();
                cache[7][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_1)
                        .to_ulong();
                cache[7][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_2)
                        .to_ulong();
                cache[7][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_3)
                        .to_ulong();
                cache[7][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_4)
                        .to_ulong();
                cache[7][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_5)
                        .to_ulong();
                cache[7][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_6)
                        .to_ulong();
                cache[7][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_7_line_7)
                        .to_ulong();
                cache[8][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_0)
                        .to_ulong();
                cache[8][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_1)
                        .to_ulong();
                cache[8][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_2)
                        .to_ulong();
                cache[8][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_3)
                        .to_ulong();
                cache[8][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_4)
                        .to_ulong();
                cache[8][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_5)
                        .to_ulong();
                cache[8][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_6)
                        .to_ulong();
                cache[8][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_8_line_7)
                        .to_ulong();
                cache[9][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_0)
                        .to_ulong();
                cache[9][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_1)
                        .to_ulong();
                cache[9][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_2)
                        .to_ulong();
                cache[9][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_3)
                        .to_ulong();
                cache[9][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_4)
                        .to_ulong();
                cache[9][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_5)
                        .to_ulong();
                cache[9][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_6)
                        .to_ulong();
                cache[9][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_9_line_7)
                        .to_ulong();
                cache[10][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_0)
                        .to_ulong();
                cache[10][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_1)
                        .to_ulong();
                cache[10][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_2)
                        .to_ulong();
                cache[10][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_3)
                        .to_ulong();
                cache[10][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_4)
                        .to_ulong();
                cache[10][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_5)
                        .to_ulong();
                cache[10][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_6)
                        .to_ulong();
                cache[10][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_10_line_7)
                        .to_ulong();
                cache[11][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_0)
                        .to_ulong();
                cache[11][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_1)
                        .to_ulong();
                cache[11][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_2)
                        .to_ulong();
                cache[11][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_3)
                        .to_ulong();
                cache[11][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_4)
                        .to_ulong();
                cache[11][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_5)
                        .to_ulong();
                cache[11][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_6)
                        .to_ulong();
                cache[11][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_11_line_7)
                        .to_ulong();
                cache[12][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_0)
                        .to_ulong();
                cache[12][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_1)
                        .to_ulong();
                cache[12][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_2)
                        .to_ulong();
                cache[12][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_3)
                        .to_ulong();
                cache[12][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_4)
                        .to_ulong();
                cache[12][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_5)
                        .to_ulong();
                cache[12][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_6)
                        .to_ulong();
                cache[12][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_12_line_7)
                        .to_ulong();
                cache[13][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_0)
                        .to_ulong();
                cache[13][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_1)
                        .to_ulong();
                cache[13][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_2)
                        .to_ulong();
                cache[13][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_3)
                        .to_ulong();
                cache[13][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_4)
                        .to_ulong();
                cache[13][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_5)
                        .to_ulong();
                cache[13][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_6)
                        .to_ulong();
                cache[13][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_13_line_7)
                        .to_ulong();
                cache[14][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_0)
                        .to_ulong();
                cache[14][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_1)
                        .to_ulong();
                cache[14][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_2)
                        .to_ulong();
                cache[14][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_3)
                        .to_ulong();
                cache[14][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_4)
                        .to_ulong();
                cache[14][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_5)
                        .to_ulong();
                cache[14][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_6)
                        .to_ulong();
                cache[14][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_14_line_7)
                        .to_ulong();
                cache[15][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_0)
                        .to_ulong();
                cache[15][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_1)
                        .to_ulong();
                cache[15][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_2)
                        .to_ulong();
                cache[15][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_3)
                        .to_ulong();
                cache[15][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_4)
                        .to_ulong();
                cache[15][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_5)
                        .to_ulong();
                cache[15][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_6)
                        .to_ulong();
                cache[15][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_15_line_7)
                        .to_ulong();
                cache[16][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_0)
                        .to_ulong();
                cache[16][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_1)
                        .to_ulong();
                cache[16][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_2)
                        .to_ulong();
                cache[16][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_3)
                        .to_ulong();
                cache[16][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_4)
                        .to_ulong();
                cache[16][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_5)
                        .to_ulong();
                cache[16][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_6)
                        .to_ulong();
                cache[16][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_16_line_7)
                        .to_ulong();
                cache[17][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_0)
                        .to_ulong();
                cache[17][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_1)
                        .to_ulong();
                cache[17][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_2)
                        .to_ulong();
                cache[17][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_3)
                        .to_ulong();
                cache[17][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_4)
                        .to_ulong();
                cache[17][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_5)
                        .to_ulong();
                cache[17][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_6)
                        .to_ulong();
                cache[17][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_17_line_7)
                        .to_ulong();
                cache[18][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_0)
                        .to_ulong();
                cache[18][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_1)
                        .to_ulong();
                cache[18][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_2)
                        .to_ulong();
                cache[18][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_3)
                        .to_ulong();
                cache[18][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_4)
                        .to_ulong();
                cache[18][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_5)
                        .to_ulong();
                cache[18][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_6)
                        .to_ulong();
                cache[18][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_18_line_7)
                        .to_ulong();
                cache[19][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_0)
                        .to_ulong();
                cache[19][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_1)
                        .to_ulong();
                cache[19][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_2)
                        .to_ulong();
                cache[19][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_3)
                        .to_ulong();
                cache[19][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_4)
                        .to_ulong();
                cache[19][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_5)
                        .to_ulong();
                cache[19][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_6)
                        .to_ulong();
                cache[19][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_19_line_7)
                        .to_ulong();
                cache[20][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_0)
                        .to_ulong();
                cache[20][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_1)
                        .to_ulong();
                cache[20][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_2)
                        .to_ulong();
                cache[20][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_3)
                        .to_ulong();
                cache[20][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_4)
                        .to_ulong();
                cache[20][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_5)
                        .to_ulong();
                cache[20][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_6)
                        .to_ulong();
                cache[20][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_20_line_7)
                        .to_ulong();
                cache[21][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_0)
                        .to_ulong();
                cache[21][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_1)
                        .to_ulong();
                cache[21][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_2)
                        .to_ulong();
                cache[21][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_3)
                        .to_ulong();
                cache[21][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_4)
                        .to_ulong();
                cache[21][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_5)
                        .to_ulong();
                cache[21][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_6)
                        .to_ulong();
                cache[21][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_21_line_7)
                        .to_ulong();
                cache[22][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_0)
                        .to_ulong();
                cache[22][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_1)
                        .to_ulong();
                cache[22][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_2)
                        .to_ulong();
                cache[22][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_3)
                        .to_ulong();
                cache[22][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_4)
                        .to_ulong();
                cache[22][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_5)
                        .to_ulong();
                cache[22][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_6)
                        .to_ulong();
                cache[22][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_22_line_7)
                        .to_ulong();
                cache[23][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_0)
                        .to_ulong();
                cache[23][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_1)
                        .to_ulong();
                cache[23][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_2)
                        .to_ulong();
                cache[23][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_3)
                        .to_ulong();
                cache[23][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_4)
                        .to_ulong();
                cache[23][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_5)
                        .to_ulong();
                cache[23][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_6)
                        .to_ulong();
                cache[23][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_23_line_7)
                        .to_ulong();
                cache[24][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_0)
                        .to_ulong();
                cache[24][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_1)
                        .to_ulong();
                cache[24][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_2)
                        .to_ulong();
                cache[24][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_3)
                        .to_ulong();
                cache[24][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_4)
                        .to_ulong();
                cache[24][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_5)
                        .to_ulong();
                cache[24][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_6)
                        .to_ulong();
                cache[24][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_24_line_7)
                        .to_ulong();
                cache[25][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_0)
                        .to_ulong();
                cache[25][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_1)
                        .to_ulong();
                cache[25][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_2)
                        .to_ulong();
                cache[25][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_3)
                        .to_ulong();
                cache[25][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_4)
                        .to_ulong();
                cache[25][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_5)
                        .to_ulong();
                cache[25][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_6)
                        .to_ulong();
                cache[25][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_25_line_7)
                        .to_ulong();
                cache[26][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_0)
                        .to_ulong();
                cache[26][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_1)
                        .to_ulong();
                cache[26][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_2)
                        .to_ulong();
                cache[26][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_3)
                        .to_ulong();
                cache[26][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_4)
                        .to_ulong();
                cache[26][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_5)
                        .to_ulong();
                cache[26][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_6)
                        .to_ulong();
                cache[26][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_26_line_7)
                        .to_ulong();
                cache[27][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_0)
                        .to_ulong();
                cache[27][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_1)
                        .to_ulong();
                cache[27][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_2)
                        .to_ulong();
                cache[27][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_3)
                        .to_ulong();
                cache[27][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_4)
                        .to_ulong();
                cache[27][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_5)
                        .to_ulong();
                cache[27][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_6)
                        .to_ulong();
                cache[27][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_27_line_7)
                        .to_ulong();
                cache[28][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_0)
                        .to_ulong();
                cache[28][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_1)
                        .to_ulong();
                cache[28][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_2)
                        .to_ulong();
                cache[28][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_3)
                        .to_ulong();
                cache[28][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_4)
                        .to_ulong();
                cache[28][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_5)
                        .to_ulong();
                cache[28][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_6)
                        .to_ulong();
                cache[28][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_28_line_7)
                        .to_ulong();
                cache[29][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_0)
                        .to_ulong();
                cache[29][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_1)
                        .to_ulong();
                cache[29][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_2)
                        .to_ulong();
                cache[29][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_3)
                        .to_ulong();
                cache[29][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_4)
                        .to_ulong();
                cache[29][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_5)
                        .to_ulong();
                cache[29][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_6)
                        .to_ulong();
                cache[29][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_29_line_7)
                        .to_ulong();
                cache[30][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_0)
                        .to_ulong();
                cache[30][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_1)
                        .to_ulong();
                cache[30][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_2)
                        .to_ulong();
                cache[30][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_3)
                        .to_ulong();
                cache[30][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_4)
                        .to_ulong();
                cache[30][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_5)
                        .to_ulong();
                cache[30][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_6)
                        .to_ulong();
                cache[30][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_30_line_7)
                        .to_ulong();
                cache[31][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_0)
                        .to_ulong();
                cache[31][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_1)
                        .to_ulong();
                cache[31][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_2)
                        .to_ulong();
                cache[31][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_3)
                        .to_ulong();
                cache[31][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_4)
                        .to_ulong();
                cache[31][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_5)
                        .to_ulong();
                cache[31][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_6)
                        .to_ulong();
                cache[31][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_31_line_7)
                        .to_ulong();
                cache[32][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_0)
                        .to_ulong();
                cache[32][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_1)
                        .to_ulong();
                cache[32][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_2)
                        .to_ulong();
                cache[32][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_3)
                        .to_ulong();
                cache[32][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_4)
                        .to_ulong();
                cache[32][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_5)
                        .to_ulong();
                cache[32][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_6)
                        .to_ulong();
                cache[32][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_32_line_7)
                        .to_ulong();
                cache[33][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_0)
                        .to_ulong();
                cache[33][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_1)
                        .to_ulong();
                cache[33][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_2)
                        .to_ulong();
                cache[33][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_3)
                        .to_ulong();
                cache[33][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_4)
                        .to_ulong();
                cache[33][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_5)
                        .to_ulong();
                cache[33][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_6)
                        .to_ulong();
                cache[33][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_33_line_7)
                        .to_ulong();
                cache[34][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_0)
                        .to_ulong();
                cache[34][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_1)
                        .to_ulong();
                cache[34][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_2)
                        .to_ulong();
                cache[34][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_3)
                        .to_ulong();
                cache[34][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_4)
                        .to_ulong();
                cache[34][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_5)
                        .to_ulong();
                cache[34][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_6)
                        .to_ulong();
                cache[34][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_34_line_7)
                        .to_ulong();
                cache[35][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_0)
                        .to_ulong();
                cache[35][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_1)
                        .to_ulong();
                cache[35][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_2)
                        .to_ulong();
                cache[35][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_3)
                        .to_ulong();
                cache[35][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_4)
                        .to_ulong();
                cache[35][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_5)
                        .to_ulong();
                cache[35][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_6)
                        .to_ulong();
                cache[35][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_35_line_7)
                        .to_ulong();
                cache[36][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_0)
                        .to_ulong();
                cache[36][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_1)
                        .to_ulong();
                cache[36][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_2)
                        .to_ulong();
                cache[36][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_3)
                        .to_ulong();
                cache[36][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_4)
                        .to_ulong();
                cache[36][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_5)
                        .to_ulong();
                cache[36][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_6)
                        .to_ulong();
                cache[36][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_36_line_7)
                        .to_ulong();
                cache[37][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_0)
                        .to_ulong();
                cache[37][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_1)
                        .to_ulong();
                cache[37][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_2)
                        .to_ulong();
                cache[37][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_3)
                        .to_ulong();
                cache[37][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_4)
                        .to_ulong();
                cache[37][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_5)
                        .to_ulong();
                cache[37][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_6)
                        .to_ulong();
                cache[37][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_37_line_7)
                        .to_ulong();
                cache[38][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_0)
                        .to_ulong();
                cache[38][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_1)
                        .to_ulong();
                cache[38][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_2)
                        .to_ulong();
                cache[38][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_3)
                        .to_ulong();
                cache[38][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_4)
                        .to_ulong();
                cache[38][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_5)
                        .to_ulong();
                cache[38][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_6)
                        .to_ulong();
                cache[38][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_38_line_7)
                        .to_ulong();
                cache[39][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_0)
                        .to_ulong();
                cache[39][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_1)
                        .to_ulong();
                cache[39][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_2)
                        .to_ulong();
                cache[39][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_3)
                        .to_ulong();
                cache[39][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_4)
                        .to_ulong();
                cache[39][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_5)
                        .to_ulong();
                cache[39][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_6)
                        .to_ulong();
                cache[39][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_39_line_7)
                        .to_ulong();
                cache[40][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_0)
                        .to_ulong();
                cache[40][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_1)
                        .to_ulong();
                cache[40][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_2)
                        .to_ulong();
                cache[40][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_3)
                        .to_ulong();
                cache[40][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_4)
                        .to_ulong();
                cache[40][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_5)
                        .to_ulong();
                cache[40][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_6)
                        .to_ulong();
                cache[40][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_40_line_7)
                        .to_ulong();
                cache[41][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_0)
                        .to_ulong();
                cache[41][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_1)
                        .to_ulong();
                cache[41][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_2)
                        .to_ulong();
                cache[41][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_3)
                        .to_ulong();
                cache[41][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_4)
                        .to_ulong();
                cache[41][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_5)
                        .to_ulong();
                cache[41][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_6)
                        .to_ulong();
                cache[41][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_41_line_7)
                        .to_ulong();
                cache[42][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_0)
                        .to_ulong();
                cache[42][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_1)
                        .to_ulong();
                cache[42][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_2)
                        .to_ulong();
                cache[42][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_3)
                        .to_ulong();
                cache[42][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_4)
                        .to_ulong();
                cache[42][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_5)
                        .to_ulong();
                cache[42][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_6)
                        .to_ulong();
                cache[42][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_42_line_7)
                        .to_ulong();
                cache[43][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_0)
                        .to_ulong();
                cache[43][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_1)
                        .to_ulong();
                cache[43][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_2)
                        .to_ulong();
                cache[43][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_3)
                        .to_ulong();
                cache[43][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_4)
                        .to_ulong();
                cache[43][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_5)
                        .to_ulong();
                cache[43][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_6)
                        .to_ulong();
                cache[43][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_43_line_7)
                        .to_ulong();
                cache[44][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_0)
                        .to_ulong();
                cache[44][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_1)
                        .to_ulong();
                cache[44][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_2)
                        .to_ulong();
                cache[44][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_3)
                        .to_ulong();
                cache[44][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_4)
                        .to_ulong();
                cache[44][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_5)
                        .to_ulong();
                cache[44][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_6)
                        .to_ulong();
                cache[44][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_44_line_7)
                        .to_ulong();
                cache[45][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_0)
                        .to_ulong();
                cache[45][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_1)
                        .to_ulong();
                cache[45][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_2)
                        .to_ulong();
                cache[45][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_3)
                        .to_ulong();
                cache[45][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_4)
                        .to_ulong();
                cache[45][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_5)
                        .to_ulong();
                cache[45][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_6)
                        .to_ulong();
                cache[45][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_45_line_7)
                        .to_ulong();
                cache[46][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_0)
                        .to_ulong();
                cache[46][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_1)
                        .to_ulong();
                cache[46][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_2)
                        .to_ulong();
                cache[46][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_3)
                        .to_ulong();
                cache[46][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_4)
                        .to_ulong();
                cache[46][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_5)
                        .to_ulong();
                cache[46][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_6)
                        .to_ulong();
                cache[46][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_46_line_7)
                        .to_ulong();
                cache[47][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_0)
                        .to_ulong();
                cache[47][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_1)
                        .to_ulong();
                cache[47][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_2)
                        .to_ulong();
                cache[47][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_3)
                        .to_ulong();
                cache[47][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_4)
                        .to_ulong();
                cache[47][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_5)
                        .to_ulong();
                cache[47][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_6)
                        .to_ulong();
                cache[47][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_47_line_7)
                        .to_ulong();
                cache[48][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_0)
                        .to_ulong();
                cache[48][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_1)
                        .to_ulong();
                cache[48][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_2)
                        .to_ulong();
                cache[48][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_3)
                        .to_ulong();
                cache[48][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_4)
                        .to_ulong();
                cache[48][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_5)
                        .to_ulong();
                cache[48][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_6)
                        .to_ulong();
                cache[48][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_48_line_7)
                        .to_ulong();
                cache[49][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_0)
                        .to_ulong();
                cache[49][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_1)
                        .to_ulong();
                cache[49][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_2)
                        .to_ulong();
                cache[49][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_3)
                        .to_ulong();
                cache[49][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_4)
                        .to_ulong();
                cache[49][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_5)
                        .to_ulong();
                cache[49][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_6)
                        .to_ulong();
                cache[49][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_49_line_7)
                        .to_ulong();
                cache[50][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_0)
                        .to_ulong();
                cache[50][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_1)
                        .to_ulong();
                cache[50][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_2)
                        .to_ulong();
                cache[50][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_3)
                        .to_ulong();
                cache[50][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_4)
                        .to_ulong();
                cache[50][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_5)
                        .to_ulong();
                cache[50][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_6)
                        .to_ulong();
                cache[50][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_50_line_7)
                        .to_ulong();
                cache[51][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_0)
                        .to_ulong();
                cache[51][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_1)
                        .to_ulong();
                cache[51][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_2)
                        .to_ulong();
                cache[51][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_3)
                        .to_ulong();
                cache[51][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_4)
                        .to_ulong();
                cache[51][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_5)
                        .to_ulong();
                cache[51][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_6)
                        .to_ulong();
                cache[51][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_51_line_7)
                        .to_ulong();
                cache[52][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_0)
                        .to_ulong();
                cache[52][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_1)
                        .to_ulong();
                cache[52][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_2)
                        .to_ulong();
                cache[52][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_3)
                        .to_ulong();
                cache[52][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_4)
                        .to_ulong();
                cache[52][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_5)
                        .to_ulong();
                cache[52][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_6)
                        .to_ulong();
                cache[52][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_52_line_7)
                        .to_ulong();
                cache[53][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_0)
                        .to_ulong();
                cache[53][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_1)
                        .to_ulong();
                cache[53][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_2)
                        .to_ulong();
                cache[53][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_3)
                        .to_ulong();
                cache[53][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_4)
                        .to_ulong();
                cache[53][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_5)
                        .to_ulong();
                cache[53][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_6)
                        .to_ulong();
                cache[53][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_53_line_7)
                        .to_ulong();
                cache[54][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_0)
                        .to_ulong();
                cache[54][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_1)
                        .to_ulong();
                cache[54][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_2)
                        .to_ulong();
                cache[54][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_3)
                        .to_ulong();
                cache[54][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_4)
                        .to_ulong();
                cache[54][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_5)
                        .to_ulong();
                cache[54][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_6)
                        .to_ulong();
                cache[54][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_54_line_7)
                        .to_ulong();
                cache[55][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_0)
                        .to_ulong();
                cache[55][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_1)
                        .to_ulong();
                cache[55][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_2)
                        .to_ulong();
                cache[55][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_3)
                        .to_ulong();
                cache[55][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_4)
                        .to_ulong();
                cache[55][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_5)
                        .to_ulong();
                cache[55][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_6)
                        .to_ulong();
                cache[55][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_55_line_7)
                        .to_ulong();
                cache[56][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_0)
                        .to_ulong();
                cache[56][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_1)
                        .to_ulong();
                cache[56][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_2)
                        .to_ulong();
                cache[56][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_3)
                        .to_ulong();
                cache[56][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_4)
                        .to_ulong();
                cache[56][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_5)
                        .to_ulong();
                cache[56][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_6)
                        .to_ulong();
                cache[56][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_56_line_7)
                        .to_ulong();
                cache[57][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_0)
                        .to_ulong();
                cache[57][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_1)
                        .to_ulong();
                cache[57][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_2)
                        .to_ulong();
                cache[57][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_3)
                        .to_ulong();
                cache[57][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_4)
                        .to_ulong();
                cache[57][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_5)
                        .to_ulong();
                cache[57][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_6)
                        .to_ulong();
                cache[57][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_57_line_7)
                        .to_ulong();
                cache[58][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_0)
                        .to_ulong();
                cache[58][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_1)
                        .to_ulong();
                cache[58][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_2)
                        .to_ulong();
                cache[58][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_3)
                        .to_ulong();
                cache[58][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_4)
                        .to_ulong();
                cache[58][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_5)
                        .to_ulong();
                cache[58][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_6)
                        .to_ulong();
                cache[58][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_58_line_7)
                        .to_ulong();
                cache[59][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_0)
                        .to_ulong();
                cache[59][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_1)
                        .to_ulong();
                cache[59][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_2)
                        .to_ulong();
                cache[59][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_3)
                        .to_ulong();
                cache[59][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_4)
                        .to_ulong();
                cache[59][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_5)
                        .to_ulong();
                cache[59][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_6)
                        .to_ulong();
                cache[59][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_59_line_7)
                        .to_ulong();
                cache[60][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_0)
                        .to_ulong();
                cache[60][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_1)
                        .to_ulong();
                cache[60][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_2)
                        .to_ulong();
                cache[60][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_3)
                        .to_ulong();
                cache[60][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_4)
                        .to_ulong();
                cache[60][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_5)
                        .to_ulong();
                cache[60][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_6)
                        .to_ulong();
                cache[60][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_60_line_7)
                        .to_ulong();
                cache[61][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_0)
                        .to_ulong();
                cache[61][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_1)
                        .to_ulong();
                cache[61][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_2)
                        .to_ulong();
                cache[61][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_3)
                        .to_ulong();
                cache[61][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_4)
                        .to_ulong();
                cache[61][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_5)
                        .to_ulong();
                cache[61][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_6)
                        .to_ulong();
                cache[61][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_61_line_7)
                        .to_ulong();
                cache[62][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_0)
                        .to_ulong();
                cache[62][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_1)
                        .to_ulong();
                cache[62][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_2)
                        .to_ulong();
                cache[62][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_3)
                        .to_ulong();
                cache[62][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_4)
                        .to_ulong();
                cache[62][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_5)
                        .to_ulong();
                cache[62][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_6)
                        .to_ulong();
                cache[62][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_62_line_7)
                        .to_ulong();
                cache[63][0] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_0)
                        .to_ulong();
                cache[63][1] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_1)
                        .to_ulong();
                cache[63][2] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_2)
                        .to_ulong();
                cache[63][3] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_3)
                        .to_ulong();
                cache[63][4] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_4)
                        .to_ulong();
                cache[63][5] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_5)
                        .to_ulong();
                cache[63][6] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_6)
                        .to_ulong();
                cache[63][7] =
                    (int)std::bitset<32>(
                        tb->Processor__DOT__cacheCore__DOT__cache__DOT__cache_63_line_7)
                        .to_ulong();
            } else
                finished = true;
        }
        printf("\n----------------------------------------------------------\n");
        printf("\n\n");

        tb->clock = 1;
        tb->eval();

        if (instrAddrs == 16) {
            std::cout << "\n\n-----------------------CACHE "
                         "MEMORY-----------------------\n"
                      << std::endl;
            for (int j = 0; j < 64; j++) {
                for (int i = 0; i < 8; i++) {
                    printf("%d\t", cache[j][i]);
                }
                std::cout <<std::endl;
                
            }
            printf("----------------------------------------------------------\n");
            break;
        }
        instrAddrs = tb->io_instrAddrs;
        // usleep(20);
    }
    delete tb;
    exit(EXIT_SUCCESS);
}