OBJS += src/gameres/physmapres/room.o \
src/gameres/physmapres/physmap.o

src/gameres/physmapres/%.o: ../src/gameres/physmapres/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<
