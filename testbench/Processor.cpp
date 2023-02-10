#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <bitset>
#include <vector>
#include "VProcessor.h"
#include "verilated.h"

int main(int argc, char **argv)
{
    Verilated::commandArgs(argc, argv);

    VProcessor *tb = new VProcessor;
    const char *filename = "verilatorInstr.txt";
    unsigned int instr;
    std::string line;
    std::ifstream infile(filename, std::fstream::in);
    std::vector<unsigned int> instructions;

    while (infile >> std::hex >> instr)
    {
        instructions.push_back(instr);
    }

    unsigned int instrAddrs = 0;
    tb->reset = 0;
    tb->eval();
    tb->reset = 1;
    tb->eval();
    tb->reset = 0;
    tb->eval();
    while (!Verilated::gotFinish())
    {

        // infile >> std::hex >> a;

        std::cout << std::hex << instructions[instrAddrs] << std::endl;
        tb->io_instr = instructions[instrAddrs];
        tb->clock = 0;
        tb->eval();
        printf("memAdrrs :%d\n", tb->io_memAdrrs);
        printf("Next Instr. Addrs. :%d\n", tb->io_instrAddrs);
        printf("MemRead :%d\n", tb->io_memRead);
        printf("MemWrite :%d\n", tb->io_memWrite);
        printf("memWriteBlock :%d\n", tb->io_memWriteBlock);
        line = std::bitset<256>(tb->Processor__DOT__cacheCore__DOT__cache__DOT___dataBuffer_T).to_string();
        std::cout << line << std::endl;
        printf("\n");

        tb->clock = 1;
        tb->eval();

        if (instrAddrs == 16) break;
        instrAddrs = tb->io_instrAddrs;
        
        usleep(20);

        

        
    }
    delete tb;
    exit(EXIT_SUCCESS);
}