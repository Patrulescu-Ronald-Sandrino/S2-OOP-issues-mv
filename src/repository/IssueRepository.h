//
// Created by kamui on 06.06.2022.
//

#ifndef ISSUES_MV_ISSUEREPOSITORY_H
#define ISSUES_MV_ISSUEREPOSITORY_H

#include <string>
#include <vector>
#include "../domain/Issue.h"

using namespace std;

class IssueRepository {
private:
    string filename;
    vector<Issue> issues;
public:
    IssueRepository(const string &filename);
    ~IssueRepository();
    int size() const;
    vector<Issue> getAll() const;
    void addIssue(const Issue& issue) noexcept(false);
    void updateIssue(const Issue& i);
    void removeIssue(const string& description);
private:
    void readFromFile();
    void writeToFile() const;
};


#endif //ISSUES_MV_ISSUEREPOSITORY_H
