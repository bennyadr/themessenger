CFLAGS=-c -Wall
CPPFLAGS = -g -c -Wall
CC=g++
#LDFLAGS=
SOURCES= message_base.h socket.cpp ypacket.cpp main.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ymess

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@ 

clean:
	-rm printenv *~ *.o *.bak core tags
