#pragma once

#include "core.h"
#include "instruction_set.h"

void fetch(MIPS32Simulator * sim);

void decode(MIPS32Simulator * sim);

void execution();

void memory();

void write_back();