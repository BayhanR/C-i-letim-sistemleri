@echo off
gcc -S ex1.c -o ex1.s
gcc -c ex1.s -o ex1.o
gcc ex1.o -o ex1.exe
ex1.exe
%output%