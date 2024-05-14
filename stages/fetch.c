#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/

/*
 * fetch the program
 * call decode stage
 * update pipeline register
 * @param pc   
*/
void fetch(MIPS32Simulator * sim)
{
    int inst = 0;

    /* if branch is taken */
    if(sim->ex_mem_ctrl.Branch && sim->ex_mem_reg.zero)
        inst = sim->memory[sim->ex_mem_reg.br_tgt];
    /* if branch is not taken */
    else
        inst = sim->memory[sim->pc];

    /* no operation? */
    if(inst != 0x00000000)
        sim->if_id_reg.pc = sim->pc+1; // update pc 
        sim->pc += 1; // next pc
    
    /* update pipeline register */
    sim->if_id_reg.instruction = inst; 
}