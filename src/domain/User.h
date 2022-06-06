//
// Created by kamui on 06.06.2022.
//

#ifndef ISSUES_MV_USER_H
#define ISSUES_MV_USER_H

#include <string>

using namespace std;

class User {
private:
    string name;
    string type;
public:
    User(const string &name, const string &type);
    User() = default;
    const string &getName() const;
    const string &getType() const;

    friend istream& operator>>(istream& is, User& user);
};


#endif //ISSUES_MV_USER_H
