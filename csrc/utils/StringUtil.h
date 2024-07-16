#pragma once

#include <cstddef>
#include <ostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

namespace hamster {
namespace utils {

inline std::ostream& _str(std::ostream& ss) {
    return ss;
}

template <typename T>
inline std::ostream& _str(std::ostream& ss, const T& t) {
    ss << t;
    return ss;
}

template <typename T, typename... Args>
inline std::ostream& _str(std::ostream& ss, const T& t, const Args &... args) {
   return _str(_str(ss, t), args...); 
}

template <typename... Args>
inline std::string str(const Args&... args) {
    std::ostringstream ss;
    _str(ss, args...);
    return ss.str();
}

template<>
inline std::string str(const std::string& str) {
    return str;
}
inline std::string str(const char* c_str) {
    return c_str;
}

template <class Container>
inline std::string join(const std::string& delimiter, const Container& container) {
    std::stringstream ss;
    int cnt = static_cast<int64_t>(container.size()) - 1;
    for (auto i = container.begin(); i != container.end(); ++i, --cnt) {
        ss << (*i) << (cnt ? delimiter : "");
    }
    return ss.str();
}

// Replace all occurrences of "from" substring to "to" string.
// Returns number of replacements
size_t ReplaceAll(std::string& s, const char* from, const char* to);

/// Represents a location in source code (for debugging).
struct SourceLocation {
  const char* function;
  const char* file;
  uint32_t line;
};

std::ostream& operator<<(std::ostream& out, const SourceLocation& loc);



} // namespace utils
} // namespace hamster