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

void Controller::addExpress(Express* express) {
    expressList.push_back(express);
    expressMap[express->getExpressId()] = express;
    dynamic_cast<User*>(personMap[express->getSender()])
        ->addSendExpress(express);
    dynamic_cast<User*>(personMap[express->getReceiver()])
        ->addReceiveExpress(express);
}

string Controller::inputUsername(string infomation) {
    cout << infomation;
    string username = "";
    cin >> username;
    int cnt = 0;
    while (personMap.find(username) == personMap.end()) {
        cout << "用户名不存在，请重新输入用户名:";
        cin >> username;
        if (++cnt > 3) {
            cout << "输入错误次数过多，已退出" << endl;
        }
    }
    return username;
}

void Controller::run() {
    cout << "系统内现在共有" << personList.size() << "个用户" << endl;
    cout << "系统内现在共有" << expressList.size() << "个快递" << endl;
}

Controller::Controller() {
    for (auto& p : std::filesystem::directory_iterator(USER_DIR)) {
        Person* person = Person::load(p.path().string());
        if (person != nullptr) this->addPerson(person);
    }

    for (auto& p : std::filesystem::directory_iterator(EXPRESS_DIR)) {
        Express* express = Express::load(p.path().string());
        if (express != nullptr) this->addExpress(express);
    }
}

Controller::~Controller() {
    for (auto person : personList) {
        delete person;
    }
    for (auto express : expressList) {
        delete express;
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
    cout << "下面开始登录用户。" << endl;
    string username = this->inputUsername("请输入用户名:");
    if (!username.length()) return;
    cout << "请输入密码:";
    string password;
    cin >> password;
    if (personMap[username]->checkPassword(password)) {
        currentPerson = personMap[username];
        cout << "登录成功! 欢迎你，亲爱的" << currentPerson->getNickname()
             << endl;
        switch (currentPerson->getType()) {
            case PersonType::USER:
                currentUser = dynamic_cast<User*>(currentPerson);
                break;
            case PersonType::ADMIN:
                currentAdmin = dynamic_cast<Admin*>(currentPerson);
                break;
        }
    } else {
        cout << "密码错误，已退出" << endl;
    }
};

void Controller::logoutUser() {
    if (currentPerson == nullptr) {
        cout << "当前没有用户登录，无法退出" << endl;
        return;
    }
    cout << "欢迎下次光临，亲爱的" << currentPerson->getNickname() << endl;
    currentPerson = nullptr;
    currentUser = nullptr;
    currentAdmin = nullptr;
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

void Controller::sendExpress() {
    if (currentPerson == nullptr) {
        cout << "请先登录" << endl;
        return;
    }
    if (currentPerson->getType() != PersonType::USER) {
        cout << "你不是用户，不能发送快递" << endl;
        return;
    }
    string receiver = this->inputUsername("请输入收件人用户名:");
    if (!receiver.size()) return;
    if (personMap[receiver]->getType() != PersonType::USER) {
        cout << "收件人不是普通用户，不能接收快递" << endl;
        return;
    }
    this->addExpress(new Express(currentPerson->getUsername(), receiver));
};

void Controller::receiveExpress() {
    if (currentPerson == nullptr) {
        cout << "请先登录" << endl;
        return;
    }
    if (currentPerson->getType() != PersonType::USER) {
        cout << "你不是用户，不能接收快递" << endl;
        return;
    }
    auto list = currentUser->getExpressList(true, false);
    if (!list.size()) {
        cout << "没有找到可接收的快递" << endl;
        return;
    }
    for (auto express : list) {
        cout << express->toString() << endl;
    }
    cout << "你想接收的快递是：";
    string expressId;
    cin >> expressId;
    int cnt = 0;
    while (expressMap.find(expressId) == expressMap.end()) {
        cout << "输入错误，请重新输入" << endl;
        cin >> expressId;

        if (++cnt > 3) {
            cout << "输入错误次数过多" << endl;
            return;
        }
    }
    auto express = expressMap[expressId];
    if (express->getReceiver() != currentPerson->getUsername()) {
        cout << "你不是收件人，不能接收快递" << endl;
        return;
    }
    express->Receive();
    cout << "收件成功！" << endl;
};

void Controller::queryExpress(){};

void Controller::queryUserInfo(){};

void Controller::queryExpressInfo(){};
