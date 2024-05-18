#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/

/*
 * access memory
*/
void memory(MIPS32Simulator * sim, History history[MEM_SIZE])
{
    /* no operation? */
    if(sim->ex_mem_ctrl.Branch==OFF && sim->ex_mem_ctrl.Jump==OFF && sim->ex_mem_ctrl.MemRead==OFF 
    && sim->ex_mem_ctrl.MemtoReg==OFF && sim->ex_mem_ctrl.MemWrite==OFF && sim->ex_mem_ctrl.RegWrite==OFF)
        return;

    /* read ex/mem pipeline register */
    int br_trgt = sim->ex_mem_reg.br_tgt;
    int zero = sim->ex_mem_reg.zero;
    int ALU_result = sim->ex_mem_reg.ALU_result;
    int rt_val = sim->ex_mem_reg.rt_val;
    int rd_num = sim->ex_mem_reg.rd_num;
    
    /* read control signals */
    int RegWrite = sim->ex_mem_ctrl.RegWrite;
    int MemtoReg = sim->ex_mem_ctrl.MemtoReg;

    int address = sim->mem_wb_reg.ALU_result;

    /* Load */
    if(sim->ex_mem_ctrl.MemRead == ON)
        sim->mem_wb_reg.load_data = sim->memory[address];
        
    /* Store */
    else if(sim->ex_mem_ctrl.MemWrite == ON)
    {
        sim->mem_wb_reg.load_data = EMPTY;
        sim->memory[address] = rt_val;
    }

    /* update pipeline register */
    sim->mem_wb_reg.ALU_result = ALU_result;
    sim->mem_wb_reg.rd_num = rd_num;
    
    /* update control signals */
    sim->mem_wb_ctrl.RegWrite = RegWrite;
    sim->mem_wb_ctrl.MemtoReg = MemtoReg;

    /* recording the instruction history */
    history[sim->MEM_pc].MEM = TRUE;
    history[sim->MEM_pc].MEM_clock = sim->clock;
    sim->WB_pc = sim->MEM_pc;
}