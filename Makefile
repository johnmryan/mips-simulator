SRCS = main.cpp Instruction.cpp

CPP = g++
CFLAGS = 
INCLUDES = 
LFLAGS = -g
LIBS =

OBJS = $(SRCS:.cpp=.o)

all: decode.x

decode.x: $(OBJS)
	$(CPP) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

%.cpp: %.h

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f *.o *.x

main.o: Instruction.h
Instruction.o: Instruction.h
