# Makefile for suid_chmod.c
suid_chmod: suid_chmod.c
	gcc -Wall -O2 -o suid_chmod suid_chmod.c

