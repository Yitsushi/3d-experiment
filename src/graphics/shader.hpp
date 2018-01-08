#ifndef _GRAPHICS_SHADERS_HPP_
#define _GRAPHICS_SHADERS_HPP_

#include <GLFW/glfw3.h>

#define SHADER_DIR "shaders"

namespace Graphics {
    class Shader {
        public:
            static GLuint LoadShaders(
                const char * vertex_file_path,
                const char * fragment_file_path
            );
    };
}

#endif
