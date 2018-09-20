OBJS = $(OBJS) \
src\topt\topt.o

src\topt\topt.o:
	$(CC) $(CFLAG) ..\src\topt\topt.cpp /Fo: src\topt\topt.o