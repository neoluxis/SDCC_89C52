#ifndef __NEOLIB51_BTN_H
#define __NEOLIB51_BTN_H

#include "neolib51/neolib51.h"

#if BTN == ENABLE

#include "types.h"

/**
 * @brief 按键扫描模式
 * BTN_Scan_Block 阻塞
 * BTN_Scan_NonBlock 非阻塞
 * BTN_Scan_Continuous 连续
 * BTN_Scan_NonContinuous 非连续
 */
typedef enum
{
    BTN_Scan_Block = 0,     // Block until released
    BTN_Scan_NonBlock,      // Non-blocking
    BTN_Scan_Continuous,    // Continuous
    BTN_Scan_NonContinuous, // Non-continuous
} nbtn_scan_mode;

/**
 * @brief 按键状态
 * BTN_State_Pressed 按键按下
 * BTN_State_Released 按键释放
 * BTN_State_Err 按键错误
 */
typedef enum
{
    BTN_State_Pressed = 0,
    BTN_State_Released,
    BTN_State_Err,
} nbtn_state;

/**
 * @brief 按键编号
 * BTNx 为独立按键
 * MATBTN_xy 为矩阵按键
 */
typedef enum
{
    NONE_BTN = 0,
    BTN1,
    BTN2,
    BTN3,
    BTN4,
    MATBTN_11,
    MATBTN_12,
    MATBTN_13,
    MATBTN_14,
    MATBTN_21,
    MATBTN_22,
    MATBTN_23,
    MATBTN_24,
    MATBTN_31,
    MATBTN_32,
    MATBTN_33,
    MATBTN_34,
    MATBTN_41,
    MATBTN_42,
    MATBTN_43,
    MATBTN_44,
} nbtn_ord;

/**
 * @brief 扫描独立键盘
 * @return nbtn_ord 返回按键编号
 * @param block 按键扫描模式：BTN_Scan_Block 阻塞，BTN_Scan_NonBlock 非阻塞
 * @param cont 按键扫描模式：BTN_Scan_Continuous 连续，BTN_Scan_NonContinuous 非连续
 */
extern nbtn_ord nbtn_scan_dep(const nbtn_scan_mode cont);

/**
 * @brief 扫描矩阵键盘
 * @return nbtn_ord 返回按键编号
 * @param cont 按键扫描模式：BTN_Scan_Continuous 连续，BTN_Scan_NonContinuous 非连续
 */
extern nbtn_ord nbtn_scan_matrix(const nbtn_scan_mode cont);

#endif

#endif