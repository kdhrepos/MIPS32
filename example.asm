# data hazard example asm
sub $2, $1,$3 # Register $2 written by sub
and $12,$2,$5 # 1st operand($2) depends on sub
or $13,$6,$2 # 2nd operand($2) depends on sub
add $14,$2,$2 # 1st($2) & 2nd($2) depend on sub
sw $15,100($2) # Base ($2) depends on sub