all: clean bin/meshconverter run

bin/meshconverter:
	mkdir -p bin/
	gcc -g meshconverter.c -o bin/meshconverter

run: bin/meshconverter Box01.mesh
	./bin/meshconverter Box01.mesh

clean:
	rm -fr bin/
