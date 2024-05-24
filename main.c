#include "./core.h"
#include "./stages/stages.h"
#include "./util/print.h"
#include "./util/history.h"
#include "./hazard/hazard.h"
/*
 *
 * @todo implement data forwarding unit
 * @todo implement hazard detection unit
 * @todo implement id stage branch result checking
 * @todo execution logic for pipeline datapath if instruction like j or branch is executed, we cannot write
 * 
*/

/*
 * Component Init
 *
 * set all components to 0
 * compnents are memory, general purpose register, control signal, pipeline register
 * 
 * @author kdhrepos
 **/
int hist_itr = 0; // instruction iterator for execution history

void run_simulator(MIPS32Simulator * sim, History history[MEM_SIZE],
 int program[], int program_size)
{
    boolean smooth = FALSE; /* no input if it's TRUE */
    int last_inst = program_size - 1; // stage_pointer

    /* execute instructions until the last instruction is fully executed*/
    while(!history[last_inst].end)
    {
        sim->clk++;
        forwarding(sim); /* data hazard control */
        /* parallel execution */
        if(!history[last_inst].WB)
            write_back(sim, history);
        if(!history[last_inst].MEM)
            memory(sim, history);
        if(!history[last_inst].EXE)
            execute(sim, history);
        if(!history[last_inst].ID)
            decode(sim, history);
        if(!history[last_inst].IF)
            fetch(sim, history, hist_itr);
        hist_itr++;
        
        print_pipeline_register(sim);
        print_reg_file(sim);   
        print_history(sim, history, hist_itr);
        print_guideline();
        char c = getchar(); 
    }
}

/* Load Program */
void load_program(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i < program_size; i++)
        sim->im[i] = program[i];
}

int main()
{
    MIPS32Simulator sim;
    History history[MEM_SIZE]; /* instruction history for print */
                               /* stores progress status for each of instructions */
    
    int program [] = {
        0x20080002,     // $t0 = 2
        0x20090001,     // $t1 = 1
        0x200D0004,     // $t4 = 4
        0x01285020,   // $t2 = $t0 + $t1
        // 0x200E0004,     // $t5 = 5
        // 0x00000000,     // no op
        // 0x200C0003,     // $t3 = 3
    };

    init(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, history, program, sizeof(program) / sizeof(int));

    // print_pipeline_register(&sim);
    // print_reg_file(&sim);
    // print_history(&sim, history, hist_itr);
}