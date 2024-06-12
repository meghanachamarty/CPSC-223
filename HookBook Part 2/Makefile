PROJ_NAME=HookBook
CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g

HookBook: hookbook.o pirate_list.o
	${CC} ${CFLAGS} -o $@ $^ -lm

main.o: hookbook.c pirate.h pirate_list.h
	${CC} ${CFLAGS} -c $< -o $@

pirate_list.o: pirate_list.c pirate_list.h pirate.h
	${CC} ${CFLAGS} -c $< -o $@