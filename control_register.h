#pragma once

/* Signals */
#define ON 1
#define OFF 0
#define DONT_CARE -1

typedef struct {
    // EX
	int ALUSrc, ALUOp, RegDst;
    // MEM
    int MemRead, MemWrite, Branch, Jump;
    // WB
    int RegWrite, MemtoReg;
}ID_EX_CTRL;

typedef struct {
    // MEM
    int MemRead, MemWrite, Branch, Jump;
    // WB
    int RegWrite, MemtoReg;
}EX_MEM_CTRL;

typedef struct{
    // WB
    int RegWrite, MemtoReg;
}MEM_WB_CTRL;