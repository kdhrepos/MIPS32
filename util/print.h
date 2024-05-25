#pragma once

#include "../core.h"
#include "log.h"

void print_guideline();

void print_pipeline_register(MIPS32Simulator * sim);

void print_reg_file(MIPS32Simulator * sim);

void print_log(MIPS32Simulator * sim, Log log[MEM_SIZE], int hist_itr);

void print_data_memory(MIPS32Simulator * sim);