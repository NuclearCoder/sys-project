# -- constants

C_FILES = $(wildcard src/*.c)
OBJ_FILES = $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

DIST_NAME = ProjetS6

# -- make flags

#CC = clang
LDFLAGS = -pthread -lrt
CFLAGS = -std=c11 -pedantic -Wall -Wextra -Wconversion -Werror -fstack-protector-all -fPIC -D_XOPEN_SOURCE=700 -g -O2 -pthread

prefix = $(HOME)/
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin
libdir = $(prefix)/lib

# -- rules

.PHONY: all clean re install uninstall dist
.SECONDARY: $(OBJ_FILES)

all: main

# compiling in two steps with .o intermediary files is slower but allows for incremental compilation

main: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

obj/%.o: src/%.c
	@mkdir -p obj/
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -f $(OBJ_FILES)
	@rm -f main

re: clean all


install: main
	@mkdir -p $(bindir)
	@cp main $(bindir)


uninstall:
	@rm -f $(bindir)/main

dist: 
	@rm -f $(DIST_NAME).zip
	@zip -r $(DIST_NAME).zip src/
	@zip $(DIST_NAME).zip Makefile
