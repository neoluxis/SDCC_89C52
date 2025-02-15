#include "neolib51/btn.h"
#include "neolib51/time.h"

#include "REGX52.H"

// Button port
#define BTN_Port P3

nbtn_ord nbtn_scan_dep(const nbtn_scan_mode cont)
{
    static nbtn_state btn_state = BTN_State_Released;
    nbtn_ord btn = NONE_BTN;
    uint8_t kvalue = 0xff;

    // 连续扫描
    if (cont == BTN_Scan_Continuous)
    {
        btn_state = BTN_State_Released;
    }

    if (btn_state == BTN_State_Pressed)
    {
        BTN_Port = 0xff;
        kvalue = BTN_Port;
        if (kvalue == 0xff)
        {
            btn_state = BTN_State_Released;
        }
        else
        {
            return NONE_BTN;
        }
    }

    BTN_Port = 0xff;
    kvalue = BTN_Port;
    if (kvalue == 0xff)
    {
        return NONE_BTN;
    }
    ntime_delay_ms(10);
    kvalue = BTN_Port;
    switch (kvalue)
    {
    case 0xfe:
        return BTN1;
        break;
    case 0xfd:
        return BTN2;
        break;
    case 0xfb:
        return BTN3;
        break;
    case 0xf7:
        return BTN4;
        break;
    default:
        break;
    }
    return NONE_BTN;
}

/**
 * @brief 扫描矩阵键盘列
 * @return nbtn_ord 返回对应列第一行的按键编号
 */
static nbtn_ord __nbtn_mat_col_scan(void)
{
    uint8_t kvalue = 0;
    BTN_Port = 0x0f;
    kvalue = BTN_Port & 0x0f;
    if (kvalue == 0x0f)
    {
        return NONE_BTN;
    }
    BTN_Port = 0x0f;
    ntime_delay_ms(2);
    kvalue = BTN_Port & 0x0f;
    switch (kvalue)
    {
    case 0x0e:
        return MATBTN_11;
        break;
    case 0x0d:
        return MATBTN_21;
        break;
    case 0x0b:
        return MATBTN_31;
        break;
    case 0x07:
        return MATBTN_41;
        break;
    default:
        break;
    }
    return NONE_BTN;
}

/**
 * @brief 扫描矩阵键盘行, 在列扫描后的数据上加上行的偏移
 * @return nbtn_ord 返回的按键编号
 */
static nbtn_ord __nbtn_mat_row_scan(nbtn_ord col)
{
    uint8_t kvalue = 0;

    if (col == NONE_BTN)
    {
        return NONE_BTN;
    }

    BTN_Port = 0xf0;
    kvalue = BTN_Port & 0xf0;
    if (kvalue == 0xf0)
    {
        return NONE_BTN;
    }
    BTN_Port = 0xf0;
    ntime_delay_ms(1);
    kvalue = BTN_Port & 0xf0;
    switch (kvalue)
    {
    case 0xe0:
        return col + 0;
        break;
    case 0xd0:
        return col + 1;
        break;
    case 0xb0:
        return col + 2;
        break;
    case 0x70:
        return col + 3;
        break;
    default:
        break;
    }
    return NONE_BTN;
}

static nbtn_ord __nbtn_mat_full_scan(void)
{
    nbtn_ord col = __nbtn_mat_col_scan();
    return __nbtn_mat_row_scan(col);
}

nbtn_ord nbtn_scan_matrix(const nbtn_scan_mode cont)
{
    static nbtn_state btn_state = BTN_State_Released;
    nbtn_ord btn = NONE_BTN;
    uint8_t kvalue = 0xff;

    // 连续扫描
    if (cont == BTN_Scan_Continuous)
    {
        btn_state = BTN_State_Released;
    }

    if (btn_state == BTN_State_Pressed)
    {
        btn = __nbtn_mat_full_scan();
        if (btn == NONE_BTN)
        {
            btn_state = BTN_State_Released;
        }
        else
        {
            return NONE_BTN;
        }
    }

    btn = __nbtn_mat_full_scan();
    return btn;
}
