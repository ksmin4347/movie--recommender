#pragma once
#include "User.h"
#include <vector>
#include <string>

class UserManager {
private:
    std::vector<User> users;

public:
    void addUser(int id, const std::string& name, const std::string& email);
    void printAllUsers() const;
    bool hasUser(int userId) const;
};