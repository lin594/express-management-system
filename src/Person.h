#pragma once
#include <string>
using std::string;
/**
 * @brief 各种用户的基类
 *
 */
class Person {
   private:
    /**
     * @brief 账户余额
     *
     */
    int balance = 0;
    /**
     * @brief 用户名
     *
     */
    string username;
    /**
     * @brief 姓名
     *
     */
    string nickname;
    /**
     * @brief 密码
     *
     */
    string password;

   public:
    /////////////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////////////

    Person() = default;

    ////////////////////////////////////////////////////////////////////////////////
    // Getter and Setter
    ////////////////////////////////////////////////////////////////////////////////

    void setBalance(int balance);
    int getBalance();
    void setUsername(string username);
    string getUsername();
    void setNickname(string nickname);
    string getNickname();
    void setPassword(string password);
    string getPassword();
};
