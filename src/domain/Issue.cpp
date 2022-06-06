//
// Created by kamui on 06.06.2022.
//

#include "Issue.h"

Issue::Issue(const string &description, const string &status, const string &reporter, const string &solver)
        : description(description), status(status), reporter(reporter), solver(solver) {}

Issue::Issue(const string &description, const string &reporter): description(description), status("open"), reporter(reporter), solver("") {}

const string &Issue::getDescription() const {
    return description;
}

const string &Issue::getStatus() const {
    return status;
}

const string &Issue::getReporter() const {
    return reporter;
}

const string &Issue::getSolver() const {
    return solver;
}

bool Issue::sameAs(const Issue &other) const {
    return description == other.description;
}

void Issue::solve(const string &solver) {
    status = "closed";
    this->solver = solver;
}

ostream &operator<<(ostream &os, const Issue &issue) {
    os << issue.description << "," << issue.status << "," << issue.reporter
       << "," << issue.solver;
    return os;
}

istream &operator>>(istream &is, Issue &issue) {
    getline(is, issue.description, ',');
    getline(is, issue.status, ',');
    getline(is, issue.reporter, ',');
    getline(is, issue.solver, '\n');

    return is;
}
