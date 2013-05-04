#!/bin/sh

as asm/out.s -o asm/out.o
as lib/print.s -o asm/print.o
ld -o asm/out asm/out.o asm/print.o
rm asm/*.o
asm/out
