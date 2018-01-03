#include "constants.hpp"
#include "graphics/vertex_buffer_store.hpp"
#include <map>
#include <GLFW/glfw3.h>

namespace Graphics {
    std::map< const char *, GLuint > vertex_buffers;
    std::map< int, const char * > layout_map;

    void VertexBufferStore::Add(const char * name, int layout, std::size_t data_size, GLfloat * data, int size) {
        if (layout_map.find(layout) == layout_map.end()) {
            layout_map[layout] = name;
        }
        glGenBuffers(1, &(vertex_buffers[name]));
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[name]);
        glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(layout);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[name]);
        glVertexAttribPointer(layout, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }

    GLuint VertexBufferStore::Get(const char * name) {
        return vertex_buffers[name];
    }

    void VertexBufferStore::DisableAll() {
        for (auto const& layout : layout_map) {
            glDisableVertexAttribArray(layout.first);
        }
    }

    void VertexBufferStore::Clear() {
        for (auto const& buffer : vertex_buffers) {
            if (DEBUG) {
                printf("Delete vertex buffer: %s\n", buffer.first);
            }
            glDeleteBuffers(1, &(buffer.second));
        }
    }
}
