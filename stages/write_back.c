#include "stages.h"

/*
 * Write Back
 * write back stage for MIPS32 pipeline
 * @param sim pointer of simulator
 * @param instruction_pc pc value of current instruction to record instruction history
*/
void write_back(MIPS32Simulator * sim, History history[MEM_SIZE])
{
    /* no operation? */
    if(sim->mem_wb_ctrl.MemtoReg==OFF && sim->mem_wb_ctrl.RegWrite==OFF)
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

    /* recording the instruction history */
    history[sim->WB_hist_itr].end = TRUE;
    history[sim->WB_hist_itr].WB = TRUE;
    history[sim->WB_hist_itr].WB_clock = sim->clock;
}