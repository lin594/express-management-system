#include "Controller.h"

#include <filesystem>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

void Controller::run() {
    cout << "系统内现在共有" << personList.size() << "个用户" << endl;
    cout << "系统内现在共有" << expressList.size() << "个快递" << endl;
}

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

string Controller::inputExpressId(string information, int failCnt) {
    cout << information;
    string expressId = "";
    cin >> expressId;
    int cnt = 0;
    while (expressMap.find(expressId) == expressMap.end()) {
        if (++cnt > failCnt) {
            cout << "输入错误次数过多，已退出" << endl;
            break;
        }
        cout << "快递不存在，请重新输入快递号:";
        cin >> expressId;
    }
    return expressId;
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
    auto list = currentUser->getReceiveExpressList();
    if (!list.size()) {
        cout << "没有找到可接收的快递" << endl;
        return;
    }
    for (auto express : list) {
        cout << express->toString() << endl;
    }
    string expressId = this->inputExpressId("你想接收的快递是：");
    if (expressId.empty()) return;
    auto express = expressMap[expressId];
    if (express->getReceiver() != currentPerson->getUsername()) {
        cout << "你不是收件人，不能接收快递" << endl;
        return;
    }
    express->Receive();
    cout << "收件成功！" << endl;
};

/**
 * @brief 输入一个bool值
 *
 * 默认为false
 *
 * @param information 提示信息
 * @return true 输入为true
 * @return false 输入为false或默认
 */
bool inputYesNo(string information) {
    string input;
    cout << information << "[y/N]";
    getline(cin, input);
    while (true) {
        if (input == "y" || input == "Y") {
            return true;
        } else if (input == "n" || input == "N") {
            return false;
        } else if (input.empty()) {
            return false;
        } else {
            cout << "输入错误，请重新输入" << endl;
            getline(cin, input);
        }
    }
}

/**
 * @brief 获取符合条件的快递列表
 *
 * @param receiver 接收人，如果为空则查找所有
 * @param sender 发送人，如果为空则查找所有
 * @param expressId 快递单号，如果为空则查找所有
 * @param states 快递状态，默认全部
 * @param startTime 起始发件时间，如果为0则查找所有
 * @param endTime 结束发件时间，如果为0则查找所有
 * @return vector<Express*> 符合条件的快递列表
 */
vector<Express*> Controller::getExpressList(const string receiver,
                                            const string sender,
                                            const string expressId,
                                            const set<ExpressState> states,
                                            const time_t startTime,
                                            const time_t endTime) {
    vector<Express*> result;
    for (auto express : this->expressList) {
        if (!receiver.empty() && express->getReceiver() != receiver) continue;
        if (!sender.empty() && express->getSender() != sender) continue;
        if (!expressId.empty() && express->getExpressId() != expressId)
            continue;
        if (states.count(express->getState()) == 0) continue;
        if (startTime && express->getSendTime() < startTime) continue;
        if (endTime && express->getSendTime() > endTime) continue;
        result.push_back(express);
    }
    return result;
}

/**
 * @brief 输入快递状态集合
 *
 * @param information 提示信息
 * @return set<ExpressState> 快递状态集合
 */
set<ExpressState> inputExpressStates(string information) {
    set<ExpressState> states;
    string input;
    cout << information << "[SENT,RECEIVED]";
    while (true) {
        getline(cin, input);
        if (!input.length()) return ALL_EXPRESS_STATES;
        std::stringstream ss(input);
        string state;
        while (getline(ss, state, ',')) {
            if (state == "SENT") {
                states.insert(ExpressState::SENT);
            } else if (state == "RECEIVED") {
                states.insert(ExpressState::RECEIVED);
            } else {
                cout << "输入错误，请重新输入" << endl;
                states.clear();
            }
        }
        break;
    }
    return states;
}

void Controller::queryExpress() {
    if (currentPerson == nullptr) {
        cout << "请先登录" << endl;
        return;
    }
    if (currentPerson->getType() != PersonType::USER) {
        cout << "你不是用户，不能通过用户接口查询快递" << endl;
        return;
    }
    cin.ignore();
    bool send = inputYesNo("是否查询发件记录？");
    bool receive = inputYesNo("是否查询收件记录？");
    set<ExpressState> states = inputExpressStates("是否查询特定状态的快递？");
    string expressId = "";
    if (inputYesNo("是否查询特定快递编号?"))
        expressId = this->inputExpressId("请输入快递编号:");
    vector<Express*> list;
    if (send) {
        auto&& sendList = this->getExpressList("", currentPerson->getUsername(),
                                               expressId, states, 0, 0);
        list.insert(list.end(), sendList.begin(), sendList.end());
    }
    if (receive) {
        auto&& receiveList = this->getExpressList(currentPerson->getUsername(),
                                                  "", expressId, states, 0, 0);
        list.insert(list.end(), receiveList.begin(), receiveList.end());
    }
    for (auto express : list) {
        cout << express->toString() << endl;
    }
    if (list.size() == 0) {
        cout << "没有找到符合条件的快递" << endl;
    } else {
        cout << "共找到" << list.size() << "条符合条件的快递" << endl;
    }
};

void Controller::queryUserInfo(){};

void Controller::queryExpressInfo(){};
