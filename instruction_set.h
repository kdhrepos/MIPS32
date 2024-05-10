/*
 * instruction_set.h
 * 
 * Name : Opcode (hex)
*/

// R-Type Instructions, Function code
#define RTYPEOP 0x0
#define ADD	0x20
#define ADDU 0x21
#define AND	0x24
#define JR	0x8
#define NOR 0x27
#define OR	0x25
#define SLT	0x2A
#define SLTU 0x2B
#define SLL	0x0
#define SRL	0x2
#define SUB	0x22
#define SUBU 0x23

// I-Type Instructions, Opcode
/* Store */
#define SH 0x29
#define SW	0x2B
#define SB 0x28
/* Load */
#define LBU 0x24
#define LW	0x23
#define LHU 0x25
/* Branch */
#define BEQ	0x4
#define BNE	0x5
/* Constant */
#define ADDI 0x8
#define ADDIU 0x9
#define ANDI 0xC
#define LUI	0xF
#define ORI	0xD
#define SLTI 0xA
#define SLTIU 0xB
/* Synchronization */
#define LL 0x30
#define SC 0x38

// J-Type Instructions
#define J	0x2
#define JAL	0x3