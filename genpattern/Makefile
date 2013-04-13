CC = g++
CFLAGS = -O2 -g -Wall

SOURCES = genpattern.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = genpattern

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $< 

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rvf $(TARGET) $(OBJECTS)
