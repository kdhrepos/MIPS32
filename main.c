#include <stdio.h>
#include "core.h"
#include "stages.h"
#include "print.c"

/*
 * Component Init
 **/
void init_simulator(MIPS32Simulator * sim)
{
    /* Memory Init */
    for (int i = 0; i < MEM_SIZE; i++) 
        sim->memory[i] = 0;

    /* Register Init */     
    for (int i = 0; i < REG_SIZE; i++) 
        sim->reg_file[i] = 0;

    /* ID/EX control signal initialization */
	sim->id_ex_ctrl.ALUSrc=OFF, sim->id_ex_ctrl.ALUOp=OFF, sim->id_ex_ctrl.RegDst=OFF;
    sim->id_ex_ctrl.MemRead=OFF, sim->id_ex_ctrl.MemWrite=OFF, sim->id_ex_ctrl.Branch=OFF, sim->id_ex_ctrl.Jump=OFF;
    sim->id_ex_ctrl.RegWrite=OFF, sim->id_ex_ctrl.MemtoReg=OFF;

    /* EX/MEM control signal initialization */
    sim->ex_mem_ctrl.MemRead,sim->ex_mem_ctrl.MemWrite=OFF, sim->ex_mem_ctrl.Branch=OFF, sim->ex_mem_ctrl.Jump=OFF;
    sim->ex_mem_ctrl.RegWrite=OFF, sim->ex_mem_ctrl.MemtoReg=OFF;

    /* MEM/WB control signal initialization */
    sim->mem_wb_ctrl.RegWrite=OFF, sim->mem_wb_ctrl.MemtoReg=OFF;

    /* ID/EX pipeline register initialization */

    sim->pc = 0;  /* PC Init */
}

void run_simulator(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i<7; i++)
    {
        // parallel execution
        write_back(sim);
        memory(sim);
        execute(sim);
        decode(sim);
        fetch(sim);
    }
}

/* Load Program */
void load_program(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i < program_size; i++)
    {
        sim->memory[i] = program[i];
        // printf("Instruction : %d\n", program[i]);
    }

    // sim->memory[program_size] = -1; // end of the program
}

int main()
{
    MIPS32Simulator sim;

    int program [] = {
        0x20080002,     // $t0 = 1
        0x20090001,     // $t1 = 1
        0x01285020,   // $t2 = $t0 + $t1
    };

    init_simulator(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, program, sizeof(program) / sizeof(int));

    /* print result & status */
    print_pipeline_register(&sim);
    print_reg_file(&sim);
}