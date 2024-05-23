
/*
 * Definition of pipeline register
*/

#define EMPTY 0;

typedef struct {
	int instruction;
    int pc;
}IfIdReg;

typedef struct {
    int pc;
    int rs_val;
    int rt_val;
    int rt_num;
    int rd_num;
    int imm_val;
    int rs_num;
}IdExeReg;

typedef struct {
    int br_tgt;
    int zero;
    int ALU_result;
    int rt_val;
    int rd_num;
}ExeMemReg;

typedef struct {
    int load_data; // data from memory
    int ALU_result;
    int rd_num;
}MemWbReg;
