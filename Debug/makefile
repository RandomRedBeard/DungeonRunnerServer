CC = gcc
CFLAG = -Wall -c
LFLAG = -std=c++17 -lstdc++ -lpthread -lm

OBJS = 

include src/subdir.mk
include src/iores/subdir.mk
include src/topt/subdir.mk
include src/gameres/subdir.mk
include src/gameres/itemres/subdir.mk
include src/gameres/monsterres/subdir.mk
include src/gameres/physmapres/subdir.mk

drserver: $(OBJS)
	$(CC) $(OBJS) $(LFLAG) -o drserver
clean:
	rm -f $(OBJS)
