//
// Created by kamui on 06.06.2022.
//

#include <fstream>
#include "IssueRepository.h"

IssueRepository::IssueRepository(const string &filename) : filename(filename) {
    readFromFile();
}

IssueRepository::~IssueRepository() {
    writeToFile();
}

int IssueRepository::size() const {
    return issues.size();
}

vector<Issue> IssueRepository::getAll() const {
    return issues;
}

void IssueRepository::addIssue(const Issue& issue) noexcept(false) {
    for (const auto& i: issues) {
//        if (i.getDescription() == issue.getDescription())
        if (i.sameAs(issue))
            throw runtime_error("Issue already exists");
    }
    issues.push_back(issue);
}

void IssueRepository::updateIssue(const Issue& issue) {
    for (auto & i : issues) {
//        if (i.getDescription() == issue.getDescription()) {
        if (i.sameAs(issue)) {
            i = issue;
            return;
        }
    }
}

void IssueRepository::removeIssue(const string& description) {
    vector<Issue> newIssues;
    for (auto & i : issues) {
        if (i.getDescription() != description) {
            newIssues.push_back(i);
        }
    }
    issues = newIssues;
}

void IssueRepository::readFromFile() {
    ifstream file(filename);
    if (!file.is_open()) {
        fprintf(stderr, "failed to read from %s\n", filename.c_str());
        return;
    }
    Issue i;
    while (file >> i) {
        issues.push_back(i);
    }
}

void IssueRepository::writeToFile() const {
    ofstream file(filename);
    if (!file.is_open()) {
        fprintf(stderr, "failed to write to %s\n", filename.c_str());
        return;
    }
    for (const auto& i: issues) {
        file << i << "\n";
    }
}
