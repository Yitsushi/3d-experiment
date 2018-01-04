#include "util/callback_wrapper.hpp"
#include <GLFW/glfw3.h>

namespace Util {
    Object::Camera* CallbackWrapper::s_camera;

    void CallbackWrapper::SetCamera(Object::Camera* camera) {
        CallbackWrapper::s_camera = camera;
    }

    void CallbackWrapper::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        s_camera->ScrollCallback(window, xoffset, yoffset);
    }

    void CallbackWrapper::MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
        int sw, sh;
        glfwGetWindowSize(window, &sw, &sh);
        glfwSetCursorPos(window, sw/2, sh/2);

        s_camera->MousePositionCallback(window, xpos, ypos);
    }
}
