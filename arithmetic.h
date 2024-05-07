/* MIPS32 Arithmetic Operations : Declaration */
/*
 * @author kdh
 * */

#pragma once

#include "core.h"

/* 
 * @brief add, R[rd] = R[rs] + R[rt]
 * @author kdh
 * Signed Integer Addition
 */
void add(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief addu, R[rd] = R[rs] + R[rt]
 * @author kdh
 * Unsigned Integer Addition
 */
void addu(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief sub, R[rd] = R[rs] - R[rt]
 * @author kdh
 * Signed Integer Substraction
 */
void sub(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief subu, R[rd] = R[rs] - R[rt]
 * @author kdh
 * Unsigned Integer Substraction
 */
void subu(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief addi, R[rd] = R[rs] + R[rt]
 * @author kdh
 * Signed Integer Constant Addition
 */
void addi(MIPS32Simulator * sim, int rt, int rs, int imm);

/* 
 * @brief 
 * @author kdh
 * Unsigned Integer Constant Addition
 */
void addiu(MIPS32Simulator * sim, int rt, int rs, int imm);

/* 
 * @brief 
 * @author kdh
 * Signed Integer Multiply
 */
void mult(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief 
 * @author kdh
 * Unsigned Integer Multiply
 */
void multu(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief 
 * @author kdh
 * Integer Divide Signed
 */
void div(MIPS32Simulator * sim, int rd, int rs, int rt);

/* 
 * @brief 
 * @author kdh
 * Integer Divide Unsigned
 */
void divu(MIPS32Simulator * sim, int rd, int rs, int rt);