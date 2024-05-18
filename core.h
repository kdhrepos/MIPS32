/* MIPS32 Core */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./register_set/control_register.h"
#include "./register_set/pipeline_register.h"

/* SIZE */
#define MEM_SIZE 1024
#define REG_SIZE 32

/* BOOLEAN */
// we have to make util.h file
#define TRUE 1
#define FALSE 0
typedef int boolean;


/* mips 32 simulator datapath */
typedef struct {
	int memory[MEM_SIZE];
	int reg_file[REG_SIZE];
	int pc;
	int clock;
	
	/* pipeline registers */
	IF_ID_REG if_id_reg;
	ID_EX_REG id_ex_reg;
	EX_MEM_REG ex_mem_reg;
	MEM_WB_REG mem_wb_reg;

	/* control signals */
	ID_EX_CTRL id_ex_ctrl; /* control signals on id/ex pipeline register */
	EX_MEM_CTRL ex_mem_ctrl; /* control signals on ex/mem pipeline register */
	MEM_WB_CTRL mem_wb_ctrl; /* control signals on mem/wb pipeline register */

	/* pc for each of the instructions to record history  */
	int ID_pc;
	int EXE_pc;
	int MEM_pc;
	int WB_pc;
} MIPS32Simulator;
