/* MIPS32 Core */

#pragma once

/* SIZE */
#define MEM_SIZE 1024
#define GP_REG_SIZE 32

/* BOOLEAN */
#define TRUE 1
#define FALSE 0
typedef int bool;

/* Core Simulator */
typedef struct {
	int memory[MEM_SIZE];
	int gp_registers[GP_REG_SIZE];
	int pc;
} MIPS32Simulator;