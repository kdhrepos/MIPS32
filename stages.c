#pragma once

#include "stages.h"

/*
 * all pipeline registers stay at MIPS32Simulator
 * each stage called reversely, wb -> if because of pipeline register not to be overwrited
 * 
 * 
*/

/*
 * fetch the program
 * call decode stage
 * update pipeline register
 * @param pc   
*/
void fetch(MIPS32Simulator * sim)
{
    int inst = sim->memory[sim->pc]; // instruction fetch

    /* update pipeline register */
    sim->if_id_reg.instruction = inst; 
    sim->if_id_reg.pc = sim->pc; 
    sim->pc += 1; // next pc
}

/*
 * decode the instruction
 * hazard detection
*/
void decode(MIPS32Simulator * sim)
{
    /* get datas from pipeline register */
    int inst = sim->if_id_reg.instruction; // instruction
    int pc = sim->if_id_reg.pc; // pc
    printf("ID Stage Instruction : %x\n", inst);

    /* parsing instruction */
    int opcode = (inst >> 26) & 0x3F; // opcode
    int rs = (inst >> 21) & 0x1F; // first source register
    int rt = (inst >> 16) & 0x1F; /* second source register on r-type */ /* destination register on I-type */
    int rd = (inst >> 11) & 0x1F; // destination register
    int shamt = (inst >> 6) & 0x1F;  // shift amount
    int funct = inst & 0x3F; // function code
    int imm = inst & 0xFFFF; // immediate value
    int addr = inst & 0x1FFFF; // jump address

    if(opcode == RTYPEOP)
    {
        printf("| %d | %d | %d | %d | %d |\n", opcode, rs, rt, shamt, funct);

        int rs_value = sim->reg_file[rs]; // read rs from register file
        int rt_value = sim->reg_file[rt]; // read rt from register file

        /* set exe stage control signals */
        sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt in r-type
        sim->id_ex_ctrl.ALUOp = (opcode >> 4) & 0x3; // ALUOp
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
        sim->id_ex_reg.rs_val = rs_value;
        sim->id_ex_reg.rt_val = rt_value;
        sim->id_ex_reg.rt_num = rt;
        sim->id_ex_reg.rd_num = rd;
        sim->id_ex_reg.imm_val = -1; // don't use immediate field
        sim->id_ex_reg.pc = pc;
        sim->id_ex_reg.shamt=shamt;
        sim->id_ex_reg.funct = funct; // input for alu control
    }
    else
    {
        /* I Type */
        if(opcode != J && opcode != JAL)
        {
            int rs_value = sim->reg_file[rs]; // read rs from register file
            int rt_value = sim->reg_file[rt]; // read rt from register file

            /* Branch */
            if(opcode == BEQ || opcode == BNE)
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = (opcode >> 4) & 0x3; // ALUOp
                sim->id_ex_ctrl.RegDst = DONT_CARE; // RegDst, don't care

                /* set mem stage control signals */
                sim->id_ex_ctrl.MemRead = OFF; // MemRead, don't read memory on branch
                sim->id_ex_ctrl.MemWrite = OFF; // MemWrite, dont' write memory on branch
                sim->id_ex_ctrl.Branch = ON; // Branch
                sim->id_ex_ctrl.Jump = OFF; // Jump

                /* set wb stage control signals */
                sim->id_ex_ctrl.RegWrite = OFF; // RegWrite, write result to register, not memory
                sim->id_ex_ctrl.MemtoReg = DONT_CARE; // MemtoReg, don't care


                /* update pipeline register */
                sim->id_ex_reg.rs_val = rs_value;
                sim->id_ex_reg.rt_val = rt_value;
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = -1; // don't use rd register number
                sim->id_ex_reg.imm_val = -1; // don't use immediate field
                sim->id_ex_reg.pc = pc;
            }
            /* Store */
            else if(opcode == SW) // first, we don't implement another store operataions like sb, sh
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc
                sim->id_ex_ctrl.ALUOp = (opcode >> 4) & 0x3; // ALUOp
                sim->id_ex_ctrl.RegDst = DONT_CARE; // RegDst, don't care

                /* set mem stage control signals */
                sim->id_ex_ctrl.MemRead = OFF; // MemRead
                sim->id_ex_ctrl.MemWrite = ON; // MemWrite
                sim->id_ex_ctrl.Branch = OFF; // Branch
                sim->id_ex_ctrl.Jump = OFF; // Jump

                /* set wb stage control signals */
                sim->id_ex_ctrl.RegWrite = OFF; // RegWrite, write result to register, not memory
                sim->id_ex_ctrl.MemtoReg = DONT_CARE; // MemtoReg, don't care

                /* update pipeline register */
                sim->id_ex_reg.rs_val = rs_value;
                sim->id_ex_reg.rt_val = -1; // don't need rt register value
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = -1; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.pc = pc;
            }
            /* Load */
            else if(opcode == LW) // first, we don't implement another store operataions like lb, lh
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc
                sim->id_ex_ctrl.ALUOp = (opcode >> 4) & 0x3; // ALUOp
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
                sim->id_ex_reg.rt_num = -1; // don't use rt register number
                sim->id_ex_reg.rd_num = -1; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.pc = pc;
            }
            /* Constant */
            else
            {
                printf("║ %x ║ %x ║ %x ║ %x ║\n", opcode, rs, rt, imm);

                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = (opcode >> 4) & 0x3; // ALUOp
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
                sim->id_ex_reg.rt_val = -1; // don't use rt register value
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = -1; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.pc = pc;
            }
        }
        /* J Type */
        else
        {
            /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = (opcode >> 4) & 0x3; // ALUOp
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
                sim->id_ex_reg.rs_val = -1;
                sim->id_ex_reg.rt_val = -1;
                sim->id_ex_reg.rt_num = -1;
                sim->id_ex_reg.rd_num = -1;
                sim->id_ex_reg.imm_val = addr;
                sim->id_ex_reg.pc = pc;
        }
        sim->id_ex_reg.shamt = -1; // no shamt for I-Type instruction
        sim->id_ex_reg.funct = -1; // no funct code for I-Type instruction
    }
    // opcode -> generate control input like RegWrite
    // read register file
    // sign extension -> do not use in simulator
    // update pipeline register
}

/*
 * instruction execution
*/
void execution()
{
    // alu operation
    // add imm value
    // update pipeline register
}

/*
 * access memory
*/
void memory()
{
    // memory access with imm value
    // update pipeline register
}

void write_back()
{

}