#include "Controller.h"

#include <filesystem>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void Controller::addPerson(Person* person) {
    personList.push_back(person);
    personMap[person->getUsername()] = person;
}

void Controller::run() {
    cout << "系统内现在共有" << personList.size() << "个用户" << endl;
}

Controller::Controller() {
    for (auto& p : std::filesystem::directory_iterator(USER_DIR)) {
        Person* person = Person::load(p.path().string());
        if (person != nullptr) this->addPerson(person);
    }
}

Controller::~Controller() {
    for (auto person : personList) {
        delete person;
    }
}

void Controller::registerUser() {
    cout << "下面开始注册用户。" << endl << "请输入用户名:";
    string username;
    cin >> username;
    int cnt = 0;
    while (personMap.find(username) != personMap.end()) {
        cout << "用户名已存在，请重新输入用户名:";
        cin >> username;
        if (++cnt > 10) {
            cout << "输入次数过多，请稍后再试。" << endl;
            return;
        }
    }
    cout << "请输入密码:";
    string password;
    cin >> password;
    cout << "请输入姓名:";
    string nickname;
    cin >> nickname;
    this->addPerson(new User(username, nickname, password));
};

void Controller::loginUser() {
    cout << "下面开始登录用户。" << endl << "请输入用户名:";
    string username;
    cin >> username;
    int cnt = 0;
    while (personMap.find(username) == personMap.end()) {
        cout << "用户名不存在，请重新输入用户名:";
        cin >> username;
        if (++cnt > 3) {
            cout << "输入错误次数过多，已退出" << endl;
        }
    }
    cout << "请输入密码:";
    string password;
    cin >> password;
    if (personMap[username]->checkPassword(password)) {
        currentPerson = personMap[username];
        cout << "登录成功! 欢迎你，亲爱的" << currentPerson->getNickname()
             << endl;
    } else {
        cout << "密码错误，已退出" << endl;
    }
};

void Controller::changePassword() {
    if (currentPerson == nullptr) {
        cout << "请先登录" << endl;
        return;
    }
    string oldPassword;
    cout << "请输入旧密码:";
    cin >> oldPassword;
    if (currentPerson->checkPassword(oldPassword)) {
        string newPassword;
        cout << "请输入新密码:";
        cin >> newPassword;
        string repeatedPassword;
        cout << "请再次输入新密码:";
        cin >> repeatedPassword;
        if (newPassword == repeatedPassword) {
            currentPerson->setPassword(newPassword);
            cout << "密码修改成功！" << endl;
        } else {
            cout << "两次输入的密码不一致，请重新再试！" << endl;
        }
    } else {
        cout << "密码错误，修改失败" << endl;
    }
};

void Controller::queryBalance() {
    if (currentPerson == nullptr) {
        cout << "请先登录" << endl;
        return;
    }
    cout << "你的余额为：" << currentPerson->getBalance() << endl;
};

void Controller::recharge() {
    if (currentPerson == nullptr) {
        cout << "请先登录" << endl;
        return;
    }
    this->queryBalance();
    cout << "请输入充值金额:";
    double money;
    cin >> money;
    if (money > 0) {
        currentPerson->setBalance(currentPerson->getBalance() + money);
        cout << "充值成功！" << endl;
    } else {
        cout << "充值金额必须大于0！" << endl;
    }
};

void Controller::sendExpress(){};

void Controller::receiveExpress(){};

void Controller::queryExpress(){};

void Controller::queryUserInfo(){};

void Controller::queryExpressInfo(){};
