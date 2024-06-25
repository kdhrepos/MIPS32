#include "./hazard.h"

void hazard_detection(MIPS32Simulator * sim, int rs, int rt)
{
    // load-use data hazard
    if(sim->id_ex_ctrl.MemRead &&       /* if (ID/EX.MemRead and */
    (sim->id_ex_reg.rt_num == rs        /* ((ID/EX.RegisterRt = IF/ID.RegisterRs) */
    || sim->id_ex_reg.rt_num == rt))    /* or (ID/EX.RegisterRt = IF/ID.RegisterRt))) */
    {
        // load-use data hazard occurred, stall the pipeline
        // printf("Hazard Occurred\n");
        sim->hzrd_ctrl.pc_write = OFF;
        sim->hzrd_ctrl.if_id_write = OFF;
        sim->if_id_reg.instruction = 0x00000000; /* no op */
        return; 
    }
    // no data hazard
    sim->hzrd_ctrl.pc_write = ON;
    sim->hzrd_ctrl.if_id_write = ON;

    // control hazard
    // int imm_val = 0xFFFF;
    // int br_tgt = sim->pc + (imm_val << 2);
}