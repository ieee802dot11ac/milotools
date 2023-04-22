SRCDIR := src/

OBJDIR := obj/
BINDIR := bin/
OUTLIBDIR := $(BINDIR)/lib/

SOURCES := $(shell find "$(SRCDIR)/" -name "*.c")
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.c.o)

CC := gcc
CCARGS := -Wall -Wextra -Wpedantic -I$(SRCDIR)/include/ -g

LD := gcc
LDARGS := 

.PHONY: all cleanRun genclang run clean mkdirs

all: mkdirs $(BINDIR)/mconv
cleanRun: clean run

genclang: mkdirs
	bear -- clang -c $(CCARGS) $(SRCDIR)/meshconverter.c -o $(OBJDIR)/meshconverter.c.o
	rm $(OBJDIR)/meshconverter.c.o

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c $(CCARGS) $< -o $@

$(BINDIR)/mconv: $(OBJECTS)
	mkdir -p "$(dir $@)"
	echo "Using compiler $(CC) $(CCARGS)"
	echo "Using linker $(LD) $(LDARGS)"
	$(LD) $(LDARGS) $^ -o $@

run: $(BINDIR)/mconv Box01.mesh
	echo
	./$(BINDIR)/mconv Box01.mesh

clean:
	rm -fr $(BINDIR)/ $(OBJDIR)/ $(OUTLIBDIR)/
