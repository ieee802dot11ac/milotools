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
	bear -- clang -c $(CCARGS) $(SRCDIR)/miloconv.c -o $(OBJDIR)/miloconv.c.o
	rm $(OBJDIR)/miloconv.c.o

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c $(CCARGS) $< -o $@

$(LIBOBJDIR)/%.c.o: $(LIBSRCDIR)/%.c
	mkdir -p "$(dir $@)"
	$(CC) -c -fPIC $(CCARGS) $< -o $@

binary: library $(BINDIR)/miloconv

$(BINDIR)/miloconv: $(OBJECTS)
	mkdir -p "$(dir $@)"
	echo "Using compiler $(CC) $(CCARGS)"
	echo "Using linker $(LD) $(LDARGS)"
	$(LD) $(LDARGS) $^ -o $@ -L$(LIBBINDIR)/ -lmilo_obj

library: $(LIBBINDIR)/libmilo_obj.so $(LIBBINDIR)/libmilo_obj.a

$(LIBBINDIR)/libmilo_obj.so: $(LIBOBJECTS)
	mkdir -p "$(dir $@)"
	$(LD) $(LDARGS) -shared $^ -o $@

$(LIBBINDIR)/libmilo_obj.a: $(LIBOBJECTS)
	mkdir -p "$(dir $@)"
	$(AR) $(ARARGS) r $@ $^

run: binary _input/Box01.milomesh _input/particle_board_mip.milotex
	LD_LIBRARY_PATH=$(LIBBINDIR)/ ./$(BINDIR)/miloconv _input/Box01.milomesh _output/Box01.obj
	LD_LIBRARY_PATH=$(LIBBINDIR)/ ./$(BINDIR)/miloconv _input/particle_board_mip.milotex _output/particle_board_mip.pam

clean:
	rm -f vgcore*
	rm -fr $(BINDIR)/ $(OBJDIR)/
	rm -fr $(LIBBINDIR)/ $(LIBOBJDIR)/
