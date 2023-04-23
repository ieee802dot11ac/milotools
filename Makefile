SRCDIR := src/
OBJDIR := obj/
BINDIR := bin/

LIBSRCDIR := lib/src/
LIBOBJDIR := lib/obj/
LIBBINDIR := lib/bin/

SOURCES := $(shell find "$(SRCDIR)/" -name "*.c")
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.c.o)

LIBSOURCES := $(shell find "$(LIBSRCDIR)/" -name "*.c")
LIBOBJECTS := $(LIBSOURCES:$(LIBSRCDIR)/%.c=$(LIBOBJDIR)/%.c.o)

CC := gcc
CCARGS := -g -O3 -Wall -Wextra -Wpedantic -I$(SRCDIR)/include/ -I$(LIBSRCDIR)/include/

LD := gcc
LDARGS := 

AR := ar
ARARGS := 

.PHONY: all cleanRun genclang run clean mkdirs library binary

all: mkdirs library binary
cleanBuild: clean all
cleanRun: clean run

genclang: mkdirs
	bear -- clang -c $(CCARGS) $(SRCDIR)/mconv.c -o $(OBJDIR)/mconv.c.o
	rm $(OBJDIR)/mconv.c.o

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c $(CCARGS) $< -o $@

$(LIBOBJDIR)/%.c.o: $(LIBSRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c -fPIC $(CCARGS) $< -o $@

binary: $(BINDIR)/mconv

$(BINDIR)/mconv: $(OBJECTS)
	mkdir -p "$(dir $@)"
	echo "Using compiler $(CC) $(CCARGS)"
	echo "Using linker $(LD) $(LDARGS)"
	$(LD) $(LDARGS) $^ -o $@ -L$(LIBBINDIR)/ -lhmxobj

library: $(LIBBINDIR)/libhmxobj.so $(LIBBINDIR)/libhmxobj.a

$(LIBBINDIR)/libhmxobj.so: $(LIBOBJECTS)
	mkdir -p "$(dir $@)"
	$(LD) $(LDARGS) -shared $^ -o $@

$(LIBBINDIR)/libhmxobj.a: $(LIBOBJECTS)
	mkdir -p "$(dir $@)"
	$(AR) $(ARARGS) r $@ $^

run: $(BINDIR)/mconv Box01.mesh
	LD_LIBRARY_PATH=$(LIBBINDIR)/ ./$(BINDIR)/mconv Box01.mesh Box01.obj

clean:
	rm -fr $(BINDIR)/ $(OBJDIR)/
	rm -fr $(LIBBINDIR)/ $(LIBOBJDIR)/
