SRCS = mem-reg-main.cpp Memory.cpp RegFile.cpp

CPP = g++
CFLAGS = 
INCLUDES = 
LFLAGS = -g
LIBS =

OBJS = $(SRCS:.cpp=.o)

all: mem-reg.x

mem-reg.x: $(OBJS)
	$(CPP) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

%.cpp: %.h

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f *.o *.x

depend:
	makedepend -Y --$(CFLAGS) -- $(SRCS)

# DO NOT DELETE

mem-reg-main.o: global.h Memory.h
Memory.o: Memory.h global.h
RegFile.o: RegFile.h global.h