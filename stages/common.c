
#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/

int ALU_control_input(int ALUOp, int funct)
{
    int ALUOp_0 = ALUOp & 0x1;
    int ALUOp_1 = (ALUOp >> 1) & 0x1;

    int funct_shifted = funct >> 4;

    if(ALUOp_0 == OFF && ALUOp_1 == OFF)
        return 0x2; // b'0010
    else if(ALUOp_0 == ON)
        return 0x6; // b'0110
    else if(ALUOp_1 == ON)
    {
        if(funct_shifted == 0x0)
            return 0x2; // b'0010
        if(funct_shifted == 0x2)
            return 0x6; // b'0110
        if(funct_shifted == 0x4)
            return 0x0; // b'0000
        if(funct_shifted == 0x5)
            return 0x1; // b'0001
        if(funct_shifted == 0x6)
            return 0x7; // b'0111
    }
}
