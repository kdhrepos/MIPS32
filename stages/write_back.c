#include "stages.h"

/*
 * Write Back
 * write back stage for MIPS32 pipeline
 * @param sim pointer of simulator
 * @param instruction_pc pc value of current instruction to record instruction history
*/
void write_back(MIPS32Simulator * sim, Log log[MEM_SIZE])
{
    // previous stage is off, so off the wb stage
    if(sim->mem_on == OFF)
    {
        sim->wb_on = OFF; /* program finally exited */
        return;
    }

    // no operation?
    // if(sim->mem_wb_ctrl.MemtoReg == OFF 
    // && sim->mem_wb_ctrl.RegWrite == OFF)
    //     return;

    // read mem/wb pipeline register
    int loaded_data = sim->mem_wb_reg.load_data;
    int ALU_result = sim->mem_wb_reg.ALU_result;
    int rd_num = sim->mem_wb_reg.rd_num;

    // read mem/wb control signals
    int RegWrite = sim->mem_wb_ctrl.RegWrite;
    int MemtoReg = sim->mem_wb_ctrl.MemtoReg;

    if(RegWrite == ON)
    {
        // Load
        if(MemtoReg == ON)
            sim->reg_file[rd_num] = loaded_data;
        // RTYPEOP
        else
            sim->reg_file[rd_num] = ALU_result;
    }

    if(sim->WB_log_itr < 0) return;

    // recording the instruction history
    log[sim->WB_log_itr].end = TRUE;
    log[sim->WB_log_itr].WB = TRUE;
    log[sim->WB_log_itr].WB_clk = sim->clk;
}