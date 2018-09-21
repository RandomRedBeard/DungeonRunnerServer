OBJS = $(OBJS) \
src\iores\myPoll.o \
src\iores\io.o \
src\iores\Socket.o \
src\iores\ServerSocket.o 

src\iores\myPoll.o:
	$(CC) $(CFLAG) ..\src\iores\myPoll.cpp /Fo: src\iores\myPoll.o
src\iores\io.o:
	$(CC) $(CFLAG) ..\src\iores\io.cpp /Fo: src\iores\io.o
src\iores\Socket.o:
	$(CC) $(CFLAG) ..\src\iores\Socket.cpp /Fo: src\iores\Socket.o
src\iores\ServerSocket.o:
	$(CC) $(CFLAG) ..\src\iores\ServerSocket.cpp /Fo: src\iores\ServerSocket.o