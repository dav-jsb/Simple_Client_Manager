SOURCES = $(wildcard ./src/*.c)

INCLUDE = -I./include

LINUX_FLAG = -lpthread -ldl

all:
	gcc $(INCLUDE) $(SOURCES) -o ./build/ClientManager

linux:
	gcc $(INCLUDE) $(SOURCES) $(LINUX_FLAG) -O ./build/ClientManager

run:
	.\build\ClientManager.exe

clean:
	rm -rf ./build/*