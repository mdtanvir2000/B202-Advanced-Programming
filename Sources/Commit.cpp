#include "../Headers/Commit.h"
#include "../Headers/Hashing.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <dirent.h> // for directory operations
#include <ctime>

std::vector<std::string> listDirectory(const std::string& path) {
    std::vector<std::string> fileList;
    DIR* dirp = opendir(path.c_str());
    struct dirent* dp;
    while ((dp = readdir(dirp)) != nullptr) {
        if (dp->d_type == DT_REG) { // DT_REG means regular file
            fileList.push_back(dp->d_name);
        }
    }
    closedir(dirp);
    return fileList;
}

void commitChanges(const std::string& repoName, const std::string& message) {
    std::ifstream trackFile(repoName + "/.tracking");
    std::string filename;
    std::string commitHash = generateHash(std::to_string(std::time(nullptr)) + message);

    std::ofstream commitFile(repoName + "/" + commitHash + ".commit");
    commitFile << "Commit message: " << message << std::endl;
    commitFile << "Files:" << std::endl;

    while (std::getline(trackFile, filename)) {
        std::ifstream file(repoName + "/" + filename);
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        commitFile << filename << " " << generateHash(content) << std::endl;
    }

    std::cout << "Committed changes with hash: " << commitHash << std::endl;
}

void viewLog(const std::string& repoName) {
    std::vector<std::string> files = listDirectory(repoName);
    for (const std::string& file : files) {
        if (file.find(".commit") != std::string::npos) {
            std::ifstream commitFile(repoName + "/" + file);
            std::string line;
            while (std::getline(commitFile, line)) {
                std::cout << line << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

void revertFile(const std::string& repoName, const std::string& commitHash, const std::string& filename) {
    std::ifstream commitFile(repoName + "/" + commitHash + ".commit");
    std::string line;
    bool found = false;

    while (std::getline(commitFile, line)) {
        if (line.find(filename) != std::string::npos) {
            found = true;
            std::string fileHash = line.substr(line.find_last_of(' ') + 1);
            std::cout << "Reverting " << filename << " to hash " << fileHash << std::endl;
            break;
        }
    }

    if (!found) {
        std::cout << "File not found in commit " << commitHash << std::endl;
    }
}
