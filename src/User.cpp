#include "User.h"

#include <fstream>
void User::setTelephone(string telephone) {
    this->telephone = telephone;
    this->save();
}
string User::getTelephone() { return telephone; }

void User::setAddress(string address) {
    this->address = address;
    this->save();
}
string User::getAddress() { return address; }
vector<Express*> User::getSendExpressList() { return sendExpressList; }
vector<Express*> User::getReceiveExpressList() { return receiveExpressList; }

/**
 * @brief 无参构造函数
 *
 */
User::User() { this->type = PersonType::USER; }

/**
 * @brief 通过文件流构造函数
 *
 * @param in 从文件中读取的流
 */
User::User(ifstream& in) : Person(in) {
    in >> this->telephone;
    getline(in, this->address);
}

/**
 * @brief 创建用户
 *
 * @param username 用户名
 * @param nickname 姓名
 * @param password 密码
 */
User::User(string username, string nickname, string password) : User{} {
    this->username = username;
    this->nickname = nickname;
    this->password = password;
    this->save();
}

void User::save() {
    Person::save();
    std::ofstream out(USER_DIR + username + ".txt", std::ios::app);
    if (out.is_open()) {
        out << telephone << std::endl;
        out << address << std::endl;
        out.close();
    }
}

/**
 * @brief 添加发件快递
 *
 * @param express 快递
 */
void User::addSendExpress(Express* express) {
    this->sendExpressList.push_back(express);
}

/**
 * @brief 添加收件快递
 *
 * @param express 快递
 */
void User::addReceiveExpress(Express* express) {
    this->receiveExpressList.push_back(express);
}

string User::toDetailString() {
    string str = "";
    str += "用户名：" + this->username + "\n";
    str += "用户类型：普通用户\n";
    str += "姓名：" + this->nickname + "\n";
    str += "余额：" + std::to_string(this->balance) + "\n";
    str += "电话：" + this->telephone + "\n";
    str += "地址：" + this->address + "\n";
    return str;
}