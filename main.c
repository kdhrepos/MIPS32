#pragma once

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

    sim->pc = 0;  /* PC Init */
}

void run_simulator(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i<program_size; i++)
    {
        fetch(sim);
        decode(sim);
    }
}

/* Load Program */
void load_program(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i < program_size; i++)
        sim->memory[i] = program[i];

    sim->memory[program_size] = -1; // end of the program
}

int main()
{
    MIPS32Simulator sim;

    int program [] = {
        0x20080002,     // $t0 = 1
        // 0x20090001,     // $t1 = 1
        // 0x01285020,   // $t2 = $t0 + $t1
    };

    init_simulator(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, program, sizeof(program) / sizeof(int));

    print_pipeline_register(&sim);
    print_reg_file(&sim);
}