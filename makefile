# Makefile for suid_chmod.c
suid_chmod: suid_chmod.o change_own.o change_mod.o
	gcc -Wall -O2 -o suid_chmod suid_chmod.o change_own.o change_mod.o

suid_chmod.o: suid_chmod.c
	gcc -c suid_chmod.c
change_own.o: change_own.c
	gcc  -c change_own.c
change_mod: change_mod.c
	gcc  -c change_mod.c
