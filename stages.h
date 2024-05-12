#pragma once

#include "core.h"
#include "instruction_set.h"

void fetch(MIPS32Simulator * sim);

void decode(MIPS32Simulator * sim);

void execute();

void memory();

void write_back();

int ALU_control_input(int ALUOp, int funct);

bool is_noop(MIPS32Simulator * sim);