#pragma once

#include <stdio.h>
#include "core.h"

/*
 * Component Init
 **/
void init_simulator(MIPS32Simulator * sim)
{
    /* Memory Init */
    for (int i = 0; i < MEM_SIZE; i++) 
        sim->memory[i] = 0;

    /* GP Register Init */     
    for (int i = 0; i < GP_REG_SIZE; i++) 
        sim->gp_registers[i] = 0;

    sim->pc = 0;  /* PC Init */
}

void run_simulator(MIPS32Simulator * sim)
{
    while(TRUE)
    {
        int inst = sim -> memory[sim -> pc / 4]; /* Current Instruction */
        sim -> pc += 4; /* Next Instruction */

        int opcode = (inst >> 26) & 0x3F;
        int rs = (inst >> 21) & 0x1F;
        int rt = (inst >> 16) & 0x1F;
        int rd = (inst >> 11) & 0x1F;
        int imm = inst & 0xFFFF;
    }
}

int main()
{
    MIPS32Simulator sim;

    init_simulator(&sim);
}