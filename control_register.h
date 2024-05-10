#pragma once

/* Signals */
#define ON 1
#define OFF 0
#define DONT_CARE -1

typedef struct {

	int ALUSrc, ALUOp, RegDst;
    
    int MemRead, MemWrite, Branch, Jump;

    int RegWrite, MemtoReg;
}ID_EX_CTRL;

typedef struct {
    
    int MemRead, MemWrite, Branch, Jump;

    int RegWrite, MemtoReg;
}EX_MEM_CTRL;

typedef struct{
    
    int RegWrite, MemtoReg;
}MEM_WB_CTRL;