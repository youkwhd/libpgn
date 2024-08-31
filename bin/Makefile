EXE     = pgn

CC      = cc
CFLAGS  = -std=c99 -Wall -Wextra

LD      = cc
LDLIBS  = -lpgn

SRC    := $(wildcard *.c)
DEPS   := $(wildcard *.h)
OBJ    := $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(LD) $(LDLIBS) -Wl,-rpath=$(shell pwd)/.. -L.. $^ -o $(EXE)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -I.. -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXE)

.PHONY: $(EXE) clean
