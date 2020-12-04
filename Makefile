CC=gcc
CFLAGS=-Wall -g

main: main.c
	gcc $(CFLAGS) -o main main.c