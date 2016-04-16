#gcc -I"/usr/include/SDL" -c sdldemo.c
#gcc sdldemo.o -lSDL -lm -o sdldemo
CC=g++
INCLUDES=-I"/usr/include/SDL/"
CFLAGS=$(INCLUDES) -c
LDFLAGS= -lSDL -lm
SOURCES=sdl_gol_main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=cellauto

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
