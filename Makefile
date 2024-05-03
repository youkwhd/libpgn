LIB           = libpgn
EXT           = .so

CC            = gcc
CFLAGS        = -std=c99 -pedantic-errors -Wall -Wextra

LD            = ld
LDLIBS        = 
LDFLAGS       =

INST          = /usr

SRC          := $(wildcard *.c)
DEPS         := $(SRC:.c=.h)
OBJ          := $(SRC:.c=.o)

ifeq ($(OS), Windows_NT)
	LD  := $(CC)
	EXT := .dll
endif

all: $(LIB)

$(LIB): $(OBJ)
	$(LD) $(LDLIBS) $(LDFLAGS) -shared $^ -o $(LIB)$(EXT)

TESTS        := $(wildcard tests/*.c)
EXE          := $(TESTS:.c=)

test: $(LIB) $(EXE)

$(EXE):
	$(CC) $@.c -lpgn -L. -I. -o $@
	./$@

install: $(LIB)
	mkdir -p $(INST)/include/pgn
	cp *.h $(INST)/include/pgn
	sed -i $(INST)/include/pgn/pgn.h -e "s/#include \"/#include \"pgn\//g"
	mv $(INST)/include/pgn/pgn.h $(INST)/include
	cp $(LIB)$(EXT) $(INST)/lib

uninstall:
	$(RM) $(INST)/lib/$(LIB)$(EXT)
	$(RM) -r $(INST)/include/pgn
	$(RM) $(INST)/include/pgn.h

# Assuming every file
# depens on header DEPS
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	$(RM) $(OBJ) $(LIB)$(EXT)

.PHONY: clean all $(LIB) install uninstall test
