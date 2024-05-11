
/*
 * Definition of pipeline register
*/

#define EMPTY 0;

typedef struct {
	int instruction;
    int pc;
}IF_ID_REG;

typedef struct {
    int pc;
    int rs_val;
    int rt_val;
    int rt_num;
    int rd_num;
    int imm_val;
}ID_EX_REG;

typedef struct {
    int br_trgt;
    int zero;
    int ALU_result;
    int rt_val;
    int rd_num;
}EX_MEM_REG;

typedef struct {
    int load_data; // data from memory
    int ALU_result;
    int rd_num;
}MEM_WB_REG;
