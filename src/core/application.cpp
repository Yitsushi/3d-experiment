#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

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

        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        Graphics::ShaderStore::Register("simple", "simple.vertexshader", "simple.fragmentshader");

        GLuint MatrixID = glGetUniformLocation(Graphics::ShaderStore::Get("simple"), "MVP");
        glm::mat4 MVP = GetMVP();

        GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
        };

        GLfloat g_color_buffer_data[] = {
            1.0f,  0.0f,  0.0f,
            0.0f,  1.0f,  0.0f,
            0.0f,  0.0f,  1.0f,
        };

        Graphics::VertexBufferStore *bufferStore = new Graphics::VertexBufferStore();

        int timer = 0;
        do {
            timer = (timer + 1) % 360;
            float deg = ((timer) * PI/180) * 6;

            g_vertex_buffer_data[2] = sin(deg);
            g_vertex_buffer_data[5] = -sin(deg);
            g_vertex_buffer_data[8] = cos(deg);

            g_color_buffer_data[0] = (abs(cos(deg)) + 4) * 0.2;
            g_color_buffer_data[4] = (abs(sin(deg)) + 4) * 0.2;
            g_color_buffer_data[8] = (abs(-sin(deg)) + 4) * 0.2;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(Graphics::ShaderStore::Get("simple"));
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

            bufferStore->Add("vertex", 0, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, 3);
            bufferStore->Add("color", 1, sizeof(g_color_buffer_data), g_color_buffer_data, 3);

            glDrawArrays(GL_TRIANGLES, 0, (sizeof(g_vertex_buffer_data) / sizeof(*g_vertex_buffer_data) / 3));

            bufferStore->DisableAll();

            glfwSwapBuffers(m_window);
            glfwPollEvents();
        } while( glfwGetKey(m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0 );

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
        glClearColor(0.0f, 0.4f, 0.5f, 0.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        return window;
    }

    glm::mat4 Application::GetMVP() {
        glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
        glm::mat4 View = glm::lookAt(
                glm::vec3(0,0,5), // position
                glm::vec3(0,0,0), // loot at
                glm::vec3(0,1,0)  // head is up
                );
        glm::mat4 Model = glm::mat4(1.0f);
        glm::mat4 MVP = Projection * View * Model;

        return MVP;
    }
}
