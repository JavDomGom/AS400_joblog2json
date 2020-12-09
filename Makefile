CC=gcc
CFLAGS=-Wall -g
PROGRAM_NAME=main
DEPS=joblogreader.c joblogreader.h

main: $(PROGRAM_NAME).c $(DEPS)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(PROGRAM_NAME).c $(DEPS)