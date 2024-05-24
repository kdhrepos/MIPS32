#include "core.h"

void init(MIPS32Simulator * sim)
{
    /* Memory initialization */
    memset(sim->im, 0, sizeof(sim->im)/sizeof(int));

    /* Register file initialization */     
    memset(sim->reg_file, 0, sizeof(sim->reg_file)/sizeof(int));

    /* ID/EX control signal initialization */
    sim->id_ex_ctrl.ALUSrc=OFF; sim->id_ex_ctrl.ALUOp=OFF; sim->id_ex_ctrl.RegDst=OFF;
    sim->id_ex_ctrl.MemRead=OFF; sim->id_ex_ctrl.MemWrite=OFF; sim->id_ex_ctrl.Branch=OFF; 
    sim->id_ex_ctrl.Jump=OFF; sim->id_ex_ctrl.RegWrite=OFF; sim->id_ex_ctrl.MemtoReg=OFF;

    /* EX/MEM control signal initialization */
    sim->ex_mem_ctrl.MemRead;sim->ex_mem_ctrl.MemWrite=OFF; sim->ex_mem_ctrl.Branch=OFF; 
    sim->ex_mem_ctrl.Jump=OFF; sim->ex_mem_ctrl.RegWrite=OFF; sim->ex_mem_ctrl.MemtoReg=OFF;

    /* MEM/WB control signal initialization */
    sim->mem_wb_ctrl.RegWrite=OFF; sim->mem_wb_ctrl.MemtoReg=OFF;

    /* IF/ID pipeline register initialization */
    sim->if_id_reg.instruction=0; sim->if_id_reg.pc=0;

    /* ID/EX pipeline register initialization */
    sim->id_ex_reg.pc=0; sim->id_ex_reg.rs_val=0; sim->id_ex_reg.rt_val=0;
    sim->id_ex_reg.rt_num=0; sim->id_ex_reg.rd_num=0; sim->id_ex_reg.imm_val=0;
    
    /* EX/MEM pipeline register initialization */
    sim->ex_mem_reg.br_tgt=0; sim->ex_mem_reg.zero=0; sim->ex_mem_reg.ALU_result=0;
    sim->ex_mem_reg.rt_val=0; sim->ex_mem_reg.rd_num=0;

    /* MEM/WB  pipeline register initialization */
    sim->mem_wb_reg.ALU_result=0; sim->mem_wb_reg.load_data=0;
    sim->mem_wb_reg.rd_num=0;

    /* Forwarding control signal initialization */
    sim->fwd_ctrl.FwdA = 0x00; sim->fwd_ctrl.FwdB = 0x00;

    /* Hazard control signal initialization */
    sim->hzrd_ctrl.if_flush = ON; sim->hzrd_ctrl.if_id_write = ON;
    sim->hzrd_ctrl.pc_write = ON;

    /* PC Init */
    sim->pc = 0; 
}
