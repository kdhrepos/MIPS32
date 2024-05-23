#include "./hazard.h"

boolean hazard_detection(MIPS32Simulator * sim, int rs, int rt)
{
    /*

    * if (ID/EX.MemRead and
        ((ID/EX.RegisterRt = IF/ID.RegisterRs) or
        (ID/EX.RegisterRt = IF/ID.RegisterRt)))
        stall the pipeline

    */
    /* load-use data hazard */
    if(sim->id_ex_ctrl.MemRead && 
    (sim->id_ex_reg.rt_num == rs || sim->id_ex_reg.rt_num == rt))
    {
        sim->hzrd_ctrl.pc_write = OFF;
        sim->hzrd_ctrl.if_id_write = OFF;
        return TRUE; // hazard occurred
    }
    sim->hzrd_ctrl.pc_write = ON;
    sim->hzrd_ctrl.if_id_write = ON;
    return FALSE; // no hazard

    /* control hazard */
    int imm_val = 0xFFFF;
    int br_tgt = sim->pc + (imm_val << 2);
}