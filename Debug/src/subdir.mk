OBJS += src/main.o src/game.o src/log.o

src/%.o: ../src/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<
