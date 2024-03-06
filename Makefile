all:
	clang -g -fsanitize=address -Wall main.c -o main
run:
	./main
