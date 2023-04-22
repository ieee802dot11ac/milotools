all: bin/mconv
cleanRun: clean run

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
	$(CC) -c $(CCARGS) src/hmxmesh.c -o obj/hmxmesh.c.o
	$(CC) -c $(CCARGS) src/hmxenums.c -o obj/hmxenums.c.o
	$(CC) -c $(CCARGS) src/hmxreference.c -o obj/hmxreference.c.o
	$(CC) -c $(CCARGS) src/hmxtransform.c -o obj/hmxtransform.c.o
	$(LD) $(LDARGS) obj/*.c.o -o bin/mconv

run: bin/mconv Box01.mesh
	./bin/mconv Box01.mesh

clean:
	rm -fr bin/ obj/

mkdirs:
	mkdir -p bin/ obj/
