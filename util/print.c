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

void print_log(MIPS32Simulator * sim, Log log[MEM_SIZE], int log_itr)
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

        
       // Execution log
       for(int itr = 0; itr < sim->pc; itr++)
       {
              printf("║  %3d  ║     0x%08X     ║", itr*4, sim->im[itr]);
              
              int stage_flag = 0;
              int last_stage_clk = 0; // last stage clock of the instruction
              if(log[itr].IF) {stage_flag = 1; last_stage_clk = log[itr].IF_clk;}
              if(log[itr].ID) {stage_flag = 2; last_stage_clk = log[itr].ID_clk;}
              if(log[itr].EXE) {stage_flag = 3; last_stage_clk = log[itr].EXE_clk;}
              if(log[itr].MEM) {stage_flag = 4; last_stage_clk = log[itr].MEM_clk;}
              if(log[itr].WB) {stage_flag = 5; last_stage_clk = log[itr].WB_clk;}

              for(int space = 0; space < (log[itr].IF_clk - 1) * 6; space++)
                     printf(" ");

              if(stage_flag >= 1) printf("   IF ");
              if(stage_flag >= 2) printf("   ID ");
              if(stage_flag >= 3) printf("   EXE");
              if(stage_flag >= 4) printf("   MEM");
              if(stage_flag >= 5) printf("   WB ");

              for(int space = 0; space < (sim->clk - last_stage_clk) * 6; space++)
                     printf(" ");
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

void print_guideline()
{
       printf("Press [Any Key] to run\nPress [Q] to stop\n");
}