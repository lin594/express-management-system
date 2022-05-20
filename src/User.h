#pragma once
#include <vector>

#include "Express.h"
#include "Person.h"

using std::vector;
/**
 * @brief 用户类
 *
 */
class User : public Person {
   private:
    /**
     * @brief 电话号码
     *
     */
    string telephone;
    /**
     * @brief 收件地址
     *
     */
    string address;
    /**
     * @brief 保存文件至本地
     *
     */
    void save() override;
    /**
     * @brief 发送快递列表
     *
     */
    vector<Express*> sendExpressList;
    /**
     * @brief 收件快递列表
     *
     */
    vector<Express*> receiveExpressList;

   public:
    void addSendExpress(Express* express);
    void addReceiveExpress(Express* express);

    /////////////////////////////////////////////////////////////////////////////
    // Constructor
    /////////////////////////////////////////////////////////////////////////////

    User();
    User(ifstream& in);
    User(string username, string nickname, string password);

    ////////////////////////////////////////////////////////////////////////////////
    // Getter and Setter
    ////////////////////////////////////////////////////////////////////////////////

    void setTelephone(string telephone);
    string getTelephone();
    void setAddress(string address);
    string getAddress();

    vector<Express*> getExpressList(
        const bool receive = true, const bool send = true,
        const string expressId = "",
        const set<ExpressState> states = ALL_EXPRESS_STATES);
};