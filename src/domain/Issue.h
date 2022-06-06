//
// Created by kamui on 06.06.2022.
//

#ifndef ISSUES_MV_ISSUE_H
#define ISSUES_MV_ISSUE_H
#include <string>
#include <ostream>

using namespace std;

class Issue {
private:
    string description;
    string status;
    string reporter;
    string solver;
public:
    Issue(const string &description, const string &status, const string &reporter, const string &solver);
    Issue(const string &description, const string &reporter);
    Issue() = default;

    const string &getDescription() const;

    const string &getStatus() const;

    const string &getReporter() const;

    const string &getSolver() const;

    bool sameAs(const Issue& other) const;

    bool isOpen() const { return status == "open"; }
    bool isClosed() const { return status == "closed"; }

    void solve(const string &solver);

    friend ostream &operator<<(ostream &os, const Issue &issue);

    friend istream &operator>>(istream &is, Issue &issue);
};


#endif //ISSUES_MV_ISSUE_H
