#pragma once

#include "../core.h"

typedef struct{
    int address; /* instruction address */
    boolean IF; int IF_clock; /* denotes inst. was executed or not on IF stage and what clock inst. was executed */
    boolean ID; int ID_clock; /* denotes inst. was executed or not on ID stage and what clock inst. was executed */
    boolean EXE; int EXE_clock; /* denotes inst. was executed or not on EXE stage and what clock inst. was executed */
    boolean MEM; int MEM_clock; /* denotes inst. was executed or not on MEM stage and what clock inst. was executed */
    boolean WB; int WB_clock; /* denotes inst. was executed or not on WB stage and what clock inst. was executed */
    boolean end; /* denotes inst. was ended or not */
}History;

