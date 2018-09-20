OBJS += src/gameres/monsterres/kobold.o \
src/gameres/monsterres/minion.o \
src/gameres/monsterres/monster.o \
src/gameres/monsterres/monstergen.o

src/gameres/monsterres/%.o: src/gameres/monsterres/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<
