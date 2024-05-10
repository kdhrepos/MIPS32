/* MIPS32 Core */

#pragma once

#include "control_register.h"
#include "pipeline_register.h"

/* SIZE */
#define MEM_SIZE 1024
#define REG_SIZE 32

/* BOOLEAN */
// we have to make util.h file
#define TRUE 1
#define FALSE 0
typedef int bool;


/* Core Simulator */
typedef struct {
	int memory[MEM_SIZE];
	int reg_file[REG_SIZE];
	int pc;
	
	// pipeline registers
	IF_ID_REG if_id_reg;
	ID_EX_REG id_ex_reg;
	EX_MEM_REG ex_mem_reg;
	MEM_WB_REG mem_wb_reg;

	// control signals
	ID_EX_CTRL id_ex_ctrl; /* control signals on id/ex pipeline register */
	EX_MEM_CTRL ex_mem_ctrl; /* control signals on ex/mem pipeline register */
	MEM_WB_CTRL mem_wb_ctrl; /* control signals on mem/wb pipeline register */
} MIPS32Simulator;
