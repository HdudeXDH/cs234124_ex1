CC = gcc
OBJS = tool/main.o tool/AsciiArtTool.o RLEList.o
EXEC = AsciiArtTool
COMP_FLAG = -std=c99 -Wall -Werror -I/home/mtm/public/2122b/ex1 -Itool

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@
RLEList.o: RLEList.c RLEList.h
	$(CC) -c -o $@ $(COMP_FLAG) RLEList.c
tool/main.o: tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c -o $@ $(COMP_FLAG) tool/main.c
tool/AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c -o $@ $(COMP_FLAG) tool/AsciiArtTool.c
clean:
	rm -f $(OBJS) $(EXEC)
