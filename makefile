CFLAGS=-std=c99
prog: AsciiArtTool.o main.o RLEList.o
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
main.o: main.c AsciiArtTool.h RLEList.h
RLEList.o: RLEList.c RLEList.h

