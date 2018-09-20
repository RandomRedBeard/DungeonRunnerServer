OBJS = $(OBJS) \
src\gameres\monsterres\minion.o \
src\gameres\monsterres\monster.o \
src\gameres\monsterres\kobold.o \
src\gameres\monsterres\monstergen.o

src\gameres\monsterres\minion.o:
	$(CC) $(CFLAG) ..\src\gameres\monsterres\minion.cpp /Fo: src\gameres\monsterres\minion.o
src\gameres\monsterres\monster.o:
	$(CC) $(CFLAG) ..\src\gameres\monsterres\monster.cpp /Fo: src\gameres\monsterres\monster.o
src\gameres\monsterres\kobold.o:
	$(CC) $(CFLAG) ..\src\gameres\monsterres\kobold.cpp /Fo: src\gameres\monsterres\kobold.o
src\gameres\monsterres\monstergen.o:
	$(CC) $(CFLAG) ..\src\gameres\monsterres\monstergen.cpp /Fo: src\gameres\monsterres\monstergen.o