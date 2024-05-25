#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/


/*
 * decode the instruction
 * hazard detection
*/
void decode(MIPS32Simulator * sim, Log log[MEM_SIZE])
{
    /* get datas from pipeline register */
    int inst = sim->if_id_reg.instruction; // instruction
    int pc = sim->if_id_reg.pc; // pc

    /* no operation? */
    if(inst == 0x00000000)
    {
        /* set exe stage control signals */
        sim->id_ex_ctrl.ALUSrc = OFF, sim->id_ex_ctrl.ALUOp = OFF, sim->id_ex_ctrl.RegDst = OFF;

        /* set mem stage control signals */
        sim->id_ex_ctrl.MemRead = OFF, sim->id_ex_ctrl.MemWrite = OFF;
        sim->id_ex_ctrl.Branch = OFF, sim->id_ex_ctrl.Jump = OFF;

        /* set wb stage control signals */
        sim->id_ex_ctrl.RegWrite = OFF, sim->id_ex_ctrl.MemtoReg = OFF;
        
        /* FIXME : pc, if_id_write off */

        /* update pipeline register */
        sim->id_ex_reg.rs_val = EMPTY;
        sim->id_ex_reg.rt_val = EMPTY;
        sim->id_ex_reg.rt_num = EMPTY;
        sim->id_ex_reg.rd_num = EMPTY;
        sim->id_ex_reg.imm_val = EMPTY;
        sim->id_ex_reg.pc = pc;
        return;
    }

    /* parsing instruction */
    int opcode = (inst >> 26) & 0x3F; // opcode
    int rs = (inst >> 21) & 0x1F; // first source register
    int rt = (inst >> 16) & 0x1F; /* second source register on r-type */ 
                                  /* destination register on I-type */
    int rd = (inst >> 11) & 0x1F; // destination register
    int shamt = (inst >> 6) & 0x1F;  // shift amount
    int funct = inst & 0x3F; // function code
    int imm = inst & 0xFFFF; // immediate value
    int addr = inst & 0x1FFFF; // jump address

    // hazard_detection(sim, rs, rt);

    if(opcode == RTYPEOP)
    {
        printf("R-Type Instruction : \n|%d|%d|%d|%d|%d|%d|\n", opcode, rs, rt, rd, shamt, funct);

        int rs_val = sim->reg_file[rs]; // read rs from register file
        int rt_val = sim->reg_file[rt]; // read rt from register file

        /* set exe stage control signals */
        sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt in r-type
        sim->id_ex_ctrl.ALUOp = get_ALUOp(opcode); // ALUOp
        sim->id_ex_ctrl.RegDst = ON; // RegDst, destination register is rd in r-type

        /* set mem stage control signals */
        sim->id_ex_ctrl.MemRead = OFF; // MemRead, don't read memory on r-type
        sim->id_ex_ctrl.MemWrite = OFF; // MemWrite, dont' write memory on r-type
        sim->id_ex_ctrl.Branch = OFF; // Branch, don't use branch on r-type
        sim->id_ex_ctrl.Jump = OFF; // Jump

        /* set wb stage control signals */
        sim->id_ex_ctrl.RegWrite = ON; // RegWrite, write result to register, not memory
        sim->id_ex_ctrl.MemtoReg = OFF; // MemtoReg, don't read memory on r-type

        /* update pipeline register */
        sim->id_ex_reg.rs_val = rs_val;
        sim->id_ex_reg.rt_val = rt_val;
        sim->id_ex_reg.rt_num = rt;
        sim->id_ex_reg.rd_num = rd;
        sim->id_ex_reg.imm_val = funct;
        sim->id_ex_reg.rs_num = rs;
        sim->id_ex_reg.pc = pc;
    }
    else
    {
        /* I Type */
        if(opcode != J && opcode != JAL)
        {
            printf("I-Type Instruction : \n|%d|%d|%d|%d|\n", opcode, rs, rt, imm);

            int rs_value = sim->reg_file[rs]; // read rs from register file
            int rt_value = sim->reg_file[rt]; // read rt from register file

            /* Branch */
            if(opcode == BEQ || opcode == BNE)
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = get_ALUOp(opcode); // ALUOp. b'01
                sim->id_ex_ctrl.RegDst = OFF; // RegDst, don't care

                /* set mem stage control signals */
                sim->id_ex_ctrl.MemRead = OFF; // MemRead, don't read memory on branch
                sim->id_ex_ctrl.MemWrite = OFF; // MemWrite, dont' write memory on branch
                sim->id_ex_ctrl.Branch = ON; // Branch
                sim->id_ex_ctrl.Jump = OFF; // Jump

                /* set wb stage control signals */
                sim->id_ex_ctrl.RegWrite = OFF; // RegWrite, write result to register, not memory
                sim->id_ex_ctrl.MemtoReg = OFF; // MemtoReg, don't care

                /* update pipeline register */
                sim->id_ex_reg.rs_val = rs_value;
                sim->id_ex_reg.rt_val = rt_value;
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = EMPTY; // don't use rd register number
                sim->id_ex_reg.imm_val = EMPTY; // don't use immediate field
                sim->id_ex_reg.rs_num = rs;
                sim->id_ex_reg.pc = pc;
            }
            /* Store */
            else if(opcode == SW) // first, we don't implement another store operataions like sb, sh
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc
                sim->id_ex_ctrl.ALUOp = get_ALUOp(opcode); // ALUOp, b'00
                sim->id_ex_ctrl.RegDst = OFF; // RegDst, don't care

                /* set mem stage control signals */
                sim->id_ex_ctrl.MemRead = OFF; // MemRead
                sim->id_ex_ctrl.MemWrite = ON; // MemWrite
                sim->id_ex_ctrl.Branch = OFF; // Branch
                sim->id_ex_ctrl.Jump = OFF; // Jump

                /* set wb stage control signals */
                sim->id_ex_ctrl.RegWrite = OFF; // RegWrite, write result to register, not memory
                sim->id_ex_ctrl.MemtoReg = OFF; // MemtoReg, don't care

                /* update pipeline register */
                sim->id_ex_reg.rs_val = rs_value;
                sim->id_ex_reg.rt_val = EMPTY; // don't need rt register value
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = EMPTY; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.rs_num = rs;
                sim->id_ex_reg.pc = pc;
            }
            /* Load */
            else if(opcode == LW) // first, we don't implement another store operataions like lb, lh
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc
                sim->id_ex_ctrl.ALUOp = get_ALUOp(opcode); // ALUOp, b'00
                sim->id_ex_ctrl.RegDst = OFF; // RegDst, don't use rd on load word

                /* set mem stage control signals */
                sim->id_ex_ctrl.MemRead = ON; // MemRead, don't read memory
                sim->id_ex_ctrl.MemWrite = OFF; // MemWrite, dont' write memory
                sim->id_ex_ctrl.Branch = OFF; // Branch
                sim->id_ex_ctrl.Jump = OFF; // Jump

                /* set wb stage control signals */
                sim->id_ex_ctrl.RegWrite = ON; // RegWrite, write result to register, not memory
                sim->id_ex_ctrl.MemtoReg = ON; // MemtoReg, don't care

                /* update pipeline register */
                sim->id_ex_reg.rs_val = rs_value;
                sim->id_ex_reg.rt_val = rt_value;
                sim->id_ex_reg.rt_num = EMPTY; // don't use rt register number
                sim->id_ex_reg.rd_num = EMPTY; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.rs_num = rs;
                sim->id_ex_reg.pc = pc;
            }
            /* Constant */
            else
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = get_ALUOp(opcode); // ALUOp, b'??
                sim->id_ex_ctrl.RegDst = OFF; // RegDst, don't use rd on constant operation

                /* set mem stage control signals */
                sim->id_ex_ctrl.MemRead = OFF; // MemRead, don't read memory
                sim->id_ex_ctrl.MemWrite = OFF; // MemWrite, dont' write memory
                sim->id_ex_ctrl.Branch = OFF; // Branch
                sim->id_ex_ctrl.Jump = OFF; // Jump

                /* set wb stage control signals */
                sim->id_ex_ctrl.RegWrite = ON; // RegWrite, write result to register, not memory
                sim->id_ex_ctrl.MemtoReg = OFF; // MemtoReg, don't care

                /* update pipeline register */
                sim->id_ex_reg.rs_val = rs_value;
                sim->id_ex_reg.rt_val = EMPTY; // don't use rt register value
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = EMPTY; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.rs_num = rs;
                sim->id_ex_reg.pc = pc;
            }
        }
        /* J Type */
        else
        {
            printf("J-Type Instruction : \n|%d|%d|\n", opcode, addr);

            /* set exe stage control signals */
            sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt on branch
            sim->id_ex_ctrl.ALUOp = get_ALUOp(opcode); // ALUOp, b'??
            sim->id_ex_ctrl.RegDst = OFF; // RegDst, don't use rd on constant operation

            /* set mem stage control signals */
            sim->id_ex_ctrl.MemRead = OFF; // MemRead, don't read memory
            sim->id_ex_ctrl.MemWrite = OFF; // MemWrite, dont' write memory
            sim->id_ex_ctrl.Branch = OFF; // Branch
            sim->id_ex_ctrl.Jump = ON; // Jump

            /* set wb stage control signals */
            sim->id_ex_ctrl.RegWrite = OFF; // RegWrite, write result to register, not memory
            sim->id_ex_ctrl.MemtoReg = OFF; // MemtoReg, don't care

            /* update pipeline register */
            sim->id_ex_reg.rs_val = EMPTY;
            sim->id_ex_reg.rt_val = EMPTY;
            sim->id_ex_reg.rt_num = EMPTY;
            sim->id_ex_reg.rd_num = EMPTY;
            sim->id_ex_reg.imm_val = addr;
            sim->id_ex_reg.rs_num = rs;
            sim->id_ex_reg.pc = pc;
        }
    }

    /* recording the instruction history */
    if(sim->ID_log_itr < 0) return;
    log[sim->ID_log_itr].ID = TRUE;
    log[sim->ID_log_itr].ID_clk = sim->clk;
    sim->EXE_log_itr = sim->ID_log_itr;
}

int get_ALUOp(int opcode)
{
    /* RTYPEOP */
    if(opcode == RTYPEOP)
        return 0x7; // b'111
    else
    {
        /* ITYPEOP */
        if(opcode != J && opcode != JAL)
        {
            if(opcode == ADDI || opcode == ADDIU
            || opcode == LW || opcode == LBU || opcode == LHU 
            || opcode == SH || opcode == SW || opcode == SB)
                return 0x0; // b'000
            if(opcode == BEQ)
                return 0x1; // b'001
            if(opcode == BNE)
                return 0x2; // b'010
            if(opcode == SLTI || opcode == SLTIU)
                return 0x3; // b'011
            if(opcode == ANDI)
                return 0x4; // b'100
            if(opcode == ORI)
                return 0x5; // b'101
            if(opcode == LUI)
                return 0x6; // b'110
        }
        /* JTYPEOP */
        else
            return 0x0; // b'000, don't use ALU
    }
}