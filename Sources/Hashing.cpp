#include "../Headers/Hashing.h"
#include <functional>

std::string generateHash(const std::string& data) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(data));
}
