CC = gcc
CFLAGS = -Wextra -Wall  -pedantic -std=gnu99
SDIR = src
OBJ = src/main.o
PRJ = my_secmalloc
LIBNAME = my_secmalloc

$(PRJ): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

lib$(LIBNAME).a: $(OBJ)

all: $(PRJ)

clean: $(OBJ)
	$(RM) $(OBJ) *~ .*.swp

static: lib$(LIBNAME).a

distclean: clean
	$(RM) lib$(LIBNAME).a

test:
	$(CC) $(CFLAGS) test/test.c -l$(LIBNAME) -L. -o test

%.a:
	$(AR) $(ARFLAGS) $@ $^

.PHONY: all clean static test
