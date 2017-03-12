.entry LENGTH
.entry STR
.extern L3
.extern L2
.extern W
MAIN: mov ***, W
		   add r2,STR
LOOP: jmp W
prn #-5
sub r1, r4
inc K
mov **,r3
bne L3
END: stop
STR: .string "abcdef"
LENGTH: .data 6,-9,15
K: .data 2
