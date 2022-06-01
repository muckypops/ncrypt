# all: ncrypt.o
# 	gcc -o ncrypt ncrypt.o
# ncrypt.o: ncrypt.c
# 	gcc -c ncrypt.c
# clean:
# 	rm *.o ncrypt
# ^^^^ OLD MAKEFILE CODE ^^^^


CC = gcc
CPP = g++
CFLAGS = -Wall
CXXFLAGS = -Wall
BIN = ncrypt
OBJS = ncrypt.o
DEBUGHEADER = debug.h

all:$(BIN)

$(BIN):$(OBJS)
	$(CPP) $(CXXFLAGS) $^ -o $@

debug: CFLAGS += -g -DDEBUG#adds debug flags to compiler calls!
debug: CXXFLAGS += -g -DDEBUG#adds debug flags to compiler calls!
debug: clean # have to do clean compile to get debug functionality into .o OBJS
debug: all

%.o: %.c %.h $(DEBUGHEADER)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp %.h $(DEBUGHEADER)
	$(CPP) $(CXXFLAGS) -c $< -o $@
#$@ - replace with target name
#$^ - replace with all pre-requisites (w/out duplicates)
#$< - replace with first pre-requisite (%.cpp in this case)
#more info available at: https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

clean:
	$(RM) -r *.o $(BIN) 
#removed -f flag cuz it apparently is already in the RM variable

# gcc on compile has flag -D for debugging
# example is gcc -DDEBUG will define DEBUG token in source code.
# very useful
