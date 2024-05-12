#pragma once

#include "../core.h"
#include "../instruction_set.h"

void fetch(MIPS32Simulator * sim);

void decode(MIPS32Simulator * sim);

void execute(MIPS32Simulator * sim);

void memory(MIPS32Simulator * sim);

void write_back(MIPS32Simulator * sim);

int ALU_control_input(int ALUOp, int funct);

bool is_noop(MIPS32Simulator * sim);