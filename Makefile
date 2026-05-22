CC = gcc
FILES = ./src/main.c
EXECUTABLE_NAME = nine-circle
FLAGS = -Wall -I ./include -L ./lib -lraylib -lm

build: ${FILES}
	@${CC} -o ${EXECUTABLE_NAME} ${FILES} ${FLAGS}
	@mv ${EXECUTABLE_NAME} ./bin

debug: ${FILES}
	@${CC} -o ${EXECUTABLE_NAME} ${FILES} ${FLAGS} -D NINE_CIRCLE_DEBUG
	@mv ${EXECUTABLE_NAME} ./bin

wasm: ${FILES}
	@echo "TODO"