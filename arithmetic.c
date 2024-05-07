/* MIPS32 Arithmetic Operations : Implementation*/
/*
 * This is implementations for MIPS32 arithmetic operations 
 * @author kdh
 * */

#pragma once

#include "arithmetic.h"


/* 
 * @brief add, R[rd] = R[rs] + R[rt]
 * @author kdh
 * Integer Add
 */
void add(MIPS32Simulator * sim, int rd, int rs, int rt)
{
	sim -> gp_registers[rd] = sim -> gp_registers[rs] + sim -> gp_registers[rt];
}

/* 
 * @brief sub, R[rd] = R[rs] + R[rt]
 * @author kdh
 * Integer Substraction
 */
void sub(MIPS32Simulator * sim, int rd, int rs, int rt)
{
	sim -> gp_registers[rd] = sim -> gp_registers[rs] - sim -> gp_registers[rt];
}

/* 
 * @brief addi, R[rd] = R[rs] + R[rt]
 * @author kdh
 * Integer Add Immediate
 */
void addi(MIPS32Simulator * sim, int rt, int rs, int imm)
{
	sim -> gp_registers[rt] = sim -> gp_registers[rs] + imm;
}


void addiu(MIPS32Simulator * sim, int rt, int rs, int imm)
{

}

void mult(MIPS32Simulator * sim, int rd, int rs, int rt)
{

}

void div(MIPS32Simulator * sim, int rd, int rs, int rt)
{

}