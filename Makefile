CC = gcc
CFLAGS = -Wextra -Wall -pedantic -std=gnu99 -Iinclude
OBJ = src/main.o
MLC = src/my_secmalloc.o
FNC = src/main.c src/my_secmalloc.c src/func.c
PRJ = my_secmalloc
LIBNAME = my_secmalloc

$(PRJ): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

lib$(LIBNAME).a: $(MLC)

lib$(LIBNAME).so: CFLAGS += -fPIC
lib$(LIBNAME).so: $(MLC) #$(FNC)

all: $(PRJ)

clean: $(OBJ)
	$(RM) $(OBJ) $(MLC) *~ .*.swp

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
	#$(LINK.c) -shared $^ -o $@
	gcc -shared -fPIC $(FNC) -o $@ 

.PHONY: all clean distclean dataclean static dynamic test
