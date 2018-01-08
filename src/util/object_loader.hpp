#ifndef _UTIL_OBJECT_LOADER_HPP_
#define _UTIL_OBJECT_LOADER_HPP_

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace Util {
    class ObjectLoader {
        public:
            static GLuint loadDDS(std::string imagepath);
            static bool load(
                std::string path,
                std::vector<glm::vec3> & out_vertices,
                std::vector<glm::vec2> & out_uvs,
                std::vector<glm::vec3> & out_normals
            );
    };
}

#endif
