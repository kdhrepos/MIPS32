
/*
 * Definition of pipeline register
*/
typedef struct {
	int instruction;
    int pc;
}IF_ID_REG;

typedef struct {
    int rs_val;
    int rt_val;
    int rt_num;
    int rd_num;
    int imm_val;
    int pc;
    int shamt;
    int funct;
}ID_EX_REG;

typedef struct {
    
}EX_MEM_REG;

typedef struct {

}MEM_WB_REG;
