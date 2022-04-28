CC = gcc
OBJS = main.o RLEList.o AsciiArtTool.o
EXEC = AsciiArtTool
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
PATH = /home/mtm/public/2122b/ex1


$(EXEC): $(OBJS)
	$(CC) -g $(OBJS) -o $@

main.o: main.c RLEList.h AsciiArtTool.h
	$(CC) -c $(CFLAGS) $*.c


RLEList.o: RLEList.c RLEList.h AsciiArtTool.h
	$(CC) -c $(CFLAGS) $*.c


AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h
	$(CC) -c $(CFLAGS) $*.c


clean:
	rm -f $(OBJS) $(EXEC)

