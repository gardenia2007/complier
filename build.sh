#!/bin/sh

Debug/complier 
as -gstabs asm/out.s -o asm/out.o 
as -gstabs lib/print.s -o asm/print.o 
as -gstabs lib/common.s -o asm/common.o 
ld -o asm/out asm/out.o asm/print.o asm/common.o 
rm asm/*.o 
asm/out
