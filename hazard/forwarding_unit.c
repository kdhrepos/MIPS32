#include "hazard.h"

void forwarding(MIPS32Simulator * sim)
{
   /* no hazard */
   sim->fwd_ctrl.FwdA = 0x00;
   sim->fwd_ctrl.FwdB = 0x00;

   /* EXE Forward - rs */
   if(sim->ex_mem_ctrl.RegWrite && 
      sim->ex_mem_reg.rd_num != 0 &&
      sim->ex_mem_reg.rd_num == sim->id_ex_reg.rs_num)
      sim->fwd_ctrl.FwdA = 0x02;

   /* MEM Forward - rs */
   if(sim->mem_wb_ctrl.RegWrite && sim->mem_wb_reg.rd_num != 0
   && !(sim->ex_mem_ctrl.RegWrite && sim->ex_mem_reg.rd_num != 0
   && (sim->ex_mem_reg.rd_num == sim->id_ex_reg.rs_num))
   && sim->mem_wb_reg.rd_num == sim->id_ex_reg.rs_num)
      sim->fwd_ctrl.FwdA = 0x01;

   /* EXE Forward - rt */
   if(sim->ex_mem_ctrl.RegWrite && 
      sim->ex_mem_reg.rd_num != 0 && 
      sim->ex_mem_reg.rd_num == sim->id_ex_reg.rt_num)
      sim->fwd_ctrl.FwdB = 0x02;

   /* MEM Forward - rt */
   if(sim->mem_wb_ctrl.RegWrite && sim->mem_wb_reg.rd_num != 0
   && !(sim->ex_mem_ctrl.RegWrite && sim->ex_mem_reg.rd_num != 0
   && (sim->ex_mem_reg.rd_num == sim->id_ex_reg.rt_num))
   && sim->mem_wb_reg.rd_num == sim->id_ex_reg.rt_num)
      sim->fwd_ctrl.FwdB = 0x01;
   
    // MUX - first source operand, hazard check
   if(sim->fwd_ctrl.FwdA == 0x02) /* EXE Forward */
      sim->id_ex_reg.rs_val = sim->ex_mem_reg.ALU_result;
   else if(sim->fwd_ctrl.FwdA == 0x01) /* MEM Forward */
      sim->id_ex_reg.rs_val = (sim->mem_wb_ctrl.MemtoReg == ON) ? 
      sim->mem_wb_reg.load_data : sim->mem_wb_reg.ALU_result;

    // MUX - second source operand, hazard check
    if(sim->fwd_ctrl.FwdB == 0x02) /* EXE Forward */
        sim->id_ex_reg.rt_val = sim->ex_mem_reg.ALU_result;
   
    else if(sim->fwd_ctrl.FwdB == 0x01) /* MEM Forward */
        sim->id_ex_reg.rt_val = (sim->mem_wb_ctrl.MemtoReg == ON) ?
        sim->mem_wb_reg.load_data : sim->mem_wb_reg.ALU_result;
    
}