LIB           = libpgn

CC            = gcc
CFLAGS        = -std=c99 -pedantic-errors -Wall -Wextra

LD            = ld
LDLIBS        = 
LDFLAGS       =

INST          = /usr

SRC          := $(wildcard *.c)
DEPS         := $(SRC:.c=.h)
OBJ          := $(SRC:.c=.o)

all: $(LIB)

$(LIB): $(OBJ)
	$(LD) $(LDLIBS) -shared $^ -o $(LIB).so

install: $(LIB)
	mkdir -p $(INST)/include/pgn
	cp *.h $(INST)/include/pgn
	cp $(LIB).so $(INST)/lib

uninstall:
	$(RM) $(INST)/lib/$(LIB).so
	$(RM) -r $(INST)/include/pgn

# Assuming every file
# depens on header DEPS
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	$(RM) $(OBJ) $(LIB).so

.PHONY: clean all $(LIB) install uninstall
