OBJS += src/gameres/itemres/armor.o \
src/gameres/itemres/arrow.o \
src/gameres/itemres/axe.o \
src/gameres/itemres/bow.o \
src/gameres/itemres/ironarmor.o \
src/gameres/itemres/item.o \
src/gameres/itemres/itemgen.o \
src/gameres/itemres/leatherarmor.o \
src/gameres/itemres/longbow.o \
src/gameres/itemres/longsword.o \
src/gameres/itemres/shortsword.o \
src/gameres/itemres/steelarmor.o \
src/gameres/itemres/weapon.o \
src/gameres/itemres/woodarrow.o \
src/gameres/itemres/woodbow.o

src/gameres/itemres/%.o: ../src/gameres/itemres/%.cpp
	$(CC) $(CFLAG) $(LFLAG) -o $@ $<
