#ifndef _GRAPHICS_VERTEX_BUFFER_STORE_HPP_
#define _GRAPHICS_VERTEX_BUFFER_STORE_HPP_

#include <map>
#include <GLFW/glfw3.h>

namespace Graphics {
    class VertexBufferStore {
        std::map< const char *, GLuint > vertex_buffers;
        std::map< int, const char * > layout_map;

        public:
            void Add(const char * name, int layout, std::size_t data_size, GLfloat * data, int size);
            GLuint Get(const char * name);
            void DisableAll();
            void Clear();
    };
}

#endif

