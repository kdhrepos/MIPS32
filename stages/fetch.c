#include "stages.h"

/*
 * fetch the program
 * call decode stage
 * update pipeline register
 * @param pc   
*/
void fetch(MIPS32Simulator * sim, Log log[MEM_SIZE], int log_itr)
{
    int pc;

    if(sim->ex_mem_ctrl.Branch && sim->ex_mem_reg.zero) /* if branch is taken */
        pc = sim->ex_mem_reg.br_tgt;
    else /* if branch is not taken or instruction is not branch */
        pc = sim->pc;
    
    // update pc if pc_write is ON
    if(sim->hzrd_ctrl.pc_write == ON)
        sim->pc = pc;

    // update pipeline register if IF/ID Write is ON
    if(sim->hzrd_ctrl.if_id_write == ON)
    {
        sim->if_id_reg.instruction = sim->im[pc]; 
        sim->if_id_reg.pc = sim->pc++; /* pc + 4*/
                                       /* update pipeline register */
    }
        
    /* no op? */
    if(sim->if_id_reg.instruction == 0x00000000)
        return;

    /* recording the instruction history */
    log[log_itr].address = pc; 
    log[log_itr].IF = TRUE;
    log[log_itr].IF_clk = sim->clk;
    sim->ID_log_itr = log_itr;
}