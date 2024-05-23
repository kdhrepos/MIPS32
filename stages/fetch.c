#include "stages.h"

/*
 * fetch the program
 * call decode stage
 * update pipeline register
 * @param pc   
*/
void fetch(MIPS32Simulator * sim, History history[MEM_SIZE], int hist_itr)
{
    int pc;

    /* if branch is taken */
    if(sim->ex_mem_ctrl.Branch && sim->ex_mem_reg.zero)
        pc = sim->ex_mem_reg.br_tgt;
    /* if branch is not taken or instruction is not branch */
    else
        pc = sim->pc;

    /* update pipeline register */
    sim->if_id_reg.instruction = sim->im[pc]; 
    sim->if_id_reg.pc = sim->pc++; /* pc + 4*/
                                   /* update pipeline register */

    /* no op? */
    if(sim->if_id_reg.instruction == 0x00000000)
        return;

    /* recording the instruction history */
    history[hist_itr].address = pc; 
    history[hist_itr].IF = TRUE;
    history[hist_itr].IF_clk = sim->clk;
    sim->ID_hist_itr = hist_itr;
}