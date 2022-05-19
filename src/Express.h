#include <ctime>
#include <string>

using std::string;
/**
 * @brief 快递状态枚举类型
 *
 */
enum class ExpressState {
    // WAITING,
    // SENDING,
    /**
     * @brief 待签收
     *
     */
    SENT,
    /**
     * @brief 已签收
     *
     */
    RECEIVED
};

/**
 * @brief 快递类
 *
 */
class Express {
   private:
    /**
     * @brief 快递状态
     *
     */
    ExpressState state;
    /**
     * @brief 寄送时间
     *
     */
    time_t sendTime;
    /**
     * @brief 接收时间
     *
     */
    time_t receiveTime;
    /**
     * @brief 寄件用户
     *
     */
    string sender;
    /**
     * @brief 收件用户
     *
     */
    string receiver;
    /**
     * @brief 物品描述
     *
     */
    string description;

   public:
    ////////////////////////////////////////////////////////////////////////////////
    // Constructor
    ////////////////////////////////////////////////////////////////////////////////

    Express() = default;

    ////////////////////////////////////////////////////////////////////////////////
    // Getter and Setter
    ////////////////////////////////////////////////////////////////////////////////

    void setState(ExpressState state);
    ExpressState getState();
    void setSendTime(time_t sendTime);
    time_t getSendTime();
    void setReceiveTime(time_t receiveTime);
    time_t getReceiveTime();
    void setSender(string sender);
    string getSender();
    void setReceiver(string receiver);
    string getReceiver();
    void setDescription(string description);
    string getDescription();
    void setExpressState(ExpressState state);
    ExpressState getExpressState();
};