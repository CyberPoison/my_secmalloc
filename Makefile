CC = gcc
CFLAGS = -Wextra -Wall -Werror -pedantic -std=c99
SDIR = src
OBJ = src/main.o
PRJ = my_secmalloc

$(PRJ): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

all: $(PRJ)

clean: $(OBJ)
	$(RM) $(OBJ) *~ .*.swp

static:
	${CC} $(SDIR)/main.c -o libmy_secmalloc.a

.PHONY: all clean
