#ifndef _SHADERS_HPP_
#define _SHADERS_HPP_

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
