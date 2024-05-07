#pragma once

#include "core.h"

/*
 * if(R[rs]==R[rt])
 *  PC=PC+4+BranchAddr
*/
bool beq(MIPS32Simulator * sim, int rs, int rt);

/*
 * if(R[rs]!=R[rt])
 *  PC=PC+4+BranchAddr
*/
bool bne(MIPS32Simulator * sim, int rs, int rt);

void j(MIPS32Simulator * sim, int jump_addr);

void jal(MIPS32Simulator * sim);

void jr(MIPS32Simulator * sim);

void slt(MIPS32Simulator * sim, int rt, int rs, int rd);

void slti(MIPS32Simulator * sim, int rt, int rs, int imm);

void sltu(MIPS32Simulator * sim, int rs, int rt, int imm);

void sltiu(MIPS32Simulator * sim, int rt, int rs, int imm);