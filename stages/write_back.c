#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/

void write_back(MIPS32Simulator * sim)
{
    /* no operation? */
    if(sim->ex_mem_ctrl.MemtoReg==OFF && sim->ex_mem_ctrl.RegWrite==OFF)
        return;

    /* read mem/wb pipeline register */
    int loaded_data = sim->mem_wb_reg.load_data;
    int ALU_result = sim->mem_wb_reg.ALU_result;
    int rd_num = sim->mem_wb_reg.rd_num;

    /* read mem/wb control signals */
    int RegWrite = sim->mem_wb_ctrl.RegWrite;
    int MemtoReg = sim->mem_wb_ctrl.MemtoReg;

    if(RegWrite == ON)
    {
        /* Load */
        if(MemtoReg == ON)
            sim->reg_file[rd_num] = loaded_data;
        /* R-Type */
        else 
            sim->reg_file[rd_num] = ALU_result;
    }
}