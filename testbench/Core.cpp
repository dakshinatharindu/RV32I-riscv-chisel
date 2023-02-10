#include <stdlib.h>
#include <fstream>
#include <vector>
#include "VCore.h"
#include "verilated.h"

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);

    VCore *tb = new VCore;
    const char *filename = "verilatorInstr.txt";
    unsigned int instr;
    std::ifstream infile(filename, std::fstream::in);
    std::vector<unsigned int> instructions;

    while (infile >> std::hex >> instr)
    {
        instructions.push_back(instr);
    }

    unsigned int instrAddrs = 0;
    tb->io_valid = 1;
    while (!Verilated::gotFinish())
    {

        // infile >> std::hex >> a;

        
        tb->io_instr = instructions[instrAddrs];
        tb->clock = 0;
        tb->eval();
        tb->clock = 1;
        tb->eval();
        instrAddrs = tb->io_instrAddrs;
        printf("ALUOUT :%d\n", tb->io_ALUOut);
        printf("Next Instr. Addrs. :%d\n", tb->io_instrAddrs);
        printf("MemRead :%d\n", tb->io_memRead);
        printf("MemWrite :%d\n", tb->io_memWrite);
        printf("MemWriteData :%d\n", tb->io_memWriteData);
        printf("\n");
        usleep(200000);
        if (instrAddrs == 0) break;
    }
    delete tb;
    exit(EXIT_SUCCESS);
}