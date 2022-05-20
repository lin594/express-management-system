#pragma once
#include <set>

using std::set;
/**
 * @brief 快递状态枚举类型
 *
 */
enum class ExpressState {
    // WAITING,
    // SENDING,
    /**
     * @brief 已发送
     *
     */
    SENT,
    /**
     * @brief 已签收
     *
     */
    RECEIVED,
};

const set<ExpressState> ALL_EXPRESS_STATES{ExpressState::SENT,
                                           ExpressState::RECEIVED};
