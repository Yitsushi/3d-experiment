#ifndef _OBJECT_CAMERA_HPP_
#define _OBJECT_CAMERA_HPP_

#include <glm/glm.hpp>

#define DEFAULT_FOV 45.0f

namespace Object {
    class Camera {
        glm::vec3 position;
        glm::vec2 angle;
        float fov;
        float speed;

        public:
            Camera();
            glm::mat4 MVP();
            glm::vec3 Position();
            glm::vec2 Angle();
            glm::mat4 Perspective();
            glm::mat4 View();
            glm::mat4 Model();
            glm::vec3 Direction();
            glm::vec3 RelativeRight();
            void AddRelativeOrientation(float, float);
            void Move(glm::vec3, bool);

    };
}

#endif
