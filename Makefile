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
	bear -- clang -c $(CCARGS) $(SRCDIR)/hxconv.c -o $(OBJDIR)/hxconv.c.o
	rm $(OBJDIR)/hxconv.c.o

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c $(CCARGS) $< -o $@

$(LIBOBJDIR)/%.c.o: $(LIBSRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c -fPIC $(CCARGS) $< -o $@

binary: library $(BINDIR)/hxconv

$(BINDIR)/hxconv: $(OBJECTS)
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

run: binary _input/Box01.hxmesh
	LD_LIBRARY_PATH=$(LIBBINDIR)/ ./$(BINDIR)/hxconv _input/Box01.hxmesh _output/Box01.obj
	LD_LIBRARY_PATH=$(LIBBINDIR)/ ./$(BINDIR)/hxconv _input/particle_board_mip.hxtex _output/particle_board_mip.pam

clean:
	rm vgcore*
	rm -fr $(BINDIR)/ $(OBJDIR)/
	rm -fr $(LIBBINDIR)/ $(LIBOBJDIR)/
