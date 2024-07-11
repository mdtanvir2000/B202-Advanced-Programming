#include "../Headers/Tracking.h"
#include <fstream>
#include <iostream>

void trackFile(const std::string& repoName, const std::string& filename) {
    std::ofstream file(repoName + "/.tracking", std::ios::app);
    file << filename << std::endl;
    std::cout << "Tracking file: " << filename << std::endl;
}
