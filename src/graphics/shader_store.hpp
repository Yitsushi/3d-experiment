#ifndef _GRAPHICS_SHADER_STORE_HPP_
#define _GRAPHICS_SHADER_STORE_HPP_ 

#include <GLFW/glfw3.h>
#include <map>

namespace Graphics {
    class ShaderStore {
        static std::map< const char *, GLuint > loaded_shaders;

        public:
            static GLuint Get(const char * name);
            static void Register(
                const char * name,
                const char * vertex_file_path,
                const char * fragment_file_path
            );
            static void Clear();
    };
}

#endif
