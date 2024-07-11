#include "../Headers/Repository.h"
#include <iostream>
#include <sys/stat.h> // for mkdir

#ifdef _WIN32
#include <direct.h> // for _mkdir
#define mkdir _mkdir
#else
#include <unistd.h>
#endif

bool directoryExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        return false;
    }
    return (info.st_mode & S_IFDIR) != 0;
}

void initRepo(const std::string& repoName) {
    if (!directoryExists(repoName)) {
        mkdir(repoName.c_str());
        std::cout << "Repository initialized: " << repoName << std::endl;
    } else {
        std::cout << "Repository already exists: " << repoName << std::endl;
    }
}
