/* MIPS32 Memory Operations : Declaration */

/* 
 * I-Type Instructions
 * Instruction Format : opcode(6) | rs(5) | rt(5) | immediate(16) 
 * @author kdhrepos
 * */

#pragma once

#include "core.h"


void lw(MIPS32Simulator * sim, int rt, int rs, int imm);

void lh(MIPS32Simulator * sim, int rs, int rt, int imm);

void lhu(MIPS32Simulator * sim, int rs, int rt, int imm);

void lb(MIPS32Simulator * sim, int rs, int rt, int imm);

void lbu(MIPS32Simulator * sim, int rs, int rt, int imm);

void sw(MIPS32Simulator * sim, int rt, int rs, int imm);

void sh(MIPS32Simulator * sim, int rs, int rt, int imm);

void sb(MIPS32Simulator * sim, int rs, int rt, int imm);