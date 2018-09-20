OBJS += src/topt/topt.o

src/topt/%.o: ../src/topt/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<
