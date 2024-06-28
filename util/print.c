#include "print.h"

void print_pipeline_register(MIPS32Simulator * sim)
{   
    printf("╔════════════════════╦════════════[CONTROL SIGNALS]════════════╦════════════════════╗\n");
    printf("║      [IF/ID]       ║      [ID/EX]       ║      [EX/MEM]      ║      [MEM/WB]      ║\n");
    printf("║════════════════════╬════════════════════╬════════════════════╬════════════════════║\n");
    printf("║                    ║     MEM_TO_REG=[%d] ║     MEM_TO_REG=[%d] ║     MEM_TO_REG=[%d] ║\n", sim->id_ex_ctrl.MemtoReg, sim->ex_mem_ctrl.MemtoReg, sim->mem_wb_ctrl.MemtoReg);
    printf("║                    ║      REG_WRITE=[%d] ║      REG_WRITE=[%d] ║      REG_WRITE=[%d] ║\n", sim->id_ex_ctrl.RegWrite, sim->ex_mem_ctrl.RegWrite, sim->mem_wb_ctrl.RegWrite);
    printf("║                    ║         BRANCH=[%d] ║         BRANCH=[%d] ║                    ║\n", sim->id_ex_ctrl.Branch, sim->ex_mem_ctrl.Branch);
    printf("║                    ║       MEM_READ=[%d] ║       MEM_READ=[%d] ║                    ║\n", sim->id_ex_ctrl.MemRead, sim->ex_mem_ctrl.MemRead);
    printf("║                    ║      MEM_WRITE=[%d] ║      MEM_WRITE=[%d] ║                    ║\n", sim->id_ex_ctrl.MemWrite, sim->ex_mem_ctrl.MemWrite);
    printf("║                    ║        REG_DST=[%d] ║                    ║                    ║\n", sim->id_ex_ctrl.RegDst);
    printf("║                    ║        ALU_SRC=[%d] ║                    ║                    ║\n", sim->id_ex_ctrl.ALUSrc);
    printf("║                    ║       ALU_OP=[%03b] ║                    ║                    ║\n", sim->id_ex_ctrl.ALUOp);
    printf("╠════════════════════╬═══════════[PIPELINE REGISTERS]══════════╬════════════════════╣\n");
    printf("║     NPC=[%08X] ║     NPC=[%08X] ║  BR_TGT=[%08X] ║                    ║\n", sim->if_id_reg.pc, sim->id_ex_reg.pc, sim->ex_mem_reg.br_tgt);
    printf("║                    ║       A=[%08X] ║    ZERO=[%08X] ║     LMD=[%08X] ║\n", sim->id_ex_reg.rs_val, sim->ex_mem_reg.zero, sim->mem_wb_reg.load_data);
    printf("║      IR=[%08X] ║       B=[%08X] ║ ALU_OUT=[%08X] ║                    ║\n",  sim->if_id_reg.instruction, sim->id_ex_reg.rt_val, sim->ex_mem_reg.ALU_result);
    printf("║                    ║      RT=[%08X] ║       B=[%08X] ║ ALU_OUT=[%08X] ║\n", sim->id_ex_reg.rt_num, sim->ex_mem_reg.rt_val, sim->mem_wb_reg.ALU_result);
    printf("║                    ║      RD=[%08X] ║      RD=[%08X] ║      RD=[%08X] ║\n", sim->id_ex_reg.rd_num, sim->ex_mem_reg.rd_num, sim->mem_wb_reg.rd_num);
    printf("║                    ║     IMM=[%08X] ║                    ║                    ║\n", sim->id_ex_reg.imm_val);
    printf("║                    ║      RS=[%08X] ║                    ║                    ║\n", sim->id_ex_reg.rs_num);
    printf("╚════════════════════╩════════════════════╩════════════════════╩════════════════════╝\n");
}

void print_reg_file(MIPS32Simulator * sim)
{
    printf("╔════════════════════╦═══════════════[REGISTERS]═══════════════╦════════════════════╗\n");
    printf("║ $00[ 0]=[%08X] ║ $t0[ 8]=[%08X] ║ $s0[16]=[%08X] ║ $t8[24]=[%08X] ║\n", 
           sim->reg_file[0], sim->reg_file[8], sim->reg_file[16], sim->reg_file[24]);
    printf("║ $at[ 1]=[%08X] ║ $t1[ 9]=[%08X] ║ $s1[17]=[%08X] ║ $t9[25]=[%08X] ║\n", 
           sim->reg_file[1], sim->reg_file[9], sim->reg_file[17], sim->reg_file[25]);
    printf("║ $v0[ 2]=[%08X] ║ $t2[10]=[%08X] ║ $s2[18]=[%08X] ║ $k0[26]=[%08X] ║\n", 
           sim->reg_file[2], sim->reg_file[10], sim->reg_file[18], sim->reg_file[26]);
    printf("║ $v1[ 3]=[%08X] ║ $t3[11]=[%08X] ║ $s3[19]=[%08X] ║ $k1[27]=[%08X] ║\n", 
           sim->reg_file[3], sim->reg_file[11], sim->reg_file[19], sim->reg_file[27]);
    printf("║ $a0[ 4]=[%08X] ║ $t4[12]=[%08X] ║ $s4[20]=[%08X] ║ $gp[28]=[%08X] ║\n", 
           sim->reg_file[4], sim->reg_file[12], sim->reg_file[20], sim->reg_file[28]);
    printf("║ $a1[ 5]=[%08X] ║ $t5[13]=[%08X] ║ $s5[21]=[%08X] ║ $sp[29]=[%08X] ║\n", 
           sim->reg_file[5], sim->reg_file[13], sim->reg_file[21], sim->reg_file[29]);
    printf("║ $a2[ 6]=[%08X] ║ $t6[14]=[%08X] ║ $s6[22]=[%08X] ║ $fp[30]=[%08X] ║\n", 
           sim->reg_file[6], sim->reg_file[14], sim->reg_file[22], sim->reg_file[30]);
    printf("║ $a3[ 7]=[%08X] ║ $t7[15]=[%08X] ║ $s7[23]=[%08X] ║ $ra[31]=[%08X] ║\n", 
           sim->reg_file[7], sim->reg_file[15], sim->reg_file[23], sim->reg_file[31]);
    printf("╚════════════════════╩════════════════════╩════════════════════╩════════════════════╝\n");
}

