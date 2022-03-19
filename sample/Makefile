CXX=g++
CXXFLAGS=-Wall -Werror #-fno-stack-clash-protection
PRJ=heap_overflow_from_file
OBJ=${PRJ}.o

${PRJ}: ${OBJ}

all: ${PRJ}

clean:
	${RM} ${OBJ}

.PHONY: all clean

%: %.cc
	${LINK.cc} $< -o $@
