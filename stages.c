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
    int inst = 0;

    /* if branch is taken */
    if(sim->ex_mem_ctrl.Branch && sim->ex_mem_reg.zero)
        inst = sim->memory[sim->ex_mem_reg.br_tgt];
    /* if branch is not taken */
    else
        inst = sim->memory[sim->pc];
    
    /* update pipeline register */
    sim->if_id_reg.instruction = inst; 
    sim->if_id_reg.pc = sim->pc+1; // update pc 
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

    if(opcode == RTYPEOP)
    {
        printf("R-Type Instruction : \n|%d|%d|%d|%d|%d|%d|\n", opcode, rs, rt, rd, shamt, funct);

        int rs_val = sim->reg_file[rs]; // read rs from register file
        int rt_val = sim->reg_file[rt]; // read rt from register file

        /* set exe stage control signals */
        sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt in r-type
        sim->id_ex_ctrl.ALUOp = 0x2; // ALUOp, b'10
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
        sim->id_ex_reg.imm_val = EMPTY; // don't use immediate field
        sim->id_ex_reg.pc = pc;
    }
    else
    {
        /* I Type */
        if(opcode != J && opcode != JAL)
        {
            printf("I-Type Instruction : \n|%d|%d|%d|\n", opcode, rs, rt, imm);

            int rs_value = sim->reg_file[rs]; // read rs from register file
            int rt_value = sim->reg_file[rt]; // read rt from register file

            /* Branch */
            if(opcode == BEQ || opcode == BNE)
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = OFF; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = 0x1; // ALUOp. b'01
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
                sim->id_ex_reg.rd_num = EMPTY; // don't use rd register number
                sim->id_ex_reg.imm_val = EMPTY; // don't use immediate field
                sim->id_ex_reg.pc = pc;
            }
            /* Store */
            else if(opcode == SW) // first, we don't implement another store operataions like sb, sh
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc
                sim->id_ex_ctrl.ALUOp = 0x0; // ALUOp, b'00
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
                sim->id_ex_reg.rt_val = EMPTY; // don't need rt register value
                sim->id_ex_reg.rt_num = rt;
                sim->id_ex_reg.rd_num = EMPTY; // don't use rd register number
                sim->id_ex_reg.imm_val = imm;
                sim->id_ex_reg.pc = pc;
            }
            /* Load */
            else if(opcode == LW) // first, we don't implement another store operataions like lb, lh
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc
                sim->id_ex_ctrl.ALUOp = 0x0; // ALUOp, b'00
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
                sim->id_ex_reg.pc = pc;
            }
            /* Constant */
            else
            {
                /* set exe stage control signals */
                sim->id_ex_ctrl.ALUSrc = ON; // ALUSrc, source register is rt on branch
                sim->id_ex_ctrl.ALUOp = 0x11; // ALUOp, b'??
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
                sim->id_ex_reg.pc = pc;
            }
        }
        /* J Type */
        else
        {
            printf("J-Type Instruction : \n|%d|%d|\n", opcode, addr);

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
            sim->id_ex_reg.rs_val = EMPTY;
            sim->id_ex_reg.rt_val = EMPTY;
            sim->id_ex_reg.rt_num = EMPTY;
            sim->id_ex_reg.rd_num = EMPTY;
            sim->id_ex_reg.imm_val = addr;
            sim->id_ex_reg.pc = pc;
        }
    }
}

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

    printf("A : %d, B : %d\n", rs_val, rt_val);
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

/*
 * access memory
*/
void memory(MIPS32Simulator * sim)
{
    /* no operation? */
    if(sim->ex_mem_ctrl.Branch==OFF && sim->ex_mem_ctrl.Jump==OFF && sim->ex_mem_ctrl.MemRead==OFF 
    && sim->ex_mem_ctrl.MemtoReg==OFF && sim->ex_mem_ctrl.MemWrite==OFF && sim->ex_mem_ctrl.RegWrite==OFF)
        return;

    /* read ex/mem pipeline register */
    int br_trgt = sim->ex_mem_reg.br_tgt;
    int zero = sim->ex_mem_reg.zero;
    int ALU_result = sim->ex_mem_reg.ALU_result;
    int rt_val = sim->ex_mem_reg.rt_val;
    int rd_num = sim->ex_mem_reg.rd_num;
    
    /* read control signals */
    int RegWrite = sim->ex_mem_ctrl.RegWrite;
    int MemtoReg = sim->ex_mem_ctrl.MemtoReg;

    int address = sim->mem_wb_reg.ALU_result;

    /* Load */
    if(sim->ex_mem_ctrl.MemRead == ON)
        sim->mem_wb_reg.load_data = sim->memory[address];
    /* Store */
    else if(sim->ex_mem_ctrl.MemWrite = ON)
    {
        sim->mem_wb_reg.load_data = EMPTY;
        sim->memory[address] = rt_val;
    }

    /* update pipeline register */
    sim->mem_wb_reg.ALU_result = ALU_result;
    sim->mem_wb_reg.rd_num = rd_num;
    
    /* update control signals */
    sim->mem_wb_ctrl.RegWrite = RegWrite;
    sim->mem_wb_ctrl.MemtoReg = MemtoReg;
}

void write_back(MIPS32Simulator * sim)
{
    /* no operation? */
    if(sim->ex_mem_ctrl.MemtoReg==OFF && sim->ex_mem_ctrl.RegWrite==OFF)
        return;

    /* read mem/wb pipeline register */
    int loaded_data = sim->mem_wb_reg.load_data;
    int ALU_result = sim->mem_wb_reg.ALU_result;
    int rd_num = sim->mem_wb_reg.rd_num;

    /* read mem/wb control signals */
    int RegWrite = sim->mem_wb_ctrl.RegWrite;
    int MemtoReg = sim->mem_wb_ctrl.MemtoReg;

    if(RegWrite == ON)
    {
        /* Load */
        if(MemtoReg == ON)
            sim->reg_file[rd_num] = loaded_data;
        /* R-Type */
        else 
            sim->reg_file[rd_num] = ALU_result;
    }
}

int ALU_control_input(int ALUOp, int funct)
{
    int ALUOp_0 = ALUOp & 0x1;
    int ALUOp_1 = (ALUOp >> 1) & 0x1;

    int funct_shifted = funct >> 4;

    if(ALUOp_0 == OFF && ALUOp_1 == OFF)
        return 0x2; // b'0010
    else if(ALUOp_0 == ON)
        return 0x6; // b'0110
    else if(ALUOp_1 == ON)
    {
        if(funct_shifted == 0x0)
            return 0x2; // b'0010
        if(funct_shifted == 0x2)
            return 0x6; // b'0110
        if(funct_shifted == 0x4)
            return 0x0; // b'0000
        if(funct_shifted == 0x5)
            return 0x1; // b'0001
        if(funct_shifted == 0x6)
            return 0x7; // b'0111
    }
}

bool is_noop_id_ex(MIPS32Simulator * sim)
{
    
}
