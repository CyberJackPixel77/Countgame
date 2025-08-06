CC = gcc
HEADER = src/Countgame.h
OBJECTS = Countgame.o gamesaves.o filecheck.o main.o countgame-ico.o

all: Countgame.exe

Countgame.exe: $(OBJECTS)
	$(CC) $(OBJECTS) -o Countgame.exe

Countgame.o: src/Countgame.c $(HEADER)
	$(CC) -c src/Countgame.c -o Countgame.o

filecheck.o: src/filecheck.c $(HEADER)
	$(CC) -c src/filecheck.c -o filecheck.o

gamesaves.o: src/gamesaves.c $(HEADER)
	$(CC) -c src/gamesaves.c -o gamesaves.o

main.o: src/main.c $(HEADER)
	$(CC) -c src/main.c -o main.o

countgame-ico.o: src/countgame-ico.rc
	windres src/countgame-ico.rc -O coff -o countgame-ico.o

.INTERMEDIATE: $(OBJECTS)