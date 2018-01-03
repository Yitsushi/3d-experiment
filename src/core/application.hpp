#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Core {
    class Application {
        GLFWwindow* m_window;

        public:
            Application();
            glm::mat4 GetMVP();

        private:
            GLFWwindow* InitWindow(int width, int height, const char* title);
            void setup();
    };
}

#endif
