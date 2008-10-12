CFLAGS=-c -Wall
CPPFLAGS = -g -c -Wall
CC=g++
#LDFLAGS=
SOURCES= sha.c md5.c magic_shit.cpp ypacket.cpp socket.cpp  login.cpp priorityQueue.cpp thread.cpp main.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ymess

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@ 

clean:
	-rm printenv *~ *.o *.bak core tags
