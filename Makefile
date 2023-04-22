all: bin/mconv

CC := gcc
CCARGS := -Wall -Wextra -Wpedantic -Isrc/include/

LD := gcc
LDARGS := 

genclang: mkdirs
	bear -- clang -c $(CCARGS) src/meshconverter.c -o obj/meshconverter.c.o
	rm obj/meshconverter.c.o

bin/mconv: mkdirs
	echo "Using compiler $(CC) $(CCARGS)"
	echo "Using linker $(LD) $(LDARGS)"
	$(CC) -c $(CCARGS) src/meshconverter.c -o obj/meshconverter.c.o
	$(LD) $(LDARGS) obj/meshconverter.c.o -o bin/mconv

run: bin/mconv Box01.mesh
	./bin/mconv Box01.mesh

clean:
	rm -fr bin/ obj/

mkdirs:
	mkdir -p bin/ obj/
