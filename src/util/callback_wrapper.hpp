#ifndef _UTIL_CALLBACK_WRAPPER_HPP_
#define _UTIL_CALLBACK_WRAPPER_HPP_

#include "object/camera.hpp"

namespace Util {
    class CallbackWrapper {

        public:
            CallbackWrapper() = delete;
            ~CallbackWrapper() = delete;

            static void SetCamera(Object::Camera* camera);
            static void ScrollCallback(GLFWwindow*, double, double);
            static void MousePositionCallback(GLFWwindow*, double, double);

        private:
            static Object::Camera* s_camera;
    };
}

#endif

