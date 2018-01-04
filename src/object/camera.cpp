#include "object/camera.hpp"
#include "constants.hpp"

#include <GLFW/glfw3.h>

// OpenGL Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Object {
    Camera::Camera() {
        position = glm::vec3(0.0f, 0.0f, 5.0f);
        angle = glm::vec2(3.14f, 0.0f);
        fov = DEFAULT_FOV;
        speed = 0.03f;
    }

    glm::vec3 Camera::Position() {
        return position;
    }

    glm::vec2 Camera::Angle() {
        return angle;
    }

    glm::mat4 Camera::Perspective() {
        return glm::perspective(glm::radians(fov), 4.0f / 3.0f, 0.1f, 100.0f);
    }

    glm::mat4 Camera::View() {
        glm::vec3 up = glm::cross( RelativeRight(), Direction() );

        return glm::lookAt(
                position,
                position + Direction(),
                up
        );
    }

    glm::mat4 Camera::Model() {
        return glm::mat4(1.0f);
    }

    glm::mat4 Camera::MVP() {
        return Perspective() * View() * Model();
    }

    glm::vec3 Camera::RelativeRight() {
        return glm::vec3(
            sin(angle.x - PI/2.0f),
            0,
            cos(angle.x - PI/2.0f)
        );
    }

    glm::vec3 Camera::Direction() {
        return glm::vec3(
            cos(angle.y) * sin(angle.x),
            sin(angle.y),
            cos(angle.y) * cos(angle.x)
        );
    }

    void Camera::AddRelativeOrientation(float x, float y) {
        angle.x += x;
        angle.y += y;
    }

    void Camera::Move(glm::vec3 value, bool negate) {
        if (negate) {
            position -= value * speed;
        } else {
            position += value * speed;
        }
    }
}
