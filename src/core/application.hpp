#ifndef _CORE_APPLICATION_HPP_
#define _CORE_APPLICATION_HPP_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "graphics/vertex_buffer_store.hpp"
#include "object/camera.hpp"

#define OBJECT_DIR "objects"

namespace Core {
    class Application {
        GLFWwindow* m_window;
        Graphics::VertexBufferStore* bufferStore;
        GLuint VertexArrayID;

        Object::Camera* camera;

        public:
            Application();
            ~Application();

        private:
            GLFWwindow* InitWindow(int width, int height, const char* title);
            void setup();
            void HandleInput();
    };
}

#endif
