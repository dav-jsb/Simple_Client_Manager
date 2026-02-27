SOURCES = $(wildcard ./src/*.c)

INCLUDE = -I./include

LINUX_FLAG = -lpthread -ldl

C_FLAGS = -g -Wall

all:
	gcc $(INCLUDE) $(SOURCES) -o ./build/ClientManager

linux:
	gcc $(INCLUDE) $(SOURCES) $(LINUX_FLAG) -O ./build/ClientManager

debug:
	gcc $(INCLUDE) $(SOURCES) $(C_FLAGS) -o ./build/ClientManager

run:
	.\build\ClientManager.exe

clean:
	rm -rf ./build/*