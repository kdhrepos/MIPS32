/* MIPS32 Core */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./register_set/control_signal.h"
#include "./register_set/pipeline_register.h"

/* SIZE */
#define MEM_SIZE 1024
#define REG_SIZE 32

/* BOOLEAN */
// FIXME : split it into another file
#define TRUE 1
#define FALSE 0
typedef int boolean;

/* mips 32 simulator datapath */
typedef struct {
	int im[MEM_SIZE]; // instruction memory
	int dm[MEM_SIZE]; // data memory
	int reg_file[REG_SIZE]; // register file
	int pc; // program counter
	int clk;
	
	/* pipeline registers */
	IfIdReg if_id_reg;
	IdExeReg id_ex_reg;
	ExeMemReg ex_mem_reg;
	MemWbReg mem_wb_reg;

	/* control signals */
	IdExCtrl id_ex_ctrl; /* control signals on id/ex pipeline register */
	ExeMemCtrl ex_mem_ctrl; /* control signals on ex/mem pipeline register */
	MemWbCtrl mem_wb_ctrl; /* control signals on mem/wb pipeline register */

	/* forwarding signals */
	FwdCtrl fwd_ctrl; 

	/* hazard detection signals */
	HzrdCtrl hzrd_ctrl;

	/* iterator for recording execution history  */
	int ID_hist_itr;
	int EXE_hist_itr;
	int MEM_hist_itr;
	int WB_hist_itr;
} MIPS32Simulator;

void init(MIPS32Simulator * sim);