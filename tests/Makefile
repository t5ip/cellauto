CC=g++
#INCLUDES=-I"/usr/include/SDL/"
CFLAGS=$(INCLUDES) -c -g
#LDFLAGS= -lSDL -lm -lconfig++
SOURCES=catch_main.cpp ../cellautomaton.cpp ../grid.cpp cellautomaton_test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
