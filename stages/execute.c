#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/

/*
 * instruction execution
*/
void execute(MIPS32Simulator * sim)
{
    /* no operation? */
    if(sim->id_ex_ctrl.ALUOp==OFF && sim->id_ex_ctrl.ALUSrc==OFF && sim->id_ex_ctrl.RegDst==OFF
    && sim->id_ex_ctrl.Branch==OFF && sim->id_ex_ctrl.Jump==OFF && sim->id_ex_ctrl.MemRead==OFF 
    && sim->id_ex_ctrl.MemtoReg==OFF && sim->id_ex_ctrl.MemWrite==OFF && sim->id_ex_ctrl.RegWrite==OFF)
        return;

    /* read id/ex pipeline register */
    int rs_val = sim->id_ex_reg.rs_val;
    int rt_val = sim->id_ex_reg.rt_val;
    int rt_num = sim->id_ex_reg.rt_num;
    int rd_num = sim->id_ex_reg.rd_num;
    int imm_val = sim->id_ex_reg.imm_val;
    int pc = sim->id_ex_reg.pc;
    int shamt = (imm_val >> 6) & 0x1F;
    int funct = imm_val & 0x3F;

    /* read id/ex control register */
    int ALUOp = sim->id_ex_ctrl.ALUOp;
    int ALUSrc = sim->id_ex_ctrl.ALUSrc;
    int RegDst = sim->id_ex_ctrl.RegDst;
    
    /* generate ALU control input */
    int ALU_ctrl_input = ALU_control_input(ALUOp, funct);
    int ALU_result;

    /* R-Type */
    if(ALUOp == 0x2) // b'10
    {
        if(ALU_ctrl_input == 0x2) /* add, b'0010 */
            ALU_result = rs_val + rt_val;
        else if(ALU_ctrl_input == 0x6) /* subtract, b'0110 */
            ALU_result = rs_val - rt_val;
        else if(ALU_ctrl_input == 0x0) /* AND, b'0000 */
            ALU_result = rs_val & rt_val;
        else if(ALU_ctrl_input == 0x1) /* OR, b'0001 */
            ALU_result = rs_val | rt_val;
        else if(ALU_ctrl_input == 0x7) /* set on less than, b'0111 */
            ALU_result = rs_val - rt_val;
    }
    /* I-Type */
    else
    {
        /* Load Word, Store Word */
        if(ALUOp == 0x0) /* b'00 */
            ALU_result = rs_val + imm_val;
        /* Branch Equal */
        else if(ALUOp == 0x1) /* b'01 */
            ALU_result = rs_val - rt_val;
    }

    /* update EX/MEM register */
    sim->ex_mem_reg.br_tgt = pc + (imm_val << 2);
    sim->ex_mem_reg.zero = (ALU_result == 0) ? ON : OFF;
    sim->ex_mem_reg.ALU_result = ALU_result;
    sim->ex_mem_reg.rt_val = rt_val;
    sim->ex_mem_reg.rd_num = RegDst ? rd_num : rt_num;

    /* update control signals */
    // EX
    sim->ex_mem_ctrl.MemRead =  sim->id_ex_ctrl.MemRead;
    sim->ex_mem_ctrl.MemWrite  = sim->id_ex_ctrl.MemWrite;
    sim->ex_mem_ctrl.Branch  = sim->id_ex_ctrl.Branch;
    sim->ex_mem_ctrl.Jump  = sim->id_ex_ctrl.Jump; 
    // MEM
    sim->ex_mem_ctrl.RegWrite  = sim->id_ex_ctrl.RegWrite;
    sim->ex_mem_ctrl.MemtoReg  = sim->id_ex_ctrl.MemtoReg;
}