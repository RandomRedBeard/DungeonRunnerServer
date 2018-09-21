OBJS = $(OBJS) \
src\main.o \
src\game.o \
src\log.o

src\main.o: 
	$(CC) $(CFLAG) ..\src\main.cpp /Fo: src\main.o
src\game.o:
	$(CC) $(CFLAG) ..\src\game.cpp /Fo: src\game.o
src\log.o:
	$(CC) $(CFLAG) ..\src\log.cpp /Fo: src\log.o