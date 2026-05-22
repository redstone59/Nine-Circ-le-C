CC=gcc
FILES=./src/main.c

build: ${FILES}
	${CC} -o nine-circle -Wall ${FILES} -I ./include -L ./lib -lraylib -lm	