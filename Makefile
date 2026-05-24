CC = gcc
FILES = ./src/main.c
EXECUTABLE_NAME = nine-circle
FLAGS = -Wall -I ./include -L ./lib

RAYLIB_FLAGS = -lraylib -lm
WASM_FLAGS = -D CLAY_WASM -D NINE_CIRCLE_WASM

build: ${FILES}
	@${CC} -o ${EXECUTABLE_NAME} ${FILES} ${FLAGS} ${RAYLIB_FLAGS}
	@mv ${EXECUTABLE_NAME} ./bin

debug: ${FILES}
	@${CC} -o ${EXECUTABLE_NAME} ${FILES} ${FLAGS} ${RAYLIB_FLAGS} -D NINE_CIRCLE_DEBUG -fsanitize=address
	@mv ${EXECUTABLE_NAME} ./bin

wasm: ${FILES}
	@echo "TODO: wasm make"