CC = gcc
OBJS = main.o AsciiArtTool.o RLEList.o
EXEC = AsciiArtTool
COMP_FLAG = -std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
AsciiArtTool.o: tool/AsciiArtTool.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/AsciiArtTool.c
RLEList.o: RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) RLEList.c
main.o: tool/main.c tool/AsciiArtTool.h RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tool/main.c
clean:
	rm -f $(OBJS) $(EXEC)
