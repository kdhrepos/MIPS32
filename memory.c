/* MIPS32 Memory Operations */

#pragma once

#include "core.h"

/* Load Word */
void lw(MIPS32Simulator * sim, int rt, int rs, int imm)
{
	int address = sim -> gp_registers[rs] + imm;
	sim -> gp_registers[rt] = sim -> memory[address / 4];
}

/* Store Word */
void sw(MIPS32Simulator * sim, int rt, int rs, int imm)
{
	int address = sim -> gp_registers[rs] + imm;
	sim -> memory[address / 4] = sim -> gp_registers[rt];
}
