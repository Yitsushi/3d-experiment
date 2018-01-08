#include <unistd.h>
#include <limits.h>
#include <string>
#include <mach-o/dyld.h>

#include "system.hpp"

namespace Util {
    std::string System::AppRoot() {
        // throw std::runtime_error(Util::System::AppRoot());
        // Extend path to abolsute based on binary path
        char result[PATH_MAX];
        uint32_t len = sizeof(result);
        _NSGetExecutablePath(result, &len);
        char *canonicalPath = realpath(result, NULL);
        if (canonicalPath != NULL) {
            strncpy(result, canonicalPath, len);
            free(canonicalPath);
        }

        std::string path = std::string(result);
        path = path.substr(0, path.find_last_of("\\/")) + "/..";

        return path;
    }

    std::string System::PathFor(const char * category, const char * file) {
        std::string path = System::AppRoot() + "/" + category + "/" + file;
        return path;
    }
}
