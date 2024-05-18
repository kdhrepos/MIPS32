#include "core.h"
#include "./stages/stages.h"
#include "./util/print.h"
#include "./util/history.h"

/*
 *
 * @todo implement data forwarding unit
 * @todo implement hazard detection unit
 * @todo implement id stage branch result checking
 * @todo execution logic for pipeline datapath if instruction like j or branch is executed, we cannot write
 * the instruction history to MEM or WB Stage <- modify!!!!!!!!!!!!!!
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
void init_simulator(MIPS32Simulator * sim)
{
    /* Memory Init */
    memset(sim->memory, 0, sizeof(sim->memory)/sizeof(int));

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
    int pointer = 0; // stage_pointer
    int instruction = program_size - 1;

    /* execute instructions until the last instruction is fully executed*/
    while(!history[instruction].end)
    {
        /* parallel execution */
        sim->clock++;
        if(!history[instruction].WB)
            write_back(sim, history);
        if(!history[instruction].MEM)
            memory(sim, history);
        if(!history[instruction].EXE)
            execute(sim, history);
        if(!history[instruction].ID)
            decode(sim, history);
        if(!history[instruction].IF)
            fetch(sim, history);

    }
}

/* Load Program */
void load_program(MIPS32Simulator * sim, int program[], int program_size)
{
    for(int i = 0; i < program_size; i++)
        sim->memory[i] = program[i];
}

int main()
{
    MIPS32Simulator sim;
    History history[MEM_SIZE]; /* instruction history for print */
                               /* stores progress status for each of instructions */
    
    int program [] = {
        0x01285020,   // $t2 = $t0 + $t1
        0x20080002,     // $t0 = 2
        0x20090001,     // $t1 = 1
        // 0x200D0004,     // $t4 = 4
        // 0x200E0004,     // $t5 = 5
        0x00000000,     // no op
        0x200C0003,     // $t3 = 3
    };

    init_simulator(&sim);
    load_program(&sim, program, sizeof(program) / sizeof(int));

    run_simulator(&sim, history, program, sizeof(program) / sizeof(int));

    print_pipeline_register(&sim);
    print_reg_file(&sim);
    print_history(&sim, history);
}
