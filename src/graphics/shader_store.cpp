#include <GLFW/glfw3.h>

#include "constants.hpp"
#include "graphics/shader.hpp"
#include "graphics/shader_store.hpp"

namespace Graphics {
    std::map< const char *, GLuint > ShaderStore::loaded_shaders;

    GLuint ShaderStore::Get(const char * name) {
        return loaded_shaders[name];
    }

    void ShaderStore::Register(
        const char * name,
        const char * vertex_file_path,
        const char * fragment_file_path
    ) {
        loaded_shaders[name] = Shader::LoadShaders(
            vertex_file_path,
            fragment_file_path
        );
    }

    void ShaderStore::Clear() {
        for (auto const& shader : loaded_shaders) {
            if (DEBUG) {
                printf("Unload shader: %s\n", shader.first);
            }
            glDeleteProgram(shader.second);
        }
    }
}
