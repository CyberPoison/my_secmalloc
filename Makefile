SDIR = src

CC = gcc

static:
	${CC} $(SDIR)/main.c -o libmy_secmalloc.a