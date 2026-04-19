#include "UserManager.h"
#include <iostream>

void UserManager::addUser(int id, const std::string& name, const std::string& email) {
    for (const User& user : users) {
        if (user.getId() == id) {
            std::cout << "이미 존재하는 사용자 ID입니다." << std::endl;
            return;
        }
    }

    users.push_back(User(id, name, email));
    std::cout << "사용자가 추가되었습니다." << std::endl;
}

void UserManager::printAllUsers() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return;
    }

    for (const User& user : users) {
        std::cout << user << std::endl;
    }
}

bool UserManager::hasUser(int userId) const {
    for (const User& user : users) {
        if (user.getId() == userId) {
            return true;
        }
    }
    return false;
}