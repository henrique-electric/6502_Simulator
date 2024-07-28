all: src/cpu.c src/mem.c
	@gcc -c src/cpu.c -o obj/cpu.o
	@gcc -c src/mem.c -o obj/mem.o
	@gcc src/main.c obj/cpu.o obj/mem.o -o main
	@clear
	@./main
