OBJS += src/gameres/point.o \
src/gameres/map.o \
src/gameres/objid.o \
src/gameres/player.o \
src/gameres/probability.o \
src/gameres/protocols.o

src/gameres/%.o: ../src/gameres/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<
