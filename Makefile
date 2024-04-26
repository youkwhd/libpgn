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
	LD      := $(CC)
	EXT     := .dll
endif

all: $(LIB)

$(LIB): $(OBJ)
	$(LD) $(LDLIBS) $(LDFLAGS) -shared $^ -o $(LIB)$(EXT)

install: $(LIB)
	mkdir -p $(INST)/include/pgn
	cp *.h $(INST)/include/pgn
	cp $(LIB)$(EXT) $(INST)/lib

uninstall:
	$(RM) $(INST)/lib/$(LIB)$(EXT)
	$(RM) -r $(INST)/include/pgn

# Assuming every file
# depens on header DEPS
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	$(RM) $(OBJ) $(LIB)$(EXT)

.PHONY: clean all $(LIB) install uninstall
