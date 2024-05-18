#include "stages.h"

/*
 * fetch the program
 * call decode stage
 * update pipeline register
 * @param pc   
*/
void fetch(MIPS32Simulator * sim, History history[MEM_SIZE])
{
    int pc;

    /* if branch is taken */
    if(sim->ex_mem_ctrl.Branch && sim->ex_mem_reg.zero)
        pc = sim->ex_mem_reg.br_tgt;
    /* if branch is not taken or inst. is not branch */
    else
        pc = sim->pc;

    /* update pipeline register */
    sim->if_id_reg.instruction = sim->memory[pc]; 
    sim->if_id_reg.pc = sim->pc++; /* pc + 4*/
                                   /* update pipeline register */

    /* recording the instruction history */
    history[pc].IF = TRUE;
    history[pc].IF_clock = sim->clock;
    sim->ID_pc = pc;
}