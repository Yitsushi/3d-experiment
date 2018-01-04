#include "util/timer.hpp"
#include <GLFW/glfw3.h>

namespace Util {
    float Timer::DeltaTime() {
        static double lastTime = glfwGetTime();

        return float(glfwGetTime() - lastTime);
    }

}
