#include "Express.h"

void Express::setState(ExpressState state) { this->state = state; }
ExpressState Express::getState() { return state; };

void Express::setSendTime(time_t sendTime) { this->sendTime = sendTime; }

time_t Express::getSendTime() { return sendTime; };

void Express::setReceiveTime(time_t receiveTime) {
    this->receiveTime = receiveTime;
}
time_t Express::getReceiveTime() { return receiveTime; };

void Express::setSender(string sender) { this->sender = sender; }
string Express::getSender() { return sender; };

void Express::setReceiver(string receiver) { this->receiver = receiver; }
string Express::getReceiver() { return receiver; };

void Express::setDescription(string description) {
    this->description = description;
}
string Express::getDescription() { return description; };

void Express::setExpressState(ExpressState state) { this->state = state; }
ExpressState Express::getExpressState() { return state; };