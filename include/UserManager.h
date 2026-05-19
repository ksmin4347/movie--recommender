#pragma once

#include "BaseManager.h"
#include "User.h"
#include <vector>
#include <string>

class UserManager : public BaseManager {
private:
    std::vector<User> users;

    void sortUsersById();

public:
    void addUser(int id, const std::string& name, const std::string& email);

    void printAllUsers() const;

    bool hasUser(int userId) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};