void print_log(MIPS32Simulator * sim, Log log[MEM_SIZE])
{
       // First Line
       printf("╔═══════╦════════════════════╦");
       for(int bar = 0; bar <= sim->clk * 6; bar++)
              printf("═");            
       printf("╗\n");
       
       // Header 
       printf("║  Mem  ║     Instruction    ║ ");
       for(int clk = 1; clk <= sim->clk; clk++)
              printf("%3d   ", clk); 
       printf("║\n");

       printf("╠═══════╬════════════════════╬");
       for(int bar = 0; bar <= 6 * sim->clk; bar++)
              printf("═");            
       printf("╣\n");

       int last_inst_clk = 1;
       int last_inst_itr = sim->log_itr - 1;
       if(log[last_inst_itr].IF) last_inst_clk = log[last_inst_itr].IF_clk;
       if(log[last_inst_itr].ID) last_inst_clk = log[last_inst_itr].ID_clk;
       if(log[last_inst_itr].EXE) last_inst_clk = log[last_inst_itr].EXE_clk;
       if(log[last_inst_itr].MEM) last_inst_clk = log[last_inst_itr].MEM_clk;
       if(log[last_inst_itr].WB) last_inst_clk = log[last_inst_itr].WB_clk;

       // print execution log
       for(int itr = 0; itr <= last_inst_itr; itr++)
       {
              printf("║  %3d  ║     0x%08X     ║", itr*4, log[itr].instruction);

              int clk = 1;
              int stage_ptr = 0; /* IF : 0, ID : 1, EXE : 2, MEM : 3, WB : 4 */
              int stage_clk[] = {log[itr].IF_clk, log[itr].ID_clk, log[itr].EXE_clk, log[itr].MEM_clk, log[itr].WB_clk}; /* clock cycle for each stage */
              char * stage_str[] = {"IF ", "ID ", "EXE", "MEM", "WB "};

              while(clk <= last_inst_clk)
              {
                     if(stage_clk[stage_ptr] == clk) 
                            printf("   %s", stage_str[stage_ptr++]);
                     else 
                     {
                            // instruction was started but ain't done,
                            // but empty clock occurred -> insert NOP
                            if(stage_ptr > 0 && stage_ptr < 5)
                                   printf("  !NOP");
                            else /* print the space */
                                   for(int space = 0; space < 6; space++) printf(" ");

                     }
                     clk++;
              }
              printf(" ║\n");
       }
       
       // Last Line 
       printf("╚═══════╩════════════════════╩");
       for(int bar = 0; bar <= sim->clk * 6; bar++)
              printf("═");     
       printf("╝\n");
}

void print_data_memory(MIPS32Simulator * sim)
{      
       printf("╔═══════════════════════╦═══════════════════[MEMORY]════════════════════╦═══════════════════════╗\n");
       for(int i = 0; i < 60; i += 4)
              printf("║ [%08x]=[%08x] ║ [%08x]=[%08x] ║ [%08x]=[%08x] ║ [%08x]=[%08x] ║\n",
              i*4, sim->dm[i],
              (i+1)*4, sim->dm[i+1],
              (i+2)*4, sim->dm[i+2],
              (i+3)*4, sim->dm[i+3]);

       printf("╚═══════════════════════╩═══════════════════════╩═══════════════════════╩═══════════════════════╝\n");
}

void print_forwarding(MIPS32Simulator * sim, Log log[MEM_SIZE], char * msg)
{
       int EXE_log_itr = sim->EXE_log_itr;
       int MEM_log_itr = sim->MEM_log_itr;
       int WB_log_itr = sim->WB_log_itr;

       if(strcmp(msg, "EXE")==0)
       {
              printf("╔═══════════════════════════════════════════╗\n");
              printf("║ [!] EXE Forward, 0x%08X -> 0x%08X ║\n", 
              log[MEM_log_itr].instruction, log[EXE_log_itr].instruction);
              printf("╚═══════════════════════════════════════════╝\n");
       }
       if (strcmp(msg, "MEM")==0)
       {
              printf("╔═══════════════════════════════════════════╗\n");
              printf("║ [!] MEM Forward, 0x%08X -> 0x%08X ║\n", 
              log[WB_log_itr].instruction, log[EXE_log_itr].instruction);
              printf("╚═══════════════════════════════════════════╝\n");
       }
}

void print_ld_hazard(MIPS32Simulator * sim, Log log[MEM_SIZE])
{
       int IF_log_itr = sim->log_itr;
       int ID_log_itr = sim->ID_log_itr;
       int EXE_log_itr = sim->EXE_log_itr;

       printf("╔══════════════════════════════════════════════════════╗\n");
       printf("║ [!]  Load-use Data Hazard, 0x%08X -> 0x%08X  ║\n", 
       log[EXE_log_itr].instruction, log[ID_log_itr].instruction);
       printf("╚══════════════════════════════════════════════════════╝\n");
}

void print_guideline()
{
       printf("Press [Any Key] to run\nPress [E] to exit\n");
}