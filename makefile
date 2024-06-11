CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -g

Hello: hello.c
	${CC} ${CFLAGS} -o $@ $^