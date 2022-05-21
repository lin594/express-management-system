#include "Express.h"

#include <iostream>

ExpressState Express::getState() { return state; };
time_t Express::getSendTime() { return sendTime; };
time_t Express::getReceiveTime() { return receiveTime; };
string Express::getSender() { return sender; };
string Express::getReceiver() { return receiver; };
string Express::getDescription() { return description; };
string Express::getExpressId() { return expressId; };
string Express::getFilePath() { return EXPRESS_DIR + expressId + ".txt"; };

/**
 * @brief Construct a new Express:: Express object
 *
 * @param sender 发送者
 * @param receiver 接收者
 * @param description 物品描述
 */
Express::Express(string sender, string receiver, string description) {
    this->sender = sender;
    this->receiver = receiver;
    this->description = description;
    this->state = ExpressState::SENT;
    this->sendTime = time(nullptr);
    this->receiveTime = 0;
    char buf[100];
    strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", localtime(&sendTime));
    srand(time(nullptr));
    string id = std::to_string(rand() % 10000);
    this->expressId = string(buf) + string(4 - id.length(), '0') + id;
    std::cout << "快递订单 " << expressId << " 已经生成" << std::endl;
    this->save();
}

/**
 * @brief 通过快递单号构造快递
 *
 */
Express::Express(ifstream& in) {
    int _state;
    in >> _state;
    this->state = (ExpressState)_state;
    in >> expressId >> sendTime >> receiveTime >> sender >> receiver;
    in.ignore();
    getline(in, description);
}

Express* Express::load(string file) {
    std::ifstream in(file);
    if (in.is_open()) {
        Express* express = new Express(in);
        in.close();
        return express;
    }
    return nullptr;
}

/**
 * @brief 接收快递
 *
 */
void Express::Receive() {
    this->state = ExpressState::RECEIVED;
    this->receiveTime = time(nullptr);
    this->save();
}

void Express::save() {
    std::ofstream out(this->getFilePath());
    if (out.is_open()) {
        out << int(state) << std::endl;
        out << expressId << std::endl;
        out << sendTime << std::endl;
        out << receiveTime << std::endl;
        out << sender << std::endl;
        out << receiver << std::endl;
        out << description << std::endl;
        out.close();
    } else {
        std::cout << "[Express::save()]Error: Could not open file " +
                         this->getFilePath()
                  << std::endl;
    }
}

string Express::toString() {
    string str = "快递单号: " + expressId + "\n";
    str += "快递状态: ";
    switch (state) {
        case ExpressState::SENT:
            str += "已发送";
            break;
        case ExpressState::RECEIVED:
            str += "已接收";
            break;
        default:
            str += "未知";
            break;
    }
    str += "\n";
    str += "寄送时间: " + string(ctime(&sendTime));
    str += "接收时间: " +
           (receiveTime ? string(ctime(&receiveTime)) : "（未接收）\n");
    str += "寄件人: " + sender + "\n";
    str += "收件人: " + receiver + "\n";
    str += "物品描述: " + description + "\n";
    return str;
}