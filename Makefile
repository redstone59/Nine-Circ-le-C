CC = gcc
FILES = ./src/main.c
EXECUTABLE_NAME = nine-circle

build: ${FILES}
	@${CC} -o ${EXECUTABLE_NAME} -Wall ${FILES} -I ./include -L ./lib -lraylib -lm
	@mv ${EXECUTABLE_NAME} ./bin