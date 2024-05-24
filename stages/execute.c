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
void execute(MIPS32Simulator * sim, History history[MEM_SIZE])
{
    /* no operation? */
    if(sim->id_ex_ctrl.ALUOp==OFF && sim->id_ex_ctrl.ALUSrc==OFF && sim->id_ex_ctrl.RegDst==OFF
    && sim->id_ex_ctrl.Branch==OFF && sim->id_ex_ctrl.Jump==OFF && sim->id_ex_ctrl.MemRead==OFF 
    && sim->id_ex_ctrl.MemtoReg==OFF && sim->id_ex_ctrl.MemWrite==OFF && sim->id_ex_ctrl.RegWrite==OFF)
    {
        /* set mem stage control signals */
        sim->ex_mem_ctrl.Branch = OFF, sim->ex_mem_ctrl.Jump = OFF, sim->ex_mem_ctrl.MemRead = OFF,
        sim->ex_mem_ctrl.MemtoReg = OFF, sim->ex_mem_ctrl.MemWrite = OFF, sim->ex_mem_ctrl.RegWrite = OFF;
        
        // /* update pipeline register */
        // sim->ex_mem_reg.br_tgt = EMPTY;
        // sim->ex_mem_reg.zero = EMPTY;
        // sim->ex_mem_reg.ALU_result = EMPTY;
        // sim->ex_mem_reg.rt_val = EMPTY;
        // sim->ex_mem_reg.rd_num = EMPTY;
        return;
    }

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

    /* ALU inputs */
    int ALU_ctrl_input = get_ALU_ctrl(ALUOp, funct);
    int ALU_operand_1 = rs_val;
    int ALU_operand_2 = ALUSrc ? imm_val : rt_val;
    int ALU_result;

    if(ALU_ctrl_input == 0x0) // and, b'0000
        ALU_result = ALU_operand_1 & ALU_operand_2;
    else if(ALU_ctrl_input == 0x1) // or, b'0001
        ALU_result = ALU_operand_1 | ALU_operand_2;
    else if(ALU_ctrl_input == 0x2) // nor, b'0010
        ALU_result = !(ALU_operand_1 | ALU_operand_2);
    else if(ALU_ctrl_input == 0x3) // add, b'0011
        ALU_result = ALU_operand_1 + ALU_operand_2;
    else if(ALU_ctrl_input == 0x4) // sub, b'0100
        ALU_result = ALU_operand_1 - ALU_operand_2;
    else if(ALU_ctrl_input == 0x5) // ~sub, b'0101
        ALU_result = !(ALU_operand_1 - ALU_operand_2);
    else if(ALU_ctrl_input == 0x6) // set on less than, b'0110
        ALU_result = (ALU_operand_1 < ALU_operand_2) ? ON : OFF;
    else if(ALU_ctrl_input == 0x7) // shift left, b'0111
        ALU_result = ALU_operand_1 << shamt;
    else if(ALU_ctrl_input == 0x8) // shift right, b'1000
        ALU_result = (int)((unsigned int)ALU_operand_1 >> shamt);
    else if(ALU_ctrl_input == 0x9) // arithmetic shift right, b'1001
        ALU_result = ALU_operand_1 >> shamt;
    else if(ALU_ctrl_input == 0xA) // shift -> or, b'1010
        ALU_result = ALU_operand_1 & ALU_operand_2;

    /* update EX/MEM register */
    sim->ex_mem_reg.br_tgt = pc + (imm_val << 2);
    sim->ex_mem_reg.zero = (ALU_result == 0) ? ON : OFF;
    sim->ex_mem_reg.ALU_result = ALU_result;
    sim->ex_mem_reg.rt_val = rt_val;
    sim->ex_mem_reg.rd_num = RegDst ? rd_num : rt_num;

    /* update control signals */
    // MEM
    sim->ex_mem_ctrl.MemRead =  sim->id_ex_ctrl.MemRead;
    sim->ex_mem_ctrl.MemWrite  = sim->id_ex_ctrl.MemWrite;
    sim->ex_mem_ctrl.Branch  = sim->id_ex_ctrl.Branch;
    sim->ex_mem_ctrl.Jump  = sim->id_ex_ctrl.Jump; 
    // WB
    sim->ex_mem_ctrl.RegWrite  = sim->id_ex_ctrl.RegWrite;
    sim->ex_mem_ctrl.MemtoReg  = sim->id_ex_ctrl.MemtoReg;

    /* recording the instruction history */
    history[sim->EXE_hist_itr].EXE = TRUE;
    history[sim->EXE_hist_itr].EXE_clk = sim->clk;
    sim->MEM_hist_itr = sim->EXE_hist_itr;
}

int get_ALU_ctrl(int ALUOp, int funct)
{
    /* RTYPEOP */
    if(ALUOp == 0x7) // b'111
    {
        /* add addu */
        if(funct == ADD || funct == ADDU)
            return 0x3; // add, b'0011
        /* sub subu */
        else if(funct == SUB || funct == SUBU)
            return 0x4; // sub, b'0100
        /* and */
        else if(funct == AND)
            return 0x0; // and, b'0000
        /* or */
        else if(funct == OR)
            return 0x1; // or, b'0001
        /* nor */
        else if(funct == NOR)
            return 0x2; // nor, b'0010
    }
    /* addi addiu memory operation, b'000 */
    else if(ALUOp == 0x0)
        return 0x3; // add, b'0011
    /* beq, b'001 */
    else if(ALUOp == 0x1) 
        return 0x4; // sub, b'0100
    /* bne, b'010 */
    else if(ALUOp == 0x2)
        return 0x5; // ~sub, b'0101
    /* slti sltiu, b'011 */
    else if(ALUOp == 0x3)
        return 0x6; // slt, b'0110
    /* andi, b'100 */
    else if(ALUOp == 0x4)
        return 0x0; // and, b'0000
    /* ori, b'101 */
    else if(ALUOp == 0x5)
        return 0x1; // or, b'0001
    /* lui, b'110 */
    else if(ALUOp == 0x6)
        return 0xA; // shift -> or, b'1010
    /* JTYPEOP */
    else
        return 0x0; // noop, b'0000
}
