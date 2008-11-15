CFLAGS=-c -Wall
CPPFLAGS = -g -c -Wall
CC=g++
SOURCES= sha.cpp md5.cpp magic_shit.cpp ypacket.cpp socket.cpp buddy_list.cpp login.cpp priorityQueue.cpp yinstance.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ymess

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CPPFLAGS) $< -o $@

clean:
		-rm printenv *~ *.o *.bak core tags
tags:
		-etags *.cpp *.h


