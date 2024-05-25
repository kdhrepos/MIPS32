#pragma once

/* Signals */
#define ON 1
#define OFF 0

typedef struct {
    // EX
	int ALUSrc, ALUOp, RegDst;
    // MEM
    int MemRead, MemWrite, Branch, Jump;
    // WB
    int RegWrite, MemtoReg;
}IdExCtrl;

typedef struct {
    // MEM
    int MemRead, MemWrite, Branch, Jump;
    // WB
    int RegWrite, MemtoReg;
}ExeMemCtrl;

typedef struct{
    // WB
    int RegWrite, MemtoReg;
}MemWbCtrl;

typedef struct{
    int FwdA;
    int FwdB;
}FwdCtrl; // Forwarding Control Signals

typedef struct{
    int pc_write; /* no write if data hazard occurred */
    int if_id_write; /* no write if data hazard occurred */
    int if_flush; /* flush if control hazard occurred */
}HzrdCtrl;