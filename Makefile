all: build

build: src/chessviz.c
	gcc -Wall -Werror -o bin/chessviz src/chessviz.c

clean: bin/chessviz
	rm bin/chessviz

run: bin/chessviz
	./bin/chessviz
