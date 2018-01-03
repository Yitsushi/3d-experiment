CC= g++
CFLAGS= -g -c -Wall -std=c++0x -stdlib=libc++
LDFLAGS= -lglfw -framework OpenGL
SOURCES= src/main.cpp \
		 src/graphics/shader.cpp \
		 src/graphics/shader_store.cpp \
		 src/graphics/vertex_buffer_store.cpp \
		 src/core/application.cpp
INCLUDES= -Isrc
OBJECTS= $(SOURCES:.cpp=.o)
TARGET= bin/app

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET).cpp
