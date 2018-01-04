#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <vector>

#include <math.h>
#include <time.h>

#include "constants.hpp"

#include <GLFW/glfw3.h>

// OpenGL Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/application.hpp"
#include "graphics/shader_store.hpp"
#include "graphics/vertex_buffer_store.hpp"

namespace Core {
    Application::Application() {
        if ( !glfwInit() ) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        setup();

        m_window = InitWindow(1280, 720, APP_NAME);

        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to open GLFW window.");
        }

        glfwPollEvents();
        updateScreenSize();
        glfwSetCursorPos(m_window, screenSize.x/2, screenSize.y/2);

        bufferStore = new Graphics::VertexBufferStore();

        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        Graphics::ShaderStore::Register("simple", "simple.vertexshader", "simple.fragmentshader");

        GLuint MatrixID = glGetUniformLocation(Graphics::ShaderStore::Get("simple"), "MVP");

        camera = new Object::Camera();

        std::vector<glm::vec3> vertex_data{
            glm::vec3(-1.0f,  -1.0f,  0.0f),
            glm::vec3(1.0f,  -1.0f,  0.0f),
            glm::vec3(0.0f,  1.0f,  0.0f),

            glm::vec3(-2.0f,  -2.0f,  -1.0f),
            glm::vec3(0.0f,  -2.0f,  -1.0f),
            glm::vec3(-1.0f,  0.0f,  -1.0f),
        };

        std::vector<glm::vec3> color_data{
            glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3(0.0f,  0.0f,  1.0f),
        };

        int timer = 0;
        do {
            glfwPollEvents();
            HandleInput();

            glm::mat4 MVP = camera->MVP();
            timer = (timer + 1) % 360;
            float deg = ((timer) * PI/180) * 6;

            vertex_data[0].z = sin(deg);
            vertex_data[1].z = -sin(deg);
            vertex_data[2].z = cos(deg);

            color_data[0].r = (abs(cos(deg)) + 4) * 0.2;
            color_data[1].g = (abs(sin(deg)) + 4) * 0.2;
            color_data[2].b = (abs(-sin(deg)) + 4) * 0.2;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(Graphics::ShaderStore::Get("simple"));
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

            bufferStore->Add("vertex", 0, vertex_data);
            bufferStore->Add("color", 1, color_data);

            glDrawArrays(GL_TRIANGLES, 0, vertex_data.size());

            bufferStore->DisableAll();

            glfwSwapBuffers(m_window);
        } while( glfwGetKey(m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0 );
    }

    Application::~Application() {
        bufferStore->Clear();
        Graphics::ShaderStore::Clear();
        glDeleteVertexArrays(1, &VertexArrayID);

        glfwTerminate();
    }

    void Application::setup() {
#ifdef __APPLE__
        /* We need to explicitly ask for a 3.2 context on OS X */
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

        glfwWindowHint(GLFW_SAMPLES, 4);
    }


    GLFWwindow* Application::InitWindow(int width, int height, const char* title) {
        GLFWwindow* window;
        window = glfwCreateWindow( width, height, title, NULL, NULL );

        if (!window) {
            return window;
        }

        glfwMakeContextCurrent(window);

        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glClearColor(0.0f, 0.4f, 0.5f, 0.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return window;
    }

    void Application::HandleInput() {

        // Mouse
        double xpos, ypos;
        glfwGetCursorPos(m_window, &xpos, &ypos);
        glfwSetCursorPos(m_window, screenSize.x/2, screenSize.y/2);

        float factor = 0.0008f * deltaTime();
        camera->AddRelativeOrientation(
            factor * float(screenSize.x/2 - xpos),
            factor * float(screenSize.y/2 - ypos)
        );

        // Keyboard
        if (glfwGetKey(m_window, 'W') == GLFW_PRESS) {
            camera->Move(camera->Direction() * deltaTime(), false);
        }
        if (glfwGetKey(m_window, 'S') == GLFW_PRESS) {
            camera->Move(camera->Direction() * deltaTime(), true);
        }
        if (glfwGetKey(m_window, 'D') == GLFW_PRESS) {
            camera->Move(camera->RelativeRight() * deltaTime(), false);
        }
        if (glfwGetKey(m_window, 'A') == GLFW_PRESS) {
            camera->Move(camera->RelativeRight() * deltaTime(), true);
        }
    }

    void Application::updateScreenSize() {
        int w, h;
        glfwGetWindowSize(m_window, &w, &h);
        screenSize.x = w;
        screenSize.y = h;
    }

    float Application::deltaTime() {
        static double lastTime = glfwGetTime();

        return float(glfwGetTime() - lastTime);
    }
}
