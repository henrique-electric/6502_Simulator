all: cpu.o mem.o instructions.o
	gcc cpu.o instructions.o mem.o src/main.c -o main
	./main

cpu.o: src/cpu/cpu.c 
	gcc -c src/cpu/cpu.c
	

mem.o: src/mem.c
	gcc -c src/mem.c 

instructions.o: src/cpu/instructions.c
	gcc -c src/cpu/instructions.c
