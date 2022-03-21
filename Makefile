CC = gcc
CFLAGS = -Wextra -Wall -Werror -pendantic -std=c99
SDIR = src
OBJ = *.o
PRJ = my_secmalloc

$(PRJ): $(OBJ)
^I$(CC) $(CFLAGS) $^ -o $@

all: $(PRJ)

clean: $(OBJ)
^I$(RM) $(OBJ) *~ .*.swp

static:
^I${CC} $(SDIR)/main.c -o libmy_secmalloc.a

.PHONY: all clean
