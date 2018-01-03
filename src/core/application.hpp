#ifndef _CORE_APPLICATION_HPP_
#define _CORE_APPLICATION_HPP_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "graphics/vertex_buffer_store.hpp"

namespace Core {
    class Application {
        GLFWwindow* m_window;
        Graphics::VertexBufferStore* bufferStore;
        GLuint VertexArrayID;

        public:
            Application();
            ~Application();
            glm::mat4 GetMVP();

        private:
            GLFWwindow* InitWindow(int width, int height, const char* title);
            void setup();
    };
}

#endif
