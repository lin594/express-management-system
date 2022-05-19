#include "Person.h"

#include <fstream>
#include <iostream>

#include "User.h"
void Person::setBalance(int balance) {
    this->balance = balance;
    this->save();
}
int Person::getBalance() { return balance; }

void Person::setUsername(string username) {
    this->username = username;
    this->save();
}
string Person::getUsername() { return username; }

void Person::setNickname(string nickname) {
    this->nickname = nickname;
    this->save();
}
string Person::getNickname() { return nickname; }

void Person::setPassword(string password) {
    this->password = password;
    this->save();
}
string Person::getPassword() { return password; }

void Person::save() {
    std::ofstream out(USER_DIR + username + ".txt");
    if (out.is_open()) {
        out << int(type) << std::endl;
        out << username << std::endl;
        out << nickname << std::endl;
        out << password << std::endl;
        out << balance << std::endl;
        out.close();
    } else {
        std::cout << "[Person::save()]Error: Could not open file " + USER_DIR +
                         username + ".txt"
                  << std::endl;
    }
}

Person::Person(ifstream& in) {
    in >> username;
    in >> nickname;
    in >> password;
    in >> balance;
}

Person* Person::load(string file) {
    Person* person = nullptr;
    std::ifstream in(file);
    if (in.is_open()) {
        int _type;
        in >> _type;

        PersonType type{_type};

        switch (type) {
            case PersonType::USER:
                person = new User(in);
                break;
        }
        in.close();
    } else {
        std::cout << "[Person::load()]Error: Could not open file " + file
                  << std::endl;
    }
    return person;
}