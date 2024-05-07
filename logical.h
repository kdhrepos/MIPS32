/* MIPS32 Logical Operations : Declaration */

#include "core.h"

void sll(MIPS32Simulator * sim, int rd, int rt, int shamt);

void srl(MIPS32Simulator * sim, int rd, int rt, int shamt);

void _and(MIPS32Simulator * sim, int rd, int rs, int rt);

void andi(MIPS32Simulator * sim, int rt, int rs, int imm);

void _or(MIPS32Simulator * sim, int rd, int rs, int rt);

void ori(MIPS32Simulator * sim, int rt, int rs, int imm);

void nor(MIPS32Simulator * sim, int rd, int rs, int rt);

void lui(MIPS32Simulator * sim, int rs, int rt, int imm);