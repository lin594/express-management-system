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

User::User() { this->type = PersonType::USER; }

User::User(ifstream& in) : Person(in) {
    in >> this->telephone;
    in >> this->address;
}

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
