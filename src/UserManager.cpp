#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void UserManager::sortUsersById() {
    std::sort(users.begin(), users.end(),
        [](const User& a, const User& b) {
            return a.getId() < b.getId();
        }
    );
}

void UserManager::addUser(int id, const std::string& name, const std::string& email) {
    for (const User& user : users) {
        if (user.getId() == id) {
            std::cout << "이미 존재하는 사용자 ID입니다." << std::endl;
            return;
        }
    }

    users.push_back(User(id, name, email));
    sortUsersById();

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

void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일을 열 수 없습니다." << std::endl;
        return;
    }

    users.clear();

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;

        int id;
        std::string name;
        std::string email;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, name, ',');

        std::getline(ss, email, ',');

        users.push_back(User(id, name, email));
    }

    sortUsersById();

    file.close();

    std::cout << filename << " 로드 완료: " << users.size() << "건" << std::endl;
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 파일 저장 실패" << std::endl;
        return;
    }

    file << "id,name,email" << std::endl;

    for (const User& user : users) {
        file << user.getId() << ","
             << user.getName() << ","
             << user.getEmail() << std::endl;
    }

    file.close();

    std::cout << filename << " 저장 완료: " << users.size() << "건" << std::endl;
}

int UserManager::size() const {
    return static_cast<int>(users.size());
}