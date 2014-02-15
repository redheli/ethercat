#ifndef __OBJECT_DICTIONARY_H__
#define __OBJECT_DICTIONARY_H__

namespace fm_auto
{

enum HOMING_METHOD
{
    HM_Method_1 = -1, //Negative stop evaluating the zero impulse
    HM_current_position= 37,

    HM_fail = 100
};

enum OPERATIN_MODE
{
    OM_NOT_READY_TO_SWITCH_ON = 0x0000,
    OM_QUICK_STOP_ACTIVE = 0x0007,
    OM_FAULT_OR_FAULT_REACTION_ACTIVE = 0x000F,

    OM_READY_TO_SWITCH_ON  = 0x0021,
    OM_SWITCHED_ON  = 0x0023,
    OM_OPERATION_ENABLE = 0x0027,

    OM_SWITCH_ON_DISABLED = 0x0040

};

static unsigned int OFFSET_CONTROLWORD;/* Controlword */
static unsigned int OFFSET_MODE_OF_OPERATION;/* Mode_of_Operation */
static unsigned int OFFSET_HOMING_METHOD;/* Homing_Method */
static unsigned int OFFSET_TARGET_POSITION;/* Target_Position */
static unsigned int OFFSET_TARGET_VELOCITY;/* Target_Velocity */
static unsigned int OFFSET_TARGET_TORQUE;/* Target_Torque */

static unsigned int OFFSET_STATUSWORD;/* Statusword */
static unsigned int OFFSET_ACTURAL_VALUE;/* Position_Actual_Value */
static unsigned int OFFSET_MODES_OF_OPERATION_DISPLAY;/* Modes_Of_Operation_Display */
static unsigned int OFFSET_REGISTER;/* Error_Register */
static unsigned int OFFSET_VELOCITY_ACTUAL_VALUE;/* Velocity_Actual_Value */
static unsigned int OFFSET_TORQUE_ACTURAL_VALUE;/* Torque_Actual_Value */

// current only have one slave
#define SlaveZeroAliasAndPosition  0, 0
#define VendorID_ProductCode  0x000000e4, 0x00001133

const static ec_pdo_entry_reg_t domain_output_regs[] = {
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6040, 0, &OFFSET_CONTROLWORD},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x607a, 0, &OFFSET_TARGET_POSITION},
    {}
};
const static ec_pdo_entry_reg_t domain_input_regs[] = {
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6061, 0, &OFFSET_MODES_OF_OPERATION_DISPLAY},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6041, 0, &OFFSET_STATUSWORD},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x606c, 0, &OFFSET_VELOCITY_ACTUAL_VALUE},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x1001, 0, &OFFSET_REGISTER},
    {}
};


}//fm_auto

#endif
