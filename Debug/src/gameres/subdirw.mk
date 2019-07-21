OBJS = $(OBJS) \
src\gameres\map.o \
src\gameres\objid.o \
src\gameres\player.o \
src\gameres\probability.o \
src\gameres\protocols.o \
src\gameres\point.o \
src\gameres\attr.o

src\gameres\map.o:
	$(CC) $(CFLAG) ..\src\gameres\map.cpp $(INCLUDES) /Fo: src\gameres\map.o
src\gameres\objid.o:
	$(CC) $(CFLAG) ..\src\gameres\objid.cpp $(INCLUDES) /Fo: src\gameres\objid.o
src\gameres\player.o:
	$(CC) $(CFLAG) ..\src\gameres\player.cpp $(INCLUDES) /Fo: src\gameres\player.o
src\gameres\probability.o:
	$(CC) $(CFLAG) ..\src\gameres\probability.cpp $(INCLUDES) /Fo: src\gameres\probability.o
src\gameres\protocols.o:
	$(CC) $(CFLAG) ..\src\gameres\protocols.cpp $(INCLUDES) /Fo: src\gameres\protocols.o
src\gameres\point.o:
	$(CC) $(CFLAG) ..\src\gameres\point.cpp $(INCLUDES) /Fo: src\gameres\point.o
src\gameres\attr.o:
	$(CC) $(CFLAG) ..\src\gameres\attr.cpp $(INCLUDES) /Fo: src\gameres\attr.o