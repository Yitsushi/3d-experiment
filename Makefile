CC= g++
CFLAGS= -g -c -Wall -std=c++0x -stdlib=libc++
LDFLAGS= -lglfw -framework OpenGL -framework Carbon
SOURCES= src/main.cpp \
		 src/graphics/shader.cpp \
		 src/graphics/shader_store.cpp \
		 src/graphics/vertex_buffer_store.cpp \
		 src/object/camera.cpp \
		 src/util/callback_wrapper.cpp \
		 src/util/timer.cpp \
		 src/util/object_loader.cpp \
		 src/util/system.cpp \
		 src/core/application.cpp
INCLUDES= -Isrc
OBJECTS= $(SOURCES:.cpp=.o)
TARGET= bin/app

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

mac:
	mkdir -p 3dExperiment.app/Contents/MacOS
	cp bin/app 3dExperiment.app/Contents/MacOS/3dExperiment
	cp -r objects 3dExperiment.app/Contents/objects
	cp -r shaders 3dExperiment.app/Contents/shaders

clean:
	rm -rf $(OBJECTS) $(TARGET).cpp 3dExperiment.app
