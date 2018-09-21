OBJS = $(OBJS) \
src\gameres\physmapres\room.o \
src\gameres\physmapres\physmap.o

src\gameres\physmapres\room.o:
	$(CC) $(CFLAG) ..\src\gameres\physmapres\room.cpp /Fo: src\gameres\physmapres\room.o
src\gameres\physmapres\physmap.o:
	$(CC) $(CFLAG) ..\src\gameres\physmapres\physmap.cpp /Fo: src\gameres\physmapres\physmap.o