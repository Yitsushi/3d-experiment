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
#include "util/callback_wrapper.hpp"
#include "util/timer.hpp"
#include "util/object_loader.hpp"

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

        {
            int sw, sh;
            glfwGetWindowSize(m_window, &sw, &sh);
            glfwSetCursorPos(m_window, sw/2, sh/2);
        }

        bufferStore = new Graphics::VertexBufferStore();

        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        Graphics::ShaderStore::Register("simple", "simple.vertexshader", "simple.fragmentshader");

        GLuint MatrixID = glGetUniformLocation(Graphics::ShaderStore::Get("simple"), "MVP");

        camera = new Object::Camera();
        Util::CallbackWrapper::SetCamera(camera);

        glfwSetScrollCallback(
                m_window,
                Util::CallbackWrapper::ScrollCallback
        );

        glfwSetCursorPosCallback(
                m_window,
                Util::CallbackWrapper::MousePositionCallback
        );

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals; // Won't be used at the moment.
        Util::ObjectLoader::load(
            "objects/cube.obj",
            vertices, uvs, normals
        );

        GLuint Texture = Util::ObjectLoader::loadDDS("objects/cube.DDS");
        GLuint TextureID = glGetUniformLocation(Graphics::ShaderStore::Get("simple"), "simpleTexture");

        int timer = 0;
        do {
            glfwPollEvents();
            HandleInput();

            glm::mat4 MVP = camera->MVP();
            timer = (timer + 1) % 360;
            //float deg = ((timer) * PI/180) * 6;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(Graphics::ShaderStore::Get("simple"));
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, Texture);
            glUniform1i(TextureID, 0);

            bufferStore->Add("vertex", 0, vertices);
            bufferStore->Add("uv", 1, uvs);

            //bufferStore->Add("color", 1, color_data);

            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

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
        // Keyboard
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
            camera->Move(camera->Direction() * Util::Timer::DeltaTime(), false);
        }
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
            camera->Move(camera->Direction() * Util::Timer::DeltaTime(), true);
        }
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
            camera->Move(camera->RelativeRight() * Util::Timer::DeltaTime(), false);
        }
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
            camera->Move(camera->RelativeRight() * Util::Timer::DeltaTime(), true);
        }
    }
}
