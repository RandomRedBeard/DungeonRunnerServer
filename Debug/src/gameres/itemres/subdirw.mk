OBJS = $(OBJS) \
src\gameres\itemres\armor.o \
src\gameres\itemres\arrow.o \
src\gameres\itemres\axe.o \
src\gameres\itemres\bow.o \
src\gameres\itemres\ironarmor.o \
src\gameres\itemres\item.o \
src\gameres\itemres\itemgen.o \
src\gameres\itemres\leatherarmor.o \
src\gameres\itemres\longbow.o \
src\gameres\itemres\longsword.o \
src\gameres\itemres\shortsword.o \
src\gameres\itemres\steelarmor.o \
src\gameres\itemres\weapon.o \
src\gameres\itemres\woodarrow.o \
src\gameres\itemres\woodbow.o

src\gameres\itemres\armor.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\armor.cpp /Fo: src\gameres\itemres\armor.o
src\gameres\itemres\arrow.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\arrow.cpp /Fo: src\gameres\itemres\arrow.o
src\gameres\itemres\axe.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\axe.cpp /Fo: src\gameres\itemres\axe.o
src\gameres\itemres\bow.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\bow.cpp /Fo: src\gameres\itemres\bow.o
src\gameres\itemres\ironarmor.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\ironarmor.cpp /Fo: src\gameres\itemres\ironarmor.o
src\gameres\itemres\item.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\item.cpp /Fo: src\gameres\itemres\item.o
src\gameres\itemres\itemgen.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\itemgen.cpp /Fo: src\gameres\itemres\itemgen.o
src\gameres\itemres\leatherarmor.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\leatherarmor.cpp /Fo: src\gameres\itemres\leatherarmor.o
src\gameres\itemres\longbow.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\longbow.cpp /Fo: src\gameres\itemres\longbow.o
src\gameres\itemres\longsword.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\longsword.cpp /Fo: src\gameres\itemres\longsword.o
src\gameres\itemres\shortsword.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\shortsword.cpp /Fo: src\gameres\itemres\shortsword.o
src\gameres\itemres\steelarmor.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\steelarmor.cpp /Fo: src\gameres\itemres\steelarmor.o
src\gameres\itemres\weapon.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\weapon.cpp /Fo: src\gameres\itemres\weapon.o
src\gameres\itemres\woodarrow.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\woodarrow.cpp /Fo: src\gameres\itemres\woodarrow.o
src\gameres\itemres\woodbow.o:
	$(CC) $(CFLAG) ..\src\gameres\itemres\woodbow.cpp /Fo: src\gameres\itemres\woodbow.o