#include "User.h"
#include <iostream>

User::User() : id(0) {}

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {}

int User::getId() const { return id; }
std::string User::getName() const { return name; }
std::string User::getEmail() const { return email; }

void User::display() const {
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.getId() << " " << user.getName() << " " << user.getEmail();
    return os;
}