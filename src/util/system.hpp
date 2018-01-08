#ifndef _UTIL_SYSTEM_HPP_
#define _UTIL_SYSTEM_HPP_

namespace Util {
    class System {
        public:
            static std::string AppRoot();
            static std::string PathFor(
                const char * category,
                const char * file
            );
    };
}

#endif
