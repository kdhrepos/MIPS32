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

void init_simulator(MIPS32Simulator * sim)
{
    /* Memory Init */
    memset(sim->im, 0, sizeof(sim->im)/sizeof(int));

    /* Register Init */     
    memset(sim->reg_file, 0, sizeof(sim->reg_file)/sizeof(int));

    /* ID/EX control signal initialization */
    sim->id_ex_ctrl.ALUSrc=OFF, sim->id_ex_ctrl.ALUOp=OFF, sim->id_ex_ctrl.RegDst=OFF;
    sim->id_ex_ctrl.MemRead=OFF, sim->id_ex_ctrl.MemWrite=OFF, sim->id_ex_ctrl.Branch=OFF, 
    sim->id_ex_ctrl.Jump=OFF, sim->id_ex_ctrl.RegWrite=OFF, sim->id_ex_ctrl.MemtoReg=OFF;

    /* EX/MEM control signal initialization */
    sim->ex_mem_ctrl.MemRead,sim->ex_mem_ctrl.MemWrite=OFF, sim->ex_mem_ctrl.Branch=OFF, 
    sim->ex_mem_ctrl.Jump=OFF, sim->ex_mem_ctrl.RegWrite=OFF, sim->ex_mem_ctrl.MemtoReg=OFF;

    /* MEM/WB control signal initialization */
    sim->mem_wb_ctrl.RegWrite=OFF, sim->mem_wb_ctrl.MemtoReg=OFF;

    /* IF/ID pipeline register initialization */
    sim->if_id_reg.instruction=0, sim->if_id_reg.pc=0;

    /* ID/EX pipeline register initialization */
    sim->id_ex_reg.pc=0, sim->id_ex_reg.rs_val=0, sim->id_ex_reg.rt_val=0,
    sim->id_ex_reg.rt_num=0, sim->id_ex_reg.rd_num=0, sim->id_ex_reg.imm_val=0;
    
    /* EX/MEM pipeline register initialization */
    sim->ex_mem_reg.br_tgt=0, sim->ex_mem_reg.zero=0, sim->ex_mem_reg.ALU_result=0,
    sim->ex_mem_reg.rt_val=0, sim->ex_mem_reg.rd_num=0;

    /* MEM/WB  pipeline register initialization */
    sim->mem_wb_reg.ALU_result=0, sim->mem_wb_reg.load_data=0,
    sim->mem_wb_reg.rd_num=0;

    /* PC Init */
    sim->pc = 0; 
}

void run_simulator(MIPS32Simulator * sim, History history[MEM_SIZE],
 int program[], int program_size)
{
    int last_inst = program_size - 1; // stage_pointer

    /* execute instructions until the last instruction is fully executed*/
    while(!history[last_inst].end)
    {
        sim->clk++;
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
        0x200E0004,     // $t5 = 5
        0x00000000,     // no op
        0x200C0003,     // $t3 = 3
        0x01285020,   // $t2 = $t0 + $t1
    };

    init_simulator(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, history, program, sizeof(program) / sizeof(int));

    print_pipeline_register(&sim);
    print_reg_file(&sim);
    print_history(&sim, history, hist_itr);
}