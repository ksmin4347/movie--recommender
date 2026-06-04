#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>

void UserManager::sortUsersById() {
    std::sort(users.begin(), users.end(),
        [](const User& a, const User& b) {
            return a.getId() < b.getId();
        }
    );
}

void UserManager::addUser(int id, const std::string& name,
                          const std::string& email) {
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
    std::ifstream file;

    if (!openInputFile(file, filename)) {
        return;
    }

    users.clear();
    skipHeader(file);

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> fields = splitCsvLine(line);

        if (fields.size() != 3) {
            std::cerr << "CSV 형식 오류: " << line << std::endl;
            continue;
        }

        try {
            int id = std::stoi(fields[0]);
            std::string name = fields[1];
            std::string email = fields[2];

            users.push_back(User(id, name, email));
        } catch (const std::exception& e) {
            std::cerr << "CSV 파싱 오류: " << line
                      << " (" << e.what() << ")"
                      << std::endl;
        }
    }

    sortUsersById();
    file.close();

    printLoadComplete(filename, size());
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file;

    if (!openOutputFile(file, filename)) {
        return;
    }

    file << "id,name,email" << std::endl;

    for (const User& user : users) {
        file << user.getId() << ","
             << user.getName() << ","
             << user.getEmail() << std::endl;
    }

    file.close();

    printSaveComplete(filename, size());
}

int UserManager::size() const {
    return static_cast<int>(users.size());
}