OBJS = $(OBJS) \
src\main.o \
src\game.o \
src\log.o

src\main.o: 
	$(CC) $(CFLAG) ..\src\main.cpp $(INCLUDES) /Fo: src\main.o
src\game.o:
	$(CC) $(CFLAG) ..\src\game.cpp $(INCLUDES) /Fo: src\game.o
src\log.o:
	$(CC) $(CFLAG) ..\src\log.cpp $(INCLUDES) /Fo: src\log.o