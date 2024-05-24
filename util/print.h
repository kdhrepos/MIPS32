#pragma once

#include "../core.h"
#include "history.h"

void print_guideline();

void print_pipeline_register(MIPS32Simulator * sim);

void print_reg_file(MIPS32Simulator * sim);

void print_history(MIPS32Simulator * sim, History history[MEM_SIZE], int hist_itr);