#include "./core.h"
#include "./stages/stages.h"
#include "./util/print.h"
#include "./util/log.h"
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
int log_itr = 0; // instruction iterator for execution history

void run_simulator(MIPS32Simulator * sim, Log log[MEM_SIZE],
 int program[], int program_size)
{
    boolean smooth = FALSE; /* no input if it's TRUE */
    int last_inst = program_size - 1; // stage_pointer

    /* execute instructions until the last instruction is fully executed*/
    while(!log[last_inst].end)
    {
        sim->clk++;
        forwarding(sim); /* data hazard control */
        /* parallel execution */
        if(!log[last_inst].WB)
            write_back(sim, log);
        if(!log[last_inst].MEM)
            memory(sim, log);
        if(!log[last_inst].EXE)
            execute(sim, log);
        if(!log[last_inst].ID)
            decode(sim, log);
        if(!log[last_inst].IF) 
            fetch(sim, log, log_itr);
        log_itr++;
        
        print_pipeline_register(sim);
        print_reg_file(sim);   
        print_log(sim, log, log_itr);
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
}

int main()
{
    MIPS32Simulator sim;
    Log log[MEM_SIZE]; /* instruction history for print */
                               /* stores progress status for each of instructions */
    
    int program [] = {
        // 0x20080002,     // $t0 = 2
        0x20090001,     // $t1 = 1
        // 0x01285020,     // $t2 = $t0 + $t1
        // 0xac0a0000,     // sw $t2, 0($zero)
        // 0x8e6a0000,     // lw $t2, 0($t3)
        // 0x200D0004,     // $t4 = 4
        // 0x200E0004,     // $t5 = 5
        // 0x00000000,     // no op
        // 0x200C0003,     // $t3 = 3
        0x8C280000,  // lw $t0, 0($t1)
        // 0x010B4020,  // add $t2, $t0, $t3
    };

    init(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, log, program, sizeof(program) / sizeof(int));

    print_data_memory(&sim);
    // print_pipeline_register(&sim);
    // print_reg_file(&sim);
    // print_history(&sim, history, hist_itr);
}