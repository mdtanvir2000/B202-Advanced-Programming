#include "Headers/Repository.h"
#include "Headers/Tracking.h"
#include "Headers/Commit.h"
#include <iostream>

int main() {
    std::string repoName = "my_repo";
    initRepo(repoName);
    trackFile(repoName, "example.txt");
    commitChanges(repoName, "Initial commit");
    viewLog(repoName);
    revertFile(repoName, "commit_hash_here", "example.txt");
    return 0;
}
