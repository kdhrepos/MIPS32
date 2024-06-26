#include "./core.h"
#include "./stages/stages.h"
#include "./util/print.h"
#include "./util/log.h"
#include "./hazard/hazard.h"

void run_simulator(
    MIPS32Simulator * sim, Log log[MEM_SIZE],
    int program[], int program_size)
{
    // boolean smooth = FALSE; /* no input if it's TRUE */

    // execute instructions until all instruction is executed
    while(sim->mem_on)
    {   
        sim->clk++;
        // parallel execution
        forwarding(sim); /* data hazard control */
        
        if(sim->wb_on)   write_back(sim, log);
        if(sim->mem_on)  memory(sim, log);
        if(sim->ex_on)   execute(sim, log);
        if(sim->id_on)   decode(sim, log);
        if(sim->if_on)   fetch(sim, log);

        hazard_detection(sim, 
        (sim->if_id_reg.instruction >> 21) & 0x1F,  /* rs */
        (sim->if_id_reg.instruction >> 16) & 0x1F); /* rt */

        // print_pipeline_register(sim);
        // print_reg_file(sim);
        print_log(sim, log);
        // print_data_memory(sim);
        print_guideline();
        char c = getchar(); 
        if(c == 'q')
            return;
    }
}

/* Load Program */
void load_program(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i < program_size; i++)
        sim->im[i] = program[i];
    sim->im[program_size] = EOP; /* End of Program, denotes no more instruction */
}

int main()
{
    MIPS32Simulator sim;
    Log log[MEM_SIZE];  /* instruction history for print */
                        /* stores progress status for each of instructions */
    int program [] = {
        // 0x20080002,     // $t0 = 2
        0x200A000A,     // $t2 = 10
        0x200D0004,     // $t4 = 4
        0x200E0004,     // $t5 = 5
        // 0xAC0A0000,     // sw $t2, 0($zero)
        // 0x8e6a0000,     // lw $t2, 0($t3)
        // 0x8C080000,     // lw $t0, 0($zero)
        // 0x01084020,     // add $t0, $t0, $t0
        // 0x01085820,     // add $t3, $t0, $t0
        // // 0x00000000,     // no op
        // // 0x200C0003,     // $t3 = wj3
        // 0x8D280000,  // lw $t0, 0($t1)
        // 0x20090001,     // $t1 = 1
        // 0x01285020,     // $t2 = $t0 + $t1
        // // 0x010B4020,  // add $t2, $t0, $t3
    };

    init(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, log, program, sizeof(program) / sizeof(int));

    // print_data_memory(&sim);
    // print_pipeline_register(&sim);
    // print_reg_file(&sim);
    // print_log(&sim, log);
    // print_history(&sim, history, hist_itr);
}