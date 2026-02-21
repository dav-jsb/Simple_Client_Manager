SOURCES = $(wildcard ./src/*.c)

INCLUDE = -I./include

all:
	gcc $(INCLUDE) $(SOURCES) -o ./build/ClientManager

run:
	.\build\ClientManager.exe