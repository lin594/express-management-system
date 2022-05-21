#include <filesystem>
#include <iostream>
#include <string>

#include "Controller.h"
namespace fs = std::filesystem;
string USER_DIR;
string EXPRESS_DIR;
int main(int argc, char** argv) {
    // 确定数据库存储位置
    fs::current_path(fs::path(std::string(argv[0])).parent_path());
    USER_DIR = fs::current_path() / "data" / "user";
    USER_DIR += "/";
    EXPRESS_DIR = fs::current_path() / "data" / "express";
    EXPRESS_DIR += "/";

    // 正式运行
    Controller c;
    c.run();
    return 0;
}