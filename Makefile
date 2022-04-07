CC = gcc
CFLAGS = -Wextra -Wall -pedantic -std=gnu99 -Iinclude
OBJ = src/main.o
MLC = src/my_secmalloc.o
PRJ = my_secmalloc
LIBNAME = my_secmalloc
#LDLIBS = -lm

$(PRJ): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

lib$(LIBNAME).a: $(MLC)

lib$(LIBNAME).so: CFLAGS += -fPIC
lib$(LIBNAME).so: $(MLC)

all: $(PRJ)

clean: $(OBJ)
	$(RM) $(OBJ) *~ .*.swp

static: lib$(LIBNAME).a

distclean: clean
	$(RM) lib$(LIBNAME).a
	$(RM) lib$(LIBNAME).so

dynamic: lib$(LIBNAME).so

test:
	$(CC) $(CFLAGS) test/test.c lib$(LIBNAME).a -L. -o test_malloc

dataclean:
	$(RM) data.log

%.a:
	$(AR) $(ARFLAGS) $@ $^

%.so:
	$(LINK.c) -shared $^ $(LDLIBS) -o $@

.PHONY: all clean distclean dataclean static dynamic test
