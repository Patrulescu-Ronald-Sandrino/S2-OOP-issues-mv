//
// Created by kamui on 06.06.2022.
//

#include "User.h"

User::User(const string &name, const string &type) : name(name), type(type) {}

const string &User::getName() const {
    return name;
}

const string &User::getType() const {
    return type;
}

istream& operator>>(istream& is, User& user) {
    getline(is, user.name, ',');
    getline(is, user.type, '\n');

    return is;
}