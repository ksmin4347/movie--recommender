#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class BaseManager {
public:
    virtual void loadFromFile(const std::string& filename) = 0;
    virtual void saveToFile(const std::string& filename) const = 0;
    virtual int size() const = 0;

    virtual ~BaseManager() = default;

protected:
    static bool openInputFile(std::ifstream& file,
                              const std::string& filename) {
        file.open(filename);

        if (!file.is_open()) {
            std::cerr << "Error: " << filename
                      << " 파일을 열 수 없습니다."
                      << std::endl;
            return false;
        }

        return true;
    }

    static bool openOutputFile(std::ofstream& file,
                               const std::string& filename) {
        file.open(filename);

        if (!file.is_open()) {
            std::cerr << "Error: " << filename
                      << " 파일 저장 실패"
                      << std::endl;
            return false;
        }

        return true;
    }

    static void skipHeader(std::ifstream& file) {
        std::string header;
        std::getline(file, header);
    }

    static std::vector<std::string> splitCsvLine(const std::string& line) {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            fields.push_back(token);
        }

        return fields;
    }

    static void printLoadComplete(const std::string& filename, int count) {
        std::cout << filename << " 로드 완료: "
                  << count << "건" << std::endl;
    }

    static void printSaveComplete(const std::string& filename, int count) {
        std::cout << filename << " 저장 완료: "
                  << count << "건" << std::endl;
    }
};