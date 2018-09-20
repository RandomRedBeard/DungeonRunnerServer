OBJS += src/iores/myPoll.o \
src/iores/io.o \
src/iores/Socket.o \
src/iores/ServerSocket.o

src/iores/%.o: ../src/iores/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<

