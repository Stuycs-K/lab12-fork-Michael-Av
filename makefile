.PHONY: run compile clean
compile runme: fork.o
	@gcc fork.o -Wall
run: runme
	@./a.out

fork.o: fork.c
	@gcc -c fork.c -Wall

clean:
	rm -f a.out
	rm -f fork.o
