#include <map>
#include <vector>

#include "Admin.h"
#include "Express.h"
#include "Person.h"
#include "User.h"
using std::map;
using std::vector;
/**
 * @brief 控制类
 * 控制程序的启动、关闭、更新等
 */
class Controller {
   private:
    /**
     * @brief 用户列表
     *
     */
    vector<Person*> personList;
    /**
     * @brief 用户映射
     *
     */
    map<string, Person*> personMap;
    /**
     * @brief 快递列表
     *
     */
    vector<Express*> expressList;
    /**
     * @brief 快递映射
     *
     */
    map<string, Express*> expressMap;

    /**
     * @brief 当前用户
     *
     */
    Person* currentPerson = nullptr;

    /**
     * @brief 当前普通用户
     *
     */
    User* currentUser = nullptr;
    /**
     * @brief 当前管理员
     *
     */
    Admin* currentAdmin = nullptr;

    /**
     * @brief 增加用户
     *
     */
    void addPerson(Person*);
    /**
     * @brief 增加快递
     *
     */
    void addExpress(Express*);

    /**
     * @brief 输入合法用户名
     *
     * @param information 提示信息
     * @param failCnt 最大错误次数
     * @return string 用户名（失败返回空）
     */
    string inputUsername(string information = "", int failCnt = 3);

    /**
     * @brief 输入合法快递单号
     *
     * @param information 提示信息
     * @param failCnt 最大错误次数
     * @return string 快递单号（失败返回空）
     */
    string inputExpressId(string information = "", int failCnt = 3);

   public:
    /**
     * @brief Construct a new Controller object
     *
     */
    Controller();
    /**
     * @brief Destroy the Controller object
     *
     */
    ~Controller();
    /**
     * @brief 控制类的主函数
     * （其实是个死循环，监听各类操作
     */
    void run();

    vector<Express*> getExpressList(
        const string receiver = "", const string sender = "",
        const string expressId = "",
        const set<ExpressState> states = ALL_EXPRESS_STATES,
        const time_t startTime = 0, const time_t endTime = 0);

    //////////////////////////////////////////////////////////////////////////////
    // User 区
    //////////////////////////////////////////////////////////////////////////////
    /**
     * @brief 用户注册
     *
     */
    void registerUser();
    /**
     * @brief 用户登录
     *
     */
    void loginUser();
    /**
     * @brief 用户退出
     *
     */
    void logoutUser();
    /**
     * @brief 用户修改密码
     *
     */
    void changePassword();
    /**
     * @brief 用户查询余额
     *
     */
    void queryBalance();
    /**
     * @brief 用户充值
     *
     */
    void recharge();
    /**
     * @brief 用户发送快递
     *
     */
    void sendExpress();
    /**
     * @brief 用户接受快递
     *
     */
    void receiveExpress();
    /**
     * @brief 用户查询快递
     *
     */
    void queryExpress();

    //////////////////////////////////////////////////////////////////////////////
    // Admin 区
    //////////////////////////////////////////////////////////////////////////////

    /**
     * @brief 物流公司管理员查询用户信息
     *
     */
    void queryUserInfo();
    /**
     * @brief 物流公司管理员查询历史快递信息
     *
     */
    void queryExpressInfo();
};