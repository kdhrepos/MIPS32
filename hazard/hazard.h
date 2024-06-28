#pragma once

#include "../core.h"
#include "../util/print.h"

void forwarding(MIPS32Simulator * sim, Log log[MEM_SIZE]);
void hazard_detection(MIPS32Simulator * sim, Log log[MEM_SIZE]);