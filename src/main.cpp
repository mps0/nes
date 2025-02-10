#include "cpu.h"
#include "memory.h"
#include "byte.h"
#include <cstdio>

int main()
{
    Memory mem;
    CPU cpu(mem);

    std::vector<b1> prog = {0xa9, 0xc0, 0xaa, 0xe8, 0x00};

    mem.load(prog);
    mem.printProgramMemory(5);
    getchar();
    cpu.run();

    return 0;
}
