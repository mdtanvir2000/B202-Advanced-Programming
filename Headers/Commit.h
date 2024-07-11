#ifndef COMMIT_H
#define COMMIT_H

#include <string>

void commitChanges(const std::string& repoName, const std::string& message);
void viewLog(const std::string& repoName);
void revertFile(const std::string& repoName, const std::string& commitHash, const std::string& filename);

#endif
