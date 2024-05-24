#pragma once

#include "../core.h"
#include "../instruction_set.h"
#include "../hazard/hazard.h"
#include "../util/history.h"

void fetch(MIPS32Simulator * sim, History history[MEM_SIZE], int hist_itr);

void decode(MIPS32Simulator * sim, History history[MEM_SIZE]);
int get_ALUOp(int opcode);

void execute(MIPS32Simulator * sim, History history[MEM_SIZE]);
int get_ALU_ctrl(int ALUOp, int funct);

void memory(MIPS32Simulator * sim, History history[MEM_SIZE]);

void write_back(MIPS32Simulator * sim, History history[MEM_SIZE]);