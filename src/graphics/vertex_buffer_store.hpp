#ifndef _GRAPHICS_VERTEX_BUFFER_STORE_HPP_
#define _GRAPHICS_VERTEX_BUFFER_STORE_HPP_

#include <map>
#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Graphics {
    class VertexBufferStore {
        std::map< const char *, GLuint > vertex_buffers;
        std::map< int, const char * > layout_map;

        public:
            void Add(const char * name, int layout, std::vector<glm::vec3> data);
            void DisableAll();
            void Clear();
    };
}

#endif

