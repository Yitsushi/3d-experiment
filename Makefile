CC= g++
CFLAGS= -g -c -Wall -std=c++0x -stdlib=libc++
LDFLAGS= -lglfw -framework OpenGL
SOURCES= main.cpp
INCLUDES= -I.
OBJECTS= $(SOURCES:.cpp=.o)
TARGET= bin/app

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET).cpp
