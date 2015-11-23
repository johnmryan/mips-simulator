SRCS = exec-main.cpp Memory.cpp RegFile.cpp Instruction.cpp global.cpp

CPP = g++
CFLAGS = 
INCLUDES = 
LFLAGS = -g
LIBS =

OBJS = $(SRCS:.cpp=.o)

all: mipsim.x

mipsim.x: $(OBJS)
	$(CPP) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

%.cpp: %.h

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f *.o *.x

depend:
	makedepend -Y --$(CFLAGS) -- $(SRCS)

# DO NOT DELETE

exec-main.o: global.h Memory.h RegFile.h Instruction.h
Memory.o: Memory.h global.h
RegFile.o: RegFile.h global.h
Instruction.o: Instruction.h global.h RegFile.h Memory.h
global.o: global.h RegFile.h Memory.h
